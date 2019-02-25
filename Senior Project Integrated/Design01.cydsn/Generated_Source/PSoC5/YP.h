/*******************************************************************************
* File Name: YP.h  
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

#if !defined(CY_PINS_YP_H) /* Pins YP_H */
#define CY_PINS_YP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "YP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 YP__PORT == 15 && ((YP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    YP_Write(uint8 value);
void    YP_SetDriveMode(uint8 mode);
uint8   YP_ReadDataReg(void);
uint8   YP_Read(void);
void    YP_SetInterruptMode(uint16 position, uint16 mode);
uint8   YP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the YP_SetDriveMode() function.
     *  @{
     */
        #define YP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define YP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define YP_DM_RES_UP          PIN_DM_RES_UP
        #define YP_DM_RES_DWN         PIN_DM_RES_DWN
        #define YP_DM_OD_LO           PIN_DM_OD_LO
        #define YP_DM_OD_HI           PIN_DM_OD_HI
        #define YP_DM_STRONG          PIN_DM_STRONG
        #define YP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define YP_MASK               YP__MASK
#define YP_SHIFT              YP__SHIFT
#define YP_WIDTH              1u

/* Interrupt constants */
#if defined(YP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in YP_SetInterruptMode() function.
     *  @{
     */
        #define YP_INTR_NONE      (uint16)(0x0000u)
        #define YP_INTR_RISING    (uint16)(0x0001u)
        #define YP_INTR_FALLING   (uint16)(0x0002u)
        #define YP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define YP_INTR_MASK      (0x01u) 
#endif /* (YP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define YP_PS                     (* (reg8 *) YP__PS)
/* Data Register */
#define YP_DR                     (* (reg8 *) YP__DR)
/* Port Number */
#define YP_PRT_NUM                (* (reg8 *) YP__PRT) 
/* Connect to Analog Globals */                                                  
#define YP_AG                     (* (reg8 *) YP__AG)                       
/* Analog MUX bux enable */
#define YP_AMUX                   (* (reg8 *) YP__AMUX) 
/* Bidirectional Enable */                                                        
#define YP_BIE                    (* (reg8 *) YP__BIE)
/* Bit-mask for Aliased Register Access */
#define YP_BIT_MASK               (* (reg8 *) YP__BIT_MASK)
/* Bypass Enable */
#define YP_BYP                    (* (reg8 *) YP__BYP)
/* Port wide control signals */                                                   
#define YP_CTL                    (* (reg8 *) YP__CTL)
/* Drive Modes */
#define YP_DM0                    (* (reg8 *) YP__DM0) 
#define YP_DM1                    (* (reg8 *) YP__DM1)
#define YP_DM2                    (* (reg8 *) YP__DM2) 
/* Input Buffer Disable Override */
#define YP_INP_DIS                (* (reg8 *) YP__INP_DIS)
/* LCD Common or Segment Drive */
#define YP_LCD_COM_SEG            (* (reg8 *) YP__LCD_COM_SEG)
/* Enable Segment LCD */
#define YP_LCD_EN                 (* (reg8 *) YP__LCD_EN)
/* Slew Rate Control */
#define YP_SLW                    (* (reg8 *) YP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define YP_PRTDSI__CAPS_SEL       (* (reg8 *) YP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define YP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) YP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define YP_PRTDSI__OE_SEL0        (* (reg8 *) YP__PRTDSI__OE_SEL0) 
#define YP_PRTDSI__OE_SEL1        (* (reg8 *) YP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define YP_PRTDSI__OUT_SEL0       (* (reg8 *) YP__PRTDSI__OUT_SEL0) 
#define YP_PRTDSI__OUT_SEL1       (* (reg8 *) YP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define YP_PRTDSI__SYNC_OUT       (* (reg8 *) YP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(YP__SIO_CFG)
    #define YP_SIO_HYST_EN        (* (reg8 *) YP__SIO_HYST_EN)
    #define YP_SIO_REG_HIFREQ     (* (reg8 *) YP__SIO_REG_HIFREQ)
    #define YP_SIO_CFG            (* (reg8 *) YP__SIO_CFG)
    #define YP_SIO_DIFF           (* (reg8 *) YP__SIO_DIFF)
#endif /* (YP__SIO_CFG) */

/* Interrupt Registers */
#if defined(YP__INTSTAT)
    #define YP_INTSTAT            (* (reg8 *) YP__INTSTAT)
    #define YP_SNAP               (* (reg8 *) YP__SNAP)
    
	#define YP_0_INTTYPE_REG 		(* (reg8 *) YP__0__INTTYPE)
#endif /* (YP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_YP_H */


/* [] END OF FILE */
