/* ========================================
 *
 * Never-lose
 * 
 * 2023/05
 *
 * Kiên Tran-Ngoc
 * Thomas De Deyn
 * Ismaël
 * Lionel 
 * ========================================
*/
#include "project.h"
#include "keypad.h"
#include <stdio.h>
#include "math.h"

#define Jump_sound 1200  //the sound emitted during a jump or a duck will be different in frequency 
#define Duck_sound 600
#define signal_size 100 //we used what we did in lab0 2
#define PI 3.14159
#define LCD_size 8
#define PRESS 4550         //position of servomotor when pressing button
#define UNPRESS 4000  //position of servomotor when not pressing any button
                        // values depends on your keyboard

// Variables
int score = 0 ; 
int state = 0 ; //indicates if the score is running or not
int sound = 0 ; //indicates if the sound is playing or not
enum Move {Jump, Duck} ; //a variable's value of type Move can be "Jump" or "Duck"
float signal[signal_size] ;
int signal_counter = 0 ;
int current_audio = 0 ; //this variable holds the current value of the audio frequency
int current_photo = 0 ; //this variables indicates the photoresistor currently linked to the ADC (0 = jump and 1 = duck)
char buffer[LCD_size];
int bufferIndex = 0;
int canSend = 1 ;//to avoid sending several time "jump"/"duck" for a single jump/duck
int mode_day = 1 ; // equal to 0 if it's night mode
int j_obstacle = 0 ; 
int d_obstacle = 0 ; //those 2 variables indicates if the associated (jump/duck) photoresistor detects an obstacle or not
//if both detect an obstacle, it is impossible (bc there is only one obstacle at a time) and thus it means that the 
//mode has changed
int move = 1 ; //this variable indicates if the last move was a jump or a duck




// General functions
void start_F() ; 
void update() ; 
void restart_score() ; 
void start_score(enum Move move) ; 
void LED_off() ;    

void jump() ; 
void duck() ;
void LED_LCD(enum Move move) ; //turn on and display on the LCD corresponding to the move (jump or duck)
void activation(enum Move move) ; //the parameter is either "Jump" or "Duck" and calls the associated events
void detect_obs() ;
int condition_j(int brightness) ; //the 2 photoresistors have differents values for the same brightness (imperfect component)
int condition_d(int brightness) ; //so we need 2 different conditions for each one
void create_signal() ;


//Interrupts :

CY_ISR(SW3_Handler){ //triggered when SW3 is pressed and restart the score
    restart_score() ;
    SW3_ClearInterrupt() ; 
}

CY_ISR(CLEAR_Handler) { //triggered 0.25sec after a jump/duck, clears the left LCD, turns off the LEDs, turns off audio, sets back servomotors
    //Clear LCD
    LCD_Position(0,0) ;
    LCD_PrintString("        ");
    //turn off LEDs
    LED_off();
    //turn off audio
    sound = 0 ;
    //put up the servomotors
    PWM1_WriteCompare(UNPRESS);
    PWM2_WriteCompare(UNPRESS);
    //allow sending again
    canSend = 1 ;
    
    if (move) {
        PWM2_WriteCompare(PRESS);//this line aims to limit the duration of the jump (useful when the game starts going to fast)
        Timer_clear2_Start() ; 
    } 
    
    Timer_clear_ReadStatusRegister() ;
    Timer_clear_Stop() ; //we stop the timer until a move (jump/duck) starts it again
}

CY_ISR(CLEAR2_Handler) { 
    
    PWM2_WriteCompare(UNPRESS);

    Timer_clear2_ReadStatusRegister() ;
    Timer_clear2_Stop() ; 
}


