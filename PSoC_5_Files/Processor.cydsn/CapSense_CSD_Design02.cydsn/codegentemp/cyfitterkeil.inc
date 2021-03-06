#ifndef INCLUDED_CYFITTERKEIL_INC
#define INCLUDED_CYFITTERKEIL_INC
$INCLUDE (cydevicekeil.inc)
$INCLUDE (cydevicekeil_trm.inc)

; LCD_LCDPort
LCD_LCDPort__0__INTTYPE EQU CYREG_PICU2_INTTYPE0
LCD_LCDPort__0__MASK EQU 0x01
LCD_LCDPort__0__PC EQU CYREG_PRT2_PC0
LCD_LCDPort__0__PORT EQU 2
LCD_LCDPort__0__SHIFT EQU 0
LCD_LCDPort__1__INTTYPE EQU CYREG_PICU2_INTTYPE1
LCD_LCDPort__1__MASK EQU 0x02
LCD_LCDPort__1__PC EQU CYREG_PRT2_PC1
LCD_LCDPort__1__PORT EQU 2
LCD_LCDPort__1__SHIFT EQU 1
LCD_LCDPort__2__INTTYPE EQU CYREG_PICU2_INTTYPE2
LCD_LCDPort__2__MASK EQU 0x04
LCD_LCDPort__2__PC EQU CYREG_PRT2_PC2
LCD_LCDPort__2__PORT EQU 2
LCD_LCDPort__2__SHIFT EQU 2
LCD_LCDPort__3__INTTYPE EQU CYREG_PICU2_INTTYPE3
LCD_LCDPort__3__MASK EQU 0x08
LCD_LCDPort__3__PC EQU CYREG_PRT2_PC3
LCD_LCDPort__3__PORT EQU 2
LCD_LCDPort__3__SHIFT EQU 3
LCD_LCDPort__4__INTTYPE EQU CYREG_PICU2_INTTYPE4
LCD_LCDPort__4__MASK EQU 0x10
LCD_LCDPort__4__PC EQU CYREG_PRT2_PC4
LCD_LCDPort__4__PORT EQU 2
LCD_LCDPort__4__SHIFT EQU 4
LCD_LCDPort__5__INTTYPE EQU CYREG_PICU2_INTTYPE5
LCD_LCDPort__5__MASK EQU 0x20
LCD_LCDPort__5__PC EQU CYREG_PRT2_PC5
LCD_LCDPort__5__PORT EQU 2
LCD_LCDPort__5__SHIFT EQU 5
LCD_LCDPort__6__INTTYPE EQU CYREG_PICU2_INTTYPE6
LCD_LCDPort__6__MASK EQU 0x40
LCD_LCDPort__6__PC EQU CYREG_PRT2_PC6
LCD_LCDPort__6__PORT EQU 2
LCD_LCDPort__6__SHIFT EQU 6
LCD_LCDPort__AG EQU CYREG_PRT2_AG
LCD_LCDPort__AMUX EQU CYREG_PRT2_AMUX
LCD_LCDPort__BIE EQU CYREG_PRT2_BIE
LCD_LCDPort__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LCD_LCDPort__BYP EQU CYREG_PRT2_BYP
LCD_LCDPort__CTL EQU CYREG_PRT2_CTL
LCD_LCDPort__DM0 EQU CYREG_PRT2_DM0
LCD_LCDPort__DM1 EQU CYREG_PRT2_DM1
LCD_LCDPort__DM2 EQU CYREG_PRT2_DM2
LCD_LCDPort__DR EQU CYREG_PRT2_DR
LCD_LCDPort__INP_DIS EQU CYREG_PRT2_INP_DIS
LCD_LCDPort__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
LCD_LCDPort__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LCD_LCDPort__LCD_EN EQU CYREG_PRT2_LCD_EN
LCD_LCDPort__MASK EQU 0x7F
LCD_LCDPort__PORT EQU 2
LCD_LCDPort__PRT EQU CYREG_PRT2_PRT
LCD_LCDPort__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LCD_LCDPort__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LCD_LCDPort__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LCD_LCDPort__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LCD_LCDPort__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LCD_LCDPort__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LCD_LCDPort__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LCD_LCDPort__PS EQU CYREG_PRT2_PS
LCD_LCDPort__SHIFT EQU 0
LCD_LCDPort__SLW EQU CYREG_PRT2_SLW

