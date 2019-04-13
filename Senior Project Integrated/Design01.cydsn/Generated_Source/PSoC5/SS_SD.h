/*******************************************************************************
* File Name: SS_SD.h  
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

#if !defined(CY_PINS_SS_SD_H) /* Pins SS_SD_H */
#define CY_PINS_SS_SD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS_SD_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS_SD__PORT == 15 && ((SS_SD__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS_SD_Write(uint8 value);
void    SS_SD_SetDriveMode(uint8 mode);
uint8   SS_SD_ReadDataReg(void);
uint8   SS_SD_Read(void);
void    SS_SD_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS_SD_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS_SD_SetDriveMode() function.
     *  @{
     */
        #define SS_SD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS_SD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS_SD_DM_RES_UP          PIN_DM_RES_UP
        #define SS_SD_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS_SD_DM_OD_LO           PIN_DM_OD_LO
        #define SS_SD_DM_OD_HI           PIN_DM_OD_HI
        #define SS_SD_DM_STRONG          PIN_DM_STRONG
        #define SS_SD_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS_SD_MASK               SS_SD__MASK
#define SS_SD_SHIFT              SS_SD__SHIFT
#define SS_SD_WIDTH              1u

/* Interrupt constants */
#if defined(SS_SD__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS_SD_SetInterruptMode() function.
     *  @{
     */
        #define SS_SD_INTR_NONE      (uint16)(0x0000u)
        #define SS_SD_INTR_RISING    (uint16)(0x0001u)
        #define SS_SD_INTR_FALLING   (uint16)(0x0002u)
        #define SS_SD_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS_SD_INTR_MASK      (0x01u) 
#endif /* (SS_SD__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS_SD_PS                     (* (reg8 *) SS_SD__PS)
/* Data Register */
#define SS_SD_DR                     (* (reg8 *) SS_SD__DR)
/* Port Number */
#define SS_SD_PRT_NUM                (* (reg8 *) SS_SD__PRT) 
/* Connect to Analog Globals */                                                  
#define SS_SD_AG                     (* (reg8 *) SS_SD__AG)                       
/* Analog MUX bux enable */
#define SS_SD_AMUX                   (* (reg8 *) SS_SD__AMUX) 
/* Bidirectional Enable */                                                        
#define SS_SD_BIE                    (* (reg8 *) SS_SD__BIE)
/* Bit-mask for Aliased Register Access */
#define SS_SD_BIT_MASK               (* (reg8 *) SS_SD__BIT_MASK)
/* Bypass Enable */
#define SS_SD_BYP                    (* (reg8 *) SS_SD__BYP)
/* Port wide control signals */                                                   
#define SS_SD_CTL                    (* (reg8 *) SS_SD__CTL)
/* Drive Modes */
#define SS_SD_DM0                    (* (reg8 *) SS_SD__DM0) 
#define SS_SD_DM1                    (* (reg8 *) SS_SD__DM1)
#define SS_SD_DM2                    (* (reg8 *) SS_SD__DM2) 
/* Input Buffer Disable Override */
#define SS_SD_INP_DIS                (* (reg8 *) SS_SD__INP_DIS)
/* LCD Common or Segment Drive */
#define SS_SD_LCD_COM_SEG            (* (reg8 *) SS_SD__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS_SD_LCD_EN                 (* (reg8 *) SS_SD__LCD_EN)
/* Slew Rate Control */
#define SS_SD_SLW                    (* (reg8 *) SS_SD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS_SD_PRTDSI__CAPS_SEL       (* (reg8 *) SS_SD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS_SD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS_SD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS_SD_PRTDSI__OE_SEL0        (* (reg8 *) SS_SD__PRTDSI__OE_SEL0) 
#define SS_SD_PRTDSI__OE_SEL1        (* (reg8 *) SS_SD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS_SD_PRTDSI__OUT_SEL0       (* (reg8 *) SS_SD__PRTDSI__OUT_SEL0) 
#define SS_SD_PRTDSI__OUT_SEL1       (* (reg8 *) SS_SD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS_SD_PRTDSI__SYNC_OUT       (* (reg8 *) SS_SD__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS_SD__SIO_CFG)
    #define SS_SD_SIO_HYST_EN        (* (reg8 *) SS_SD__SIO_HYST_EN)
    #define SS_SD_SIO_REG_HIFREQ     (* (reg8 *) SS_SD__SIO_REG_HIFREQ)
    #define SS_SD_SIO_CFG            (* (reg8 *) SS_SD__SIO_CFG)
    #define SS_SD_SIO_DIFF           (* (reg8 *) SS_SD__SIO_DIFF)
#endif /* (SS_SD__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS_SD__INTSTAT)
    #define SS_SD_INTSTAT            (* (reg8 *) SS_SD__INTSTAT)
    #define SS_SD_SNAP               (* (reg8 *) SS_SD__SNAP)
    
	#define SS_SD_0_INTTYPE_REG 		(* (reg8 *) SS_SD__0__INTTYPE)
#endif /* (SS_SD__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS_SD_H */


/* [] END OF FILE */
