/*******************************************************************************
* File Name: LED01.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED01_H) /* Pins LED01_H */
#define CY_PINS_LED01_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED01_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED01__PORT == 15 && ((LED01__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED01_Write(uint8 value);
void    LED01_SetDriveMode(uint8 mode);
uint8   LED01_ReadDataReg(void);
uint8   LED01_Read(void);
void    LED01_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED01_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED01_SetDriveMode() function.
     *  @{
     */
        #define LED01_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED01_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED01_DM_RES_UP          PIN_DM_RES_UP
        #define LED01_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED01_DM_OD_LO           PIN_DM_OD_LO
        #define LED01_DM_OD_HI           PIN_DM_OD_HI
        #define LED01_DM_STRONG          PIN_DM_STRONG
        #define LED01_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED01_MASK               LED01__MASK
#define LED01_SHIFT              LED01__SHIFT
#define LED01_WIDTH              1u

/* Interrupt constants */
#if defined(LED01__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED01_SetInterruptMode() function.
     *  @{
     */
        #define LED01_INTR_NONE      (uint16)(0x0000u)
        #define LED01_INTR_RISING    (uint16)(0x0001u)
        #define LED01_INTR_FALLING   (uint16)(0x0002u)
        #define LED01_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED01_INTR_MASK      (0x01u) 
#endif /* (LED01__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED01_PS                     (* (reg8 *) LED01__PS)
/* Data Register */
#define LED01_DR                     (* (reg8 *) LED01__DR)
/* Port Number */
#define LED01_PRT_NUM                (* (reg8 *) LED01__PRT) 
/* Connect to Analog Globals */                                                  
#define LED01_AG                     (* (reg8 *) LED01__AG)                       
/* Analog MUX bux enable */
#define LED01_AMUX                   (* (reg8 *) LED01__AMUX) 
/* Bidirectional Enable */                                                        
#define LED01_BIE                    (* (reg8 *) LED01__BIE)
/* Bit-mask for Aliased Register Access */
#define LED01_BIT_MASK               (* (reg8 *) LED01__BIT_MASK)
/* Bypass Enable */
#define LED01_BYP                    (* (reg8 *) LED01__BYP)
/* Port wide control signals */                                                   
#define LED01_CTL                    (* (reg8 *) LED01__CTL)
/* Drive Modes */
#define LED01_DM0                    (* (reg8 *) LED01__DM0) 
#define LED01_DM1                    (* (reg8 *) LED01__DM1)
#define LED01_DM2                    (* (reg8 *) LED01__DM2) 
/* Input Buffer Disable Override */
#define LED01_INP_DIS                (* (reg8 *) LED01__INP_DIS)
/* LCD Common or Segment Drive */
#define LED01_LCD_COM_SEG            (* (reg8 *) LED01__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED01_LCD_EN                 (* (reg8 *) LED01__LCD_EN)
/* Slew Rate Control */
#define LED01_SLW                    (* (reg8 *) LED01__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED01_PRTDSI__CAPS_SEL       (* (reg8 *) LED01__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED01_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED01__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED01_PRTDSI__OE_SEL0        (* (reg8 *) LED01__PRTDSI__OE_SEL0) 
#define LED01_PRTDSI__OE_SEL1        (* (reg8 *) LED01__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED01_PRTDSI__OUT_SEL0       (* (reg8 *) LED01__PRTDSI__OUT_SEL0) 
#define LED01_PRTDSI__OUT_SEL1       (* (reg8 *) LED01__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED01_PRTDSI__SYNC_OUT       (* (reg8 *) LED01__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED01__SIO_CFG)
    #define LED01_SIO_HYST_EN        (* (reg8 *) LED01__SIO_HYST_EN)
    #define LED01_SIO_REG_HIFREQ     (* (reg8 *) LED01__SIO_REG_HIFREQ)
    #define LED01_SIO_CFG            (* (reg8 *) LED01__SIO_CFG)
    #define LED01_SIO_DIFF           (* (reg8 *) LED01__SIO_DIFF)
#endif /* (LED01__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED01__INTSTAT)
    #define LED01_INTSTAT            (* (reg8 *) LED01__INTSTAT)
    #define LED01_SNAP               (* (reg8 *) LED01__SNAP)
    
	#define LED01_0_INTTYPE_REG 		(* (reg8 *) LED01__0__INTTYPE)
#endif /* (LED01__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED01_H */


/* [] END OF FILE */