; LED1
LED1__0__INTTYPE EQU CYREG_PICU1_INTTYPE6
LED1__0__MASK EQU 0x40
LED1__0__PC EQU CYREG_PRT1_PC6
LED1__0__PORT EQU 1
LED1__0__SHIFT EQU 6
LED1__AG EQU CYREG_PRT1_AG
LED1__AMUX EQU CYREG_PRT1_AMUX
LED1__BIE EQU CYREG_PRT1_BIE
LED1__BIT_MASK EQU CYREG_PRT1_BIT_MASK
LED1__BYP EQU CYREG_PRT1_BYP
LED1__CTL EQU CYREG_PRT1_CTL
LED1__DM0 EQU CYREG_PRT1_DM0
LED1__DM1 EQU CYREG_PRT1_DM1
LED1__DM2 EQU CYREG_PRT1_DM2
LED1__DR EQU CYREG_PRT1_DR
LED1__INP_DIS EQU CYREG_PRT1_INP_DIS
LED1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU1_BASE
LED1__LCD_COM_SEG EQU CYREG_PRT1_LCD_COM_SEG
LED1__LCD_EN EQU CYREG_PRT1_LCD_EN
LED1__MASK EQU 0x40
LED1__PORT EQU 1
LED1__PRT EQU CYREG_PRT1_PRT
LED1__PRTDSI__CAPS_SEL EQU CYREG_PRT1_CAPS_SEL
LED1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT1_DBL_SYNC_IN
LED1__PRTDSI__OE_SEL0 EQU CYREG_PRT1_OE_SEL0
LED1__PRTDSI__OE_SEL1 EQU CYREG_PRT1_OE_SEL1
LED1__PRTDSI__OUT_SEL0 EQU CYREG_PRT1_OUT_SEL0
LED1__PRTDSI__OUT_SEL1 EQU CYREG_PRT1_OUT_SEL1
LED1__PRTDSI__SYNC_OUT EQU CYREG_PRT1_SYNC_OUT
LED1__PS EQU CYREG_PRT1_PS
LED1__SHIFT EQU 6
LED1__SLW EQU CYREG_PRT1_SLW

; LED2
LED2__0__INTTYPE EQU CYREG_PICU1_INTTYPE7
LED2__0__MASK EQU 0x80
LED2__0__PC EQU CYREG_PRT1_PC7
LED2__0__PORT EQU 1
LED2__0__SHIFT EQU 7
LED2__AG EQU CYREG_PRT1_AG
LED2__AMUX EQU CYREG_PRT1_AMUX
LED2__BIE EQU CYREG_PRT1_BIE
LED2__BIT_MASK EQU CYREG_PRT1_BIT_MASK
LED2__BYP EQU CYREG_PRT1_BYP
LED2__CTL EQU CYREG_PRT1_CTL
LED2__DM0 EQU CYREG_PRT1_DM0
LED2__DM1 EQU CYREG_PRT1_DM1
LED2__DM2 EQU CYREG_PRT1_DM2
LED2__DR EQU CYREG_PRT1_DR
LED2__INP_DIS EQU CYREG_PRT1_INP_DIS
LED2__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU1_BASE
LED2__LCD_COM_SEG EQU CYREG_PRT1_LCD_COM_SEG
LED2__LCD_EN EQU CYREG_PRT1_LCD_EN
LED2__MASK EQU 0x80
LED2__PORT EQU 1
LED2__PRT EQU CYREG_PRT1_PRT
LED2__PRTDSI__CAPS_SEL EQU CYREG_PRT1_CAPS_SEL
LED2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT1_DBL_SYNC_IN
LED2__PRTDSI__OE_SEL0 EQU CYREG_PRT1_OE_SEL0
LED2__PRTDSI__OE_SEL1 EQU CYREG_PRT1_OE_SEL1
LED2__PRTDSI__OUT_SEL0 EQU CYREG_PRT1_OUT_SEL0
LED2__PRTDSI__OUT_SEL1 EQU CYREG_PRT1_OUT_SEL1
LED2__PRTDSI__SYNC_OUT EQU CYREG_PRT1_SYNC_OUT
LED2__PS EQU CYREG_PRT1_PS
LED2__SHIFT EQU 7
LED2__SLW EQU CYREG_PRT1_SLW

; CapSense_CSD_BufCH0
CapSense_CSD_BufCH0__CFG0 EQU CYREG_CAPSL_CFG0
CapSense_CSD_BufCH0__CFG1 EQU CYREG_CAPSL_CFG1
CapSense_CSD_BufCH0__PM_ACT_CFG EQU CYREG_PM_ACT_CFG11
CapSense_CSD_BufCH0__PM_ACT_MSK EQU 0x10
CapSense_CSD_BufCH0__PM_STBY_CFG EQU CYREG_PM_STBY_CFG11
CapSense_CSD_BufCH0__PM_STBY_MSK EQU 0x10

