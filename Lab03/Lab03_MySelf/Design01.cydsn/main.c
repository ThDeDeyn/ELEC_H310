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

#define PI 3.14159
#define N 7

int Start_F(){
    
    LCD_Start();
    LCD_DisplayOn();
    LCD_ClearDisplay();
    //end for LCD
    
    ADC_Start();
    //Timer_start(); 
    return 0; 
}


int LED_off();

uint8 j = 0; 
uint8 rxData;

CY_ISR ( isr_uart_rx_Handler ) {
uint8_t status = 0;
do{
    // Checks if no UART Rx errors
    status = UART_ReadRxStatus ();
    if (( status & UART_RX_STS_PAR_ERROR ) |
    ( status & UART_RX_STS_STOP_ERROR ) |
    ( status & UART_RX_STS_BREAK ) |
    ( status & UART_RX_STS_OVERRUN ) ) {
        // Parity , framing , break or overrun error
        LCD_Position (1 ,0);
        LCD_PrintString (" UART err");
    }
    // Check that rx buffer is not empty and get rx data
    if ( ( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0){
            rxData = UART_ReadRxData();
            UART_PutChar(rxData);
            LCD_Position(1,0);
            
            LCD_Position(1,j);
            LCD_PutChar(rxData);
            LED01_Write(~LED01_Read());
            j++; 
            if ( j == N){j = 0; LCD_PrintString("     ");}
    }
    } while (( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Start_F(); 
    Timer_Start();
    PWM_Start(); 
    ADC_Start();
    LCD_Start();
    UART_Start(); 
    
    uint16_t pwm_period = 48000;
    uint32_t val_CMP = 2400;
    uint32_t val_adc;
    ADC_StartConvert();
    
    PWM_WritePeriod(pwm_period); 
    PWM_WriteCompare(val_CMP);

    LED_off();
    isr_uart_rx_StartEx(isr_uart_rx_Handler);

    UART_PutString("Wesh drare\n"); 
    LED03_Write(1);  
 
    for(;;)
    {
   
        
        /*
        if (ADC_IsEndConversion(ADC_RETURN_STATUS)){
            val_adc = ADC_GetResult32();
            val_CMP = ((val_adc /(float)0xFFFF) + 1 ) * 2400; //Conversion from [0x0000,0xFFFF] to [2400,4800] (:= [1,2ms])
            LCD_Position(0,0);
            LCD_PrintNumber(val_CMP);
            PWM_WriteCompare(val_CMP);
            CyDelay(500);
          
        }*/
        
        
    }
}


int LED_off(){
    LED01_Write(0);
    LED02_Write(0);
    LED03_Write(0);
    LED04_Write(0);
    
    return 0; 
}

/* [] END OF FILE */
