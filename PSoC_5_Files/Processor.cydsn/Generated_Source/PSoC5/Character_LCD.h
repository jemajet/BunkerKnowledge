/*******************************************************************************
* File Name: Character_LCD.h
* Version 1.70
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_Character_LCD_H)
#define CY_CHARLCD_Character_LCD_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Character_LCD_CONVERSION_ROUTINES     (1u)
#define Character_LCD_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define Character_LCD_NONE                     (0u)    /* No Custom Fonts      */
#define Character_LCD_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define Character_LCD_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define Character_LCD_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct _Character_LCD_backupStruct
{
    uint8 enableState;
} Character_LCD_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void Character_LCD_Start(void) ;
void Character_LCD_Stop(void) ;
void Character_LCD_WriteControl(uint8 cByte) ;
void Character_LCD_WriteData(uint8 dByte) ;
void Character_LCD_PrintString(char8 *string) ;
void Character_LCD_Position(uint8 row, uint8 column) ;
void Character_LCD_PutChar(char8 character) ;
void Character_LCD_IsReady(void) ;
void Character_LCD_WrDatNib(uint8 nibble) ;
void Character_LCD_WrCntrlNib(uint8 nibble) ;
void Character_LCD_Sleep(void) ;
void Character_LCD_Wakeup(void) ;

