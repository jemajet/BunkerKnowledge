/*******************************************************************************
* File Name: PSoC_UART.h
* Version 2.20
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "cytypes.h"
#include "cyfitter.h"

#if !defined(CY_UART_PSoC_UART_H)
#define CY_UART_PSoC_UART_H


/***************************************
* Conditional Compilation Parameters
***************************************/

#define PSoC_UART_RX_ENABLED                     (1u)
#define PSoC_UART_TX_ENABLED                     (1u)
#define PSoC_UART_HD_ENABLED                     (0u)
#define PSoC_UART_RX_INTERRUPT_ENABLED           (0u)
#define PSoC_UART_TX_INTERRUPT_ENABLED           (0u)
#define PSoC_UART_INTERNAL_CLOCK_USED            (1u)
#define PSoC_UART_RXHW_ADDRESS_ENABLED           (0u)
#define PSoC_UART_OVER_SAMPLE_COUNT              (8u)
#define PSoC_UART_PARITY_TYPE                    (0u)
#define PSoC_UART_PARITY_TYPE_SW                 (0u)
#define PSoC_UART_BREAK_DETECT                   (0u)
#define PSoC_UART_BREAK_BITS_TX                  (13u)
#define PSoC_UART_BREAK_BITS_RX                  (13u)
#define PSoC_UART_TXCLKGEN_DP                    (1u)
#define PSoC_UART_USE23POLLING                   (1u)
#define PSoC_UART_FLOW_CONTROL                   (0u)
#define PSoC_UART_CLK_FREQ                       (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define PSoC_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define PSoC_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _PSoC_UART_backupStruct
{
    uint8 enableState;

    #if(PSoC_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;            
    #endif /* End PSoC_UART_CONTROL_REG_REMOVED */    
    #if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0) 
            uint8 rx_mask;
            #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED)*/

    #if(PSoC_UART_TX_ENABLED)
        #if(PSoC_UART_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0) 
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End PSoC_UART_TXCLKGEN_DP */
        #if (CY_UDB_V0) 
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End PSoC_UART_TX_ENABLED */
} PSoC_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void PSoC_UART_Start(void) ;
void PSoC_UART_Stop(void) ;
uint8 PSoC_UART_ReadControlRegister(void) ;
void PSoC_UART_WriteControlRegister(uint8 control) ;

void PSoC_UART_Init(void) ;
void PSoC_UART_Enable(void) ;
void PSoC_UART_SaveConfig(void) ;
void PSoC_UART_RestoreConfig(void) ;
void PSoC_UART_Sleep(void) ;
void PSoC_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )

    #if(PSoC_UART_RX_INTERRUPT_ENABLED)
        void  PSoC_UART_EnableRxInt(void) ;
        void  PSoC_UART_DisableRxInt(void) ;
        CY_ISR_PROTO(PSoC_UART_RXISR);
    #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */

    void PSoC_UART_SetRxAddressMode(uint8 addressMode) 
                                                           ;
    void PSoC_UART_SetRxAddress1(uint8 address) ;
    void PSoC_UART_SetRxAddress2(uint8 address) ;

    void  PSoC_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 PSoC_UART_ReadRxData(void) ;
    uint8 PSoC_UART_ReadRxStatus(void) ;
    uint8 PSoC_UART_GetChar(void) ;
    uint16 PSoC_UART_GetByte(void) ;
    uint8 PSoC_UART_GetRxBufferSize(void)  
                                                            ;
    void PSoC_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define PSoC_UART_GetRxInterruptSource   PSoC_UART_ReadRxStatus

#endif /* End (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(PSoC_UART_TX_ENABLED || PSoC_UART_HD_ENABLED)

    #if(PSoC_UART_TX_INTERRUPT_ENABLED)
        void PSoC_UART_EnableTxInt(void) ;
        void PSoC_UART_DisableTxInt(void) ;
        CY_ISR_PROTO(PSoC_UART_TXISR);
    #endif /* PSoC_UART_TX_INTERRUPT_ENABLED */

    void PSoC_UART_SetTxInterruptMode(uint8 intSrc) ;
    void PSoC_UART_WriteTxData(uint8 txDataByte) ;
    uint8 PSoC_UART_ReadTxStatus(void) ;
    void PSoC_UART_PutChar(uint8 txDataByte) ;
    void PSoC_UART_PutString(char* string) ;
    void PSoC_UART_PutArray(uint8* string, uint8 byteCount)
                                                            ;
    void PSoC_UART_PutCRLF(uint8 txDataByte) ;
    void PSoC_UART_ClearTxBuffer(void) ;
    void PSoC_UART_SetTxAddressMode(uint8 addressMode) ;
    void PSoC_UART_SendBreak(uint8 retMode) ;
    uint8 PSoC_UART_GetTxBufferSize(void) 
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define PSoC_UART_PutStringConst         PSoC_UART_PutString
    #define PSoC_UART_PutArrayConst          PSoC_UART_PutArray
    #define PSoC_UART_GetTxInterruptSource   PSoC_UART_ReadTxStatus
    
