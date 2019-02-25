/*******************************************************************************
* File Name: YM.h  
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

#if !defined(CY_PINS_YM_H) /* Pins YM_H */
#define CY_PINS_YM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "YM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 YM__PORT == 15 && ((YM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    YM_Write(uint8 value);
void    YM_SetDriveMode(uint8 mode);
uint8   YM_ReadDataReg(void);
uint8   YM_Read(void);
void    YM_SetInterruptMode(uint16 position, uint16 mode);
uint8   YM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the YM_SetDriveMode() function.
     *  @{
     */
        #define YM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define YM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define YM_DM_RES_UP          PIN_DM_RES_UP
        #define YM_DM_RES_DWN         PIN_DM_RES_DWN
        #define YM_DM_OD_LO           PIN_DM_OD_LO
        #define YM_DM_OD_HI           PIN_DM_OD_HI
        #define YM_DM_STRONG          PIN_DM_STRONG
        #define YM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define YM_MASK               YM__MASK
#define YM_SHIFT              YM__SHIFT
#define YM_WIDTH              1u

/* Interrupt constants */
#if defined(YM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in YM_SetInterruptMode() function.
     *  @{
     */
        #define YM_INTR_NONE      (uint16)(0x0000u)
        #define YM_INTR_RISING    (uint16)(0x0001u)
        #define YM_INTR_FALLING   (uint16)(0x0002u)
        #define YM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define YM_INTR_MASK      (0x01u) 
#endif /* (YM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define YM_PS                     (* (reg8 *) YM__PS)
/* Data Register */
#define YM_DR                     (* (reg8 *) YM__DR)
/* Port Number */
#define YM_PRT_NUM                (* (reg8 *) YM__PRT) 
/* Connect to Analog Globals */                                                  
#define YM_AG                     (* (reg8 *) YM__AG)                       
/* Analog MUX bux enable */
#define YM_AMUX                   (* (reg8 *) YM__AMUX) 
/* Bidirectional Enable */                                                        
#define YM_BIE                    (* (reg8 *) YM__BIE)
/* Bit-mask for Aliased Register Access */
#define YM_BIT_MASK               (* (reg8 *) YM__BIT_MASK)
/* Bypass Enable */
#define YM_BYP                    (* (reg8 *) YM__BYP)
/* Port wide control signals */                                                   
#define YM_CTL                    (* (reg8 *) YM__CTL)
/* Drive Modes */
#define YM_DM0                    (* (reg8 *) YM__DM0) 
#define YM_DM1                    (* (reg8 *) YM__DM1)
#define YM_DM2                    (* (reg8 *) YM__DM2) 
/* Input Buffer Disable Override */
#define YM_INP_DIS                (* (reg8 *) YM__INP_DIS)
/* LCD Common or Segment Drive */
#define YM_LCD_COM_SEG            (* (reg8 *) YM__LCD_COM_SEG)
/* Enable Segment LCD */
#define YM_LCD_EN                 (* (reg8 *) YM__LCD_EN)
/* Slew Rate Control */
#define YM_SLW                    (* (reg8 *) YM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define YM_PRTDSI__CAPS_SEL       (* (reg8 *) YM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define YM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) YM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define YM_PRTDSI__OE_SEL0        (* (reg8 *) YM__PRTDSI__OE_SEL0) 
#define YM_PRTDSI__OE_SEL1        (* (reg8 *) YM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define YM_PRTDSI__OUT_SEL0       (* (reg8 *) YM__PRTDSI__OUT_SEL0) 
#define YM_PRTDSI__OUT_SEL1       (* (reg8 *) YM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define YM_PRTDSI__SYNC_OUT       (* (reg8 *) YM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(YM__SIO_CFG)
    #define YM_SIO_HYST_EN        (* (reg8 *) YM__SIO_HYST_EN)
    #define YM_SIO_REG_HIFREQ     (* (reg8 *) YM__SIO_REG_HIFREQ)
    #define YM_SIO_CFG            (* (reg8 *) YM__SIO_CFG)
    #define YM_SIO_DIFF           (* (reg8 *) YM__SIO_DIFF)
#endif /* (YM__SIO_CFG) */

/* Interrupt Registers */
#if defined(YM__INTSTAT)
    #define YM_INTSTAT            (* (reg8 *) YM__INTSTAT)
    #define YM_SNAP               (* (reg8 *) YM__SNAP)
    
	#define YM_0_INTTYPE_REG 		(* (reg8 *) YM__0__INTTYPE)
#endif /* (YM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_YM_H */


/* [] END OF FILE */
