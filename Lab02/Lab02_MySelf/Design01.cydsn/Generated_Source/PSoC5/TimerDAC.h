/*******************************************************************************
* File Name: TimerDAC.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_TimerDAC_H)
#define CY_TIMER_TimerDAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerDAC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerDAC_Resolution                 16u
#define TimerDAC_UsingFixedFunction         1u
#define TimerDAC_UsingHWCaptureCounter      0u
#define TimerDAC_SoftwareCaptureMode        0u
#define TimerDAC_SoftwareTriggerMode        0u
#define TimerDAC_UsingHWEnable              0u
#define TimerDAC_EnableTriggerMode          0u
#define TimerDAC_InterruptOnCaptureCount    0u
#define TimerDAC_RunModeUsed                0u
#define TimerDAC_ControlRegRemoved          0u

#if defined(TimerDAC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TimerDAC_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TimerDAC_UsingFixedFunction)
    #define TimerDAC_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TimerDAC_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TimerDAC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerDAC_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TimerDAC_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TimerDAC_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TimerDAC_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerDAC_Start(void) ;
void    TimerDAC_Stop(void) ;

void    TimerDAC_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerDAC_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerDAC_GetInterruptSource() TimerDAC_ReadStatusRegister()

#if(!TimerDAC_UDB_CONTROL_REG_REMOVED)
    uint8   TimerDAC_ReadControlRegister(void) ;
    void    TimerDAC_WriteControlRegister(uint8 control) ;
#endif /* (!TimerDAC_UDB_CONTROL_REG_REMOVED) */

uint16  TimerDAC_ReadPeriod(void) ;
void    TimerDAC_WritePeriod(uint16 period) ;
uint16  TimerDAC_ReadCounter(void) ;
void    TimerDAC_WriteCounter(uint16 counter) ;
uint16  TimerDAC_ReadCapture(void) ;
void    TimerDAC_SoftwareCapture(void) ;

#if(!TimerDAC_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerDAC_SoftwareCaptureMode)
        void    TimerDAC_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerDAC_UsingFixedFunction) */

    #if (TimerDAC_SoftwareTriggerMode)
        void    TimerDAC_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerDAC_SoftwareTriggerMode) */

    #if (TimerDAC_EnableTriggerMode)
        void    TimerDAC_EnableTrigger(void) ;
        void    TimerDAC_DisableTrigger(void) ;
    #endif /* (TimerDAC_EnableTriggerMode) */


    #if(TimerDAC_InterruptOnCaptureCount)
        void    TimerDAC_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TimerDAC_InterruptOnCaptureCount) */

    #if (TimerDAC_UsingHWCaptureCounter)
        void    TimerDAC_SetCaptureCount(uint8 captureCount) ;
        uint8   TimerDAC_ReadCaptureCount(void) ;
    #endif /* (TimerDAC_UsingHWCaptureCounter) */

    void TimerDAC_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerDAC_Init(void)          ;
void TimerDAC_Enable(void)        ;
void TimerDAC_SaveConfig(void)    ;
void TimerDAC_RestoreConfig(void) ;
void TimerDAC_Sleep(void)         ;
void TimerDAC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerDAC__B_TIMER__CM_NONE 0
#define TimerDAC__B_TIMER__CM_RISINGEDGE 1
#define TimerDAC__B_TIMER__CM_FALLINGEDGE 2
#define TimerDAC__B_TIMER__CM_EITHEREDGE 3
#define TimerDAC__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerDAC__B_TIMER__TM_NONE 0x00u
#define TimerDAC__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerDAC__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerDAC__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerDAC__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerDAC_INIT_PERIOD             599u
#define TimerDAC_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerDAC_CTRL_CAP_MODE_SHIFT))
#define TimerDAC_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerDAC_CTRL_TRIG_MODE_SHIFT))
#if (TimerDAC_UsingFixedFunction)
    #define TimerDAC_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerDAC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerDAC_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerDAC_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerDAC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerDAC_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerDAC_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerDAC_UsingFixedFunction) */