#endif /* End PSoC_UART_TX_ENABLED || PSoC_UART_HD_ENABLED */

#if(PSoC_UART_HD_ENABLED)
    void PSoC_UART_LoadRxConfig(void) ;
    void PSoC_UART_LoadTxConfig(void) ;
#endif /* End PSoC_UART_HD_ENABLED */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define PSoC_UART_SET_SPACE                              (0x00u)
#define PSoC_UART_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (PSoC_UART_TX_ENABLED) || (PSoC_UART_HD_ENABLED) )
    #if(PSoC_UART_TX_INTERRUPT_ENABLED)
        #define PSoC_UART_TX_VECT_NUM                PSoC_UART_TXInternalInterrupt__INTC_NUMBER
        #define PSoC_UART_TX_PRIOR_NUM               PSoC_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PSoC_UART_TX_INTERRUPT_ENABLED */
    #if(PSoC_UART_TX_ENABLED) 
        #define PSoC_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define PSoC_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define PSoC_UART_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define PSoC_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* PSoC_UART_TX_ENABLED */
    #if(PSoC_UART_HD_ENABLED) 
        #define PSoC_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define PSoC_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define PSoC_UART_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define PSoC_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* PSoC_UART_HD_ENABLED */
    #define PSoC_UART_TX_STS_COMPLETE                (0x01u << PSoC_UART_TX_STS_COMPLETE_SHIFT)
    #define PSoC_UART_TX_STS_FIFO_EMPTY              (0x01u << PSoC_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define PSoC_UART_TX_STS_FIFO_FULL               (0x01u << PSoC_UART_TX_STS_FIFO_FULL_SHIFT)
    #define PSoC_UART_TX_STS_FIFO_NOT_FULL           (0x01u << PSoC_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (PSoC_UART_TX_ENABLED) || (PSoC_UART_HD_ENABLED)*/

#if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
    #if(PSoC_UART_RX_INTERRUPT_ENABLED)
        #define PSoC_UART_RX_VECT_NUM                PSoC_UART_RXInternalInterrupt__INTC_NUMBER
        #define PSoC_UART_RX_PRIOR_NUM               PSoC_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */
    #define PSoC_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define PSoC_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define PSoC_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define PSoC_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define PSoC_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define PSoC_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define PSoC_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define PSoC_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define PSoC_UART_RX_STS_MRKSPC                  (0x01u << PSoC_UART_RX_STS_MRKSPC_SHIFT)
    #define PSoC_UART_RX_STS_BREAK                   (0x01u << PSoC_UART_RX_STS_BREAK_SHIFT)
    #define PSoC_UART_RX_STS_PAR_ERROR               (0x01u << PSoC_UART_RX_STS_PAR_ERROR_SHIFT)
    #define PSoC_UART_RX_STS_STOP_ERROR              (0x01u << PSoC_UART_RX_STS_STOP_ERROR_SHIFT)
    #define PSoC_UART_RX_STS_OVERRUN                 (0x01u << PSoC_UART_RX_STS_OVERRUN_SHIFT)
    #define PSoC_UART_RX_STS_FIFO_NOTEMPTY           (0x01u << PSoC_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define PSoC_UART_RX_STS_ADDR_MATCH              (0x01u << PSoC_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define PSoC_UART_RX_STS_SOFT_BUFF_OVER          (0x01u << PSoC_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define PSoC_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */

/* Control Register definitions */
#define PSoC_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define PSoC_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define PSoC_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define PSoC_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define PSoC_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define PSoC_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define PSoC_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define PSoC_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define PSoC_UART_CTRL_HD_SEND                       (0x01u << PSoC_UART_CTRL_HD_SEND_SHIFT)
#define PSoC_UART_CTRL_HD_SEND_BREAK                 (0x01u << PSoC_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define PSoC_UART_CTRL_MARK                          (0x01u << PSoC_UART_CTRL_MARK_SHIFT)
#define PSoC_UART_CTRL_PARITY_TYPE_MASK              (0x03u << PSoC_UART_CTRL_PARITY_TYPE0_SHIFT)
#define PSoC_UART_CTRL_RXADDR_MODE_MASK              (0x07u << PSoC_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define PSoC_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define PSoC_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define PSoC_UART_SEND_BREAK                         (0x00u)
#define PSoC_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define PSoC_UART_REINIT                             (0x02u)
#define PSoC_UART_SEND_WAIT_REINIT                   (0x03u)

