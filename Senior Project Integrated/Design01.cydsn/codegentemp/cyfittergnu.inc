/*******************************************************************************
* File Name: cyfittergnu.inc
* 
* PSoC Creator  4.2
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* SS */
.set SS__0__INTTYPE, CYREG_PICU0_INTTYPE1
.set SS__0__MASK, 0x02
.set SS__0__PC, CYREG_PRT0_PC1
.set SS__0__PORT, 0
.set SS__0__SHIFT, 1
.set SS__AG, CYREG_PRT0_AG
.set SS__AMUX, CYREG_PRT0_AMUX
.set SS__BIE, CYREG_PRT0_BIE
.set SS__BIT_MASK, CYREG_PRT0_BIT_MASK
.set SS__BYP, CYREG_PRT0_BYP
.set SS__CTL, CYREG_PRT0_CTL
.set SS__DM0, CYREG_PRT0_DM0
.set SS__DM1, CYREG_PRT0_DM1
.set SS__DM2, CYREG_PRT0_DM2
.set SS__DR, CYREG_PRT0_DR
.set SS__INP_DIS, CYREG_PRT0_INP_DIS
.set SS__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set SS__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set SS__LCD_EN, CYREG_PRT0_LCD_EN
.set SS__MASK, 0x02
.set SS__PORT, 0
.set SS__PRT, CYREG_PRT0_PRT
.set SS__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set SS__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set SS__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set SS__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set SS__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set SS__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set SS__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set SS__PS, CYREG_PRT0_PS
.set SS__SHIFT, 1
.set SS__SLW, CYREG_PRT0_SLW

/* CLK */
.set CLK__0__INTTYPE, CYREG_PICU0_INTTYPE7
.set CLK__0__MASK, 0x80
.set CLK__0__PC, CYREG_PRT0_PC7
.set CLK__0__PORT, 0
.set CLK__0__SHIFT, 7
.set CLK__AG, CYREG_PRT0_AG
.set CLK__AMUX, CYREG_PRT0_AMUX
.set CLK__BIE, CYREG_PRT0_BIE
.set CLK__BIT_MASK, CYREG_PRT0_BIT_MASK
.set CLK__BYP, CYREG_PRT0_BYP
.set CLK__CTL, CYREG_PRT0_CTL
.set CLK__DM0, CYREG_PRT0_DM0
.set CLK__DM1, CYREG_PRT0_DM1
.set CLK__DM2, CYREG_PRT0_DM2
.set CLK__DR, CYREG_PRT0_DR
.set CLK__INP_DIS, CYREG_PRT0_INP_DIS
.set CLK__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set CLK__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set CLK__LCD_EN, CYREG_PRT0_LCD_EN
.set CLK__MASK, 0x80
.set CLK__PORT, 0
.set CLK__PRT, CYREG_PRT0_PRT
.set CLK__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set CLK__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set CLK__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set CLK__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set CLK__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set CLK__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set CLK__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set CLK__PS, CYREG_PRT0_PS
.set CLK__SHIFT, 7
.set CLK__SLW, CYREG_PRT0_SLW

/* D_C */
.set D_C__0__INTTYPE, CYREG_PICU0_INTTYPE0
.set D_C__0__MASK, 0x01
.set D_C__0__PC, CYREG_PRT0_PC0
.set D_C__0__PORT, 0
.set D_C__0__SHIFT, 0
.set D_C__AG, CYREG_PRT0_AG
.set D_C__AMUX, CYREG_PRT0_AMUX
.set D_C__BIE, CYREG_PRT0_BIE
.set D_C__BIT_MASK, CYREG_PRT0_BIT_MASK
.set D_C__BYP, CYREG_PRT0_BYP
.set D_C__CTL, CYREG_PRT0_CTL
.set D_C__DM0, CYREG_PRT0_DM0
.set D_C__DM1, CYREG_PRT0_DM1
.set D_C__DM2, CYREG_PRT0_DM2
.set D_C__DR, CYREG_PRT0_DR
.set D_C__INP_DIS, CYREG_PRT0_INP_DIS
.set D_C__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set D_C__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set D_C__LCD_EN, CYREG_PRT0_LCD_EN
.set D_C__MASK, 0x01
.set D_C__PORT, 0
.set D_C__PRT, CYREG_PRT0_PRT
.set D_C__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set D_C__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set D_C__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set D_C__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set D_C__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set D_C__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set D_C__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set D_C__PS, CYREG_PRT0_PS
.set D_C__SHIFT, 0
.set D_C__SLW, CYREG_PRT0_SLW

