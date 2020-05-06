/*******************************************************************************
* File Name: Character_LCD_PM.c
* Version 1.70
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Character_LCD.h"


void Character_LCD_SaveConfig(void) ;
void Character_LCD_RestoreConfig(void) ;
extern void Character_LCD_Enable(void) ;

static Character_LCD_BACKUP_STRUCT Character_LCD_backup;

extern uint8 Character_LCD_enableState;


/*******************************************************************************
* Function Name: Character_LCD_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: Character_LCD_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: Character_LCD_Sleep
********************************************************************************
*
* Summary:
*  Prepares component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Character_LCD_Sleep(void) 
{
    Character_LCD_backup.enableState = Character_LCD_enableState;
    Character_LCD_SaveConfig();
    Character_LCD_Stop();
}


/*******************************************************************************
* Function Name: Character_LCD_Wakeup
********************************************************************************
*
* Summary:
*  Wakes component from sleep mode. Configures DMA and enables the component for
*  normal operation.
*
* Parameters:
*  Character_LCD_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Character_LCD_Wakeup(void) 
{
    Character_LCD_RestoreConfig();

    if(Character_LCD_backup.enableState == 1u)
    {
        Character_LCD_Enable();
    }
}


/* [] END OF FILE */
