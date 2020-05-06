/*******************************************************************************
* File Name: Character_LCD.c
* Version 1.70
*
* Description:
*  This file provides source code for the Character LCD component's API.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "Character_LCD.h"


void Character_LCD_Init(void) ;
void Character_LCD_Enable(void) ;


uint8 Character_LCD_enableState = 0u;

uint8 Character_LCD_initVar = 0u;

char8 const CYCODE Character_LCD_hex[16u] = "0123456789ABCDEF";

extern uint8 const CYCODE Character_LCD_customFonts[];


/*******************************************************************************
* Function Name: Character_LCD_Init
********************************************************************************
*
* Summary:
*  Perform initialization required for components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enable 4-bit interface
*        Clear the display
*        Enable auto cursor increment
*        Resets the cursor to start position
*  Also loads custom character set to LCD if it was defined in the customizer.
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
void Character_LCD_Init(void) 
{
    /* INIT CODE */
    CyDelay(40u);                                                        /* Delay 40 ms */
    Character_LCD_WrCntrlNib(Character_LCD_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */
    Character_LCD_WrCntrlNib(Character_LCD_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    CyDelay(15u);                                                        /* Delay 15 ms */
    Character_LCD_WrCntrlNib(Character_LCD_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    CyDelay(1u);                                                         /* Delay 1 ms */
    Character_LCD_WrCntrlNib(Character_LCD_DISPLAY_4_BIT_INIT);   /* Selects 4-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */

    Character_LCD_WriteControl(Character_LCD_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    Character_LCD_WriteControl(Character_LCD_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    Character_LCD_WriteControl(Character_LCD_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    Character_LCD_WriteControl(Character_LCD_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    Character_LCD_WriteControl(Character_LCD_CLEAR_DISPLAY);          /* Clear LCD Screen */
    Character_LCD_WriteControl(Character_LCD_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    Character_LCD_WriteControl(Character_LCD_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    CyDelay(5u);

    #if(Character_LCD_CUSTOM_CHAR_SET != Character_LCD_NONE)
        Character_LCD_LoadCustomFonts(Character_LCD_customFonts);
    #endif /* Character_LCD_CUSTOM_CHAR_SET != Character_LCD_NONE */
}


/*******************************************************************************
* Function Name: Character_LCD_Enable
********************************************************************************
*
* Summary:
*  Turns on the display.
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
* Theory:
*  This finction has no effect when it called first time as
*  Character_LCD_Init() turns on the LCD.
*
*******************************************************************************/
void Character_LCD_Enable(void) 
{
    Character_LCD_DisplayOn();
    Character_LCD_enableState = 1u;
}


/*******************************************************************************
* Function Name: Character_LCD_Start
********************************************************************************
*
* Summary:
*  Perform initialization required for components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enable 4-bit interface
*        Clear the display
*        Enable auto cursor increment
*        Resets the cursor to start position
*  Also loads custom character set to LCD if it was defined in the customizer.
*  If it was not the first call in this project then it just turns on the
*  display
*
*
* Parameters:
*  Character_LCD_initVar - global variable.
*
* Return:
*  Character_LCD_initVar - global variable.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Character_LCD_Start() 
{
    /* If not initialized then perform initialization */
    if(Character_LCD_initVar == 0u)
    {
        Character_LCD_Init();
        Character_LCD_initVar = 1u;
    }

    /* Turn on the LCD */
    Character_LCD_Enable();
}


/*******************************************************************************
* Function Name: Character_LCD_Stop
********************************************************************************
*
* Summary:
*  Turns off the display of the LCD screen.
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
void Character_LCD_Stop() 
{
    /* Calls LCD Off Macro */
    Character_LCD_DisplayOff();
    Character_LCD_enableState = 0u;
}


/*******************************************************************************
*  Function Name: Character_LCD_Position
********************************************************************************
*
* Summary:
*  Moves active cursor location to a point specified by the input arguments
*
* Parameters:
*  row:     Specific row of LCD module to be written
*  column:  Column of LCD module to be written
*
* Return:
*  None.
*
* Note:
*  This only applies for LCD displays which use the 2X40 address mode.
*  This results in Row 2 offset from row one by 0x28.
*  When there are more than 2 rows, each row must be fewer than 20 characters.
*
*******************************************************************************/
void Character_LCD_Position(uint8 row, uint8 column) 
{
    switch (row)
    {
        case 0:
            Character_LCD_WriteControl(Character_LCD_ROW_0_START + column);
            break;
        case 1:
            Character_LCD_WriteControl(Character_LCD_ROW_1_START + column);
            break;
        case 2:
            Character_LCD_WriteControl(Character_LCD_ROW_2_START + column);
            break;
        case 3:
            Character_LCD_WriteControl(Character_LCD_ROW_3_START + column);
            break;
        default:
            /* if default case is hit, invalid row argument was passed.*/
            break;
    }
}


/*******************************************************************************
* Function Name: Character_LCD_PrintString
********************************************************************************
*
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string:  pointer to head of char8 array to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_PrintString(char8 * string) 
{
    uint8 indexU8 = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while(current != (char8) '\0')
    {
        Character_LCD_WriteData(current);
        current = *(string + indexU8);
        indexU8++;
    }
}


/*******************************************************************************
*  Function Name: Character_LCD_PutChar
********************************************************************************
*
* Summary:
*  Writes a single character to the current cursor position of the LCD module.
*  Custom character names (_CUSTOM_0 through
*  _CUSTOM_7) are acceptable as inputs.
*
* Parameters:
*  character:  character to be written to the LCD
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_PutChar(char8 character) 
{
    Character_LCD_WriteData(character);
}


/*******************************************************************************
*  Function Name: Character_LCD_WriteData
********************************************************************************
*
* Summary:
*  Writes a data byte to the LCD module's Data Display RAM.
*
* Parameters:
*  dByte:  byte to be written to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_WriteData(uint8 dByte) 
{
    uint8 nibble;

    Character_LCD_IsReady();
    nibble = dByte >> Character_LCD_NIBBLE_SHIFT;

    /* Write high nibble */
    Character_LCD_WrDatNib(nibble);

    nibble = dByte & Character_LCD_NIBBLE_MASK;
    /* Write low nibble */
    Character_LCD_WrDatNib(nibble);
}


/*******************************************************************************
*  Function Name: Character_LCD_WriteControl
********************************************************************************
*
* Summary:
*  Writes a command byte to the LCD module.
*
* Parameters:
*  cByte:   byte to be written to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_WriteControl(uint8 cByte) 
{
    uint8 nibble;

    nibble = cByte >> Character_LCD_NIBBLE_SHIFT;

    Character_LCD_IsReady();
    nibble &= Character_LCD_NIBBLE_MASK;

    /* WrCntrlNib(High Nibble) */
    Character_LCD_WrCntrlNib(nibble);
    nibble = cByte & Character_LCD_NIBBLE_MASK;

    /* WrCntrlNib(Low Nibble) */
    Character_LCD_WrCntrlNib(nibble);
}


/*******************************************************************************
* Function Name: Character_LCD_IsReady
********************************************************************************
*
* Summary:
*  Polls LCD until the ready bit is set.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  Changes pins to High-Z.
*
*******************************************************************************/
void Character_LCD_IsReady() 
{
    uint8 value = 0u;

    /* Clear the LCD port*/
    Character_LCD_PORT_DR_REG &= ~Character_LCD_PORT_MASK ;

    /* Change Port to High-Z Status on data pins */

    /* Mask off data pins to clear old values out */
    value = Character_LCD_PORT_DM0_REG & ~Character_LCD_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM0_REG = value | (Character_LCD_HIGH_Z_DM0 & Character_LCD_DATA_MASK);

    /* Mask off data pins to clear old values out */
    value = Character_LCD_PORT_DM1_REG & ~Character_LCD_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM1_REG = value | (Character_LCD_HIGH_Z_DM1 & Character_LCD_DATA_MASK);

    /* Mask off data pins to clear old values out */
    value = Character_LCD_PORT_DM2_REG & ~Character_LCD_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM2_REG = value | (Character_LCD_HIGH_Z_DM2 & Character_LCD_DATA_MASK);

    /* Make sure RS is low */
    Character_LCD_PORT_DR_REG &= ~Character_LCD_RS;

    /* Set R/W high to read */
    Character_LCD_PORT_DR_REG |= Character_LCD_RW;

    do
    {
        /* 40 ns delay required before rising Enable and 500ns between neighbour Enables */
        CyDelayUs(0u);

        /* Set E high */
        Character_LCD_PORT_DR_REG |= Character_LCD_E;

        /* 360 ns delay the setup time for data pins */
        CyDelayUs(1u);

        /* Get port state */
        value = Character_LCD_PORT_PS_REG;

        /* Set enable low */
        Character_LCD_PORT_DR_REG &= ~Character_LCD_E;

        /* Allow time for the enable signal to transition */
        CyDelayUs(0u);
        
        /* Extract ready bit */
        value &= Character_LCD_READY_BIT;

        /* Set E high as we in 4-bit interface we need extra oparation */
        Character_LCD_PORT_DR_REG |= Character_LCD_E;

        /* 360 ns delay the setup time for data pins */
        CyDelayUs(1u);

        /* Set enable low */
        Character_LCD_PORT_DR_REG &= ~Character_LCD_E;

        /* Repeat until bit 4 is not zero. */

    } while (value != 0u);

    /* Set R/W low to write */
    Character_LCD_PORT_DR_REG &= ~Character_LCD_RW;

    /* Clear the LCD port*/
    Character_LCD_PORT_DR_REG &= ~Character_LCD_PORT_MASK ;

    /* Change Port to Output (Strong) on data pins */

    /* Mask off data pins to clear high z values out */
    value = Character_LCD_PORT_DM0_REG & (~Character_LCD_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM0_REG = value | (Character_LCD_STRONG_DM0 & Character_LCD_DATA_MASK);

    /* Mask off data pins to clear high z values out */
    value = Character_LCD_PORT_DM1_REG & (~Character_LCD_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM1_REG = value | (Character_LCD_STRONG_DM1 & Character_LCD_DATA_MASK);

    /* Mask off data pins to clear high z values out */
    value = Character_LCD_PORT_DM2_REG & (~Character_LCD_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    Character_LCD_PORT_DM2_REG = value | (Character_LCD_STRONG_DM2 & Character_LCD_DATA_MASK);
}


/*******************************************************************************
*  Function Name: Character_LCD_WrDatNib
********************************************************************************
*
* Summary:
*  Writes a data nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_WrDatNib(uint8 nibble) 
{
    Character_LCD_IsReady();

    /* RS shoul be low to select data register */
    Character_LCD_PORT_DR_REG |= Character_LCD_RS;
    /* Reset RW for write operation */
    Character_LCD_PORT_DR_REG &= ~Character_LCD_RW;

    /* Two following lines of code will provide us with 40ns delay */
    /* Clear data pins */
    Character_LCD_PORT_DR_REG &= ~Character_LCD_DATA_MASK;

    /* Write in data, bring E high*/
    Character_LCD_PORT_DR_REG |= (Character_LCD_E | (nibble << Character_LCD_PORT_SHIFT));

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    Character_LCD_PORT_DR_REG &= ~Character_LCD_E;
}


/*******************************************************************************
*  Function Name: Character_LCD_WrCntrlNib
********************************************************************************
*
* Summary:
*  Writes a control nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void Character_LCD_WrCntrlNib(uint8 nibble) 
{
    /* RS and RW shoul be low to select instruction register and  write operation respectively */
    Character_LCD_PORT_DR_REG &= ~(Character_LCD_RS | Character_LCD_RW);

    /* Two following lines of code will give provide ua with 40ns delay */
    /* Clear data pins */
    Character_LCD_PORT_DR_REG &= ~Character_LCD_DATA_MASK;

    /* Write control data and set enable signal */
    Character_LCD_PORT_DR_REG |= (Character_LCD_E | (nibble << Character_LCD_PORT_SHIFT));

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    Character_LCD_PORT_DR_REG &= ~Character_LCD_E;
}


#if(Character_LCD_CONVERSION_ROUTINES == 1u)

    /*******************************************************************************
    *  Function Name: Character_LCD_PrintHexUint8
    ********************************************************************************
    *
    * Summary:
    *  Print a byte as two ASCII characters.
    *
    * Parameters:
    *  value:  The byte to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Character_LCD_PrintHexUint8(uint8 value) 
    {
        Character_LCD_PutChar((char8) Character_LCD_hex[value >> Character_LCD_BYTE_UPPER_NIBBLE_SHIFT]);
        Character_LCD_PutChar((char8) Character_LCD_hex[value & Character_LCD_BYTE_LOWER_NIBBLE_MASK]);
    }


    /*******************************************************************************
    *  Function Name: Character_LCD_PrintHexUint16
    ********************************************************************************
    *
    * Summary:
    *  Print a uint16 as four ASCII characters.
    *
    * Parameters:
    *  value:   The uint16 to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Character_LCD_PrintHexUint16(uint16 value) 
    {
        Character_LCD_PrintHexUint8(value >> Character_LCD_U16_UPPER_BYTE_SHIFT);
        Character_LCD_PrintHexUint8(value & Character_LCD_U16_LOWER_BYTE_MASK);
    }


    /*******************************************************************************
    *  Function Name: Character_LCD_PrintDecUint16
    ********************************************************************************
    *
    * Summary:
    *  Print an uint32 value as a left-justified decimal value.
    *
    * Parameters:
    *  value:  The byte to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Character_LCD_PrintDecUint16(uint16 value) 
    {

        char8 number[Character_LCD_NUMBER_OF_REMAINDERS];
        char8 temp[Character_LCD_NUMBER_OF_REMAINDERS];

        uint8 index = 0u;
        uint8 numDigits = 0u;


        /* Load these in reverse order */
        while(value >= Character_LCD_TEN)
        {
            temp[index] = (value % Character_LCD_TEN) + '0';
            value /= Character_LCD_TEN;
            index++;
        }

        temp[index] = (value % Character_LCD_TEN) + '0';
        numDigits = index;

        /* While index is greater than or equal to zero */
        while (index != 0xFFu)
        {
            number[numDigits - index] = temp[index];
            index--;
        }

        /* Null Termination */
        number[numDigits + 1u] = (char8) 0;

        /* Print out number */
        Character_LCD_PrintString(number);
    }

#endif /* Character_LCD_CONVERSION_ROUTINES == 1u */


/* [] END OF FILE */
