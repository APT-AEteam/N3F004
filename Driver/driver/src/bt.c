/***********************************************************************//** 
 * \file  bt.c
 * \brief BT function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-01 <td>V2_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"

/* externs--------------------------------------------------------------------*/
/* private function-----------------------------------------------------------*/
/* global variablesr----------------------------------------------------------*/
/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/** \brief bt deinit 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_DeInit(CSP_BT_T *ptBtBase)
{
	ptBtBase->RSSR=BT_RESET_VALUE;
	ptBtBase->CR=BT_RESET_VALUE;
	ptBtBase->PSCR=BT_RESET_VALUE;
	ptBtBase->PRDR=BT_RESET_VALUE;
	ptBtBase->CMP=BT_RESET_VALUE;
	ptBtBase->CNT=BT_RESET_VALUE;
	ptBtBase->EVTRG=BT_RESET_VALUE;
	ptBtBase->RCR = BT_RESET_VALUE;
	ptBtBase->EVSWF=BT_RESET_VALUE;
	ptBtBase->IMCR=BT_RESET_VALUE;
	ptBtBase->ICR=BT_RESET_VALUE;
}

/** \brief bt start
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_Start(CSP_BT_T *ptBtBase)
{
	ptBtBase->RSSR =(ptBtBase->RSSR  & (~BT_CTRL_MSK) )  | BT_START ;
}

/** \brief bt stop
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_Stop(CSP_BT_T *ptBtBase)
{
	ptBtBase->RSSR =(ptBtBase->RSSR  & (~BT_CTRL_MSK) )  | BT_STOP;
}

/** \brief bt stop , BT_OUT stop level - high
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_Stop_High(CSP_BT_T *ptBtBase)
{
	ptBtBase->CR = (ptBtBase->CR & (~BT_IDLEST_MSK)) | (BT_IDLE_HIGH<< BT_IDLEST_POS);
	ptBtBase->RSSR =(ptBtBase->RSSR  & (~BT_CTRL_MSK) )  | BT_STOP;
}

/** \brief bt stop , BT_OUT stop level - low
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_Stop_Low(CSP_BT_T *ptBtBase)
{
	ptBtBase->CR = (ptBtBase->CR & (~BT_IDLEST_MSK)) | (BT_IDLE_LOW<< BT_IDLEST_POS);
	ptBtBase->RSSR =(ptBtBase->RSSR  & (~BT_CTRL_MSK) )  | BT_STOP;
}

/** \brief bt soft reset
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_Soft_Reset(CSP_BT_T *ptBtBase)
{
	ptBtBase->RSSR  = (ptBtBase->RSSR & (~BT_SRR_MSK) )| BT_SRR_EN ;
}

/** \brief bt config 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eClkEN:  clk of bt enable / disable control \ref bt_clk_e
 *  \param[in] HwPscrData: PSCR data setting 
 *  \param[in] eShwdStp: shadow of start bit  enable/disable control  \ref bt_shdw_e
 *  \param[in] eOpm: bt work mode select : once or continus  \ref bt_opm_e
 *  \param[in] eExtCkm: clk of bt select  \ref bt_extckm_e
 * 			   
 *  \return none
 */ 
void BT_Configure(CSP_BT_T *ptBtBase, bt_clk_e eClkEN, U16_T hwPscrData , bt_shdw_e eShwdStp, bt_opm_e eOpm,bt_extckm_e eExtCkm)
{
	ptBtBase->CR =(ptBtBase->CR & (~(BT_CLK_MSK | BT_SHDW_MSK | BT_OPM_MSK | BT_EXTCKM_MSK))) | (eClkEN << BT_CLK_POS) | (eShwdStp <<BT_SHDW_POS) | (eOpm <<BT_OPM_POS) | (eExtCkm << BT_EXTCKM_POS);
	ptBtBase->PSCR = hwPscrData;
}

