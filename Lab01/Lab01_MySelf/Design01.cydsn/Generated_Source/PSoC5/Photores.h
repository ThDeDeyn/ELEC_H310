/*******************************************************************************
* File Name: Photores.h  
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

#if !defined(CY_PINS_Photores_H) /* Pins Photores_H */
#define CY_PINS_Photores_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Photores_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Photores__PORT == 15 && ((Photores__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Photores_Write(uint8 value);
void    Photores_SetDriveMode(uint8 mode);
uint8   Photores_ReadDataReg(void);
uint8   Photores_Read(void);
void    Photores_SetInterruptMode(uint16 position, uint16 mode);
uint8   Photores_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Photores_SetDriveMode() function.
     *  @{
     */
        #define Photores_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Photores_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Photores_DM_RES_UP          PIN_DM_RES_UP
        #define Photores_DM_RES_DWN         PIN_DM_RES_DWN
        #define Photores_DM_OD_LO           PIN_DM_OD_LO
        #define Photores_DM_OD_HI           PIN_DM_OD_HI
        #define Photores_DM_STRONG          PIN_DM_STRONG
        #define Photores_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Photores_MASK               Photores__MASK
#define Photores_SHIFT              Photores__SHIFT
#define Photores_WIDTH              1u

/* Interrupt constants */
#if defined(Photores__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Photores_SetInterruptMode() function.
     *  @{
     */
        #define Photores_INTR_NONE      (uint16)(0x0000u)
        #define Photores_INTR_RISING    (uint16)(0x0001u)
        #define Photores_INTR_FALLING   (uint16)(0x0002u)
        #define Photores_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Photores_INTR_MASK      (0x01u) 
#endif /* (Photores__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Photores_PS                     (* (reg8 *) Photores__PS)
/* Data Register */
#define Photores_DR                     (* (reg8 *) Photores__DR)
/* Port Number */
#define Photores_PRT_NUM                (* (reg8 *) Photores__PRT) 
/* Connect to Analog Globals */                                                  
#define Photores_AG                     (* (reg8 *) Photores__AG)                       
/* Analog MUX bux enable */
#define Photores_AMUX                   (* (reg8 *) Photores__AMUX) 
/* Bidirectional Enable */                                                        
#define Photores_BIE                    (* (reg8 *) Photores__BIE)
/* Bit-mask for Aliased Register Access */
#define Photores_BIT_MASK               (* (reg8 *) Photores__BIT_MASK)
/* Bypass Enable */
#define Photores_BYP                    (* (reg8 *) Photores__BYP)
/* Port wide control signals */                                                   
#define Photores_CTL                    (* (reg8 *) Photores__CTL)
/* Drive Modes */
#define Photores_DM0                    (* (reg8 *) Photores__DM0) 
#define Photores_DM1                    (* (reg8 *) Photores__DM1)
#define Photores_DM2                    (* (reg8 *) Photores__DM2) 
/* Input Buffer Disable Override */
#define Photores_INP_DIS                (* (reg8 *) Photores__INP_DIS)
/* LCD Common or Segment Drive */
#define Photores_LCD_COM_SEG            (* (reg8 *) Photores__LCD_COM_SEG)
/* Enable Segment LCD */
#define Photores_LCD_EN                 (* (reg8 *) Photores__LCD_EN)
/* Slew Rate Control */
#define Photores_SLW                    (* (reg8 *) Photores__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Photores_PRTDSI__CAPS_SEL       (* (reg8 *) Photores__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Photores_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Photores__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Photores_PRTDSI__OE_SEL0        (* (reg8 *) Photores__PRTDSI__OE_SEL0) 
#define Photores_PRTDSI__OE_SEL1        (* (reg8 *) Photores__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Photores_PRTDSI__OUT_SEL0       (* (reg8 *) Photores__PRTDSI__OUT_SEL0) 
#define Photores_PRTDSI__OUT_SEL1       (* (reg8 *) Photores__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Photores_PRTDSI__SYNC_OUT       (* (reg8 *) Photores__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Photores__SIO_CFG)
    #define Photores_SIO_HYST_EN        (* (reg8 *) Photores__SIO_HYST_EN)
    #define Photores_SIO_REG_HIFREQ     (* (reg8 *) Photores__SIO_REG_HIFREQ)
    #define Photores_SIO_CFG            (* (reg8 *) Photores__SIO_CFG)
    #define Photores_SIO_DIFF           (* (reg8 *) Photores__SIO_DIFF)
#endif /* (Photores__SIO_CFG) */

/* Interrupt Registers */
#if defined(Photores__INTSTAT)
    #define Photores_INTSTAT            (* (reg8 *) Photores__INTSTAT)
    #define Photores_SNAP               (* (reg8 *) Photores__SNAP)
    
	#define Photores_0_INTTYPE_REG 		(* (reg8 *) Photores__0__INTTYPE)
#endif /* (Photores__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Photores_H */


/* [] END OF FILE */
