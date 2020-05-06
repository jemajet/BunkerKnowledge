/*******************************************************************************
* File Name: Character_LCD_LCDPort.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Character_LCD_LCDPort_H) /* Pins Character_LCD_LCDPort_H */
#define CY_PINS_Character_LCD_LCDPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Character_LCD_LCDPort_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Character_LCD_LCDPort__PORT == 15 && (Character_LCD_LCDPort__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Character_LCD_LCDPort_Write(uint8 value) ;
void    Character_LCD_LCDPort_SetDriveMode(uint8 mode) ;
uint8   Character_LCD_LCDPort_ReadDataReg(void) ;
uint8   Character_LCD_LCDPort_Read(void) ;
uint8   Character_LCD_LCDPort_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Character_LCD_LCDPort_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Character_LCD_LCDPort_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Character_LCD_LCDPort_DM_RES_UP          PIN_DM_RES_UP
#define Character_LCD_LCDPort_DM_RES_DWN         PIN_DM_RES_DWN
#define Character_LCD_LCDPort_DM_OD_LO           PIN_DM_OD_LO
#define Character_LCD_LCDPort_DM_OD_HI           PIN_DM_OD_HI
#define Character_LCD_LCDPort_DM_STRONG          PIN_DM_STRONG
#define Character_LCD_LCDPort_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Character_LCD_LCDPort_MASK               Character_LCD_LCDPort__MASK
#define Character_LCD_LCDPort_SHIFT              Character_LCD_LCDPort__SHIFT
#define Character_LCD_LCDPort_WIDTH              7u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Character_LCD_LCDPort_PS                     (* (reg8 *) Character_LCD_LCDPort__PS)
/* Data Register */
#define Character_LCD_LCDPort_DR                     (* (reg8 *) Character_LCD_LCDPort__DR)
/* Port Number */
#define Character_LCD_LCDPort_PRT_NUM                (* (reg8 *) Character_LCD_LCDPort__PRT) 
/* Connect to Analog Globals */                                                  
#define Character_LCD_LCDPort_AG                     (* (reg8 *) Character_LCD_LCDPort__AG)                       
/* Analog MUX bux enable */
#define Character_LCD_LCDPort_AMUX                   (* (reg8 *) Character_LCD_LCDPort__AMUX) 
/* Bidirectional Enable */                                                        
#define Character_LCD_LCDPort_BIE                    (* (reg8 *) Character_LCD_LCDPort__BIE)
/* Bit-mask for Aliased Register Access */
#define Character_LCD_LCDPort_BIT_MASK               (* (reg8 *) Character_LCD_LCDPort__BIT_MASK)
/* Bypass Enable */
#define Character_LCD_LCDPort_BYP                    (* (reg8 *) Character_LCD_LCDPort__BYP)
/* Port wide control signals */                                                   
#define Character_LCD_LCDPort_CTL                    (* (reg8 *) Character_LCD_LCDPort__CTL)
/* Drive Modes */
#define Character_LCD_LCDPort_DM0                    (* (reg8 *) Character_LCD_LCDPort__DM0) 
#define Character_LCD_LCDPort_DM1                    (* (reg8 *) Character_LCD_LCDPort__DM1)
#define Character_LCD_LCDPort_DM2                    (* (reg8 *) Character_LCD_LCDPort__DM2) 
/* Input Buffer Disable Override */
#define Character_LCD_LCDPort_INP_DIS                (* (reg8 *) Character_LCD_LCDPort__INP_DIS)
/* LCD Common or Segment Drive */
#define Character_LCD_LCDPort_LCD_COM_SEG            (* (reg8 *) Character_LCD_LCDPort__LCD_COM_SEG)
/* Enable Segment LCD */
#define Character_LCD_LCDPort_LCD_EN                 (* (reg8 *) Character_LCD_LCDPort__LCD_EN)
/* Slew Rate Control */
#define Character_LCD_LCDPort_SLW                    (* (reg8 *) Character_LCD_LCDPort__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Character_LCD_LCDPort_PRTDSI__CAPS_SEL       (* (reg8 *) Character_LCD_LCDPort__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Character_LCD_LCDPort_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Character_LCD_LCDPort__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Character_LCD_LCDPort_PRTDSI__OE_SEL0        (* (reg8 *) Character_LCD_LCDPort__PRTDSI__OE_SEL0) 
#define Character_LCD_LCDPort_PRTDSI__OE_SEL1        (* (reg8 *) Character_LCD_LCDPort__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Character_LCD_LCDPort_PRTDSI__OUT_SEL0       (* (reg8 *) Character_LCD_LCDPort__PRTDSI__OUT_SEL0) 
#define Character_LCD_LCDPort_PRTDSI__OUT_SEL1       (* (reg8 *) Character_LCD_LCDPort__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Character_LCD_LCDPort_PRTDSI__SYNC_OUT       (* (reg8 *) Character_LCD_LCDPort__PRTDSI__SYNC_OUT) 


#if defined(Character_LCD_LCDPort__INTSTAT)  /* Interrupt Registers */

    #define Character_LCD_LCDPort_INTSTAT                (* (reg8 *) Character_LCD_LCDPort__INTSTAT)
    #define Character_LCD_LCDPort_SNAP                   (* (reg8 *) Character_LCD_LCDPort__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Character_LCD_LCDPort_H */

#endif
/* [] END OF FILE */
