/*******************************************************************************
* File Name: Y_Enable_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Y_Enable.h"

/* Check for removal by optimization */
#if !defined(Y_Enable_Sync_ctrl_reg__REMOVED)

static Y_Enable_BACKUP_STRUCT  Y_Enable_backup = {0u};

    
/*******************************************************************************
* Function Name: Y_Enable_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Y_Enable_SaveConfig(void) 
{
    Y_Enable_backup.controlState = Y_Enable_Control;
}


/*******************************************************************************
* Function Name: Y_Enable_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Y_Enable_RestoreConfig(void) 
{
     Y_Enable_Control = Y_Enable_backup.controlState;
}


/*******************************************************************************
* Function Name: Y_Enable_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Y_Enable_Sleep(void) 
{
    Y_Enable_SaveConfig();
}


/*******************************************************************************
* Function Name: Y_Enable_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Y_Enable_Wakeup(void)  
{
    Y_Enable_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
