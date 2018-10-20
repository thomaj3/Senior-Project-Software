/*******************************************************************************
* File Name: VDAC8_0_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "VDAC8_0.h"

static VDAC8_0_backupStruct VDAC8_0_backup;


/*******************************************************************************
* Function Name: VDAC8_0_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void VDAC8_0_SaveConfig(void) 
{
    if (!((VDAC8_0_CR1 & VDAC8_0_SRC_MASK) == VDAC8_0_SRC_UDB))
    {
        VDAC8_0_backup.data_value = VDAC8_0_Data;
    }
}


/*******************************************************************************
* Function Name: VDAC8_0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void VDAC8_0_RestoreConfig(void) 
{
    if (!((VDAC8_0_CR1 & VDAC8_0_SRC_MASK) == VDAC8_0_SRC_UDB))
    {
        if((VDAC8_0_Strobe & VDAC8_0_STRB_MASK) == VDAC8_0_STRB_EN)
        {
            VDAC8_0_Strobe &= (uint8)(~VDAC8_0_STRB_MASK);
            VDAC8_0_Data = VDAC8_0_backup.data_value;
            VDAC8_0_Strobe |= VDAC8_0_STRB_EN;
        }
        else
        {
            VDAC8_0_Data = VDAC8_0_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: VDAC8_0_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  VDAC8_0_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void VDAC8_0_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(VDAC8_0_ACT_PWR_EN == (VDAC8_0_PWRMGR & VDAC8_0_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        VDAC8_0_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        VDAC8_0_backup.enableState = 0u;
    }
    
    VDAC8_0_Stop();
    VDAC8_0_SaveConfig();
}


/*******************************************************************************
* Function Name: VDAC8_0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  VDAC8_0_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void VDAC8_0_Wakeup(void) 
{
    VDAC8_0_RestoreConfig();
    
    if(VDAC8_0_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        VDAC8_0_Enable();

        /* Restore the data register */
        VDAC8_0_SetValue(VDAC8_0_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