; CapSense_CSD_ClockGen
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB10_11_A0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB10_11_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB10_11_D0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB10_11_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_11_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB10_11_F0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB10_11_F1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__A0_A1_REG EQU CYREG_B0_UDB10_A0_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__A0_REG EQU CYREG_B0_UDB10_A0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__A1_REG EQU CYREG_B0_UDB10_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__D0_D1_REG EQU CYREG_B0_UDB10_D0_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__D0_REG EQU CYREG_B0_UDB10_D0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__D1_REG EQU CYREG_B0_UDB10_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB10_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u0__F0_F1_REG EQU CYREG_B0_UDB10_F0_F1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__F0_REG EQU CYREG_B0_UDB10_F0
CapSense_CSD_ClockGen_sC16_PRSdp_u0__F1_REG EQU CYREG_B0_UDB10_F1
CapSense_CSD_ClockGen_sC16_PRSdp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_A0_REG EQU CYREG_B0_UDB11_12_A0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_A1_REG EQU CYREG_B0_UDB11_12_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_D0_REG EQU CYREG_B0_UDB11_12_D0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_D1_REG EQU CYREG_B0_UDB11_12_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB11_12_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_F0_REG EQU CYREG_B0_UDB11_12_F0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__16BIT_F1_REG EQU CYREG_B0_UDB11_12_F1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__A0_A1_REG EQU CYREG_B0_UDB11_A0_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__A0_REG EQU CYREG_B0_UDB11_A0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__A1_REG EQU CYREG_B0_UDB11_A1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__D0_D1_REG EQU CYREG_B0_UDB11_D0_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__D0_REG EQU CYREG_B0_UDB11_D0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__D1_REG EQU CYREG_B0_UDB11_D1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__DP_AUX_CTL_REG EQU CYREG_B0_UDB11_ACTL
CapSense_CSD_ClockGen_sC16_PRSdp_u1__F0_F1_REG EQU CYREG_B0_UDB11_F0_F1
CapSense_CSD_ClockGen_sC16_PRSdp_u1__F0_REG EQU CYREG_B0_UDB11_F0
CapSense_CSD_ClockGen_sC16_PRSdp_u1__F1_REG EQU CYREG_B0_UDB11_F1
CapSense_CSD_ClockGen_ScanSpeed__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB10_11_ACTL
CapSense_CSD_ClockGen_ScanSpeed__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_CSD_ClockGen_ScanSpeed__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_CSD_ClockGen_ScanSpeed__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_CSD_ClockGen_ScanSpeed__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_CSD_ClockGen_ScanSpeed__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_CSD_ClockGen_ScanSpeed__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_CSD_ClockGen_ScanSpeed__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_CSD_ClockGen_ScanSpeed__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_CSD_ClockGen_ScanSpeed__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB10_ACTL
CapSense_CSD_ClockGen_ScanSpeed__CONTROL_REG EQU CYREG_B0_UDB10_CTL
CapSense_CSD_ClockGen_ScanSpeed__CONTROL_ST_REG EQU CYREG_B0_UDB10_ST_CTL
CapSense_CSD_ClockGen_ScanSpeed__COUNT_REG EQU CYREG_B0_UDB10_CTL
CapSense_CSD_ClockGen_ScanSpeed__COUNT_ST_REG EQU CYREG_B0_UDB10_ST_CTL
CapSense_CSD_ClockGen_ScanSpeed__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_CSD_ClockGen_ScanSpeed__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_CSD_ClockGen_ScanSpeed__PERIOD_REG EQU CYREG_B0_UDB10_MSK
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__0__MASK EQU 0x01
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__0__POS EQU 0
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__1__MASK EQU 0x02
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__1__POS EQU 1
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB09_10_ACTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB09_10_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB09_10_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB09_10_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB09_10_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB09_10_MSK
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB09_10_MSK
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB09_10_MSK
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB09_10_MSK
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__2__MASK EQU 0x04
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__2__POS EQU 2
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__4__MASK EQU 0x10
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__4__POS EQU 4
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB09_ACTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__CONTROL_REG EQU CYREG_B0_UDB09_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__CONTROL_ST_REG EQU CYREG_B0_UDB09_ST_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__COUNT_REG EQU CYREG_B0_UDB09_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__COUNT_ST_REG EQU CYREG_B0_UDB09_ST_CTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__MASK EQU 0x17
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB09_MSK_ACTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB09_MSK_ACTL
CapSense_CSD_ClockGen_SyncCtrl_CtrlReg__PERIOD_REG EQU CYREG_B0_UDB09_MSK
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_A0_REG EQU CYREG_B0_UDB09_10_A0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_A1_REG EQU CYREG_B0_UDB09_10_A1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_D0_REG EQU CYREG_B0_UDB09_10_D0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_D1_REG EQU CYREG_B0_UDB09_10_D1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB09_10_ACTL
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_F0_REG EQU CYREG_B0_UDB09_10_F0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__16BIT_F1_REG EQU CYREG_B0_UDB09_10_F1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__A0_A1_REG EQU CYREG_B0_UDB09_A0_A1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__A0_REG EQU CYREG_B0_UDB09_A0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__A1_REG EQU CYREG_B0_UDB09_A1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__D0_D1_REG EQU CYREG_B0_UDB09_D0_D1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__D0_REG EQU CYREG_B0_UDB09_D0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__D1_REG EQU CYREG_B0_UDB09_D1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB09_ACTL
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__F0_F1_REG EQU CYREG_B0_UDB09_F0_F1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__F0_REG EQU CYREG_B0_UDB09_F0
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__F1_REG EQU CYREG_B0_UDB09_F1
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB09_MSK_ACTL
CapSense_CSD_ClockGen_UDB_PrescalerDp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB09_MSK_ACTL