/** \brief bt config 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eStartSt:  bt start status \ref bt_startst_e
 *  \param[in] eIdleSt: bt idle status \ref  bt_idlest_e
 *  \param[in] eSync0: sync0  enable/disable  control , sync0 trigger bt start \ref bt_sync_e
 *  \param[in] eSyncCmd: bt sync result control  \ref bt_synccmd_e
 *  \param[in] eOstMd0: bt sync0 mode control  \ref bt_ostmd_e
 *  \param[in] eAreArm: bt hardware auto rearm enable/ disable control  \ref bt_arearm_e
 *  \param[in] eCntRld: bt hardware auto reload cnt enable/disable control \ref bt_cntrld_e
 * 			   
 *  \return none
 */ 
void BT_ControlSet_Configure(CSP_BT_T *ptBtBase, bt_startst_e eStartSt, bt_idlest_e eIdleSt , bt_sync_e eSync0 ,bt_synccmd_e eSyncCmd, bt_ostmd_e eOstMd0 ,bt_arearm_e eAreArm ,bt_cntrld_e eCntRld)
{
	ptBtBase->CR = (ptBtBase->CR & (~(BT_STARTST_MSK| BT_IDLEST_MSK| BT_SYNC_MSK(BT_SYNCEN0)| BT_SYNCCMD_MSK|  BT_OSTMD_MSK(BT_SYNCEN0) |BT_AREARM_MSK| BT_CNTRLD_MSK))) 
								| (eStartSt<<BT_STARTST_POS)| (eIdleSt<<BT_IDLEST_POS)| (eSync0<<BT_SYNC_POS(BT_SYNCEN0))|(eSyncCmd<<BT_SYNCCMD_POS)| (eOstMd0<<BT_OSTMD_POS(BT_SYNCEN0))| 
								(eAreArm<<BT_AREARM_POS)| (eCntRld<< BT_CNTRLD_POS);
}

/** \brief bt Period & Compare set
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] hwPrdrData:   PRDR data
 *  \param[in] hwCmpData:  CMP data
 * 			   
 *  \return none
 */ 
void BT_Period_CMP_Write(CSP_BT_T *ptBtBase, U16_T hwPrdrData, U16_T hwCmpData)
{
	ptBtBase->PRDR =hwPrdrData;
	ptBtBase->CMP =hwCmpData;
}

/** \brief bt  counter set
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] hwPrdrData:   PRDR data
 *  \param[in] hwCmpData:  CMP data
 * 			   
 *  \return none
 */ 
void BT_CNT_Write(CSP_BT_T *ptBtBase,U16_T hwCntData)
{
	ptBtBase->CNT =hwCntData;
}

/** \brief  read bt  prdr val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return prdr val
 */ 
U16_T BT_PRDR_Read(CSP_BT_T *ptBtBase)
{
    return ptBtBase->PRDR;
}

/** \brief  read bt  cmp val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return cmp val
 */ 
U16_T BT_CMP_Read(CSP_BT_T *ptBtBase)
{
    return ptBtBase->CMP;
}

/** \brief  read bt  cnt val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return cnt val
 */ 
U16_T BT_CNT_Read(CSP_BT_T *ptBtBase)
{
    return ptBtBase->CNT;
}

/** \brief  bt  trigger init
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eEvTrg0:  trigger source of TRGEV0 event  select control \ref bt_evtrg_src_e
 *  \param[in] eEvTrg1:  trigger source of TRGEV1 event  select control \ref bt_evtrg_src_e
 *  \param[in] eTrgOe0: TRGOUT0 enable/disable control \ref  bt_trgoe_e
 *  \param[in] eTrgOe1: TRGOUT1 enable/disable control \ref  bt_trgoe_e
 * 			   
 *  \return none
 */ 
void BT_Trigger_Configure(CSP_BT_T *ptBtBase,bt_evtrg_src_e eEvTrg0,bt_evtrg_src_e eEvTrg1,bt_trgoe_e eTrgOe0 ,bt_trgoe_e eTrgOe1)
{
	ptBtBase->EVTRG=(ptBtBase->EVTRG & (~(BT_TRG0_SEL_MSK|BT_TRG1_SEL_MSK|BT_TRGOE0_MSK|BT_TRGOE1_MSK))) |(eEvTrg0<<BT_TRG0_SEL_POS)
										|(eEvTrg1<<BT_TRG1_SEL_POS) |(eTrgOe0<<BT_TRGOE0_POS) |(eTrgOe1<<BT_TRGOE1_POS);
}

