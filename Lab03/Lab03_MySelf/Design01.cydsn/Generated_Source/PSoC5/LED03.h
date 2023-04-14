/*******************************************************************************
* File Name: LED03.h  
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

#if !defined(CY_PINS_LED03_H) /* Pins LED03_H */
#define CY_PINS_LED03_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED03_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED03__PORT == 15 && ((LED03__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED03_Write(uint8 value);
void    LED03_SetDriveMode(uint8 mode);
uint8   LED03_ReadDataReg(void);
uint8   LED03_Read(void);
void    LED03_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED03_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED03_SetDriveMode() function.
     *  @{
     */
        #define LED03_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED03_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED03_DM_RES_UP          PIN_DM_RES_UP
        #define LED03_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED03_DM_OD_LO           PIN_DM_OD_LO
        #define LED03_DM_OD_HI           PIN_DM_OD_HI
        #define LED03_DM_STRONG          PIN_DM_STRONG
        #define LED03_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED03_MASK               LED03__MASK
#define LED03_SHIFT              LED03__SHIFT
#define LED03_WIDTH              1u

/* Interrupt constants */
#if defined(LED03__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED03_SetInterruptMode() function.
     *  @{
     */
        #define LED03_INTR_NONE      (uint16)(0x0000u)
        #define LED03_INTR_RISING    (uint16)(0x0001u)
        #define LED03_INTR_FALLING   (uint16)(0x0002u)
        #define LED03_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED03_INTR_MASK      (0x01u) 
#endif /* (LED03__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED03_PS                     (* (reg8 *) LED03__PS)
/* Data Register */
#define LED03_DR                     (* (reg8 *) LED03__DR)
/* Port Number */
#define LED03_PRT_NUM                (* (reg8 *) LED03__PRT) 
/* Connect to Analog Globals */                                                  
#define LED03_AG                     (* (reg8 *) LED03__AG)                       
/* Analog MUX bux enable */
#define LED03_AMUX                   (* (reg8 *) LED03__AMUX) 
/* Bidirectional Enable */                                                        
#define LED03_BIE                    (* (reg8 *) LED03__BIE)
/* Bit-mask for Aliased Register Access */
#define LED03_BIT_MASK               (* (reg8 *) LED03__BIT_MASK)
/* Bypass Enable */
#define LED03_BYP                    (* (reg8 *) LED03__BYP)
/* Port wide control signals */                                                   
#define LED03_CTL                    (* (reg8 *) LED03__CTL)
/* Drive Modes */
#define LED03_DM0                    (* (reg8 *) LED03__DM0) 
#define LED03_DM1                    (* (reg8 *) LED03__DM1)
#define LED03_DM2                    (* (reg8 *) LED03__DM2) 
/* Input Buffer Disable Override */
#define LED03_INP_DIS                (* (reg8 *) LED03__INP_DIS)
/* LCD Common or Segment Drive */
#define LED03_LCD_COM_SEG            (* (reg8 *) LED03__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED03_LCD_EN                 (* (reg8 *) LED03__LCD_EN)
/* Slew Rate Control */
#define LED03_SLW                    (* (reg8 *) LED03__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED03_PRTDSI__CAPS_SEL       (* (reg8 *) LED03__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED03_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED03__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED03_PRTDSI__OE_SEL0        (* (reg8 *) LED03__PRTDSI__OE_SEL0) 
#define LED03_PRTDSI__OE_SEL1        (* (reg8 *) LED03__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED03_PRTDSI__OUT_SEL0       (* (reg8 *) LED03__PRTDSI__OUT_SEL0) 
#define LED03_PRTDSI__OUT_SEL1       (* (reg8 *) LED03__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED03_PRTDSI__SYNC_OUT       (* (reg8 *) LED03__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED03__SIO_CFG)
    #define LED03_SIO_HYST_EN        (* (reg8 *) LED03__SIO_HYST_EN)
    #define LED03_SIO_REG_HIFREQ     (* (reg8 *) LED03__SIO_REG_HIFREQ)
    #define LED03_SIO_CFG            (* (reg8 *) LED03__SIO_CFG)
    #define LED03_SIO_DIFF           (* (reg8 *) LED03__SIO_DIFF)
#endif /* (LED03__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED03__INTSTAT)
    #define LED03_INTSTAT            (* (reg8 *) LED03__INTSTAT)
    #define LED03_SNAP               (* (reg8 *) LED03__SNAP)
    
	#define LED03_0_INTTYPE_REG 		(* (reg8 *) LED03__0__INTTYPE)
#endif /* (LED03__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED03_H */


/* [] END OF FILE */