/* MISO */
.set MISO__0__INTTYPE, CYREG_PICU0_INTTYPE6
.set MISO__0__MASK, 0x40
.set MISO__0__PC, CYREG_PRT0_PC6
.set MISO__0__PORT, 0
.set MISO__0__SHIFT, 6
.set MISO__AG, CYREG_PRT0_AG
.set MISO__AMUX, CYREG_PRT0_AMUX
.set MISO__BIE, CYREG_PRT0_BIE
.set MISO__BIT_MASK, CYREG_PRT0_BIT_MASK
.set MISO__BYP, CYREG_PRT0_BYP
.set MISO__CTL, CYREG_PRT0_CTL
.set MISO__DM0, CYREG_PRT0_DM0
.set MISO__DM1, CYREG_PRT0_DM1
.set MISO__DM2, CYREG_PRT0_DM2
.set MISO__DR, CYREG_PRT0_DR
.set MISO__INP_DIS, CYREG_PRT0_INP_DIS
.set MISO__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set MISO__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set MISO__LCD_EN, CYREG_PRT0_LCD_EN
.set MISO__MASK, 0x40
.set MISO__PORT, 0
.set MISO__PRT, CYREG_PRT0_PRT
.set MISO__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set MISO__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set MISO__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set MISO__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set MISO__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set MISO__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set MISO__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set MISO__PS, CYREG_PRT0_PS
.set MISO__SHIFT, 6
.set MISO__SLW, CYREG_PRT0_SLW

/* MOSI */
.set MOSI__0__INTTYPE, CYREG_PICU0_INTTYPE5
.set MOSI__0__MASK, 0x20
.set MOSI__0__PC, CYREG_PRT0_PC5
.set MOSI__0__PORT, 0
.set MOSI__0__SHIFT, 5
.set MOSI__AG, CYREG_PRT0_AG
.set MOSI__AMUX, CYREG_PRT0_AMUX
.set MOSI__BIE, CYREG_PRT0_BIE
.set MOSI__BIT_MASK, CYREG_PRT0_BIT_MASK
.set MOSI__BYP, CYREG_PRT0_BYP
.set MOSI__CTL, CYREG_PRT0_CTL
.set MOSI__DM0, CYREG_PRT0_DM0
.set MOSI__DM1, CYREG_PRT0_DM1
.set MOSI__DM2, CYREG_PRT0_DM2
.set MOSI__DR, CYREG_PRT0_DR
.set MOSI__INP_DIS, CYREG_PRT0_INP_DIS
.set MOSI__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set MOSI__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set MOSI__LCD_EN, CYREG_PRT0_LCD_EN
.set MOSI__MASK, 0x20
.set MOSI__PORT, 0
.set MOSI__PRT, CYREG_PRT0_PRT
.set MOSI__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set MOSI__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set MOSI__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set MOSI__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set MOSI__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set MOSI__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set MOSI__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set MOSI__PS, CYREG_PRT0_PS
.set MOSI__SHIFT, 5
.set MOSI__SLW, CYREG_PRT0_SLW