#if((Character_LCD_CUSTOM_CHAR_SET == Character_LCD_VERTICAL_BG) || \
                (Character_LCD_CUSTOM_CHAR_SET == Character_LCD_HORIZONTAL_BG))

    void  Character_LCD_LoadCustomFonts(const uint8 * customData)
                        ;

    void  Character_LCD_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void Character_LCD_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((Character_LCD_CUSTOM_CHAR_SET == Character_LCD_VERTICAL_BG) */

#if(Character_LCD_CUSTOM_CHAR_SET == Character_LCD_USER_DEFINED)

    void Character_LCD_LoadCustomFonts(const uint8 * customData)
                            ;

#endif /* ((Character_LCD_CUSTOM_CHAR_SET == Character_LCD_USER_DEFINED) */

#if(Character_LCD_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void Character_LCD_PrintHexUint8(uint8 value) ;
    void Character_LCD_PrintHexUint16(uint16 value) ;
    void Character_LCD_PrintDecUint16(uint16 value) ;

    #define Character_LCD_PrintNumber(x)       Character_LCD_PrintDecUint16(x)
    #define Character_LCD_PrintInt8(x)         Character_LCD_PrintHexUint8(x)
    #define Character_LCD_PrintInt16(x)        Character_LCD_PrintHexUint16(x)

#endif /* Character_LCD_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define Character_LCD_ClearDisplay() Character_LCD_WriteControl(Character_LCD_CLEAR_DISPLAY)

/* Off Macro */
#define Character_LCD_DisplayOff() Character_LCD_WriteControl(Character_LCD_DISPLAY_CURSOR_OFF)

/* On Macro */
#define Character_LCD_DisplayOn() Character_LCD_WriteControl(Character_LCD_DISPLAY_ON_CURSOR_OFF)


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define Character_LCD_DISPLAY_8_BIT_INIT       (0x03u)
#define Character_LCD_DISPLAY_4_BIT_INIT       (0x02u)
#define Character_LCD_DISPLAY_CURSOR_OFF       (0x08u)
#define Character_LCD_CLEAR_DISPLAY            (0x01u)
#define Character_LCD_CURSOR_AUTO_INCR_ON      (0x06u)
#define Character_LCD_DISPLAY_CURSOR_ON        (0x0Eu)
#define Character_LCD_DISPLAY_2_LINES_5x10     (0x2Cu)
#define Character_LCD_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define Character_LCD_RESET_CURSOR_POSITION    (0x03u)
#define Character_LCD_CURSOR_WINK              (0x0Du)
#define Character_LCD_CURSOR_BLINK             (0x0Fu)
#define Character_LCD_CURSOR_SH_LEFT           (0x10u)
#define Character_LCD_CURSOR_SH_RIGHT          (0x14u)
#define Character_LCD_CURSOR_HOME              (0x02u)
#define Character_LCD_CURSOR_LEFT              (0x04u)
#define Character_LCD_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define Character_LCD_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define Character_LCD_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define Character_LCD_CHARACTER_WIDTH          (0x05u)
#define Character_LCD_CHARACTER_HEIGHT         (0x08u)

#if(Character_LCD_CONVERSION_ROUTINES == 1u)
    #define Character_LCD_NUMBER_OF_REMAINDERS (0x05u)
    #define Character_LCD_TEN                  (0x0Au)
#endif /* Character_LCD_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define Character_LCD_NIBBLE_SHIFT             (0x04u)
#define Character_LCD_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define Character_LCD_ROW_0_START              (0x80u)
#define Character_LCD_ROW_1_START              (0xC0u)
#define Character_LCD_ROW_2_START              (0x94u)
#define Character_LCD_ROW_3_START              (0xD4u)

/* Custom Character References */
#define Character_LCD_CUSTOM_0                 (0x00u)
#define Character_LCD_CUSTOM_1                 (0x01u)
#define Character_LCD_CUSTOM_2                 (0x02u)
#define Character_LCD_CUSTOM_3                 (0x03u)
#define Character_LCD_CUSTOM_4                 (0x04u)
#define Character_LCD_CUSTOM_5                 (0x05u)
#define Character_LCD_CUSTOM_6                 (0x06u)
#define Character_LCD_CUSTOM_7                 (0x07u)

/* Other constants */
#define Character_LCD_BYTE_UPPER_NIBBLE_SHIFT   (0x04u)
#define Character_LCD_BYTE_LOWER_NIBBLE_MASK    (0x0Fu)
#define Character_LCD_U16_UPPER_BYTE_SHIFT      (0x08u)
#define Character_LCD_U16_LOWER_BYTE_MASK       (0xFFu)
#define Character_LCD_CUSTOM_CHAR_SET_LEN       (0x40u)


/***************************************
*             Registers
***************************************/

/* Port Register Definitions */
#define Character_LCD_PORT_DR_REG              (*(reg8 *) Character_LCD_LCDPort__DR)   /* Data Output Register */
#define Character_LCD_PORT_DR_PTR              ( (reg8 *) Character_LCD_LCDPort__DR)
#define Character_LCD_PORT_PS_REG              (*(reg8 *) Character_LCD_LCDPort__PS)   /* Pin State Register */
#define Character_LCD_PORT_PS_PTR              ( (reg8 *) Character_LCD_LCDPort__PS)
#define Character_LCD_PORT_DM0_REG             (*(reg8 *) Character_LCD_LCDPort__DM0)  /* Port Drive Mode 0 */
#define Character_LCD_PORT_DM0_PTR             ( (reg8 *) Character_LCD_LCDPort__DM0)
#define Character_LCD_PORT_DM1_REG             (*(reg8 *) Character_LCD_LCDPort__DM1)  /* Port Drive Mode 1 */
#define Character_LCD_PORT_DM1_PTR             ( (reg8 *) Character_LCD_LCDPort__DM1)
#define Character_LCD_PORT_DM2_REG             (*(reg8 *) Character_LCD_LCDPort__DM2)  /* Port Drive Mode 2 */
#define Character_LCD_PORT_DM2_PTR             ( (reg8 *) Character_LCD_LCDPort__DM2)

/* These names are obsolete and will be removed in future revisions */
#define Character_LCD_PORT_DR                  Character_LCD_PORT_DR_REG
#define Character_LCD_PORT_PS                  Character_LCD_PORT_PS_REG
#define Character_LCD_PORT_DM0                 Character_LCD_PORT_DM0_REG
#define Character_LCD_PORT_DM1                 Character_LCD_PORT_DM1_REG
#define Character_LCD_PORT_DM2                 Character_LCD_PORT_DM2_REG


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#define Character_LCD_PORT_SHIFT               Character_LCD_LCDPort__SHIFT
#define Character_LCD_PORT_MASK                Character_LCD_LCDPort__MASK

/* Drive Mode register values for High Z */
#define Character_LCD_HIGH_Z_DM0               (0xFFu)
#define Character_LCD_HIGH_Z_DM1               (0x00u)
#define Character_LCD_HIGH_Z_DM2               (0x00u)

/* Drive Mode register values for High Z Analog */
#define Character_LCD_HIGH_Z_A_DM0             (0x00u)
#define Character_LCD_HIGH_Z_A_DM1             (0x00u)
#define Character_LCD_HIGH_Z_A_DM2             (0x00u)

/* Drive Mode register values for Strong */
#define Character_LCD_STRONG_DM0               (0x00u)
#define Character_LCD_STRONG_DM1               (0xFFu)
#define Character_LCD_STRONG_DM2               (0xFFu)

/* Pin Masks */
#define Character_LCD_RS                       (0x20u << Character_LCD_LCDPort__SHIFT)
#define Character_LCD_RW                       (0x40u << Character_LCD_LCDPort__SHIFT)
#define Character_LCD_E                        (0x10u << Character_LCD_LCDPort__SHIFT)
#define Character_LCD_READY_BIT                (0x08u << Character_LCD_LCDPort__SHIFT)
#define Character_LCD_DATA_MASK                (0x0Fu << Character_LCD_LCDPort__SHIFT)

#endif /* CY_CHARLCD_Character_LCD_H */


/* [] END OF FILE */