; CapSense_CSD_CmodCH0
CapSense_CSD_CmodCH0__0__INTTYPE EQU CYREG_PICU2_INTTYPE7
CapSense_CSD_CmodCH0__0__MASK EQU 0x80
CapSense_CSD_CmodCH0__0__PC EQU CYREG_PRT2_PC7
CapSense_CSD_CmodCH0__0__PORT EQU 2
CapSense_CSD_CmodCH0__0__SHIFT EQU 7
CapSense_CSD_CmodCH0__AG EQU CYREG_PRT2_AG
CapSense_CSD_CmodCH0__AMUX EQU CYREG_PRT2_AMUX
CapSense_CSD_CmodCH0__BIE EQU CYREG_PRT2_BIE
CapSense_CSD_CmodCH0__BIT_MASK EQU CYREG_PRT2_BIT_MASK
CapSense_CSD_CmodCH0__BYP EQU CYREG_PRT2_BYP
CapSense_CSD_CmodCH0__Cmod_CH0__INTTYPE EQU CYREG_PICU2_INTTYPE7
CapSense_CSD_CmodCH0__Cmod_CH0__MASK EQU 0x80
CapSense_CSD_CmodCH0__Cmod_CH0__PC EQU CYREG_PRT2_PC7
CapSense_CSD_CmodCH0__Cmod_CH0__PORT EQU 2
CapSense_CSD_CmodCH0__Cmod_CH0__SHIFT EQU 7
CapSense_CSD_CmodCH0__CTL EQU CYREG_PRT2_CTL
CapSense_CSD_CmodCH0__DM0 EQU CYREG_PRT2_DM0
CapSense_CSD_CmodCH0__DM1 EQU CYREG_PRT2_DM1
CapSense_CSD_CmodCH0__DM2 EQU CYREG_PRT2_DM2
CapSense_CSD_CmodCH0__DR EQU CYREG_PRT2_DR
CapSense_CSD_CmodCH0__INP_DIS EQU CYREG_PRT2_INP_DIS
CapSense_CSD_CmodCH0__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
CapSense_CSD_CmodCH0__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
CapSense_CSD_CmodCH0__LCD_EN EQU CYREG_PRT2_LCD_EN
CapSense_CSD_CmodCH0__MASK EQU 0x80
CapSense_CSD_CmodCH0__PORT EQU 2
CapSense_CSD_CmodCH0__PRT EQU CYREG_PRT2_PRT
CapSense_CSD_CmodCH0__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
CapSense_CSD_CmodCH0__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
CapSense_CSD_CmodCH0__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
CapSense_CSD_CmodCH0__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
CapSense_CSD_CmodCH0__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
CapSense_CSD_CmodCH0__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
CapSense_CSD_CmodCH0__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
CapSense_CSD_CmodCH0__PS EQU CYREG_PRT2_PS
CapSense_CSD_CmodCH0__SHIFT EQU 7
CapSense_CSD_CmodCH0__SLW EQU CYREG_PRT2_SLW