CY_ISR(SCORE_Handler) { //triggered every 0.1sec and updates the score
    if (state){
        LCD_Position(1,0) ;
        LCD_PrintNumber(score) ;
        score += 1 ;
        LCD_Position(0,0) ; //this line is necessary because it can happen that the dino jumps/ducks at the sime time this 
        //interrupt happens and thus the "jump"/"duck" string is displayed on the right part of the LCD
    }
    Timer_score_ReadStatusRegister() ;
}
CY_ISR(AUDIO_Handler){//triggered when dino jumps/ducks, sends digital signal to a DAC to convert to an audio analog signal
    if (sound){
        VDAC_SetValue(128 + 128*signal[signal_counter]); 
        signal_counter++;
        if(signal_counter == signal_size){ signal_counter = 0;} 
    }
    Timer_audio_ReadStatusRegister(); 
}

CY_ISR( ISR_RX_Handler ) {
    uint8_t status = 0;
    do{
    // Checks if no UART Rx errors
    status = UART_ReadRxStatus() ;
    if (( status & UART_RX_STS_PAR_ERROR ) |
    ( status & UART_RX_STS_STOP_ERROR ) |
    ( status & UART_RX_STS_BREAK ) |
    ( status & UART_RX_STS_OVERRUN ) ) {
    // Parity , framing , break or overrun error
        LCD_Position (1 ,0) ;
        LCD_PrintString (" UART err");
    }
    
    if ( ( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0) {
        uint8 rxData = UART_ReadRxData(); //store the received message in a variable
        if (rxData != '\n'){
            buffer[bufferIndex] = rxData;  //store this message in a string one char at the time
            bufferIndex = (bufferIndex+1) % LCD_size;
        }
        else { //when the full string has been stored, check if it's "jump" or "duck"
            bufferIndex = 0;
            if (strcmp(buffer, "jump") == 0) jump();
            else if (strcmp(buffer, "duck") == 0) duck();
        }
    }
    } while (( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0) ;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    start_F() ; //everything is launched

    for(;;){update();}
}

void start_F(){
    // Initialization of LCD
    LCD_Start();
    LCD_DisplayOn();
    LCD_ClearDisplay(); 
    
    //Initialization of Timers
    Timer_score_Start() ;//score updates every 100ms
    Timer_audio_Start() ;//signal sampled every 50µs or 25µs 
    //Timer_clear_Start() ; //this timer only starts after an action
    
       
    //Initialization of interrupts
    ISR_SW3_StartEx(SW3_Handler) ;
    ISR_score_StartEx(SCORE_Handler) ;
    ISR_clear_StartEx(CLEAR_Handler) ;
    ISR_clear2_StartEx(CLEAR2_Handler) ;
    ISR_audio_StartEx(AUDIO_Handler) ;
    ISR_RX_StartEx(ISR_RX_Handler) ;
    
    //Initialization of DAC
    VDAC_Start() ;
    
    //Initialization of the keypad
    keypadInit() ;
    
    //Initialization of the audio signal
    create_signal() ;
    
    //Initialization of the MUX and the ADC
    ADC_Start() ;
    ADC_StartConvert() ;
    Mux_Start() ;
    Mux_Select(0) ;//t he first active photoresistor is the one triggering the jump
     
    //Initialization of servomotors
    PWM1_Start();
    PWM2_Start();
    
    //Initialization of UART
    UART_Start();
    
}

int condition_j(int brightness){
    if(mode_day){return (brightness < 20);} //if it's day mode, obstacles are dark
    else{return(brightness > 10) ;} //if it's night mode, obstacles are bright
}

int condition_d(int brightness){
    if(mode_day){return (brightness < 20);} //if it's day mode, obstacles are dark
    else{return(brightness > 10) ;} //if it's night mode, obstacles are bright
}

void detect_obs(){
    if (ADC_IsEndConversion(ADC_RETURN_STATUS)){//we chose this parameter so we don't need to wait
        int brightness = (100*ADC_GetResult32())/0x10000; //we convert the brightness in a percentage
//        char str[8] ;
//        sprintf(str, "%d", brightness) ; //those 2 lines were used only to determined the brightness inside/outside an obstacle
//        
        if (current_photo == 0){
            if(condition_j(brightness)){ //since the 2 photoresistors given have some variability, we need diff conditions
                jump() ;
//                UART_PutString(" OBS_J = ") ; UART_PutString(str); UART_PutString("\n") ;
                j_obstacle = 1 ; 
            }
            else {j_obstacle = 0 ;}
        }
        
        if (current_photo == 1){
            if(condition_d(brightness)){
                duck() ;
//                UART_PutString(" OBS_D = ") ; UART_PutString(str);UART_PutString("\n") ;
                d_obstacle = 1 ;
            }
            else {d_obstacle = 0 ;}
        }

    }
    
    if (j_obstacle == 1 && d_obstacle == 1){//if both photoresistors detect an obstacle, we change the mode
        if (++mode_day == 2){ mode_day = 0 ;}
        j_obstacle = 0 ;
        d_obstacle = 0 ;
         //if mode_day was 1 --> 0 and if it was 0 --> 1
            
    }
    ADC_StopConvert(); //needs to stop the conversion while changing channel in the MUX
    if (++current_photo==2) current_photo=0; //if channel was 1 -->0 ; if it was 0 --> 1
    Mux_Select(current_photo);
    ADC_StartConvert();//we restart converting after the channel changes
}

void update(){
        char a = keypadScan() ;
        if(SW1_Read() || a == '0') {jump();}  //the moves can be triggered by buttons or keypad...
        if(SW2_Read()|| a == '8') {duck();}
        detect_obs() ;                        // or by the photoresistors
        
}

void LED_off(){
//turn off all LEDs, function called 0.5sec after a move 
    LED1_Write(0) ;
    LED2_Write(0) ;
    LED3_Write(0) ;
    LED4_Write(0) ;
}

void jump() {
//called when the dino should jump and triggers the event linked to the "jump" action   
    PWM1_WriteCompare(PRESS); //when dino jumps, the corresponding servomotor press the space bar
    activation(Jump) ;
    move = 1 ;
}

void duck() {
//same for "duck" action
    PWM2_WriteCompare(PRESS);
    activation(Duck) ;
    move = 0 ;
}

void LED_LCD(enum Move move){
//this functions display the string and turn on the LEDs associated to the move given as parameter 
    LCD_Position(0,0) ;
    if (move == Jump){
        LED1_Write(1) ;
        LED2_Write(1) ;
        LCD_PrintString("  JUMP") ;
    }
    else {
    LED3_Write(1) ;
    LED4_Write(1) ;
    LCD_PrintString("  DUCK") ;
    }
}

void activation(enum Move move){
    start_score(move) ;
    LED_LCD(move) ;
    
    if (canSend) {
        if (move == Jump) UART_PutString("Jump\n");
        else UART_PutString("Duck\n");
        canSend = 0; 
    }
    
    if (move == Jump){current_audio = Jump_sound ;}
    else {current_audio = Duck_sound ;}
    Timer_audio_WritePeriod(current_audio) ; //we modify the frequency of the audio to have 2 different sounds
    sound = 1 ;
    Timer_clear_Start() ; //starts the timer and when it reaches 0.5sec, triggers the interrupt associated
}


void start_score(enum Move move) {
//start the score when the dino jumps after a restart()
    if (move == Jump && state == 0){state = 1 ;} //only start the score if it was stopped and if the dino jumps, not when it ducks
}

void restart_score(){
//called by an interrupt when SW3 is pressed, set the score at 0 and stop it fromm running
    score = 0 ;
    state = 0 ;
    LCD_ClearDisplay() ;
    LCD_Position(1,0) ;
    LCD_PrintNumber(score) ;
}

void create_signal() {
    for(int i=0 ; i<signal_size ; i++){
        signal[i] = sin(2*PI*i/signal_size) ;
    }
}


/* [] END OF FILE */
