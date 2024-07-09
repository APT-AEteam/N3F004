/***********************************************************************//** 
 * \file  bt.c
 * \brief  bt driver
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
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



/*************************************************************/
//Deinitializes the registers to their default reset
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/    
void BT_DeInit(CSP_BT_T *BTx)
{
	BTx->RSSR=BT_RESET_VALUE;
	BTx->CR=BT_RESET_VALUE;
	BTx->PSCR=BT_RESET_VALUE;
	BTx->PRDR=BT_RESET_VALUE;
	BTx->CMP=BT_RESET_VALUE;
	BTx->CNT=BT_RESET_VALUE;
	BTx->EVTRG=BT_RESET_VALUE;
	BTx->EVSWF=BT_RESET_VALUE;
	BTx->RISR=BT_RESET_VALUE;
	BTx->IMCR=BT_RESET_VALUE;
	BTx->MISR=BT_RESET_VALUE;
	BTx->ICR=BT_RESET_VALUE;
}
/*************************************************************/
//BT IO Init
//EntryParameter:LPT_OUT_PA09,LPT_OUT_PB01,LPT_IN_PA10,
//ReturnValue:NONE
/*************************************************************/
void BT_IO_Init(BT_Pin_TypeDef BT_IONAME)
{

}
/*************************************************************/
// BT start
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void BT_Start(CSP_BT_T *BTx)
{
	BTx->RSSR |=0X01;
}
/*************************************************************/
// BT stop
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void BT_Stop(CSP_BT_T *BTx)
{
	BTx->RSSR &=0X0;
}
/*************************************************************/
// BT stop High
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void BT_Stop_High(CSP_BT_T *BTx)
{
	BTx->CR |=(0x01<<6);
	BTx->RSSR &=0X0;
}
/*************************************************************/
// BT stop Low
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void BT_Stop_Low(CSP_BT_T *BTx)
{
	BTx->CR =BTx->CR & ~(0x01<<6);
	BTx->RSSR &=0X0;
}
/*************************************************************/
// BT soft reset
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void BT_Soft_Reset(CSP_BT_T *BTx)
{
	BTx->RSSR |= (0X5<<12);
}
/*************************************************************/
//BT Configure
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_Configure(CSP_BT_T *BTx,BT_CLK_TypeDef BTCLK,U16_T PSCR_DATA,BT_SHDWSTP_TypeDef BTSHDWSTP,BT_OPM_TypeDef BTOPM,BT_EXTCKM_TypeDef BTEXTCKM)
{
	BTx->CR |=BTCLK| BTSHDWSTP| BTOPM| BTEXTCKM;
	BTx->PSCR = PSCR_DATA;
}
/*************************************************************/
//BT ControlSet
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_ControlSet_Configure(CSP_BT_T *BTx,BT_STARTST_TypeDef BTSTART,BT_IDLEST_TypeDef BTIDLE,BT_SYNCEN_TypeDef BTSYNC,BT_SYNCMD_TypeDef BTSYNCMD,
							BT_OSTMDX_TypeDef BTOSTMD,BT_AREARM_TypeDef BTAREARM,BT_CNTRLD_TypeDef BTCNTRLD)
{
	BTx->CR |=BTSTART| BTIDLE| BTSYNC| BTSYNCMD| BTOSTMD| BTAREARM| BTCNTRLD;
}
/*************************************************************/
//BT Period / Compare set
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_Period_CMP_Write(CSP_BT_T *BTx,U16_T BTPRDR_DATA,U16_T BTCMP_DATA)
{
	//BTx->CR|=0X01<<2;
	BTx->PRDR =BTPRDR_DATA;
	BTx->CMP =BTCMP_DATA;
}
/*************************************************************/
//BT COUNTER set
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_CNT_Write(CSP_BT_T *BTx,U16_T BTCNT_DATA)
{
	BTx->CNT =BTCNT_DATA;
}
/*************************************************************/
//BT read counters
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
U16_T BT_PRDR_Read(CSP_BT_T *BTx)
{
    return BTx->PRDR;
}
U16_T BT_CMP_Read(CSP_BT_T *BTx)
{
    return BTx->CMP;
}
U16_T BT_CNT_Read(CSP_BT_T *BTx)
{
    return BTx->CNT;
}
/*************************************************************/
//BT Trigger Init
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_Trigger_Configure(CSP_BT_T *BTx,BT_TRGSRC_TypeDef BTTRG,BT_TRGOE_TypeDef BTTRGOE)
{
	BTx->EVTRG|=BTTRG| BTTRGOE;
}
/*************************************************************/
//BT SOFT Trigger
//EntryParameter:
//ReturnValue:NONE
/*************************************************************/
void BT_Soft_Tigger(CSP_BT_T *BTx)
{
	BTx->EVSWF=0x01;
}
/*************************************************************/
//BT inturrpt Configure
//EntryParameter:BT_IMSCR_X,NewState
//NewState:ENABLE,DISABLE
//ReturnValue:NONE
/*************************************************************/ 
void BT_ConfigInterrupt_CMD(CSP_BT_T *BTx,functional_status_e NewState,BT_IMSCR_TypeDef BT_IMSCR_X)
{
	if (NewState != DISABLE)
	{
		BTx->IMCR  |= BT_IMSCR_X;						
	}
	else
	{
		BTx->IMCR  &= ~BT_IMSCR_X;					
	}
}
/*************************************************************/
//BT0 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT0_INT_ENABLE(void)
{
//	INTC_ISER_WRITE(BT0_INT);
}
/*************************************************************/
//BT0 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT0_INT_DISABLE(void)
{
//	INTC_ICER_WRITE(BT0_INT);
}
/*************************************************************/
//BT0 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT1_INT_ENABLE(void)
{
//	INTC_ISER_WRITE(BT1_INT);
}
/*************************************************************/
//BT0 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT1_INT_DISABLE(void)
{
//	INTC_ICER_WRITE(BT1_INT);
}


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/