; CapSense_CSD_CompCH0_ctComp
CapSense_CSD_CompCH0_ctComp__CLK EQU CYREG_CMP2_CLK
CapSense_CSD_CompCH0_ctComp__CMP_MASK EQU 0x04
CapSense_CSD_CompCH0_ctComp__CMP_NUMBER EQU 2
CapSense_CSD_CompCH0_ctComp__CR EQU CYREG_CMP2_CR
CapSense_CSD_CompCH0_ctComp__LUT__CR EQU CYREG_LUT2_CR
CapSense_CSD_CompCH0_ctComp__LUT__MSK EQU CYREG_LUT_MSK
CapSense_CSD_CompCH0_ctComp__LUT__MSK_MASK EQU 0x04
CapSense_CSD_CompCH0_ctComp__LUT__MSK_SHIFT EQU 2
CapSense_CSD_CompCH0_ctComp__LUT__MX EQU CYREG_LUT2_MX
CapSense_CSD_CompCH0_ctComp__LUT__SR EQU CYREG_LUT_SR
CapSense_CSD_CompCH0_ctComp__LUT__SR_MASK EQU 0x04
CapSense_CSD_CompCH0_ctComp__LUT__SR_SHIFT EQU 2
CapSense_CSD_CompCH0_ctComp__PM_ACT_CFG EQU CYREG_PM_ACT_CFG7
CapSense_CSD_CompCH0_ctComp__PM_ACT_MSK EQU 0x04
CapSense_CSD_CompCH0_ctComp__PM_STBY_CFG EQU CYREG_PM_STBY_CFG7
CapSense_CSD_CompCH0_ctComp__PM_STBY_MSK EQU 0x04
CapSense_CSD_CompCH0_ctComp__SW0 EQU CYREG_CMP2_SW0
CapSense_CSD_CompCH0_ctComp__SW2 EQU CYREG_CMP2_SW2
CapSense_CSD_CompCH0_ctComp__SW3 EQU CYREG_CMP2_SW3
CapSense_CSD_CompCH0_ctComp__SW4 EQU CYREG_CMP2_SW4
CapSense_CSD_CompCH0_ctComp__SW6 EQU CYREG_CMP2_SW6
CapSense_CSD_CompCH0_ctComp__TR0 EQU CYREG_CMP2_TR0
CapSense_CSD_CompCH0_ctComp__TR1 EQU CYREG_CMP2_TR1
CapSense_CSD_CompCH0_ctComp__TRIM__TR0 EQU CYREG_FLSHID_MFG_CFG_CMP2_TR0
CapSense_CSD_CompCH0_ctComp__TRIM__TR0_HS EQU CYREG_FLSHID_CUST_TABLES_CMP2_TR0_HS
CapSense_CSD_CompCH0_ctComp__TRIM__TR1 EQU CYREG_FLSHID_MFG_CFG_CMP2_TR1
CapSense_CSD_CompCH0_ctComp__TRIM__TR1_HS EQU CYREG_FLSHID_CUST_TABLES_CMP2_TR1_HS
CapSense_CSD_CompCH0_ctComp__WRK EQU CYREG_CMP_WRK
CapSense_CSD_CompCH0_ctComp__WRK_MASK EQU 0x04
CapSense_CSD_CompCH0_ctComp__WRK_SHIFT EQU 2

; CapSense_CSD_IdacCH0_viDAC8
CapSense_CSD_IdacCH0_viDAC8__CR0 EQU CYREG_DAC0_CR0
CapSense_CSD_IdacCH0_viDAC8__CR1 EQU CYREG_DAC0_CR1
CapSense_CSD_IdacCH0_viDAC8__D EQU CYREG_DAC0_D
CapSense_CSD_IdacCH0_viDAC8__PM_ACT_CFG EQU CYREG_PM_ACT_CFG8
CapSense_CSD_IdacCH0_viDAC8__PM_ACT_MSK EQU 0x01
CapSense_CSD_IdacCH0_viDAC8__PM_STBY_CFG EQU CYREG_PM_STBY_CFG8
CapSense_CSD_IdacCH0_viDAC8__PM_STBY_MSK EQU 0x01
CapSense_CSD_IdacCH0_viDAC8__STROBE EQU CYREG_DAC0_STROBE
CapSense_CSD_IdacCH0_viDAC8__SW0 EQU CYREG_DAC0_SW0
CapSense_CSD_IdacCH0_viDAC8__SW2 EQU CYREG_DAC0_SW2
CapSense_CSD_IdacCH0_viDAC8__SW3 EQU CYREG_DAC0_SW3
CapSense_CSD_IdacCH0_viDAC8__SW4 EQU CYREG_DAC0_SW4
CapSense_CSD_IdacCH0_viDAC8__TR EQU CYREG_DAC0_TR
CapSense_CSD_IdacCH0_viDAC8__TRIM__M1 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M1
CapSense_CSD_IdacCH0_viDAC8__TRIM__M2 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M2
CapSense_CSD_IdacCH0_viDAC8__TRIM__M3 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M3
CapSense_CSD_IdacCH0_viDAC8__TRIM__M4 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M4
CapSense_CSD_IdacCH0_viDAC8__TRIM__M5 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M5
CapSense_CSD_IdacCH0_viDAC8__TRIM__M6 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M6
CapSense_CSD_IdacCH0_viDAC8__TRIM__M7 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M7
CapSense_CSD_IdacCH0_viDAC8__TRIM__M8 EQU CYREG_FLSHID_CUST_TABLES_DAC0_M8
CapSense_CSD_IdacCH0_viDAC8__TST EQU CYREG_DAC0_TST

; CapSense_CSD_IntClock
CapSense_CSD_IntClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
CapSense_CSD_IntClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
CapSense_CSD_IntClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
CapSense_CSD_IntClock__CFG2_SRC_SEL_MASK EQU 0x07
CapSense_CSD_IntClock__INDEX EQU 0x00
CapSense_CSD_IntClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
CapSense_CSD_IntClock__PM_ACT_MSK EQU 0x01
CapSense_CSD_IntClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
CapSense_CSD_IntClock__PM_STBY_MSK EQU 0x01