/** \brief  bt  trigger_event0 counter period configure to trigger stop 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] bPrd:  TRGEV0 counter period ,  trigger BT STOP
 * 			   
 *  \return none
 */ 
 void  BT_TRGEV0_Stop_Configure(CSP_BT_T *ptBtBase, U8_T bPrd)
 {
	 ptBtBase->EVTRG = ptBtBase->EVTRG & (~BT_TRG0_PRD_MSK) | (bPrd<<BT_TRG0_PRD_POS);
 }
 
 /** \brief  bt  trigger_event1 counter period configure to trigger stop 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] bPrd:  TRGEV1 counter period ,  trigger BT STOP
 * 			   
 *  \return none
 */ 
 void  BT_TRGEV1_Stop_Configure(CSP_BT_T *ptBtBase, U8_T bPrd)
 {
	 ptBtBase->EVTRG = ptBtBase->EVTRG & (~BT_TRG1_PRD_MSK) | (bPrd<<BT_TRG1_PRD_POS);
 }
 
 /** \brief  read TRGEV0_Counter
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return TRGEV0_Counter
 */ 
 U8_T  BT_TRGEV0_Counter(CSP_BT_T *ptBtBase)
 {
	return  ptBtBase->EVTRG = (ptBtBase->EVTRG & BT_TRG0_CNT_MSK) >>BT_TRG0_CNT_POS ;
 }
 
 /** \brief  read TRGEV1_Counter
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return TRGEV1_Counter
 */ 
 U8_T  BT_TRGEV1_Counter(CSP_BT_T *ptBtBase)
 {
	return  ptBtBase->EVTRG = (ptBtBase->EVTRG & BT_TRG1_CNT_MSK) >>BT_TRG1_CNT_POS ;
 }
 
  /** \brief  bt RPRD configure
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
 void  BT_RPRD_Configure(CSP_BT_T *ptBtBase, bt_rmode_e eRmode, bt_crossmd_e  eCrossMd, U8_T bRprd)
 {
	ptBtBase->RCR = (ptBtBase->RCR &(~(BT_RMODE_MSK|BT_CROSSMD_MSK|BT_RPRD_MSK)) ) |( eRmode<<BT_RMODE_POS) |(eCrossMd<<BT_CROSSMD_POS) |(bRprd<<BT_RPRD_POS);
 }


 /** \brief  read R_Counter
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return R_Counter
 */ 
 U8_T  BT_RCounter(CSP_BT_T *ptBtBase)
 {
	return  ptBtBase->RCR = (ptBtBase->RCR & BT_RCNT_MSK) >>BT_RCNT_POS ;
 }
 

/** \brief  bt  trigger_event0 soft trigger
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_TRGEV0_Soft_Triggle(CSP_BT_T *ptBtBase)
{
	ptBtBase->EVSWF=BT_EVSWF0_EN;
}

/** \brief  bt  trigger_event1 soft trigger
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void BT_TRGEV1_Soft_Triggle(CSP_BT_T *ptBtBase)
{
	ptBtBase->EVSWF=BT_EVSWF1_EN;
}

/** \brief  bt  interrupt config
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eState:  interrupt enable/disable control \ref FunctionalStatus
 *  \param[in] eImcr:  interrupt select \ref bt_int_e
 * 			   
 *  \return none
 */ 
void BT_ConfigInterrupt_CMD(CSP_BT_T *ptBtBase,FunctionalStatus eState,bt_int_e eImcr)
{
	if (eState != DISABLE)
	{
		ptBtBase->IMCR  |= eImcr;						
	}
	else
	{
		ptBtBase->IMCR  &= ~eImcr;					
	}
}

/** \brief  bt0  interrupt enable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void BT0_INT_ENABLE(void)
{
	csi_vic_enable_irq(BT0_INT);
}

/** \brief  bt0  interrupt disable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void BT0_INT_DISABLE(void)
{
	csi_vic_disable_irq(BT0_INT);
}

/** \brief  bt1  interrupt enable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void BT1_INT_ENABLE(void)
{
	csi_vic_enable_irq(BT1_INT);
}

/** \brief  bt1  interrupt disable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void BT1_INT_DISABLE(void)
{
	csi_vic_disable_irq(BT1_INT);
}