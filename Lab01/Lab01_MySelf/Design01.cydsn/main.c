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

int Start_F(){
    
    LCD_Start();
    LCD_DisplayOn();
    LCD_ClearDisplay();
    //end for LCD
    
    ADC_Start(); 
    return 0; 
}

int beacon(){
        
    // Test LEDs 
    LED01_Write( ~ LED01_Read());
    LED02_Write( ~ LED02_Read());
//    CyDelay(500);
    return 0; 
}

int verif_cross(){
    LED03_Write( DOWN_Read());
    LED04_Write( TOP_Read()); 
    CyDelay(100);
    return 0; 
}

int print_key(){
   
    
   LCD_Position(0,1); 
   LCD_PutChar( keypadScan() );
   CyDelay(100); 
    
    return 0; 
}

int LED_off(); 
int LED_control(int); 
int Pot_control(uint32_t); 
int Light_control(uint32_t); 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Start_F(); 
    
    LED_off();
    ADC_StartConvert(); 
    
    uint32_t potVal = 0; 
    for(;;)
    {
        Light_control(potVal); 
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

int Pot_control(uint32_t potVal){

   CyDelay(100);
   if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT)){
        potVal = ADC_GetResult32();
    }
    LCD_ClearDisplay();
    LCD_Position(0,0);
    potVal = (potVal*5000/(0xFFFF)); //Get a value between 0 and 5000 mV
    LCD_PrintNumber(potVal);
    LCD_PrintString(" mV");
        
    LED_control(potVal); 
    
    return 0; 
}

int Light_control(uint32_t potVal){

   CyDelay(100);
   if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT)){
        potVal = ADC_GetResult32();
    }
    LCD_ClearDisplay();
    LCD_Position(0,0);
    potVal = (potVal*100/(0xFFFF)); //Get a value between 0 and 5000 mV
    LCD_PrintNumber(potVal);
    LCD_PrintString(" mV");
    LCD_Position(1,7); 
    LCD_PutChar('L');
        
    LED_control(5000 - potVal * 50 );
    return 0; 
}
/* [] END OF FILE */