#define PSoC_UART_OVER_SAMPLE_8                      (8u)
#define PSoC_UART_OVER_SAMPLE_16                     (16u)

#define PSoC_UART_BIT_CENTER                         (PSoC_UART_OVER_SAMPLE_COUNT - 1u)

#define PSoC_UART_FIFO_LENGTH                        (4u)
#define PSoC_UART_NUMBER_OF_START_BIT                (1u)

/* 8X always for count7 implementation*/
#define PSoC_UART_TXBITCTR_BREAKBITS8X   (PSoC_UART_BREAK_BITS_TX * PSoC_UART_OVER_SAMPLE_8 - 1u)
/* 8X or 16X for DP implementation*/
#define PSoC_UART_TXBITCTR_BREAKBITS   (PSoC_UART_BREAK_BITS_TX * PSoC_UART_OVER_SAMPLE_COUNT - 1u)

#if (PSoC_UART_OVER_SAMPLE_COUNT == PSoC_UART_OVER_SAMPLE_8)
    #define PSoC_UART_HD_TXBITCTR_INIT   ((PSoC_UART_BREAK_BITS_TX + \
        PSoC_UART_NUMBER_OF_START_BIT) * PSoC_UART_OVER_SAMPLE_COUNT - 1u)
    /* This parameter is increased on the 1 in 2 out of 3 mode to sample voting in the middle */
    #define PSoC_UART_HD_RXBITCTR_INIT   ((PSoC_UART_BREAK_BITS_RX + \
    PSoC_UART_NUMBER_OF_START_BIT) * PSoC_UART_OVER_SAMPLE_COUNT - 1u + \
    (PSoC_UART_OVER_SAMPLE_COUNT / 2u) + (PSoC_UART_USE23POLLING * 2u) - 1u)
#else /* PSoC_UART_OVER_SAMPLE_COUNT == PSoC_UART_OVER_SAMPLE_16 */
    #define PSoC_UART_HD_TXBITCTR_INIT   (8u * PSoC_UART_OVER_SAMPLE_COUNT - 1u)
    #define PSoC_UART_HD_RXBITCTR_INIT   (7u * PSoC_UART_OVER_SAMPLE_COUNT - 1u  +  \
       (PSoC_UART_OVER_SAMPLE_COUNT / 2u) + (PSoC_UART_USE23POLLING * 2u) - 1u)
#endif /* End PSoC_UART_OVER_SAMPLE_COUNT */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define PSoC_UART__B_UART__AM_SW_BYTE_BYTE 1
#define PSoC_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define PSoC_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define PSoC_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define PSoC_UART__B_UART__AM_NONE 0

#define PSoC_UART__B_UART__NONE_REVB 0
#define PSoC_UART__B_UART__EVEN_REVB 1
#define PSoC_UART__B_UART__ODD_REVB 2
#define PSoC_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

#define PSoC_UART_TXBUFFERSIZE           (4u)
#define PSoC_UART_RXBUFFERSIZE           (4u)
/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define PSoC_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define PSoC_UART_NUMBER_OF_STOP_BITS    (1u)

#if (PSoC_UART_RXHW_ADDRESS_ENABLED)
    #define PSoC_UART_RXADDRESSMODE      (0u)
    #define PSoC_UART_RXHWADDRESS1       (0u)
    #define PSoC_UART_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define PSoC_UART_RXAddressMode      PSoC_UART_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define PSoC_UART_INIT_RX_INTERRUPTS_MASK \
                                          (0 << PSoC_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << PSoC_UART_RX_STS_OVERRUN_SHIFT)

#define PSoC_UART_INIT_TX_INTERRUPTS_MASK \
                                          (0 << PSoC_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << PSoC_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << PSoC_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << PSoC_UART_TX_STS_FIFO_NOT_FULL_SHIFT)


/***************************************
*              Registers
***************************************/

