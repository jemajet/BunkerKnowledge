/*******************************************************************************
* File Name: PSoC_UART_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
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


/***************************************
* Local data allocation
***************************************/

static PSoC_UART_BACKUP_STRUCT  PSoC_UART_backup =
{
    /* enableState - disabled */
    0u,
};        



/*******************************************************************************
* Function Name: PSoC_UART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PSoC_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PSoC_UART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(PSoC_UART_CONTROL_REG_REMOVED == 0u)
            PSoC_UART_backup.cr = PSoC_UART_CONTROL_REG;
        #endif /* End PSoC_UART_CONTROL_REG_REMOVED */

        #if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
            PSoC_UART_backup.rx_period = PSoC_UART_RXBITCTR_PERIOD_REG;
            PSoC_UART_backup.rx_mask = PSoC_UART_RXSTATUS_MASK_REG;
            #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
                PSoC_UART_backup.rx_addr1 = PSoC_UART_RXADDRESS1_REG;
                PSoC_UART_backup.rx_addr2 = PSoC_UART_RXADDRESS2_REG;
            #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End PSoC_UART_RX_ENABLED | PSoC_UART_HD_ENABLED*/

        #if(PSoC_UART_TX_ENABLED)
            #if(PSoC_UART_TXCLKGEN_DP)
                PSoC_UART_backup.tx_clk_ctr = PSoC_UART_TXBITCLKGEN_CTR_REG;
                PSoC_UART_backup.tx_clk_compl = PSoC_UART_TXBITCLKTX_COMPLETE_REG;
            #else
                PSoC_UART_backup.tx_period = PSoC_UART_TXBITCTR_PERIOD_REG;
            #endif /*End PSoC_UART_TXCLKGEN_DP */
            PSoC_UART_backup.tx_mask = PSoC_UART_TXSTATUS_MASK_REG;
        #endif /*End PSoC_UART_TX_ENABLED */

    
    #else /* CY_UDB_V1 */

        #if(PSoC_UART_CONTROL_REG_REMOVED == 0u)
            PSoC_UART_backup.cr = PSoC_UART_CONTROL_REG;
        #endif /* End PSoC_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PSoC_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PSoC_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PSoC_UART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(PSoC_UART_CONTROL_REG_REMOVED == 0u)
            PSoC_UART_CONTROL_REG = PSoC_UART_backup.cr;
        #endif /* End PSoC_UART_CONTROL_REG_REMOVED */

        #if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
            PSoC_UART_RXBITCTR_PERIOD_REG = PSoC_UART_backup.rx_period;
            PSoC_UART_RXSTATUS_MASK_REG = PSoC_UART_backup.rx_mask;
            #if (PSoC_UART_RXHW_ADDRESS_ENABLED)
                PSoC_UART_RXADDRESS1_REG = PSoC_UART_backup.rx_addr1;
                PSoC_UART_RXADDRESS2_REG = PSoC_UART_backup.rx_addr2;
            #endif /* End PSoC_UART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */

        #if(PSoC_UART_TX_ENABLED)
            #if(PSoC_UART_TXCLKGEN_DP)
                PSoC_UART_TXBITCLKGEN_CTR_REG = PSoC_UART_backup.tx_clk_ctr;
                PSoC_UART_TXBITCLKTX_COMPLETE_REG = PSoC_UART_backup.tx_clk_compl;
            #else
                PSoC_UART_TXBITCTR_PERIOD_REG = PSoC_UART_backup.tx_period;
            #endif /*End PSoC_UART_TXCLKGEN_DP */
            PSoC_UART_TXSTATUS_MASK_REG = PSoC_UART_backup.tx_mask;
        #endif /*End PSoC_UART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(PSoC_UART_CONTROL_REG_REMOVED == 0u)
            PSoC_UART_CONTROL_REG = PSoC_UART_backup.cr;
        #endif /* End PSoC_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PSoC_UART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PSoC_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PSoC_UART_Sleep(void)
{

    #if(PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED)
        if((PSoC_UART_RXSTATUS_ACTL_REG  & PSoC_UART_INT_ENABLE) != 0u) 
        {
            PSoC_UART_backup.enableState = 1u;
        }
        else
        {
            PSoC_UART_backup.enableState = 0u;
        }
    #else
        if((PSoC_UART_TXSTATUS_ACTL_REG  & PSoC_UART_INT_ENABLE) !=0u)
        {
            PSoC_UART_backup.enableState = 1u;
        }
        else
        {
            PSoC_UART_backup.enableState = 0u;
        }
    #endif /* End PSoC_UART_RX_ENABLED || PSoC_UART_HD_ENABLED*/

    PSoC_UART_Stop();
    PSoC_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: PSoC_UART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PSoC_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PSoC_UART_Wakeup(void)
{
    PSoC_UART_RestoreConfig();
    #if( (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) )
        PSoC_UART_ClearRxBuffer();
    #endif /* End (PSoC_UART_RX_ENABLED) || (PSoC_UART_HD_ENABLED) */
    #if(PSoC_UART_TX_ENABLED || PSoC_UART_HD_ENABLED)
        PSoC_UART_ClearTxBuffer();
    #endif /* End PSoC_UART_TX_ENABLED || PSoC_UART_HD_ENABLED */

    if(PSoC_UART_backup.enableState != 0u)
    {
        PSoC_UART_Enable();
    } 
}


/* [] END OF FILE */
