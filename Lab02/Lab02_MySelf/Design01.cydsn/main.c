/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "keypad.h"
#include "math.h"

#define PI 3.14159
#define N 100

int Start_F(){
    
    LCD_Start();
    LCD_DisplayOn();
    LCD_ClearDisplay();
    //end for LCD
    
    ADC_Start();
    //Timer_start(); 
    return 0; 
}


int beacon(); 
int print_keypad(); 
int LED_off(); 
int LED_control(int); 
int Pot_control(uint32_t); 
int Light_control(uint32_t); 

int blink1kHz(); 
int blink1Hz(); 

int fill(); 
int synthesizer();

float signal[100];
uint16_t j = 0;
uint8_t value;
uint16_t cpt = 0;

CY_ISR (Sound){
    value = 128 + 128*signal[j];
    DAC_SetValue(value); 
    j++;
    if(j == N){ j = 0;} 
    TimerDAC_ReadStatusRegister(); //Do not forget to reset the register
}

CY_ISR(LED){
    if(cpt < 1000){cpt++;}
    else{ LED01_Write( ~ LED01_Read()); cpt = 0; }
    Timer_ReadStatusRegister();

}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Start_F(); 
    
    LED_off();
    
    Timer_Start();
    TimerDAC_Start(); 
    DAC_Start();
    DAC_SetValue(0);
    
    isr_dac_StartEx(Sound);
    isr_led_StartEx(LED);
    
    fill();
    
    for(;;)
    {
        //synthesizer(); // no interrupt
        
    }
}

int print_keypad(){
    if(keypadScan() != 'z'){
        LCD_ClearDisplay(); 
        LCD_Position(0,1); 
        LCD_PutChar( keypadScan());
    }
    CyDelay(100);  
   
    return 0; 
}

int LED_off(){
    LED01_Write(0);
    LED02_Write(0);
    LED03_Write(0);
    LED04_Write(0);
    
    return 0; 
}

int LED_control(int potVal){
    
    if(potVal > 0 && potVal < 1000){
        LED01_Write(0); LED02_Write(0); LED03_Write(0); LED04_Write(0); 
    }
    else if(potVal >= 1000 && potVal < 2000){
        LED01_Write(1); LED02_Write(0); LED03_Write(0); LED04_Write(0); 
    }
    else if(potVal >= 2000 && potVal < 3000){
        LED01_Write(1); LED02_Write(1); LED03_Write(0); LED04_Write(0); 
    }
    else if(potVal >= 3000 && potVal < 4000){
        LED01_Write(1); LED02_Write(1); LED03_Write(1); LED04_Write(0); 
    }
    else if(potVal >= 4000){
        LED01_Write(1); LED02_Write(1); LED03_Write(1); LED04_Write(1); 
    }    
    
    
    return 0; 
}


int blink1kHz(){
    if(0x80 & Timer_ReadStatusRegister()){
        LED01_Write( ~ LED01_Read());
    }

return 0;}

int blink1Hz(int cpt){
    if(0x80 & Timer_ReadStatusRegister()){
        if(cpt < 1000)
        LED01_Write( ~ LED01_Read());
    }

return 0;}

int fill(){
    for(int i = 0; i < N;i++){
        signal[i] = sin(2*PI*i/N);
    }
return 0; 
}

int synthesizer(){
    if(0x80 & Timer_ReadStatusRegister()){
            if(cpt < 1000){cpt++;}
            else{ LED01_Write( ~ LED01_Read()); cpt = 0; }
        }
    if(0x80 & TimerDAC_ReadStatusRegister()){
            value = 128 + 128*signal[j];
            DAC_SetValue(value); 
            j++;
            if(j == N){ j = 0;}
    }

return 0;
}
/* [] END OF FILE */