/* SPIM */
.set SPIM_BSPIM_BitCounter__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB01_02_ACTL
.set SPIM_BSPIM_BitCounter__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB01_02_CTL
.set SPIM_BSPIM_BitCounter__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB01_02_CTL
.set SPIM_BSPIM_BitCounter__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB01_02_CTL
.set SPIM_BSPIM_BitCounter__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB01_02_CTL
.set SPIM_BSPIM_BitCounter__16BIT_MASK_MASK_REG, CYREG_B0_UDB01_02_MSK
.set SPIM_BSPIM_BitCounter__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB01_02_MSK
.set SPIM_BSPIM_BitCounter__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB01_02_MSK
.set SPIM_BSPIM_BitCounter__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB01_02_MSK
.set SPIM_BSPIM_BitCounter__CONTROL_AUX_CTL_REG, CYREG_B0_UDB01_ACTL
.set SPIM_BSPIM_BitCounter__CONTROL_REG, CYREG_B0_UDB01_CTL
.set SPIM_BSPIM_BitCounter__CONTROL_ST_REG, CYREG_B0_UDB01_ST_CTL
.set SPIM_BSPIM_BitCounter__COUNT_REG, CYREG_B0_UDB01_CTL
.set SPIM_BSPIM_BitCounter__COUNT_ST_REG, CYREG_B0_UDB01_ST_CTL
.set SPIM_BSPIM_BitCounter__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_BitCounter__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_BitCounter__PERIOD_REG, CYREG_B0_UDB01_MSK
.set SPIM_BSPIM_BitCounter_ST__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB01_02_ACTL
.set SPIM_BSPIM_BitCounter_ST__16BIT_STATUS_REG, CYREG_B0_UDB01_02_ST
.set SPIM_BSPIM_BitCounter_ST__MASK_REG, CYREG_B0_UDB01_MSK
.set SPIM_BSPIM_BitCounter_ST__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_BitCounter_ST__PER_ST_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_BitCounter_ST__STATUS_AUX_CTL_REG, CYREG_B0_UDB01_ACTL
.set SPIM_BSPIM_BitCounter_ST__STATUS_CNT_REG, CYREG_B0_UDB01_ST_CTL
.set SPIM_BSPIM_BitCounter_ST__STATUS_CONTROL_REG, CYREG_B0_UDB01_ST_CTL
.set SPIM_BSPIM_BitCounter_ST__STATUS_REG, CYREG_B0_UDB01_ST
.set SPIM_BSPIM_RxStsReg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB02_03_ACTL
.set SPIM_BSPIM_RxStsReg__16BIT_STATUS_REG, CYREG_B0_UDB02_03_ST
.set SPIM_BSPIM_RxStsReg__4__MASK, 0x10
.set SPIM_BSPIM_RxStsReg__4__POS, 4
.set SPIM_BSPIM_RxStsReg__5__MASK, 0x20
.set SPIM_BSPIM_RxStsReg__5__POS, 5
.set SPIM_BSPIM_RxStsReg__6__MASK, 0x40
.set SPIM_BSPIM_RxStsReg__6__POS, 6
.set SPIM_BSPIM_RxStsReg__MASK, 0x70
.set SPIM_BSPIM_RxStsReg__MASK_REG, CYREG_B0_UDB02_MSK
.set SPIM_BSPIM_RxStsReg__STATUS_AUX_CTL_REG, CYREG_B0_UDB02_ACTL
.set SPIM_BSPIM_RxStsReg__STATUS_REG, CYREG_B0_UDB02_ST
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_A0_REG, CYREG_B0_UDB01_02_A0
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_A1_REG, CYREG_B0_UDB01_02_A1
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_D0_REG, CYREG_B0_UDB01_02_D0
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_D1_REG, CYREG_B0_UDB01_02_D1
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB01_02_ACTL
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_F0_REG, CYREG_B0_UDB01_02_F0
.set SPIM_BSPIM_sR8_Dp_u0__16BIT_F1_REG, CYREG_B0_UDB01_02_F1
.set SPIM_BSPIM_sR8_Dp_u0__A0_A1_REG, CYREG_B0_UDB01_A0_A1
.set SPIM_BSPIM_sR8_Dp_u0__A0_REG, CYREG_B0_UDB01_A0
.set SPIM_BSPIM_sR8_Dp_u0__A1_REG, CYREG_B0_UDB01_A1
.set SPIM_BSPIM_sR8_Dp_u0__D0_D1_REG, CYREG_B0_UDB01_D0_D1
.set SPIM_BSPIM_sR8_Dp_u0__D0_REG, CYREG_B0_UDB01_D0
.set SPIM_BSPIM_sR8_Dp_u0__D1_REG, CYREG_B0_UDB01_D1
.set SPIM_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG, CYREG_B0_UDB01_ACTL
.set SPIM_BSPIM_sR8_Dp_u0__F0_F1_REG, CYREG_B0_UDB01_F0_F1
.set SPIM_BSPIM_sR8_Dp_u0__F0_REG, CYREG_B0_UDB01_F0
.set SPIM_BSPIM_sR8_Dp_u0__F1_REG, CYREG_B0_UDB01_F1
.set SPIM_BSPIM_sR8_Dp_u0__MSK_DP_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_sR8_Dp_u0__PER_DP_AUX_CTL_REG, CYREG_B0_UDB01_MSK_ACTL
.set SPIM_BSPIM_TxStsReg__0__MASK, 0x01
.set SPIM_BSPIM_TxStsReg__0__POS, 0
.set SPIM_BSPIM_TxStsReg__1__MASK, 0x02
.set SPIM_BSPIM_TxStsReg__1__POS, 1
.set SPIM_BSPIM_TxStsReg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB03_04_ACTL
.set SPIM_BSPIM_TxStsReg__16BIT_STATUS_REG, CYREG_B0_UDB03_04_ST
.set SPIM_BSPIM_TxStsReg__2__MASK, 0x04
.set SPIM_BSPIM_TxStsReg__2__POS, 2
.set SPIM_BSPIM_TxStsReg__3__MASK, 0x08
.set SPIM_BSPIM_TxStsReg__3__POS, 3
.set SPIM_BSPIM_TxStsReg__4__MASK, 0x10
.set SPIM_BSPIM_TxStsReg__4__POS, 4
.set SPIM_BSPIM_TxStsReg__MASK, 0x1F
.set SPIM_BSPIM_TxStsReg__MASK_REG, CYREG_B0_UDB03_MSK
.set SPIM_BSPIM_TxStsReg__STATUS_AUX_CTL_REG, CYREG_B0_UDB03_ACTL
.set SPIM_BSPIM_TxStsReg__STATUS_REG, CYREG_B0_UDB03_ST

