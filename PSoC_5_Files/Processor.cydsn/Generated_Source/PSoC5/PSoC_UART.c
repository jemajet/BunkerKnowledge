/*******************************************************************************
* File Name: PSoC_UART.c
* Version 2.20
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
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
* Global data allocation
***************************************/

#if( PSoC_UART_TX_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
    volatile uint8 PSoC_UART_txBuffer[PSoC_UART_TXBUFFERSIZE];
    volatile uint8 PSoC_UART_txBufferRead = 0u;
    uint8 PSoC_UART_txBufferWrite = 0u;
#endif /* End PSoC_UART_TX_ENABLED */
#if( ( PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED ) && \
     (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) )
    volatile uint8 PSoC_UART_rxBuffer[PSoC_UART_RXBUFFERSIZE];
    volatile uint8 PSoC_UART_rxBufferRead = 0u;
    volatile uint8 PSoC_UART_rxBufferWrite = 0u;
    volatile uint8 PSoC_UART_rxBufferLoopDetect = 0u;
    volatile uint8 PSoC_UART_rxBufferOverflow = 0u;
    #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
        volatile uint8 PSoC_UART_rxAddressMode = PSoC_UART_RXADDRESSMODE;
        volatile uint8 PSoC_UART_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */    
#endif /* End PSoC_UART_RX_ENABLED */


/***************************************
* Local data allocation
***************************************/

uint8 PSoC_UART_initVar = 0u;


