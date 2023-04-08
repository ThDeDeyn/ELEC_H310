/*******************************************************************************
* File Name: LED02.h  
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

#if !defined(CY_PINS_LED02_H) /* Pins LED02_H */
#define CY_PINS_LED02_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED02_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED02__PORT == 15 && ((LED02__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED02_Write(uint8 value);
void    LED02_SetDriveMode(uint8 mode);
uint8   LED02_ReadDataReg(void);
uint8   LED02_Read(void);
void    LED02_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED02_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED02_SetDriveMode() function.
     *  @{
     */
        #define LED02_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED02_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED02_DM_RES_UP          PIN_DM_RES_UP
        #define LED02_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED02_DM_OD_LO           PIN_DM_OD_LO
        #define LED02_DM_OD_HI           PIN_DM_OD_HI
        #define LED02_DM_STRONG          PIN_DM_STRONG
        #define LED02_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED02_MASK               LED02__MASK
#define LED02_SHIFT              LED02__SHIFT
#define LED02_WIDTH              1u

/* Interrupt constants */
#if defined(LED02__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED02_SetInterruptMode() function.
     *  @{
     */
        #define LED02_INTR_NONE      (uint16)(0x0000u)
        #define LED02_INTR_RISING    (uint16)(0x0001u)
        #define LED02_INTR_FALLING   (uint16)(0x0002u)
        #define LED02_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED02_INTR_MASK      (0x01u) 
#endif /* (LED02__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED02_PS                     (* (reg8 *) LED02__PS)
/* Data Register */
#define LED02_DR                     (* (reg8 *) LED02__DR)
/* Port Number */
#define LED02_PRT_NUM                (* (reg8 *) LED02__PRT) 
/* Connect to Analog Globals */                                                  
#define LED02_AG                     (* (reg8 *) LED02__AG)                       
/* Analog MUX bux enable */
#define LED02_AMUX                   (* (reg8 *) LED02__AMUX) 
/* Bidirectional Enable */                                                        
#define LED02_BIE                    (* (reg8 *) LED02__BIE)
/* Bit-mask for Aliased Register Access */
#define LED02_BIT_MASK               (* (reg8 *) LED02__BIT_MASK)
/* Bypass Enable */
#define LED02_BYP                    (* (reg8 *) LED02__BYP)
/* Port wide control signals */                                                   
#define LED02_CTL                    (* (reg8 *) LED02__CTL)
/* Drive Modes */
#define LED02_DM0                    (* (reg8 *) LED02__DM0) 
#define LED02_DM1                    (* (reg8 *) LED02__DM1)
#define LED02_DM2                    (* (reg8 *) LED02__DM2) 
/* Input Buffer Disable Override */
#define LED02_INP_DIS                (* (reg8 *) LED02__INP_DIS)
/* LCD Common or Segment Drive */
#define LED02_LCD_COM_SEG            (* (reg8 *) LED02__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED02_LCD_EN                 (* (reg8 *) LED02__LCD_EN)
/* Slew Rate Control */
#define LED02_SLW                    (* (reg8 *) LED02__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED02_PRTDSI__CAPS_SEL       (* (reg8 *) LED02__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED02_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED02__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED02_PRTDSI__OE_SEL0        (* (reg8 *) LED02__PRTDSI__OE_SEL0) 
#define LED02_PRTDSI__OE_SEL1        (* (reg8 *) LED02__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED02_PRTDSI__OUT_SEL0       (* (reg8 *) LED02__PRTDSI__OUT_SEL0) 
#define LED02_PRTDSI__OUT_SEL1       (* (reg8 *) LED02__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED02_PRTDSI__SYNC_OUT       (* (reg8 *) LED02__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED02__SIO_CFG)
    #define LED02_SIO_HYST_EN        (* (reg8 *) LED02__SIO_HYST_EN)
    #define LED02_SIO_REG_HIFREQ     (* (reg8 *) LED02__SIO_REG_HIFREQ)
    #define LED02_SIO_CFG            (* (reg8 *) LED02__SIO_CFG)
    #define LED02_SIO_DIFF           (* (reg8 *) LED02__SIO_DIFF)
#endif /* (LED02__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED02__INTSTAT)
    #define LED02_INTSTAT            (* (reg8 *) LED02__INTSTAT)
    #define LED02_SNAP               (* (reg8 *) LED02__SNAP)
    
	#define LED02_0_INTTYPE_REG 		(* (reg8 *) LED02__0__INTTYPE)
#endif /* (LED02__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED02_H */


/* [] END OF FILE */