; CapSense_CSD_IsrCH0
CapSense_CSD_IsrCH0__ES2_PATCH EQU 0
CapSense_CSD_IsrCH0__INTC_CLR_EN_REG EQU CYREG_INTC_CLR_EN0
CapSense_CSD_IsrCH0__INTC_CLR_PD_REG EQU CYREG_INTC_CLR_PD0
CapSense_CSD_IsrCH0__INTC_MASK EQU 0x01
CapSense_CSD_IsrCH0__INTC_NUMBER EQU 0
CapSense_CSD_IsrCH0__INTC_PRIOR_NUM EQU 7
CapSense_CSD_IsrCH0__INTC_PRIOR_REG EQU CYREG_INTC_PRIOR0
CapSense_CSD_IsrCH0__INTC_SET_EN_REG EQU CYREG_INTC_SET_EN0
CapSense_CSD_IsrCH0__INTC_SET_PD_REG EQU CYREG_INTC_SET_PD0
CapSense_CSD_IsrCH0__INTC_VECT EQU (CYREG_INTC_VECT_MBASE+0x00)

; CapSense_CSD_MeasureCH0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_A0_REG EQU CYREG_B0_UDB13_14_A0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_A1_REG EQU CYREG_B0_UDB13_14_A1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_D0_REG EQU CYREG_B0_UDB13_14_D0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_D1_REG EQU CYREG_B0_UDB13_14_D1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_F0_REG EQU CYREG_B0_UDB13_14_F0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__16BIT_F1_REG EQU CYREG_B0_UDB13_14_F1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__A0_A1_REG EQU CYREG_B0_UDB13_A0_A1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__A0_REG EQU CYREG_B0_UDB13_A0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__A1_REG EQU CYREG_B0_UDB13_A1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__D0_D1_REG EQU CYREG_B0_UDB13_D0_D1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__D0_REG EQU CYREG_B0_UDB13_D0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__D1_REG EQU CYREG_B0_UDB13_D1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
CapSense_CSD_MeasureCH0_UDB_Counter_u0__F0_F1_REG EQU CYREG_B0_UDB13_F0_F1
CapSense_CSD_MeasureCH0_UDB_Counter_u0__F0_REG EQU CYREG_B0_UDB13_F0
CapSense_CSD_MeasureCH0_UDB_Counter_u0__F1_REG EQU CYREG_B0_UDB13_F1
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_A0_REG EQU CYREG_B0_UDB12_13_A0
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_A1_REG EQU CYREG_B0_UDB12_13_A1
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_D0_REG EQU CYREG_B0_UDB12_13_D0
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_D1_REG EQU CYREG_B0_UDB12_13_D1
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB12_13_ACTL
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_F0_REG EQU CYREG_B0_UDB12_13_F0
CapSense_CSD_MeasureCH0_UDB_Window_u0__16BIT_F1_REG EQU CYREG_B0_UDB12_13_F1
CapSense_CSD_MeasureCH0_UDB_Window_u0__A0_A1_REG EQU CYREG_B0_UDB12_A0_A1
CapSense_CSD_MeasureCH0_UDB_Window_u0__A0_REG EQU CYREG_B0_UDB12_A0
CapSense_CSD_MeasureCH0_UDB_Window_u0__A1_REG EQU CYREG_B0_UDB12_A1
CapSense_CSD_MeasureCH0_UDB_Window_u0__D0_D1_REG EQU CYREG_B0_UDB12_D0_D1
CapSense_CSD_MeasureCH0_UDB_Window_u0__D0_REG EQU CYREG_B0_UDB12_D0
CapSense_CSD_MeasureCH0_UDB_Window_u0__D1_REG EQU CYREG_B0_UDB12_D1
CapSense_CSD_MeasureCH0_UDB_Window_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB12_ACTL
CapSense_CSD_MeasureCH0_UDB_Window_u0__F0_F1_REG EQU CYREG_B0_UDB12_F0_F1
CapSense_CSD_MeasureCH0_UDB_Window_u0__F0_REG EQU CYREG_B0_UDB12_F0
CapSense_CSD_MeasureCH0_UDB_Window_u0__F1_REG EQU CYREG_B0_UDB12_F1