/*******************************************************************************
* Function Name: PSoC_UART_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The PSoC_UART_intiVar variable is used to indicate initial 
*  configuration of this component. The variable is initialized to zero (0u) 
*  and set to one (1u) the first time UART_Start() is called. This allows for 
*  component initialization without re-initialization in all subsequent calls 
*  to the PSoC_UART_Start() routine. 
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PSoC_UART_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PSoC_UART_initVar == 0u)
    {
        PSoC_UART_Init();
        PSoC_UART_initVar = 1u;
    }
    PSoC_UART_Enable();
}


/*******************************************************************************
* Function Name: PSoC_UART_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PSoC_UART_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void PSoC_UART_Init(void) 
{
    #if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)

        #if(PSoC_UART_RX_INTERRUPT_ENABLED && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            CyIntSetVector(PSoC_UART_RX_VECT_NUM,   PSoC_UART_RXISR);
            CyIntSetPriority(PSoC_UART_RX_VECT_NUM, PSoC_UART_RX_PRIOR_NUM);
        #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */

        #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
            PSoC_UART_SetRxAddressMode(PSoC_UART_RXAddressMode);
            PSoC_UART_SetRxAddress1(PSoC_UART_RXHWADDRESS1);
            PSoC_UART_SetRxAddress2(PSoC_UART_RXHWADDRESS2);
        #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */

        /* Configure the Initial RX interrupt mask */
        PSoC_UART_RXSTATUS_MASK_REG  = PSoC_UART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED*/

    #if(PSoC_UART_TX_ENABLED)
        #if(PSoC_UART_TX_INTERRUPT_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            CyIntSetVector(PSoC_UART_TX_VECT_NUM,   PSoC_UART_TXISR);
            CyIntSetPriority(PSoC_UART_TX_VECT_NUM, PSoC_UART_TX_PRIOR_NUM);
        #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(PSoC_UART_TXCLKGEN_DP)
            PSoC_UART_TXBITCLKGEN_CTR_REG = PSoC_UART_BIT_CENTER;
            PSoC_UART_TXBITCLKTX_COMPLETE_REG = (PSoC_UART_NUMBER_OF_DATA_BITS + \
                                                    PSoC_UART_NUMBER_OF_START_BIT) * \
                                                    PSoC_UART_OVER_SAMPLE_COUNT;
        #else
            PSoC_UART_TXBITCTR_COUNTER_REG = (PSoC_UART_NUMBER_OF_DATA_BITS + \
                                                    PSoC_UART_NUMBER_OF_START_BIT) * \
                                                    PSoC_UART_OVER_SAMPLE_8;
        #endif /* End PSoC_UART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(PSoC_UART_TX_INTERRUPT_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            PSoC_UART_TXSTATUS_MASK_REG = PSoC_UART_TX_STS_FIFO_EMPTY;
        #else
            PSoC_UART_TXSTATUS_MASK_REG = PSoC_UART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End PSoC_UART_TX_INTERRUPT_ENABLED*/
        
    #endif /* End PSoC_UART_TX_ENABLED */

    #if(PSoC_UART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        PSoC_UART_WriteControlRegister( \
            (PSoC_UART_ReadControlRegister() & ~PSoC_UART_CTRL_PARITY_TYPE_MASK) | \
            (PSoC_UART_PARITY_TYPE << PSoC_UART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End PSoC_UART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: PSoC_UART_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PSoC_UART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void PSoC_UART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();
    
    #if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        PSoC_UART_RXBITCTR_CONTROL_REG |= PSoC_UART_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        PSoC_UART_RXSTATUS_ACTL_REG  |= PSoC_UART_INT_ENABLE;
        #if(PSoC_UART_RX_INTERRUPT_ENABLED && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            CyIntEnable(PSoC_UART_RX_VECT_NUM);
            #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
                PSoC_UART_rxAddressDetected = 0u;
            #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */
    #endif /* End PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED*/

    #if(PSoC_UART_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!PSoC_UART_TXCLKGEN_DP)
            PSoC_UART_TXBITCTR_CONTROL_REG |= PSoC_UART_CNTR_ENABLE;
        #endif /* End PSoC_UART_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        PSoC_UART_TXSTATUS_ACTL_REG |= PSoC_UART_INT_ENABLE;
        #if(PSoC_UART_TX_INTERRUPT_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            CyIntEnable(PSoC_UART_TX_VECT_NUM);
        #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED*/
     #endif /* End PSoC_UART_TX_ENABLED */

    #if(PSoC_UART_INTERNAL_CLOCK_USED)
        /* Set the bit to enable the clock. */
        PSoC_UART_INTCLOCK_CLKEN_REG |= PSoC_UART_INTCLOCK_CLKEN_MASK;
    #endif /* End PSoC_UART_INTERNAL_CLOCK_USED */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PSoC_UART_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void PSoC_UART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /*Write Bit Counter Disable */
    #if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)
        PSoC_UART_RXBITCTR_CONTROL_REG &= ~PSoC_UART_CNTR_ENABLE;
    #endif /* End PSoC_UART_RX_ENABLED */

    #if(PSoC_UART_TX_ENABLED)
        #if(!PSoC_UART_TXCLKGEN_DP)
            PSoC_UART_TXBITCTR_CONTROL_REG &= ~PSoC_UART_CNTR_ENABLE;
        #endif /* End PSoC_UART_TXCLKGEN_DP */
    #endif /* PSoC_UART_TX_ENABLED */

    #if(PSoC_UART_INTERNAL_CLOCK_USED)
        /* Clear the bit to enable the clock. */
        PSoC_UART_INTCLOCK_CLKEN_REG &= ~PSoC_UART_INTCLOCK_CLKEN_MASK;
    #endif /* End PSoC_UART_INTERNAL_CLOCK_USED */
    
    /*Disable internal interrupt component*/
    #if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)
        PSoC_UART_RXSTATUS_ACTL_REG  &= ~PSoC_UART_INT_ENABLE;
        #if(PSoC_UART_RX_INTERRUPT_ENABLED && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            PSoC_UART_DisableRxInt();
        #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */
    #endif /* End PSoC_UART_RX_ENABLED */
    
    #if(PSoC_UART_TX_ENABLED)
        PSoC_UART_TXSTATUS_ACTL_REG &= ~PSoC_UART_INT_ENABLE;
        #if(PSoC_UART_TX_INTERRUPT_ENABLED && (PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            PSoC_UART_DisableTxInt();
        #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */
    #endif /* End PSoC_UART_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PSoC_UART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 PSoC_UART_ReadControlRegister(void) 
{
    #if( PSoC_UART_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(PSoC_UART_CONTROL_REG);
    #endif /* End PSoC_UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: PSoC_UART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  PSoC_UART_WriteControlRegister(uint8 control) 
{
    #if( PSoC_UART_CONTROL_REG_REMOVED )
        control = control;      /* Reassigning to release compiler warning */ 
    #else
       PSoC_UART_CONTROL_REG = control;
    #endif /* End PSoC_UART_CONTROL_REG_REMOVED */
}


#if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)

    #if(PSoC_UART_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: PSoC_UART_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PSoC_UART_EnableRxInt(void) 
        {
            CyIntEnable(PSoC_UART_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: PSoC_UART_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PSoC_UART_DisableRxInt(void) 
        {
            CyIntDisable(PSoC_UART_RX_VECT_NUM);
        }

    #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: PSoC_UART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void PSoC_UART_SetRxInterruptMode(uint8 intSrc) 
    {
        PSoC_UART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to 
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  PSoC_UART_rxBuffer - RAM buffer pointer for save received data.
    *  PSoC_UART_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  PSoC_UART_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  PSoC_UART_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 PSoC_UART_ReadRxData(void) 
    {
        uint8 rxData;

        #if(PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_DisableRxInt();
            #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */

            if( (PSoC_UART_rxBufferRead != PSoC_UART_rxBufferWrite) ||
                (PSoC_UART_rxBufferLoopDetect > 0u) )
            {

                rxData = PSoC_UART_rxBuffer[PSoC_UART_rxBufferRead];

                PSoC_UART_rxBufferRead++;

                if(PSoC_UART_rxBufferRead >= PSoC_UART_RXBUFFERSIZE)
                {
                    PSoC_UART_rxBufferRead = 0u;
                }

                if(PSoC_UART_rxBufferLoopDetect > 0u )
                {
                    PSoC_UART_rxBufferLoopDetect = 0u;
                    #if( (PSoC_UART_RX_INTERRUPT_ENABLED) && (PSoC_UART_FLOW_CONTROL != 0u) && \
                         (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( PSoC_UART_HD_ENABLED )
                            if((PSoC_UART_CONTROL_REG & PSoC_UART_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX 
                                *  configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                PSoC_UART_RXSTATUS_MASK_REG  |= PSoC_UART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            PSoC_UART_RXSTATUS_MASK_REG  |= PSoC_UART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end PSoC_UART_HD_ENABLED */
                    #endif /* PSoC_UART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = PSoC_UART_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_EnableRxInt();
            #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */

        #else /* PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = PSoC_UART_RXDATA_REG;

        #endif /* PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  PSoC_UART_rxBufferOverflow - used to indicate overload condition. 
    *   It set to one in RX interrupt when there isn?t free space in 
    *   PSoC_UART_rxBufferRead to write new data. This condition returned 
    *   and cleared to zero by this API as an 
    *   PSoC_UART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register 
    *   bits.
    *
    *******************************************************************************/
    uint8 PSoC_UART_ReadRxStatus(void) 
    {
        uint8 status;

        status = PSoC_UART_RXSTATUS_REG;
        status &= PSoC_UART_RX_HW_MASK;

        #if(PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)
            if( PSoC_UART_rxBufferOverflow )
            {
                status |= PSoC_UART_RX_STS_SOFT_BUFF_OVER;
                PSoC_UART_rxBufferOverflow = 0u;
            }
        #endif /* PSoC_UART_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error 
    *  condition exists, zero is returned; otherwise, character is read and 
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  PSoC_UART_rxBuffer - RAM buffer pointer for save received data.
    *  PSoC_UART_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  PSoC_UART_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  PSoC_UART_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 PSoC_UART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_DisableRxInt();
            #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */

            if( (PSoC_UART_rxBufferRead != PSoC_UART_rxBufferWrite) ||
                (PSoC_UART_rxBufferLoopDetect > 0u) )
            {
                rxData = PSoC_UART_rxBuffer[PSoC_UART_rxBufferRead];

                PSoC_UART_rxBufferRead++;

                if(PSoC_UART_rxBufferRead >= PSoC_UART_RXBUFFERSIZE)
                {
                    PSoC_UART_rxBufferRead = 0u;
                }

                if(PSoC_UART_rxBufferLoopDetect > 0u ) 
                {
                    PSoC_UART_rxBufferLoopDetect = 0u;
                    #if( (PSoC_UART_RX_INTERRUPT_ENABLED) && (PSoC_UART_FLOW_CONTROL != 0u) && \
                         (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( PSoC_UART_HD_ENABLED )
                            if((PSoC_UART_CONTROL_REG & PSoC_UART_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only if 
                                *  RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                PSoC_UART_RXSTATUS_MASK_REG  |= PSoC_UART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            PSoC_UART_RXSTATUS_MASK_REG  |= PSoC_UART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end PSoC_UART_HD_ENABLED */
                    #endif /* PSoC_UART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus =PSoC_UART_RXSTATUS_REG;
                if(rxStatus & PSoC_UART_RX_STS_FIFO_NOTEMPTY)
                {   /* Read received data from FIFO*/
                    rxData = PSoC_UART_RXDATA_REG;
                    /*Check status on error*/
                    if(rxStatus & (PSoC_UART_RX_STS_BREAK | PSoC_UART_RX_STS_PAR_ERROR |
                                   PSoC_UART_RX_STS_STOP_ERROR | PSoC_UART_RX_STS_OVERRUN))
                    {
                        rxData = 0u;
                    }    
                }
            }

            /* Enable Rx interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_EnableRxInt();
            #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */

        #else /* PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

            rxStatus =PSoC_UART_RXSTATUS_REG;
            if(rxStatus & PSoC_UART_RX_STS_FIFO_NOTEMPTY)
            {   /* Read received data from FIFO*/
                rxData = PSoC_UART_RXDATA_REG;
                /*Check status on error*/
                if(rxStatus & (PSoC_UART_RX_STS_BREAK | PSoC_UART_RX_STS_PAR_ERROR |
                               PSoC_UART_RX_STS_STOP_ERROR | PSoC_UART_RX_STS_OVERRUN))
                {
                    rxData = 0u;
                }
            }
        #endif /* PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 PSoC_UART_GetByte(void) 
    {
        return ( ((uint16)PSoC_UART_ReadRxStatus() << 8u) | PSoC_UART_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left 
    *  in the RX buffer
    *
    * Global Variables:
    *  PSoC_UART_rxBufferWrite - used to calculate left bytes. 
    *  PSoC_UART_rxBufferRead - used to calculate left bytes.
    *  PSoC_UART_rxBufferLoopDetect - checked to decide left bytes amount. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 PSoC_UART_GetRxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_DisableRxInt();
            #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */

            if(PSoC_UART_rxBufferRead == PSoC_UART_rxBufferWrite)
            {
                if(PSoC_UART_rxBufferLoopDetect > 0u)
                {
                    size = PSoC_UART_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(PSoC_UART_rxBufferRead < PSoC_UART_rxBufferWrite)
            {
                size = (PSoC_UART_rxBufferWrite - PSoC_UART_rxBufferRead);
            }
            else
            {
                size = (PSoC_UART_RXBUFFERSIZE - PSoC_UART_rxBufferRead) + PSoC_UART_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_EnableRxInt();
            #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */

        #else /* PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = (PSoC_UART_RXSTATUS_REG & PSoC_UART_RX_STS_FIFO_NOTEMPTY) ? 1u : 0u;

        #endif /* End PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_rxBufferWrite - cleared to zero. 
    *  PSoC_UART_rxBufferRead - cleared to zero.
    *  PSoC_UART_rxBufferLoopDetect - cleared to zero. 
    *  PSoC_UART_rxBufferOverflow - cleared to zero. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may 
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void PSoC_UART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        PSoC_UART_RXDATA_AUX_CTL_REG |=  PSoC_UART_RX_FIFO_CLR;
        PSoC_UART_RXDATA_AUX_CTL_REG &= ~PSoC_UART_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
        
        #if(PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_DisableRxInt();
            #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */

            PSoC_UART_rxBufferRead = 0u;
            PSoC_UART_rxBufferWrite = 0u;
            PSoC_UART_rxBufferLoopDetect = 0u;
            PSoC_UART_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(PSoC_UART_RX_INTERRUPT_ENABLED)
                PSoC_UART_EnableRxInt();
            #endif /* End PSoC_UART_RX_INTERRUPT_ENABLED */
        #endif /* End PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */
        
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  PSoC_UART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address 
    *                                               detection
    *  PSoC_UART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer 
    *                                               address detection
    *  PSoC_UART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address 
    *                                               detection
    *  PSoC_UART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer 
    *                                               address detection
    *  PSoC_UART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_rxAddressMode - the parameter stored in this variable for 
    *   the farther usage in RX ISR.
    *  PSoC_UART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void PSoC_UART_SetRxAddressMode(uint8 addressMode)  
                                                        
    {
        #if(PSoC_UART_RXHW_ADDRESS_ENABLED)
            #if(PSoC_UART_CONTROL_REG_REMOVED)
                addressMode = addressMode;
            #else /* PSoC_UART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl = 0u;
                tmpCtrl = PSoC_UART_CONTROL_REG & ~PSoC_UART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= ((addressMode << PSoC_UART_CTRL_RXADDR_MODE0_SHIFT) & 
                           PSoC_UART_CTRL_RXADDR_MODE_MASK);
                PSoC_UART_CONTROL_REG = tmpCtrl;
                #if(PSoC_UART_RX_INTERRUPT_ENABLED && \
                   (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH) )
                    PSoC_UART_rxAddressMode = addressMode;
                    PSoC_UART_rxAddressDetected = 0u;
                #endif /* End PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH*/   
            #endif /* End PSoC_UART_CONTROL_REG_REMOVED */
        #else /* PSoC_UART_RXHW_ADDRESS_ENABLED */
            addressMode = addressMode;
        #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PSoC_UART_SetRxAddress1(uint8 address) 

    {
        PSoC_UART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PSoC_UART_SetRxAddress2(uint8 address) 
    {
        PSoC_UART_RXADDRESS2_REG = address;
    }
        
#endif  /* PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED*/


#if( (PSoC_UART_TX_ENABLED) || (PSoC_UART_HD_ENABLED) )

    #if(PSoC_UART_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: PSoC_UART_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PSoC_UART_EnableTxInt(void) 
        {
            CyIntEnable(PSoC_UART_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: PSoC_UART_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void PSoC_UART_DisableTxInt(void) 
        {
            CyIntDisable(PSoC_UART_TX_VECT_NUM);
        }

    #endif /* PSoC_UART_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: PSoC_UART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void PSoC_UART_SetTxInterruptMode(uint8 intSrc) 
    {
        PSoC_UART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the 
    *  bus is available. WriteTxData sends a byte without checking for buffer room 
    *  or status. It is up to the user to separately check status.    
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  PSoC_UART_txBuffer - RAM buffer pointer for save data for transmission
    *  PSoC_UART_txBufferWrite - cyclic index for write to txBuffer, 
    *    incremented after each byte saved to buffer.
    *  PSoC_UART_txBufferRead - cyclic index for read from txBuffer, 
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PSoC_UART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(PSoC_UART_initVar != 0u)
        {
            #if(PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                    PSoC_UART_DisableTxInt();
                #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

                if( (PSoC_UART_txBufferRead == PSoC_UART_txBufferWrite) &&
                   !(PSoC_UART_TXSTATUS_REG & PSoC_UART_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    PSoC_UART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(PSoC_UART_txBufferWrite >= PSoC_UART_TXBUFFERSIZE)
                    {
                        PSoC_UART_txBufferWrite = 0;
                    }

                    PSoC_UART_txBuffer[PSoC_UART_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    PSoC_UART_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                    PSoC_UART_EnableTxInt();
                #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

            #else /* PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                PSoC_UART_TXDATA_REG = txDataByte;

            #endif /* End PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to 
    *  the user to handle all bits in this return value accordingly, even if the bit 
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.    
    *
    *******************************************************************************/
    uint8 PSoC_UART_ReadTxStatus(void) 
    {
        return(PSoC_UART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_txBuffer - RAM buffer pointer for save data for transmission
    *  PSoC_UART_txBufferWrite - cyclic index for write to txBuffer, 
    *     checked to identify free space in txBuffer and incremented after each byte 
    *     saved to buffer.
    *  PSoC_UART_txBufferRead - cyclic index for read from txBuffer, 
    *     checked to identify free space in txBuffer.
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void PSoC_UART_PutChar(uint8 txDataByte) 
    {
            #if(PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

                /* Block if buffer is full, so we dont overwrite. */
                while( PSoC_UART_txBufferWrite == (PSoC_UART_txBufferRead - 1u) ||
                    (uint8)(PSoC_UART_txBufferWrite - PSoC_UART_txBufferRead) ==
                    (uint8)(PSoC_UART_TXBUFFERSIZE - 1u) )
                {
                    /* Software buffer is full. */
                }
                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                    PSoC_UART_DisableTxInt();
                #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

                if( (PSoC_UART_txBufferRead == PSoC_UART_txBufferWrite) &&
                   !(PSoC_UART_TXSTATUS_REG & PSoC_UART_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    PSoC_UART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(PSoC_UART_txBufferWrite >= PSoC_UART_TXBUFFERSIZE)
                    {
                        PSoC_UART_txBufferWrite = 0;
                    }

                    PSoC_UART_txBuffer[PSoC_UART_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    PSoC_UART_txBufferWrite++;

                }

                /* Enable Rx interrupt. */
                #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                    PSoC_UART_EnableTxInt();
                #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

            #else /* PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

                /* Block if there isnt room. */
                while(PSoC_UART_TXSTATUS_REG & PSoC_UART_TX_STS_FIFO_FULL);

                /* Add directly to the FIFO. */
                PSoC_UART_TXDATA_REG = txDataByte;

            #endif /* End PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole 
    *  string, it will block until the entire string has been written to the 
    *  transmit buffer.
    *
    *******************************************************************************/
    void PSoC_UART_PutString(char* string) 
    {
        /* If not Initialized then skip this function*/
        if(PSoC_UART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(*string != 0u)
            {
                PSoC_UART_PutChar(*string++);
            }
        }
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PSoC_UART_PutArray(uint8* string, uint8 byteCount) 
                                                                    
    {
        /* If not Initialized then skip this function*/
        if(PSoC_UART_initVar != 0u)
        {
            while(byteCount > 0u)
            {
                PSoC_UART_PutChar(*string++);
                byteCount--;
            }
        }
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void PSoC_UART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(PSoC_UART_initVar != 0u)
        {
            PSoC_UART_PutChar(txDataByte);
            PSoC_UART_PutChar(0x0Du);
            PSoC_UART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  PSoC_UART_txBufferWrite - used to calculate left space. 
    *  PSoC_UART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 PSoC_UART_GetTxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                PSoC_UART_DisableTxInt();
            #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

            if(PSoC_UART_txBufferRead == PSoC_UART_txBufferWrite)
            {
                size = 0u;
            }
            else if(PSoC_UART_txBufferRead < PSoC_UART_txBufferWrite)
            {
                size = (PSoC_UART_txBufferWrite - PSoC_UART_txBufferRead);
            }
            else
            {
                size = (PSoC_UART_TXBUFFERSIZE - PSoC_UART_txBufferRead) + PSoC_UART_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                PSoC_UART_EnableTxInt();
            #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

        #else /* PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

            size = PSoC_UART_TXSTATUS_REG;

            /* Is the fifo is full. */
            if(size & PSoC_UART_TX_STS_FIFO_FULL)
            {
                size = PSoC_UART_FIFO_LENGTH;
            }
            else if(size & PSoC_UART_TX_STS_FIFO_EMPTY)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_txBufferWrite - cleared to zero. 
    *  PSoC_UART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void PSoC_UART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        /* clear the HW FIFO */
        PSoC_UART_TXDATA_AUX_CTL_REG |=  PSoC_UART_TX_FIFO_CLR;
        PSoC_UART_TXDATA_AUX_CTL_REG &= ~PSoC_UART_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                PSoC_UART_DisableTxInt();
            #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

            PSoC_UART_txBufferRead = 0u;
            PSoC_UART_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(PSoC_UART_TX_INTERRUPT_ENABLED)
                PSoC_UART_EnableTxInt();
            #endif /* End PSoC_UART_TX_INTERRUPT_ENABLED */

        #endif /* End PSoC_UART_TXBUFFERSIZE > PSoC_UART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return 
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  PSoC_UART_initVar - checked to identify that the component has been  
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition 
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed 
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete 
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void PSoC_UART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(PSoC_UART_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(PSoC_UART_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == PSoC_UART_SEND_BREAK) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() |
                                                          PSoC_UART_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    PSoC_UART_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = PSoC_UART_TXSTATUS_REG;
                    }while(tmpStat & PSoC_UART_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == PSoC_UART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = PSoC_UART_TXSTATUS_REG;
                    }while(~tmpStat & PSoC_UART_TX_STS_COMPLETE);
                }

                if( (retMode == PSoC_UART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PSoC_UART_REINIT) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT) )
                {
                    PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() &
                                                         ~PSoC_UART_CTRL_HD_SEND_BREAK);
                }

            #else /* PSoC_UART_HD_ENABLED Full Duplex mode */

                static uint8 tx_period; 
                
                if( (retMode == PSoC_UART_SEND_BREAK) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit @ Break signal in Full Duplex mode*/
                    if( (PSoC_UART_PARITY_TYPE != PSoC_UART__B_UART__NONE_REVB) ||
                         PSoC_UART_PARITY_TYPE_SW )
                    {
                        PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() |
                                                              PSoC_UART_CTRL_HD_SEND_BREAK);
                    }                                                          

                    #if(PSoC_UART_TXCLKGEN_DP)
                        tx_period = PSoC_UART_TXBITCLKTX_COMPLETE_REG;
                        PSoC_UART_TXBITCLKTX_COMPLETE_REG = PSoC_UART_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = PSoC_UART_TXBITCTR_PERIOD_REG;
                        PSoC_UART_TXBITCTR_PERIOD_REG = PSoC_UART_TXBITCTR_BREAKBITS8X;
                    #endif /* End PSoC_UART_TXCLKGEN_DP */

                    /* Send zeros*/
                    PSoC_UART_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = PSoC_UART_TXSTATUS_REG;
                    }while(tmpStat & PSoC_UART_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == PSoC_UART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = PSoC_UART_TXSTATUS_REG;
                    }while(~tmpStat & PSoC_UART_TX_STS_COMPLETE);
                }

                if( (retMode == PSoC_UART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == PSoC_UART_REINIT) ||
                    (retMode == PSoC_UART_SEND_WAIT_REINIT) )
                {

                    #if(PSoC_UART_TXCLKGEN_DP)
                        PSoC_UART_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        PSoC_UART_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End PSoC_UART_TXCLKGEN_DP */

                    if( (PSoC_UART_PARITY_TYPE != PSoC_UART__B_UART__NONE_REVB) || 
                         PSoC_UART_PARITY_TYPE_SW )
                    {
                        PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() &
                                                             ~PSoC_UART_CTRL_HD_SEND_BREAK);
                    }                                     
                }
            #endif    /* End PSoC_UART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PSoC_UART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
            PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() | PSoC_UART_CTRL_MARK);
        }
        else
        {
            PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() & ~PSoC_UART_CTRL_MARK);
        }
    }

#endif  /* EndPSoC_UART_TX_ENABLED */

#if(PSoC_UART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: PSoC_UART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART. 
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void PSoC_UART_LoadTxConfig(void) 
    {
        #if((PSoC_UART_RX_INTERRUPT_ENABLED) && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            PSoC_UART_SetRxInterruptMode(0);
        #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */

        PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() | PSoC_UART_CTRL_HD_SEND);
        PSoC_UART_RXBITCTR_PERIOD_REG = PSoC_UART_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(PSoC_UART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: PSoC_UART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer 
    *  has been used.
    *
    *******************************************************************************/
    void PSoC_UART_LoadRxConfig(void) 
    {
        PSoC_UART_WriteControlRegister(PSoC_UART_ReadControlRegister() & ~PSoC_UART_CTRL_HD_SEND);
        PSoC_UART_RXBITCTR_PERIOD_REG = PSoC_UART_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(PSoC_UART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((PSoC_UART_RX_INTERRUPT_ENABLED) && (PSoC_UART_RXBUFFERSIZE > PSoC_UART_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            PSoC_UART_SetRxInterruptMode(PSoC_UART_INIT_RX_INTERRUPTS_MASK);    
        #endif /* PSoC_UART_RX_INTERRUPT_ENABLED */
    }

#endif  /* PSoC_UART_HD_ENABLED */


/* [] END OF FILE */