#ifdef PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define PSoC_UART_CONTROL_REG \
                            (* (reg8 *) PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define PSoC_UART_CONTROL_PTR \
                            (  (reg8 *) PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(PSoC_UART_TX_ENABLED)
    #define PSoC_UART_TXDATA_REG          (* (reg8 *) PSoC_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define PSoC_UART_TXDATA_PTR          (  (reg8 *) PSoC_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define PSoC_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) PSoC_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PSoC_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) PSoC_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PSoC_UART_TXSTATUS_REG        (* (reg8 *) PSoC_UART_BUART_sTX_TxSts__STATUS_REG)
    #define PSoC_UART_TXSTATUS_PTR        (  (reg8 *) PSoC_UART_BUART_sTX_TxSts__STATUS_REG)
    #define PSoC_UART_TXSTATUS_MASK_REG   (* (reg8 *) PSoC_UART_BUART_sTX_TxSts__MASK_REG)
    #define PSoC_UART_TXSTATUS_MASK_PTR   (  (reg8 *) PSoC_UART_BUART_sTX_TxSts__MASK_REG)
    #define PSoC_UART_TXSTATUS_ACTL_REG   (* (reg8 *) PSoC_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define PSoC_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) PSoC_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(PSoC_UART_TXCLKGEN_DP)
        #define PSoC_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PSoC_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PSoC_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define PSoC_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define PSoC_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PSoC_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PSoC_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PSoC_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PSoC_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define PSoC_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) PSoC_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* PSoC_UART_TXCLKGEN_DP */

#endif /* End PSoC_UART_TX_ENABLED */

#if(PSoC_UART_HD_ENABLED)

    #define PSoC_UART_TXDATA_REG             (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define PSoC_UART_TXDATA_PTR             (  (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define PSoC_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define PSoC_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PSoC_UART_TXSTATUS_REG           (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_REG )
    #define PSoC_UART_TXSTATUS_PTR           (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_REG )
    #define PSoC_UART_TXSTATUS_MASK_REG      (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__MASK_REG )
    #define PSoC_UART_TXSTATUS_MASK_PTR      (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__MASK_REG )
    #define PSoC_UART_TXSTATUS_ACTL_REG      (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PSoC_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End PSoC_UART_HD_ENABLED */

#if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
    #define PSoC_UART_RXDATA_REG             (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define PSoC_UART_RXDATA_PTR             (  (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define PSoC_UART_RXADDRESS1_REG         (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define PSoC_UART_RXADDRESS1_PTR         (  (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define PSoC_UART_RXADDRESS2_REG         (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define PSoC_UART_RXADDRESS2_PTR         (  (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define PSoC_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) PSoC_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PSoC_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PSoC_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PSoC_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PSoC_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PSoC_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define PSoC_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) PSoC_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define PSoC_UART_RXSTATUS_REG           (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_REG )
    #define PSoC_UART_RXSTATUS_PTR           (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_REG )
    #define PSoC_UART_RXSTATUS_MASK_REG      (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__MASK_REG )
    #define PSoC_UART_RXSTATUS_MASK_PTR      (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__MASK_REG )
    #define PSoC_UART_RXSTATUS_ACTL_REG      (* (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PSoC_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) PSoC_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */

#if(PSoC_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define PSoC_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) PSoC_UART_IntClock__PM_ACT_CFG)
    #define PSoC_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) PSoC_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define PSoC_UART_INTCLOCK_CLKEN_MASK    PSoC_UART_IntClock__PM_ACT_MSK
#endif /* End PSoC_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants              
***************************************/

#if(PSoC_UART_TX_ENABLED)
    #define PSoC_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End PSoC_UART_TX_ENABLED */

#if(PSoC_UART_HD_ENABLED)
    #define PSoC_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End PSoC_UART_HD_ENABLED */

#if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
    #define PSoC_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/

#define PSoC_UART_initvar                    PSoC_UART_initVar

#define PSoC_UART_RX_Enabled                 PSoC_UART_RX_ENABLED
#define PSoC_UART_TX_Enabled                 PSoC_UART_TX_ENABLED
#define PSoC_UART_HD_Enabled                 PSoC_UART_HD_ENABLED
#define PSoC_UART_RX_IntInterruptEnabled     PSoC_UART_RX_INTERRUPT_ENABLED
#define PSoC_UART_TX_IntInterruptEnabled     PSoC_UART_TX_INTERRUPT_ENABLED
#define PSoC_UART_InternalClockUsed          PSoC_UART_INTERNAL_CLOCK_USED
#define PSoC_UART_RXHW_Address_Enabled       PSoC_UART_RXHW_ADDRESS_ENABLED
#define PSoC_UART_OverSampleCount            PSoC_UART_OVER_SAMPLE_COUNT
#define PSoC_UART_ParityType                 PSoC_UART_PARITY_TYPE

#if( PSoC_UART_TX_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
    #define PSoC_UART_TXBUFFER               PSoC_UART_txBuffer
    #define PSoC_UART_TXBUFFERREAD           PSoC_UART_txBufferRead 
    #define PSoC_UART_TXBUFFERWRITE          PSoC_UART_txBufferWrite 
#endif /* End PSoC_UART_TX_ENABLED */
#if( ( PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED ) && \
     (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) )
    #define PSoC_UART_RXBUFFER               PSoC_UART_rxBuffer
    #define PSoC_UART_RXBUFFERREAD           PSoC_UART_rxBufferRead 
    #define PSoC_UART_RXBUFFERWRITE          PSoC_UART_rxBufferWrite 
    #define PSoC_UART_RXBUFFERLOOPDETECT     PSoC_UART_rxBufferLoopDetect
    #define PSoC_UART_RXBUFFER_OVERFLOW      PSoC_UART_rxBufferOverflow
#endif /* End PSoC_UART_RX_ENABLED */

#ifdef PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define PSoC_UART_CONTROL                PSoC_UART_CONTROL_REG 
#endif /* End PSoC_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(PSoC_UART_TX_ENABLED)
    #define PSoC_UART_TXDATA                 PSoC_UART_TXDATA_REG
    #define PSoC_UART_TXSTATUS               PSoC_UART_TXSTATUS_REG
    #define PSoC_UART_TXSTATUS_MASK          PSoC_UART_TXSTATUS_MASK_REG   
    #define PSoC_UART_TXSTATUS_ACTL          PSoC_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(PSoC_UART_TXCLKGEN_DP)
        #define PSoC_UART_TXBITCLKGEN_CTR        PSoC_UART_TXBITCLKGEN_CTR_REG
        #define PSoC_UART_TXBITCLKTX_COMPLETE    PSoC_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define PSoC_UART_TXBITCTR_PERIOD        PSoC_UART_TXBITCTR_PERIOD_REG
        #define PSoC_UART_TXBITCTR_CONTROL       PSoC_UART_TXBITCTR_CONTROL_REG
        #define PSoC_UART_TXBITCTR_COUNTER       PSoC_UART_TXBITCTR_COUNTER_REG
    #endif /* PSoC_UART_TXCLKGEN_DP */
#endif /* End PSoC_UART_TX_ENABLED */

#if(PSoC_UART_HD_ENABLED)
    #define PSoC_UART_TXDATA                 PSoC_UART_TXDATA_REG
    #define PSoC_UART_TXSTATUS               PSoC_UART_TXSTATUS_REG
    #define PSoC_UART_TXSTATUS_MASK          PSoC_UART_TXSTATUS_MASK_REG   
    #define PSoC_UART_TXSTATUS_ACTL          PSoC_UART_TXSTATUS_ACTL_REG
#endif /* End PSoC_UART_HD_ENABLED */

#if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
    #define PSoC_UART_RXDATA                 PSoC_UART_RXDATA_REG             
    #define PSoC_UART_RXADDRESS1             PSoC_UART_RXADDRESS1_REG
    #define PSoC_UART_RXADDRESS2             PSoC_UART_RXADDRESS2_REG
    #define PSoC_UART_RXBITCTR_PERIOD        PSoC_UART_RXBITCTR_PERIOD_REG
    #define PSoC_UART_RXBITCTR_CONTROL       PSoC_UART_RXBITCTR_CONTROL_REG
    #define PSoC_UART_RXBITCTR_COUNTER       PSoC_UART_RXBITCTR_COUNTER_REG
    #define PSoC_UART_RXSTATUS               PSoC_UART_RXSTATUS_REG
    #define PSoC_UART_RXSTATUS_MASK          PSoC_UART_RXSTATUS_MASK_REG
    #define PSoC_UART_RXSTATUS_ACTL          PSoC_UART_RXSTATUS_ACTL_REG
#endif /* End  (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */

#if(PSoC_UART_INTERNAL_CLOCK_USED)
    #define PSoC_UART_INTCLOCK_CLKEN         PSoC_UART_INTCLOCK_CLKEN_REG
#endif /* End PSoC_UART_INTERNAL_CLOCK_USED */

#define PSoC_UART_WAIT_FOR_COMLETE_REINIT    PSoC_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_PSoC_UART_H */


/* [] END OF FILE */
