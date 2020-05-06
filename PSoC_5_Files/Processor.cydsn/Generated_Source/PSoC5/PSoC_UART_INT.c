/*******************************************************************************
* File Name: PSoC_UART_INT.c
* Version 2.20
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PSoC_UART.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED) && \
     (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))

    extern volatile uint8 PSoC_UART_rxBuffer[];
    extern volatile uint8 PSoC_UART_rxBufferRead;
    extern volatile uint8 PSoC_UART_rxBufferWrite;
    extern volatile uint8 PSoC_UART_rxBufferLoopDetect;
    extern volatile uint8 PSoC_UART_rxBufferOverflow;
    #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 PSoC_UART_rxAddressMode;
        extern volatile uint8 PSoC_UART_rxAddressDetected;
    #endif /* End EnableHWAddress */    

    /*******************************************************************************
    * Function Name: PSoC_UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_rxBuffer - RAM buffer pointer for save received data.
    *  PSoC_UART_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     increments after each byte saved to buffer.
    *  PSoC_UART_rxBufferRead - cyclic index for read from rxBuffer, 
    *     checked to detect overflow condition.
    *  PSoC_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when PSoC_UART_rxBufferWrite index overtakes 
    *     PSoC_UART_rxBufferRead index.
    *  PSoC_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when PSoC_UART_rxBufferWrite is equal to 
    *    PSoC_UART_rxBufferRead
    *  PSoC_UART_rxAddressMode - this variable contains the Address mode, 
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  PSoC_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(PSoC_UART_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;

        /* User code required at start of ISR */
        /* `#START PSoC_UART_RXISR_START` */

        /* `#END` */

        readData = PSoC_UART_RXSTATUS_REG;

        if((readData & (PSoC_UART_RX_STS_BREAK | PSoC_UART_RX_STS_PAR_ERROR |
                        PSoC_UART_RX_STS_STOP_ERROR | PSoC_UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START PSoC_UART_RXISR_ERROR` */

            /* `#END` */
        }

        while(readData & PSoC_UART_RX_STS_FIFO_NOTEMPTY)
        {
            
            #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
                if(PSoC_UART_rxAddressMode == PSoC_UART__B_UART__AM_SW_DETECT_TO_BUFFER) 
                {
                    if((readData & PSoC_UART_RX_STS_MRKSPC) != 0u)
                    {  
                        if ((readData & PSoC_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            PSoC_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            PSoC_UART_rxAddressDetected = 0u;
                        }
                    }

                    readData = PSoC_UART_RXDATA_REG;
                    if(PSoC_UART_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        PSoC_UART_rxBuffer[PSoC_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    PSoC_UART_rxBuffer[PSoC_UART_rxBufferWrite] = PSoC_UART_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                PSoC_UART_rxBuffer[PSoC_UART_rxBufferWrite] = PSoC_UART_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */
            
            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(PSoC_UART_rxBufferLoopDetect)
                {   /* Set Software Buffer status Overflow */
                    PSoC_UART_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                PSoC_UART_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(PSoC_UART_rxBufferWrite >= PSoC_UART_RXBUFFERSIZE)
                {
                    PSoC_UART_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(PSoC_UART_rxBufferWrite == PSoC_UART_rxBufferRead)
                {
                    PSoC_UART_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(PSoC_UART_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        PSoC_UART_RXSTATUS_MASK_REG  &= ~PSoC_UART_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(PSoC_UART_RX_VECT_NUM); 
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End PSoC_UART_FLOW_CONTROL != 0 */    
                }
            }

            /* Check again if there is data. */
            readData = PSoC_UART_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START PSoC_UART_RXISR_END` */

        /* `#END` */

    }

#endif /* End PSoC_UART_RX_ENABLED && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) */


#if(PSoC_UART_TX_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))

    extern volatile uint8 PSoC_UART_txBuffer[];
    extern volatile uint8 PSoC_UART_txBufferRead;
    extern uint8 PSoC_UART_txBufferWrite;


    /*******************************************************************************
    * Function Name: PSoC_UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  PSoC_UART_txBufferRead - cyclic index for read and transmit data 
    *     from txBuffer, increments after each transmited byte.
    *  PSoC_UART_rxBufferWrite - cyclic index for write to txBuffer, 
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(PSoC_UART_TXISR)
    {

        /* User code required at start of ISR */
        /* `#START PSoC_UART_TXISR_START` */

        /* `#END` */

        while((PSoC_UART_txBufferRead != PSoC_UART_txBufferWrite) && \
             !(PSoC_UART_TXSTATUS_REG & PSoC_UART_TX_STS_FIFO_FULL))
        {
            /* Check pointer. */
            if(PSoC_UART_txBufferRead >= PSoC_UART_TXBUFFERSIZE)
            {
                PSoC_UART_txBufferRead = 0u;
            }

            PSoC_UART_TXDATA_REG = PSoC_UART_txBuffer[PSoC_UART_txBufferRead];

            /* Set next pointer. */
            PSoC_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START PSoC_UART_TXISR_END` */

        /* `#END` */
        
    }

#endif /* End PSoC_UART_TX_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) */


/* [] END OF FILE */