/* Clock */
.set Clock__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set Clock__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set Clock__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set Clock__CFG2_SRC_SEL_MASK, 0x07
.set Clock__INDEX, 0x00
.set Clock__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set Clock__PM_ACT_MSK, 0x01
.set Clock__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set Clock__PM_STBY_MSK, 0x01

/* Reset */
.set Reset__0__INTTYPE, CYREG_PICU15_INTTYPE5
.set Reset__0__MASK, 0x20
.set Reset__0__PC, CYREG_IO_PC_PRT15_PC5
.set Reset__0__PORT, 15
.set Reset__0__SHIFT, 5
.set Reset__AG, CYREG_PRT15_AG
.set Reset__AMUX, CYREG_PRT15_AMUX
.set Reset__BIE, CYREG_PRT15_BIE
.set Reset__BIT_MASK, CYREG_PRT15_BIT_MASK
.set Reset__BYP, CYREG_PRT15_BYP
.set Reset__CTL, CYREG_PRT15_CTL
.set Reset__DM0, CYREG_PRT15_DM0
.set Reset__DM1, CYREG_PRT15_DM1
.set Reset__DM2, CYREG_PRT15_DM2
.set Reset__DR, CYREG_PRT15_DR
.set Reset__INP_DIS, CYREG_PRT15_INP_DIS
.set Reset__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU15_BASE
.set Reset__LCD_COM_SEG, CYREG_PRT15_LCD_COM_SEG
.set Reset__LCD_EN, CYREG_PRT15_LCD_EN
.set Reset__MASK, 0x20
.set Reset__PORT, 15
.set Reset__PRT, CYREG_PRT15_PRT
.set Reset__PRTDSI__CAPS_SEL, CYREG_PRT15_CAPS_SEL
.set Reset__PRTDSI__DBL_SYNC_IN, CYREG_PRT15_DBL_SYNC_IN
.set Reset__PRTDSI__OE_SEL0, CYREG_PRT15_OE_SEL0
.set Reset__PRTDSI__OE_SEL1, CYREG_PRT15_OE_SEL1
.set Reset__PRTDSI__OUT_SEL0, CYREG_PRT15_OUT_SEL0
.set Reset__PRTDSI__OUT_SEL1, CYREG_PRT15_OUT_SEL1
.set Reset__PRTDSI__SYNC_OUT, CYREG_PRT15_SYNC_OUT
.set Reset__PS, CYREG_PRT15_PS
.set Reset__SHIFT, 5
.set Reset__SLW, CYREG_PRT15_SLW

