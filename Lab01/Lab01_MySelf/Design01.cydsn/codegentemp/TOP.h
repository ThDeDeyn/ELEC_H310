/*******************************************************************************
* File Name: TOP.h  
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

#if !defined(CY_PINS_TOP_H) /* Pins TOP_H */
#define CY_PINS_TOP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TOP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TOP__PORT == 15 && ((TOP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TOP_Write(uint8 value);
void    TOP_SetDriveMode(uint8 mode);
uint8   TOP_ReadDataReg(void);
uint8   TOP_Read(void);
void    TOP_SetInterruptMode(uint16 position, uint16 mode);
uint8   TOP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TOP_SetDriveMode() function.
     *  @{
     */
        #define TOP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TOP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TOP_DM_RES_UP          PIN_DM_RES_UP
        #define TOP_DM_RES_DWN         PIN_DM_RES_DWN
        #define TOP_DM_OD_LO           PIN_DM_OD_LO
        #define TOP_DM_OD_HI           PIN_DM_OD_HI
        #define TOP_DM_STRONG          PIN_DM_STRONG
        #define TOP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TOP_MASK               TOP__MASK
#define TOP_SHIFT              TOP__SHIFT
#define TOP_WIDTH              1u

/* Interrupt constants */
#if defined(TOP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TOP_SetInterruptMode() function.
     *  @{
     */
        #define TOP_INTR_NONE      (uint16)(0x0000u)
        #define TOP_INTR_RISING    (uint16)(0x0001u)
        #define TOP_INTR_FALLING   (uint16)(0x0002u)
        #define TOP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TOP_INTR_MASK      (0x01u) 
#endif /* (TOP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TOP_PS                     (* (reg8 *) TOP__PS)
/* Data Register */
#define TOP_DR                     (* (reg8 *) TOP__DR)
/* Port Number */
#define TOP_PRT_NUM                (* (reg8 *) TOP__PRT) 
/* Connect to Analog Globals */                                                  
#define TOP_AG                     (* (reg8 *) TOP__AG)                       
/* Analog MUX bux enable */
#define TOP_AMUX                   (* (reg8 *) TOP__AMUX) 
/* Bidirectional Enable */                                                        
#define TOP_BIE                    (* (reg8 *) TOP__BIE)
/* Bit-mask for Aliased Register Access */
#define TOP_BIT_MASK               (* (reg8 *) TOP__BIT_MASK)
/* Bypass Enable */
#define TOP_BYP                    (* (reg8 *) TOP__BYP)
/* Port wide control signals */                                                   
#define TOP_CTL                    (* (reg8 *) TOP__CTL)
/* Drive Modes */
#define TOP_DM0                    (* (reg8 *) TOP__DM0) 
#define TOP_DM1                    (* (reg8 *) TOP__DM1)
#define TOP_DM2                    (* (reg8 *) TOP__DM2) 
/* Input Buffer Disable Override */
#define TOP_INP_DIS                (* (reg8 *) TOP__INP_DIS)
/* LCD Common or Segment Drive */
#define TOP_LCD_COM_SEG            (* (reg8 *) TOP__LCD_COM_SEG)
/* Enable Segment LCD */
#define TOP_LCD_EN                 (* (reg8 *) TOP__LCD_EN)
/* Slew Rate Control */
#define TOP_SLW                    (* (reg8 *) TOP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TOP_PRTDSI__CAPS_SEL       (* (reg8 *) TOP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TOP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TOP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TOP_PRTDSI__OE_SEL0        (* (reg8 *) TOP__PRTDSI__OE_SEL0) 
#define TOP_PRTDSI__OE_SEL1        (* (reg8 *) TOP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TOP_PRTDSI__OUT_SEL0       (* (reg8 *) TOP__PRTDSI__OUT_SEL0) 
#define TOP_PRTDSI__OUT_SEL1       (* (reg8 *) TOP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TOP_PRTDSI__SYNC_OUT       (* (reg8 *) TOP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TOP__SIO_CFG)
    #define TOP_SIO_HYST_EN        (* (reg8 *) TOP__SIO_HYST_EN)
    #define TOP_SIO_REG_HIFREQ     (* (reg8 *) TOP__SIO_REG_HIFREQ)
    #define TOP_SIO_CFG            (* (reg8 *) TOP__SIO_CFG)
    #define TOP_SIO_DIFF           (* (reg8 *) TOP__SIO_DIFF)
#endif /* (TOP__SIO_CFG) */

/* Interrupt Registers */
#if defined(TOP__INTSTAT)
    #define TOP_INTSTAT            (* (reg8 *) TOP__INTSTAT)
    #define TOP_SNAP               (* (reg8 *) TOP__SNAP)
    
	#define TOP_0_INTTYPE_REG 		(* (reg8 *) TOP__0__INTTYPE)
#endif /* (TOP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TOP_H */


/* [] END OF FILE */
