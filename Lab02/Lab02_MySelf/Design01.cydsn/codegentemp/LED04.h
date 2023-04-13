/*******************************************************************************
* File Name: LED04.h  
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

#if !defined(CY_PINS_LED04_H) /* Pins LED04_H */
#define CY_PINS_LED04_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED04_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED04__PORT == 15 && ((LED04__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED04_Write(uint8 value);
void    LED04_SetDriveMode(uint8 mode);
uint8   LED04_ReadDataReg(void);
uint8   LED04_Read(void);
void    LED04_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED04_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED04_SetDriveMode() function.
     *  @{
     */
        #define LED04_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED04_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED04_DM_RES_UP          PIN_DM_RES_UP
        #define LED04_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED04_DM_OD_LO           PIN_DM_OD_LO
        #define LED04_DM_OD_HI           PIN_DM_OD_HI
        #define LED04_DM_STRONG          PIN_DM_STRONG
        #define LED04_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED04_MASK               LED04__MASK
#define LED04_SHIFT              LED04__SHIFT
#define LED04_WIDTH              1u

/* Interrupt constants */
#if defined(LED04__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED04_SetInterruptMode() function.
     *  @{
     */
        #define LED04_INTR_NONE      (uint16)(0x0000u)
        #define LED04_INTR_RISING    (uint16)(0x0001u)
        #define LED04_INTR_FALLING   (uint16)(0x0002u)
        #define LED04_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED04_INTR_MASK      (0x01u) 
#endif /* (LED04__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED04_PS                     (* (reg8 *) LED04__PS)
/* Data Register */
#define LED04_DR                     (* (reg8 *) LED04__DR)
/* Port Number */
#define LED04_PRT_NUM                (* (reg8 *) LED04__PRT) 
/* Connect to Analog Globals */                                                  
#define LED04_AG                     (* (reg8 *) LED04__AG)                       
/* Analog MUX bux enable */
#define LED04_AMUX                   (* (reg8 *) LED04__AMUX) 
/* Bidirectional Enable */                                                        
#define LED04_BIE                    (* (reg8 *) LED04__BIE)
/* Bit-mask for Aliased Register Access */
#define LED04_BIT_MASK               (* (reg8 *) LED04__BIT_MASK)
/* Bypass Enable */
#define LED04_BYP                    (* (reg8 *) LED04__BYP)
/* Port wide control signals */                                                   
#define LED04_CTL                    (* (reg8 *) LED04__CTL)
/* Drive Modes */
#define LED04_DM0                    (* (reg8 *) LED04__DM0) 
#define LED04_DM1                    (* (reg8 *) LED04__DM1)
#define LED04_DM2                    (* (reg8 *) LED04__DM2) 
/* Input Buffer Disable Override */
#define LED04_INP_DIS                (* (reg8 *) LED04__INP_DIS)
/* LCD Common or Segment Drive */
#define LED04_LCD_COM_SEG            (* (reg8 *) LED04__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED04_LCD_EN                 (* (reg8 *) LED04__LCD_EN)
/* Slew Rate Control */
#define LED04_SLW                    (* (reg8 *) LED04__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED04_PRTDSI__CAPS_SEL       (* (reg8 *) LED04__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED04_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED04__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED04_PRTDSI__OE_SEL0        (* (reg8 *) LED04__PRTDSI__OE_SEL0) 
#define LED04_PRTDSI__OE_SEL1        (* (reg8 *) LED04__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED04_PRTDSI__OUT_SEL0       (* (reg8 *) LED04__PRTDSI__OUT_SEL0) 
#define LED04_PRTDSI__OUT_SEL1       (* (reg8 *) LED04__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED04_PRTDSI__SYNC_OUT       (* (reg8 *) LED04__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED04__SIO_CFG)
    #define LED04_SIO_HYST_EN        (* (reg8 *) LED04__SIO_HYST_EN)
    #define LED04_SIO_REG_HIFREQ     (* (reg8 *) LED04__SIO_REG_HIFREQ)
    #define LED04_SIO_CFG            (* (reg8 *) LED04__SIO_CFG)
    #define LED04_SIO_DIFF           (* (reg8 *) LED04__SIO_DIFF)
#endif /* (LED04__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED04__INTSTAT)
    #define LED04_INTSTAT            (* (reg8 *) LED04__INTSTAT)
    #define LED04_SNAP               (* (reg8 *) LED04__SNAP)
    
	#define LED04_0_INTTYPE_REG 		(* (reg8 *) LED04__0__INTTYPE)
#endif /* (LED04__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED04_H */


/* [] END OF FILE */