; CapSense_CSD_PortCH0
CapSense_CSD_PortCH0__0__INTTYPE EQU CYREG_PICU0_INTTYPE5
CapSense_CSD_PortCH0__0__MASK EQU 0x20
CapSense_CSD_PortCH0__0__PC EQU CYREG_PRT0_PC5
CapSense_CSD_PortCH0__0__PORT EQU 0
CapSense_CSD_PortCH0__0__SHIFT EQU 5
CapSense_CSD_PortCH0__1__INTTYPE EQU CYREG_PICU0_INTTYPE6
CapSense_CSD_PortCH0__1__MASK EQU 0x40
CapSense_CSD_PortCH0__1__PC EQU CYREG_PRT0_PC6
CapSense_CSD_PortCH0__1__PORT EQU 0
CapSense_CSD_PortCH0__1__SHIFT EQU 6
CapSense_CSD_PortCH0__2__INTTYPE EQU CYREG_PICU0_INTTYPE0
CapSense_CSD_PortCH0__2__MASK EQU 0x01
CapSense_CSD_PortCH0__2__PC EQU CYREG_PRT0_PC0
CapSense_CSD_PortCH0__2__PORT EQU 0
CapSense_CSD_PortCH0__2__SHIFT EQU 0
CapSense_CSD_PortCH0__3__INTTYPE EQU CYREG_PICU0_INTTYPE1
CapSense_CSD_PortCH0__3__MASK EQU 0x02
CapSense_CSD_PortCH0__3__PC EQU CYREG_PRT0_PC1
CapSense_CSD_PortCH0__3__PORT EQU 0
CapSense_CSD_PortCH0__3__SHIFT EQU 1
CapSense_CSD_PortCH0__4__INTTYPE EQU CYREG_PICU0_INTTYPE2
CapSense_CSD_PortCH0__4__MASK EQU 0x04
CapSense_CSD_PortCH0__4__PC EQU CYREG_PRT0_PC2
CapSense_CSD_PortCH0__4__PORT EQU 0
CapSense_CSD_PortCH0__4__SHIFT EQU 2
CapSense_CSD_PortCH0__5__INTTYPE EQU CYREG_PICU0_INTTYPE3
CapSense_CSD_PortCH0__5__MASK EQU 0x08
CapSense_CSD_PortCH0__5__PC EQU CYREG_PRT0_PC3
CapSense_CSD_PortCH0__5__PORT EQU 0
CapSense_CSD_PortCH0__5__SHIFT EQU 3
CapSense_CSD_PortCH0__6__INTTYPE EQU CYREG_PICU0_INTTYPE4
CapSense_CSD_PortCH0__6__MASK EQU 0x10
CapSense_CSD_PortCH0__6__PC EQU CYREG_PRT0_PC4
CapSense_CSD_PortCH0__6__PORT EQU 0
CapSense_CSD_PortCH0__6__SHIFT EQU 4
CapSense_CSD_PortCH0__AG EQU CYREG_PRT0_AG
CapSense_CSD_PortCH0__AMUX EQU CYREG_PRT0_AMUX
CapSense_CSD_PortCH0__BIE EQU CYREG_PRT0_BIE
CapSense_CSD_PortCH0__BIT_MASK EQU CYREG_PRT0_BIT_MASK
CapSense_CSD_PortCH0__Button0__BTN__INTTYPE EQU CYREG_PICU0_INTTYPE5
CapSense_CSD_PortCH0__Button0__BTN__MASK EQU 0x20
CapSense_CSD_PortCH0__Button0__BTN__PC EQU CYREG_PRT0_PC5
CapSense_CSD_PortCH0__Button0__BTN__PORT EQU 0
CapSense_CSD_PortCH0__Button0__BTN__SHIFT EQU 5
CapSense_CSD_PortCH0__Button1__BTN__INTTYPE EQU CYREG_PICU0_INTTYPE6
CapSense_CSD_PortCH0__Button1__BTN__MASK EQU 0x40
CapSense_CSD_PortCH0__Button1__BTN__PC EQU CYREG_PRT0_PC6
CapSense_CSD_PortCH0__Button1__BTN__PORT EQU 0
CapSense_CSD_PortCH0__Button1__BTN__SHIFT EQU 6
CapSense_CSD_PortCH0__BYP EQU CYREG_PRT0_BYP
CapSense_CSD_PortCH0__CTL EQU CYREG_PRT0_CTL
CapSense_CSD_PortCH0__DM0 EQU CYREG_PRT0_DM0
CapSense_CSD_PortCH0__DM1 EQU CYREG_PRT0_DM1
CapSense_CSD_PortCH0__DM2 EQU CYREG_PRT0_DM2
CapSense_CSD_PortCH0__DR EQU CYREG_PRT0_DR
CapSense_CSD_PortCH0__INP_DIS EQU CYREG_PRT0_INP_DIS
CapSense_CSD_PortCH0__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
CapSense_CSD_PortCH0__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
CapSense_CSD_PortCH0__LCD_EN EQU CYREG_PRT0_LCD_EN
CapSense_CSD_PortCH0__LinearSlider0_e0__LS__INTTYPE EQU CYREG_PICU0_INTTYPE0
CapSense_CSD_PortCH0__LinearSlider0_e0__LS__MASK EQU 0x01
CapSense_CSD_PortCH0__LinearSlider0_e0__LS__PC EQU CYREG_PRT0_PC0
CapSense_CSD_PortCH0__LinearSlider0_e0__LS__PORT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e0__LS__SHIFT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e1__LS__INTTYPE EQU CYREG_PICU0_INTTYPE1
CapSense_CSD_PortCH0__LinearSlider0_e1__LS__MASK EQU 0x02
CapSense_CSD_PortCH0__LinearSlider0_e1__LS__PC EQU CYREG_PRT0_PC1
CapSense_CSD_PortCH0__LinearSlider0_e1__LS__PORT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e1__LS__SHIFT EQU 1
CapSense_CSD_PortCH0__LinearSlider0_e2__LS__INTTYPE EQU CYREG_PICU0_INTTYPE2
CapSense_CSD_PortCH0__LinearSlider0_e2__LS__MASK EQU 0x04
CapSense_CSD_PortCH0__LinearSlider0_e2__LS__PC EQU CYREG_PRT0_PC2
CapSense_CSD_PortCH0__LinearSlider0_e2__LS__PORT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e2__LS__SHIFT EQU 2
CapSense_CSD_PortCH0__LinearSlider0_e3__LS__INTTYPE EQU CYREG_PICU0_INTTYPE3
CapSense_CSD_PortCH0__LinearSlider0_e3__LS__MASK EQU 0x08
CapSense_CSD_PortCH0__LinearSlider0_e3__LS__PC EQU CYREG_PRT0_PC3
CapSense_CSD_PortCH0__LinearSlider0_e3__LS__PORT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e3__LS__SHIFT EQU 3
CapSense_CSD_PortCH0__LinearSlider0_e4__LS__INTTYPE EQU CYREG_PICU0_INTTYPE4
CapSense_CSD_PortCH0__LinearSlider0_e4__LS__MASK EQU 0x10
CapSense_CSD_PortCH0__LinearSlider0_e4__LS__PC EQU CYREG_PRT0_PC4
CapSense_CSD_PortCH0__LinearSlider0_e4__LS__PORT EQU 0
CapSense_CSD_PortCH0__LinearSlider0_e4__LS__SHIFT EQU 4
CapSense_CSD_PortCH0__PORT EQU 0
CapSense_CSD_PortCH0__PRT EQU CYREG_PRT0_PRT
CapSense_CSD_PortCH0__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
CapSense_CSD_PortCH0__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
CapSense_CSD_PortCH0__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
CapSense_CSD_PortCH0__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
CapSense_CSD_PortCH0__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
CapSense_CSD_PortCH0__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
CapSense_CSD_PortCH0__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
CapSense_CSD_PortCH0__PS EQU CYREG_PRT0_PS
CapSense_CSD_PortCH0__SLW EQU CYREG_PRT0_SLW

