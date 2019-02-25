/*******************************************************************************
* File Name: XP.h  
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

#if !defined(CY_PINS_XP_H) /* Pins XP_H */
#define CY_PINS_XP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "XP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 XP__PORT == 15 && ((XP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    XP_Write(uint8 value);
void    XP_SetDriveMode(uint8 mode);
uint8   XP_ReadDataReg(void);
uint8   XP_Read(void);
void    XP_SetInterruptMode(uint16 position, uint16 mode);
uint8   XP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the XP_SetDriveMode() function.
     *  @{
     */
        #define XP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define XP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define XP_DM_RES_UP          PIN_DM_RES_UP
        #define XP_DM_RES_DWN         PIN_DM_RES_DWN
        #define XP_DM_OD_LO           PIN_DM_OD_LO
        #define XP_DM_OD_HI           PIN_DM_OD_HI
        #define XP_DM_STRONG          PIN_DM_STRONG
        #define XP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define XP_MASK               XP__MASK
#define XP_SHIFT              XP__SHIFT
#define XP_WIDTH              1u

/* Interrupt constants */
#if defined(XP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in XP_SetInterruptMode() function.
     *  @{
     */
        #define XP_INTR_NONE      (uint16)(0x0000u)
        #define XP_INTR_RISING    (uint16)(0x0001u)
        #define XP_INTR_FALLING   (uint16)(0x0002u)
        #define XP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define XP_INTR_MASK      (0x01u) 
#endif /* (XP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define XP_PS                     (* (reg8 *) XP__PS)
/* Data Register */
#define XP_DR                     (* (reg8 *) XP__DR)
/* Port Number */
#define XP_PRT_NUM                (* (reg8 *) XP__PRT) 
/* Connect to Analog Globals */                                                  
#define XP_AG                     (* (reg8 *) XP__AG)                       
/* Analog MUX bux enable */
#define XP_AMUX                   (* (reg8 *) XP__AMUX) 
/* Bidirectional Enable */                                                        
#define XP_BIE                    (* (reg8 *) XP__BIE)
/* Bit-mask for Aliased Register Access */
#define XP_BIT_MASK               (* (reg8 *) XP__BIT_MASK)
/* Bypass Enable */
#define XP_BYP                    (* (reg8 *) XP__BYP)
/* Port wide control signals */                                                   
#define XP_CTL                    (* (reg8 *) XP__CTL)
/* Drive Modes */
#define XP_DM0                    (* (reg8 *) XP__DM0) 
#define XP_DM1                    (* (reg8 *) XP__DM1)
#define XP_DM2                    (* (reg8 *) XP__DM2) 
/* Input Buffer Disable Override */
#define XP_INP_DIS                (* (reg8 *) XP__INP_DIS)
/* LCD Common or Segment Drive */
#define XP_LCD_COM_SEG            (* (reg8 *) XP__LCD_COM_SEG)
/* Enable Segment LCD */
#define XP_LCD_EN                 (* (reg8 *) XP__LCD_EN)
/* Slew Rate Control */
#define XP_SLW                    (* (reg8 *) XP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define XP_PRTDSI__CAPS_SEL       (* (reg8 *) XP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define XP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) XP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define XP_PRTDSI__OE_SEL0        (* (reg8 *) XP__PRTDSI__OE_SEL0) 
#define XP_PRTDSI__OE_SEL1        (* (reg8 *) XP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define XP_PRTDSI__OUT_SEL0       (* (reg8 *) XP__PRTDSI__OUT_SEL0) 
#define XP_PRTDSI__OUT_SEL1       (* (reg8 *) XP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define XP_PRTDSI__SYNC_OUT       (* (reg8 *) XP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(XP__SIO_CFG)
    #define XP_SIO_HYST_EN        (* (reg8 *) XP__SIO_HYST_EN)
    #define XP_SIO_REG_HIFREQ     (* (reg8 *) XP__SIO_REG_HIFREQ)
    #define XP_SIO_CFG            (* (reg8 *) XP__SIO_CFG)
    #define XP_SIO_DIFF           (* (reg8 *) XP__SIO_DIFF)
#endif /* (XP__SIO_CFG) */

/* Interrupt Registers */
#if defined(XP__INTSTAT)
    #define XP_INTSTAT            (* (reg8 *) XP__INTSTAT)
    #define XP_SNAP               (* (reg8 *) XP__SNAP)
    
	#define XP_0_INTTYPE_REG 		(* (reg8 *) XP__0__INTTYPE)
#endif /* (XP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_XP_H */


/* [] END OF FILE */
