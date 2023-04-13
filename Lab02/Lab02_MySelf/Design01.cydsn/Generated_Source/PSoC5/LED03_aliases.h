/*******************************************************************************
* File Name: LED03.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED03_ALIASES_H) /* Pins LED03_ALIASES_H */
#define CY_PINS_LED03_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LED03_0			(LED03__0__PC)
#define LED03_0_INTR	((uint16)((uint16)0x0001u << LED03__0__SHIFT))

#define LED03_INTR_ALL	 ((uint16)(LED03_0_INTR))

#endif /* End Pins LED03_ALIASES_H */


/* [] END OF FILE */