; Miscellaneous
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CY_PROJECT_NAME LIT 'CapSense_CSD_Design02'
CY_VERSION LIT 'PSoC Creator  3.3 CP1'
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 18
CYDEV_CHIP_DIE_PSOC4A EQU 10
CYDEV_CHIP_DIE_PSOC5LP EQU 17
CYDEV_CHIP_DIE_TMA4 EQU 2
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC3
CYDEV_CHIP_JTAG_ID EQU 0x1E028069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 10
CYDEV_CHIP_MEMBER_4C EQU 15
CYDEV_CHIP_MEMBER_4D EQU 6
CYDEV_CHIP_MEMBER_4E EQU 4
CYDEV_CHIP_MEMBER_4F EQU 11
CYDEV_CHIP_MEMBER_4G EQU 2
CYDEV_CHIP_MEMBER_4H EQU 9
CYDEV_CHIP_MEMBER_4I EQU 14
CYDEV_CHIP_MEMBER_4J EQU 7
CYDEV_CHIP_MEMBER_4K EQU 8
CYDEV_CHIP_MEMBER_4L EQU 13
CYDEV_CHIP_MEMBER_4M EQU 12
CYDEV_CHIP_MEMBER_4N EQU 5
CYDEV_CHIP_MEMBER_4U EQU 3
CYDEV_CHIP_MEMBER_5A EQU 17
CYDEV_CHIP_MEMBER_5B EQU 16
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_3A
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4C_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_3A_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_CLEAR_SRAM EQU 1
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x01
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000001
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA LIT '5.0'
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD LIT '5.0'
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0 LIT '5.0'
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1 LIT '5.0'
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2 LIT '5.0'
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3 LIT '5.0'
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0 LIT '5.0'
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1 LIT '5.0'
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2 LIT '5.0'
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3 LIT '5.0'
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_DP8051_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERKEIL_INC */
