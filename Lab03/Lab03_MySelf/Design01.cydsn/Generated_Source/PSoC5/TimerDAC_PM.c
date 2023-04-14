/*******************************************************************************
* File Name: TimerDAC_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerDAC.h"

static TimerDAC_backupStruct TimerDAC_backup;


/*******************************************************************************
* Function Name: TimerDAC_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerDAC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerDAC_SaveConfig(void) 
{
    #if (!TimerDAC_UsingFixedFunction)
        TimerDAC_backup.TimerUdb = TimerDAC_ReadCounter();
        TimerDAC_backup.InterruptMaskValue = TimerDAC_STATUS_MASK;
        #if (TimerDAC_UsingHWCaptureCounter)
            TimerDAC_backup.TimerCaptureCounter = TimerDAC_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerDAC_UDB_CONTROL_REG_REMOVED)
            TimerDAC_backup.TimerControlRegister = TimerDAC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerDAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerDAC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerDAC_RestoreConfig(void) 
{   
    #if (!TimerDAC_UsingFixedFunction)

        TimerDAC_WriteCounter(TimerDAC_backup.TimerUdb);
        TimerDAC_STATUS_MASK =TimerDAC_backup.InterruptMaskValue;
        #if (TimerDAC_UsingHWCaptureCounter)
            TimerDAC_SetCaptureCount(TimerDAC_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerDAC_UDB_CONTROL_REG_REMOVED)
            TimerDAC_WriteControlRegister(TimerDAC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerDAC_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerDAC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerDAC_Sleep(void) 
{
    #if(!TimerDAC_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerDAC_CTRL_ENABLE == (TimerDAC_CONTROL & TimerDAC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerDAC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerDAC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerDAC_Stop();
    TimerDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerDAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerDAC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerDAC_Wakeup(void) 
{
    TimerDAC_RestoreConfig();
    #if(!TimerDAC_UDB_CONTROL_REG_REMOVED)
        if(TimerDAC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerDAC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