#define TimerDAC_INIT_CAPTURE_COUNT      (2u)
#define TimerDAC_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerDAC_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerDAC_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerDAC_STATUS         (*(reg8 *) TimerDAC_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerDAC_STATUS_MASK    (*(reg8 *) TimerDAC_TimerHW__SR0 )
    #define TimerDAC_CONTROL        (*(reg8 *) TimerDAC_TimerHW__CFG0)
    #define TimerDAC_CONTROL2       (*(reg8 *) TimerDAC_TimerHW__CFG1)
    #define TimerDAC_CONTROL2_PTR   ( (reg8 *) TimerDAC_TimerHW__CFG1)
    #define TimerDAC_RT1            (*(reg8 *) TimerDAC_TimerHW__RT1)
    #define TimerDAC_RT1_PTR        ( (reg8 *) TimerDAC_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerDAC_CONTROL3       (*(reg8 *) TimerDAC_TimerHW__CFG2)
        #define TimerDAC_CONTROL3_PTR   ( (reg8 *) TimerDAC_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerDAC_GLOBAL_ENABLE  (*(reg8 *) TimerDAC_TimerHW__PM_ACT_CFG)
    #define TimerDAC_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerDAC_TimerHW__PM_STBY_CFG)

    #define TimerDAC_CAPTURE_LSB         (* (reg16 *) TimerDAC_TimerHW__CAP0 )
    #define TimerDAC_CAPTURE_LSB_PTR       ((reg16 *) TimerDAC_TimerHW__CAP0 )
    #define TimerDAC_PERIOD_LSB          (* (reg16 *) TimerDAC_TimerHW__PER0 )
    #define TimerDAC_PERIOD_LSB_PTR        ((reg16 *) TimerDAC_TimerHW__PER0 )
    #define TimerDAC_COUNTER_LSB         (* (reg16 *) TimerDAC_TimerHW__CNT_CMP0 )
    #define TimerDAC_COUNTER_LSB_PTR       ((reg16 *) TimerDAC_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerDAC_BLOCK_EN_MASK                     TimerDAC_TimerHW__PM_ACT_MSK
    #define TimerDAC_BLOCK_STBY_EN_MASK                TimerDAC_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerDAC_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerDAC_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerDAC_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerDAC_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerDAC_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerDAC_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerDAC_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerDAC_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerDAC_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerDAC_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerDAC_CTRL_MODE_SHIFT                 0x01u
        #define TimerDAC_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TimerDAC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerDAC_CTRL_RCOD_SHIFT        0x02u
        #define TimerDAC_CTRL_ENBL_SHIFT        0x00u
        #define TimerDAC_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerDAC_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerDAC_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerDAC_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerDAC_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerDAC_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerDAC_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerDAC_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerDAC_CTRL_RCOD_SHIFT))
        #define TimerDAC_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerDAC_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerDAC_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerDAC_RT1_MASK                        ((uint8)((uint8)0x03u << TimerDAC_RT1_SHIFT))
    #define TimerDAC_SYNC                            ((uint8)((uint8)0x03u << TimerDAC_RT1_SHIFT))
    #define TimerDAC_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerDAC_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerDAC_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerDAC_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerDAC_SYNCDSI_SHIFT))

    #define TimerDAC_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerDAC_CTRL_MODE_SHIFT))
    #define TimerDAC_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerDAC_CTRL_MODE_SHIFT))
    #define TimerDAC_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerDAC_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerDAC_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerDAC_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerDAC_STATUS_TC_INT_MASK_SHIFT        (TimerDAC_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerDAC_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerDAC_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerDAC_STATUS_TC                       ((uint8)((uint8)0x01u << TimerDAC_STATUS_TC_SHIFT))
    #define TimerDAC_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerDAC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerDAC_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerDAC_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerDAC_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerDAC_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerDAC_STATUS              (* (reg8 *) TimerDAC_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerDAC_STATUS_MASK         (* (reg8 *) TimerDAC_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerDAC_STATUS_AUX_CTRL     (* (reg8 *) TimerDAC_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerDAC_CONTROL             (* (reg8 *) TimerDAC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerDAC_Resolution <= 8u) /* 8-bit Timer */
        #define TimerDAC_CAPTURE_LSB         (* (reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TimerDAC_CAPTURE_LSB_PTR       ((reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TimerDAC_PERIOD_LSB          (* (reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TimerDAC_PERIOD_LSB_PTR        ((reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TimerDAC_COUNTER_LSB         (* (reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define TimerDAC_COUNTER_LSB_PTR       ((reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(TimerDAC_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerDAC_CAPTURE_LSB         (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TimerDAC_CAPTURE_LSB_PTR       ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TimerDAC_PERIOD_LSB          (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TimerDAC_PERIOD_LSB_PTR        ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TimerDAC_COUNTER_LSB         (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define TimerDAC_COUNTER_LSB_PTR       ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerDAC_CAPTURE_LSB         (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define TimerDAC_CAPTURE_LSB_PTR       ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define TimerDAC_PERIOD_LSB          (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define TimerDAC_PERIOD_LSB_PTR        ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define TimerDAC_COUNTER_LSB         (* (reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define TimerDAC_COUNTER_LSB_PTR       ((reg16 *) TimerDAC_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerDAC_Resolution <= 24u)/* 24-bit Timer */
        #define TimerDAC_CAPTURE_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TimerDAC_CAPTURE_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TimerDAC_PERIOD_LSB          (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TimerDAC_PERIOD_LSB_PTR        ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TimerDAC_COUNTER_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define TimerDAC_COUNTER_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerDAC_CAPTURE_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TimerDAC_CAPTURE_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TimerDAC_PERIOD_LSB          (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TimerDAC_PERIOD_LSB_PTR        ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TimerDAC_COUNTER_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define TimerDAC_COUNTER_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerDAC_CAPTURE_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define TimerDAC_CAPTURE_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define TimerDAC_PERIOD_LSB          (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define TimerDAC_PERIOD_LSB_PTR        ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define TimerDAC_COUNTER_LSB         (* (reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define TimerDAC_COUNTER_LSB_PTR       ((reg32 *) TimerDAC_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TimerDAC_COUNTER_LSB_PTR_8BIT       ((reg8 *) TimerDAC_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (TimerDAC_UsingHWCaptureCounter)
        #define TimerDAC_CAP_COUNT              (*(reg8 *) TimerDAC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerDAC_CAP_COUNT_PTR          ( (reg8 *) TimerDAC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerDAC_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerDAC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerDAC_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerDAC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerDAC_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerDAC_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerDAC_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerDAC_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerDAC_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerDAC_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerDAC_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerDAC_CTRL_INTCNT_SHIFT))
    #define TimerDAC_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerDAC_CTRL_TRIG_MODE_SHIFT))
    #define TimerDAC_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerDAC_CTRL_TRIG_EN_SHIFT))
    #define TimerDAC_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerDAC_CTRL_CAP_MODE_SHIFT))
    #define TimerDAC_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerDAC_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerDAC_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerDAC_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerDAC_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerDAC_STATUS_TC_INT_MASK_SHIFT       TimerDAC_STATUS_TC_SHIFT
    #define TimerDAC_STATUS_CAPTURE_INT_MASK_SHIFT  TimerDAC_STATUS_CAPTURE_SHIFT
    #define TimerDAC_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerDAC_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerDAC_STATUS_FIFOFULL_INT_MASK_SHIFT TimerDAC_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerDAC_STATUS_TC                      ((uint8)((uint8)0x01u << TimerDAC_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerDAC_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerDAC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerDAC_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerDAC_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerDAC_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerDAC_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerDAC_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerDAC_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerDAC_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerDAC_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerDAC_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerDAC_STATUS_FIFOFULL_SHIFT))

    #define TimerDAC_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerDAC_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerDAC_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerDAC_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerDAC_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerDAC_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_TimerDAC_H */


/* [] END OF FILE */