/* Pin_DS */
.set Pin_DS__0__INTTYPE, CYREG_PICU3_INTTYPE5
.set Pin_DS__0__MASK, 0x20
.set Pin_DS__0__PC, CYREG_PRT3_PC5
.set Pin_DS__0__PORT, 3
.set Pin_DS__0__SHIFT, 5
.set Pin_DS__AG, CYREG_PRT3_AG
.set Pin_DS__AMUX, CYREG_PRT3_AMUX
.set Pin_DS__BIE, CYREG_PRT3_BIE
.set Pin_DS__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_DS__BYP, CYREG_PRT3_BYP
.set Pin_DS__CTL, CYREG_PRT3_CTL
.set Pin_DS__DM0, CYREG_PRT3_DM0
.set Pin_DS__DM1, CYREG_PRT3_DM1
.set Pin_DS__DM2, CYREG_PRT3_DM2
.set Pin_DS__DR, CYREG_PRT3_DR
.set Pin_DS__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_DS__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_DS__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_DS__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_DS__MASK, 0x20
.set Pin_DS__PORT, 3
.set Pin_DS__PRT, CYREG_PRT3_PRT
.set Pin_DS__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_DS__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_DS__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_DS__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_DS__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_DS__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_DS__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_DS__PS, CYREG_PRT3_PS
.set Pin_DS__SHIFT, 5
.set Pin_DS__SLW, CYREG_PRT3_SLW

/* Pin_GS */
.set Pin_GS__0__INTTYPE, CYREG_PICU3_INTTYPE4
.set Pin_GS__0__MASK, 0x10
.set Pin_GS__0__PC, CYREG_PRT3_PC4
.set Pin_GS__0__PORT, 3
.set Pin_GS__0__SHIFT, 4
.set Pin_GS__AG, CYREG_PRT3_AG
.set Pin_GS__AMUX, CYREG_PRT3_AMUX
.set Pin_GS__BIE, CYREG_PRT3_BIE
.set Pin_GS__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_GS__BYP, CYREG_PRT3_BYP
.set Pin_GS__CTL, CYREG_PRT3_CTL
.set Pin_GS__DM0, CYREG_PRT3_DM0
.set Pin_GS__DM1, CYREG_PRT3_DM1
.set Pin_GS__DM2, CYREG_PRT3_DM2
.set Pin_GS__DR, CYREG_PRT3_DR
.set Pin_GS__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_GS__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_GS__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_GS__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_GS__MASK, 0x10
.set Pin_GS__PORT, 3
.set Pin_GS__PRT, CYREG_PRT3_PRT
.set Pin_GS__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_GS__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_GS__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_GS__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_GS__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_GS__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_GS__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_GS__PS, CYREG_PRT3_PS
.set Pin_GS__SHIFT, 4
.set Pin_GS__SLW, CYREG_PRT3_SLW

/* Pin_ID */
.set Pin_ID__0__INTTYPE, CYREG_PICU3_INTTYPE3
.set Pin_ID__0__MASK, 0x08
.set Pin_ID__0__PC, CYREG_PRT3_PC3
.set Pin_ID__0__PORT, 3
.set Pin_ID__0__SHIFT, 3
.set Pin_ID__AG, CYREG_PRT3_AG
.set Pin_ID__AMUX, CYREG_PRT3_AMUX
.set Pin_ID__BIE, CYREG_PRT3_BIE
.set Pin_ID__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_ID__BYP, CYREG_PRT3_BYP
.set Pin_ID__CTL, CYREG_PRT3_CTL
.set Pin_ID__DM0, CYREG_PRT3_DM0
.set Pin_ID__DM1, CYREG_PRT3_DM1
.set Pin_ID__DM2, CYREG_PRT3_DM2
.set Pin_ID__DR, CYREG_PRT3_DR
.set Pin_ID__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_ID__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_ID__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_ID__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_ID__MASK, 0x08
.set Pin_ID__PORT, 3
.set Pin_ID__PRT, CYREG_PRT3_PRT
.set Pin_ID__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_ID__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_ID__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_ID__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_ID__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_ID__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_ID__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_ID__PS, CYREG_PRT3_PS
.set Pin_ID__SHIFT, 3
.set Pin_ID__SLW, CYREG_PRT3_SLW

/* VDAC8_DS */
.set VDAC8_DS_viDAC8__CR0, CYREG_DAC3_CR0
.set VDAC8_DS_viDAC8__CR1, CYREG_DAC3_CR1
.set VDAC8_DS_viDAC8__D, CYREG_DAC3_D
.set VDAC8_DS_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_DS_viDAC8__PM_ACT_MSK, 0x08
.set VDAC8_DS_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_DS_viDAC8__PM_STBY_MSK, 0x08
.set VDAC8_DS_viDAC8__STROBE, CYREG_DAC3_STROBE
.set VDAC8_DS_viDAC8__SW0, CYREG_DAC3_SW0
.set VDAC8_DS_viDAC8__SW2, CYREG_DAC3_SW2
.set VDAC8_DS_viDAC8__SW3, CYREG_DAC3_SW3
.set VDAC8_DS_viDAC8__SW4, CYREG_DAC3_SW4
.set VDAC8_DS_viDAC8__TR, CYREG_DAC3_TR
.set VDAC8_DS_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC3_M1
.set VDAC8_DS_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC3_M2
.set VDAC8_DS_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC3_M3
.set VDAC8_DS_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC3_M4
.set VDAC8_DS_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC3_M5
.set VDAC8_DS_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC3_M6
.set VDAC8_DS_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC3_M7
.set VDAC8_DS_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC3_M8
.set VDAC8_DS_viDAC8__TST, CYREG_DAC3_TST

/* VDAC8_GS */
.set VDAC8_GS_viDAC8__CR0, CYREG_DAC2_CR0
.set VDAC8_GS_viDAC8__CR1, CYREG_DAC2_CR1
.set VDAC8_GS_viDAC8__D, CYREG_DAC2_D
.set VDAC8_GS_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_GS_viDAC8__PM_ACT_MSK, 0x04
.set VDAC8_GS_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_GS_viDAC8__PM_STBY_MSK, 0x04
.set VDAC8_GS_viDAC8__STROBE, CYREG_DAC2_STROBE
.set VDAC8_GS_viDAC8__SW0, CYREG_DAC2_SW0
.set VDAC8_GS_viDAC8__SW2, CYREG_DAC2_SW2
.set VDAC8_GS_viDAC8__SW3, CYREG_DAC2_SW3
.set VDAC8_GS_viDAC8__SW4, CYREG_DAC2_SW4
.set VDAC8_GS_viDAC8__TR, CYREG_DAC2_TR
.set VDAC8_GS_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC2_M1
.set VDAC8_GS_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC2_M2
.set VDAC8_GS_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC2_M3
.set VDAC8_GS_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC2_M4
.set VDAC8_GS_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC2_M5
.set VDAC8_GS_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC2_M6
.set VDAC8_GS_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC2_M7
.set VDAC8_GS_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC2_M8
.set VDAC8_GS_viDAC8__TST, CYREG_DAC2_TST

/* ADC_SAR_1 */
.set ADC_SAR_1_ADC_SAR__CLK, CYREG_SAR1_CLK
.set ADC_SAR_1_ADC_SAR__CSR0, CYREG_SAR1_CSR0
.set ADC_SAR_1_ADC_SAR__CSR1, CYREG_SAR1_CSR1
.set ADC_SAR_1_ADC_SAR__CSR2, CYREG_SAR1_CSR2
.set ADC_SAR_1_ADC_SAR__CSR3, CYREG_SAR1_CSR3
.set ADC_SAR_1_ADC_SAR__CSR4, CYREG_SAR1_CSR4
.set ADC_SAR_1_ADC_SAR__CSR5, CYREG_SAR1_CSR5
.set ADC_SAR_1_ADC_SAR__CSR6, CYREG_SAR1_CSR6
.set ADC_SAR_1_ADC_SAR__PM_ACT_CFG, CYREG_PM_ACT_CFG11
.set ADC_SAR_1_ADC_SAR__PM_ACT_MSK, 0x02
.set ADC_SAR_1_ADC_SAR__PM_STBY_CFG, CYREG_PM_STBY_CFG11
.set ADC_SAR_1_ADC_SAR__PM_STBY_MSK, 0x02
.set ADC_SAR_1_ADC_SAR__SW0, CYREG_SAR1_SW0
.set ADC_SAR_1_ADC_SAR__SW2, CYREG_SAR1_SW2
.set ADC_SAR_1_ADC_SAR__SW3, CYREG_SAR1_SW3
.set ADC_SAR_1_ADC_SAR__SW4, CYREG_SAR1_SW4
.set ADC_SAR_1_ADC_SAR__SW6, CYREG_SAR1_SW6
.set ADC_SAR_1_ADC_SAR__TR0, CYREG_SAR1_TR0
.set ADC_SAR_1_ADC_SAR__WRK0, CYREG_SAR1_WRK0
.set ADC_SAR_1_ADC_SAR__WRK1, CYREG_SAR1_WRK1
.set ADC_SAR_1_IRQ__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set ADC_SAR_1_IRQ__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set ADC_SAR_1_IRQ__INTC_MASK, 0x01
.set ADC_SAR_1_IRQ__INTC_NUMBER, 0
.set ADC_SAR_1_IRQ__INTC_PRIOR_NUM, 7
.set ADC_SAR_1_IRQ__INTC_PRIOR_REG, CYREG_NVIC_PRI_0
.set ADC_SAR_1_IRQ__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set ADC_SAR_1_IRQ__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0
.set ADC_SAR_1_theACLK__CFG0, CYREG_CLKDIST_ACFG0_CFG0
.set ADC_SAR_1_theACLK__CFG1, CYREG_CLKDIST_ACFG0_CFG1
.set ADC_SAR_1_theACLK__CFG2, CYREG_CLKDIST_ACFG0_CFG2
.set ADC_SAR_1_theACLK__CFG2_SRC_SEL_MASK, 0x07
.set ADC_SAR_1_theACLK__CFG3, CYREG_CLKDIST_ACFG0_CFG3
.set ADC_SAR_1_theACLK__CFG3_PHASE_DLY_MASK, 0x0F
.set ADC_SAR_1_theACLK__INDEX, 0x00
.set ADC_SAR_1_theACLK__PM_ACT_CFG, CYREG_PM_ACT_CFG1
.set ADC_SAR_1_theACLK__PM_ACT_MSK, 0x01
.set ADC_SAR_1_theACLK__PM_STBY_CFG, CYREG_PM_STBY_CFG1
.set ADC_SAR_1_theACLK__PM_STBY_MSK, 0x01

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 24000000
.set BCLK__BUS_CLK__KHZ, 24000
.set BCLK__BUS_CLK__MHZ, 24
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PSOC4A, 18
.set CYDEV_CHIP_DIE_PSOC5LP, 2
.set CYDEV_CHIP_DIE_PSOC5TM, 3
.set CYDEV_CHIP_DIE_TMA4, 4
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_FM0P, 5
.set CYDEV_CHIP_FAMILY_FM3, 6
.set CYDEV_CHIP_FAMILY_FM4, 7
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_PSOC6, 4
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E161069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 18
.set CYDEV_CHIP_MEMBER_4D, 13
.set CYDEV_CHIP_MEMBER_4E, 6
.set CYDEV_CHIP_MEMBER_4F, 19
.set CYDEV_CHIP_MEMBER_4G, 4
.set CYDEV_CHIP_MEMBER_4H, 17
.set CYDEV_CHIP_MEMBER_4I, 23
.set CYDEV_CHIP_MEMBER_4J, 14
.set CYDEV_CHIP_MEMBER_4K, 15
.set CYDEV_CHIP_MEMBER_4L, 22
.set CYDEV_CHIP_MEMBER_4M, 21
.set CYDEV_CHIP_MEMBER_4N, 10
.set CYDEV_CHIP_MEMBER_4O, 7
.set CYDEV_CHIP_MEMBER_4P, 20
.set CYDEV_CHIP_MEMBER_4Q, 12
.set CYDEV_CHIP_MEMBER_4R, 8
.set CYDEV_CHIP_MEMBER_4S, 11
.set CYDEV_CHIP_MEMBER_4T, 9
.set CYDEV_CHIP_MEMBER_4U, 5
.set CYDEV_CHIP_MEMBER_4V, 16
.set CYDEV_CHIP_MEMBER_5A, 3
.set CYDEV_CHIP_MEMBER_5B, 2
.set CYDEV_CHIP_MEMBER_6A, 24
.set CYDEV_CHIP_MEMBER_FM3, 28
.set CYDEV_CHIP_MEMBER_FM4, 29
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1, 25
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2, 26
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3, 27
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES0, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES1, 1
.set CYDEV_CHIP_REV_PSOC5TM_PRODUCTION, 1
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4P_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Q_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4R_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4S_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4T_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4V_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_6A_ES, 17
.set CYDEV_CHIP_REVISION_6A_NO_UDB, 33
.set CYDEV_CHIP_REVISION_6A_PRODUCTION, 33
.set CYDEV_CHIP_REVISION_FM3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_FM4_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000001
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x0800
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000000
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif