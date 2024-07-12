/***********************************************************************
 * \file  ept.c
 * \brief EPT function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-02 <td>V1_3_0  <td>GQQ  <td>initial
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

/** \brief EPT software reset
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void ept_software_reset(void)
{
	EPT0->CEDR |=EPT_CLKEN;
	EPT0->RSSR=(EPT0->RSSR&(~EPT_RESET_MSK)) | EPT_RESET;
}

/** \brief EPT start
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void ept_start(void)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->RSSR|= EPT_START;
	while(!(EPT0->RSSR&EPT_START));
} 

/** \brief EPT stop
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */  
void ept_stop(void)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->RSSR&=~EPT_START;
	while(EPT0->RSSR&EPT_START);
}

/** \brief  EPT IO Config
 * 
 *  \param[in]  eIoMd : ept ouput channel \ref ept_iomd_e
 *  \param[in]  eIoNum : IO select  \ref ept_ionum_e
 * 
 *  \return none
 */  
void ept_io_configure(ept_iomd_e eIoMd , ept_ionum_e eIoNum)
{
	if(eIoMd==EPT_IO_CHAX)
	{
		if(eIoNum==IO_NUM_PA07)
		{
			GPIOA0->CONLR = (GPIOA0->CONLR&0X0FFFFFFF)|0X60000000;				//PA0.7
		}
		else if(eIoNum==IO_NUM_PA10)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFFF0FF)|0X00000500;				//PA0.10
		}
		else if(eIoNum==IO_NUM_PA15)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0X0FFFFFFF)|0X40000000;				//PA0.15
		}
	}
	else if(eIoMd==EPT_IO_CHAY)
	{
		if(eIoNum==IO_NUM_PB03)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFF0FFF)|0X00005000;				//PB0.3
		}
		else if(eIoNum==IO_NUM_PB05)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFF0FFFFF)|0X00500000;				//PB0.5
		}
		else if(eIoNum==IO_NUM_PA12)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFF0FFFF)|0X00050000;				//PA0.12
		}
	}
	else if(eIoMd==EPT_IO_CHBX)
	{
		if(eIoNum==IO_NUM_PB02)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFFF0FF)|0X00000600;				//PB0.2
		}
		else if(eIoNum==IO_NUM_PA11)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFF0FFF)|0X00005000;				//PA0.11
		}
		else if(eIoNum==IO_NUM_PA14)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XF0FFFFFF)|0X04000000;				//PA0.14
		}
	}
	else if(eIoMd==EPT_IO_CHBY)
	{
		if(eIoNum==IO_NUM_PB04)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFF0FFFF)|0X00050000;				//PB0.4
		}
		else if(eIoNum==IO_NUM_PA05)
		{
			GPIOA0->CONLR = (GPIOA0->CONLR&0XFF0FFFFF)|0X00800000;				//PA0.5
		}
		else if(eIoNum==IO_NUM_PA08)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFFFFF0)|0X00000005;				//PA0.8
		}
	}
	else if(eIoMd==EPT_IO_CHCX)
	{
		if(eIoNum==IO_NUM_PB05)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFF0FFFFF)|0X00400000;				//PB0.5
		}
		else if(eIoNum==IO_NUM_PA03)
		{
			GPIOA0->CONLR = (GPIOA0->CONLR&0XFFFF0FFF)|0X00005000;				//PA0.3
		}
		else if(eIoNum==IO_NUM_PB03)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFF0FFF)|0X00004000;				//PB0.3
		}
		else if(eIoNum==IO_NUM_PB00)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFFFFF0)|0X00000005;				//PB0.0
		}
	}
	else if(eIoMd==EPT_IO_CHCY)
	{
		if(eIoNum==IO_NUM_PB04)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFF0FFFF)|0X00040000;				//PB0.4
		}
		else if(eIoNum==IO_NUM_PA04)
		{
			GPIOA0->CONLR = (GPIOA0->CONLR&0XFFF0FFFF)|0X00050000;				//PA0.4
		}
		else if(eIoNum==IO_NUM_PA09)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFFFF0F)|0X00000070;				//PA0.9
		}
		else if(eIoNum==IO_NUM_PA013)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFF0FFFFF)|0X00500000;				//PA0.13
		}
	}
	else if(eIoMd==EPT_IO_CHD)
	{
		if(eIoNum==IO_NUM_PB03)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFF0FFF)|0X00006000;				//PB0.3
		}
		else if(eIoNum==IO_NUM_PA08)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFFFFF0)|0X00000004;				//PA0.8
		}
	}
	else if(eIoMd==EPT_IO_EPI)
	{
		if(eIoNum==IO_NUM_PA07)
		{
			GPIOA0->CONLR = (GPIOA0->CONLR&0X0FFFFFFF)|0X50000000;				//PA0.7 EPI0
		}
		else if(eIoNum==IO_NUM_PA013)
		{
			GPIOA0->CONHR = (GPIOA0->CONHR&0XFF0FFFFF)|0X00400000;				//PA0.13 EPI1
		}
		else if(eIoNum==IO_NUM_PB03)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFF0FFF)|0X00007000;				//PB0.3 EPI2
		}
		else if(eIoNum==IO_NUM_PB02)
		{
			GPIOB0->CONLR = (GPIOB0->CONLR&0XFFFFF0FF)|0X00000700;				//PB0.2 EPI3
		}
	}
}

/** \brief EPT PWM  Basic Configuration :clk , counter mode, operation  mode  ect.
 * 			
 *  \param[in] eClk : source clk select : PCLK OR SYNCIN3 \ref ept_clksel_e
 *  \param[in] eCntMd : Counter mode config :  increase ,decrease or increase_decrease  \ref ept_cntmd_e
 *  \param[in] eOpMd : Counter  operation mode : once or continus \ref ept_opmd_e
 *  \param[in] hwPscr : clk division control, range: 0~0XFFFF, :  Fclk=Fpclk/(PSCR+1)
 * 			   
 *  \return none
 */  
void ept_pwm_configure(ept_clksel_e eClk , ept_cntmd_e eCntMd  , ept_opmd_e eOpMd, U16_T hwPscr)		
{
	EPT0->CEDR=(EPT0->CEDR&(~(EPT_CLKEN_MSK|EPT_CKSRC_MSK|EPT_DBGEN_MSK|EPT_START_MSK)))|(EPT_CLKEN|(eClk <<EPT_CKSRC_POS)|(EPT_DBGEN)|(EPT_START_SHD));
	if(eClk==EPT_Selecte_PCLK)
	{
		EPT0->PSCR=hwPscr;
	}
	EPT0->CR=(EPT0->CR&(~(EPT_CNTMD_MSK|EPT_STARTSRC_MSK|EPT_STPST_MSK|EPT_PRDLD_MSK|EPT_OPMD_MSK|EPT_PSCLD_MSK|EPT_MODE_MSK)))
							|eCntMd|(EPT_SYNC_START<<EPT_STARTSRC_POS)|(EPT_STPST_HZ<<EPT_STPST_POS)|(EPT_LDPRDR_PRD<<EPT_PRDLD_POS)|(eOpMd << EPT_OPMD_POS)
							|(EPT_PSCLD_ZRO<<EPT_PSCLD_POS)|(EPT_MODE_OUT<<EPT_MODE_POS);
} 

/** \brief EPT Clock Gate Filter Configuration :Clock Gate source select, filter div ,filter cnt , burst ect.
 * 			
 *  \param[in] eCgsrcSel : Clock Gate source select : DIS/TIN_BT0/TIN_BT1/CHAX/CHBX \ref ept_cgsrc_e
 *  \param[in] byCgfltDiv : Clock Gate Filter DIv Setting, range: 0~0xff 
 *  \param[in] byCgfltCnt : Clock Gate Filter Cnt Setting , range: 0~0x7
 *  \param[in] eBurst : Burst enable or disable control \ref ept_burst_e
 * 			   
 *  \return none
 */  
void ept_clockgate_configure(ept_cgsrc_e eCgsrcSel , U8_T byCgfltDiv , U8_T byCgfltCnt , ept_burst_e eBurst)
{
	EPT0->CR=(EPT0->CR&(~(EPT_BURST_MSK|EPT_CGFLT_MSK|EPT_FLT_INIT_MSK)))|(eBurst<<EPT_BURST_POS)|(byCgfltCnt<<EPT_CGFLT_POS)|(EPT_FLT_INIT);
	EPT0->CEDR=(EPT0->CEDR&(~EPT_FLTPRS_MSK))|(byCgfltDiv<<EPT_FLTPRS_POS);
	if(eCgsrcSel==EPT_CGSRC_DIS)
	{
		EPT0->CEDR|=EPT_TIN_DIS<<EPT_TIN_POS;
		EPT0->CR|=EPT_CGSRC_SEL_DIS<<EPT_CGSRC_POS;
	}
	else if(eCgsrcSel==EPT_CGSRC_TIN_BT0OUT)
	{
		EPT0->CEDR|=EPT_TIN_BT0<<EPT_TIN_POS;
		EPT0->CR|=EPT_CGSRC_SEL_TIN<<EPT_CGSRC_POS;
	}
	else if(eCgsrcSel==EPT_CGSRC_TIN_BT1OUT)
	{
		EPT0->CEDR|=EPT_TIN_BT1<<EPT_TIN_POS;
		EPT0->CR|=EPT_CGSRC_SEL_TIN<<EPT_CGSRC_POS;
	}
	else if(eCgsrcSel==EPT_CGSRC_CHAX)
	{
		EPT0->CEDR|=EPT_TIN_DIS<<EPT_TIN_POS;
		EPT0->CR|=EPT_CGSRC_SEL_CHAX<<EPT_CGSRC_POS;
	}
	else if(eCgsrcSel==EPT_CGSRC_CHBX)
	{
		EPT0->CEDR|=EPT_TIN_DIS<<EPT_TIN_POS;
		EPT0->CR|=EPT_CGSRC_SEL_CHBX<<EPT_CGSRC_POS;
	}
}

/** \brief EPT Capture Config
 * 			
 *  \param[in] eClk : source clk select : PCLK OR SYNCIN3 \ref ept_clksel_e
 *  \param[in] eCntMd : Counter mode config :  increase ,decrease or increase_decrease  \ref ept_cntmd_e
 *  \param[in] eCapMd : Capture Mode Config: Once or Continus \ref ept_capmd_e
 *  \param[in] eCapldEn : cmpa  &cmpb capture event tiggered, load enable or disable control  \ref ept_capld_e
 *  \param[in] eLoadCmpa : After cmpa capture load ,counter state control:enable /disable \ref ept_ldxrst_e
 *  \param[in] eLoadCmpb : After cmpb capture load ,counter state control:enable /disable \ref ept_ldxrst_e
 *  \param[in] eLoadCmpc : After cmpc capture load ,counter state control:enable /disable \ref ept_ldxrst_e
 *  \param[in] eLoadCmpc : After cmpc capture load ,counter state control:enable /disable \ref ept_ldxrst_e
 *  \param[in] byStopWrap : In Capture Mode, Capture counter period setting: range: 0~0X3
 *  \param[in] hwPscr : clk division control, range: 0~0XFFFF, :  Fclk=Fpclk/(PSCR+1)
 * 			   
 *  \return none
 */  
void ept_cap_configure(ept_clksel_e eClk, ept_cntmd_e eCntMd , ept_capmd_e eCapMd , ept_capld_e eCapldEn 
					, ept_ldxrst_e eLoadCmpa, ept_ldxrst_e eLoadCmpb, ept_ldxrst_e eLoadCmpc, ept_ldxrst_e eLoadCmpd,  U8_T byStopWrap , U16_T hwPscr)
{
	EPT0->CEDR=(EPT0->CEDR&(~(EPT_CLKEN_MSK|EPT_CKSRC_MSK|EPT_DBGEN_MSK|EPT_START_MSK)))|(EPT_CLKEN|(eClk<<EPT_CKSRC_POS)|(EPT_DBGEN)|(EPT_START_SHD));
	if(eClk==EPT_Selecte_PCLK)
	{
		EPT0->PSCR=hwPscr;
	}
	EPT0->CR=(EPT0->CR&(~(EPT_CNTMD_MSK|EPT_STARTSRC_MSK|EPT_STPST_MSK|EPT_PRDLD_MSK|EPT_CAPLD_MSK|EPT_CAPMD_MSK|EPT_PSCLD_MSK|EPT_MODE_MSK|EPT_STOPWRAP_MSK
	|EPT_CMPA_RST_MSK|EPT_CMPB_RST_MSK |EPT_CMPC_RST_MSK|EPT_CMPD_RST_MSK)))|eCntMd|(EPT_SW_START<<EPT_STARTSRC_POS)|(EPT_STPST_HZ<<EPT_STPST_POS)|(EPT_LDPRDR_PRD<<EPT_PRDLD_POS)
	|(eCapldEn<<EPT_CAPLD_POS)|(eCapMd<<EPT_CAPMD_POS)|(EPT_PSCLD_ZRO<<EPT_PSCLD_POS)|(EPT_MODE_CAP<<EPT_MODE_POS)|(byStopWrap<<EPT_STOPWRAP_POS)
	|(eLoadCmpa<<EPT_CMPA_RST_POS)|(eLoadCmpb<<EPT_CMPB_RST_POS)|(eLoadCmpc<<EPT_CMPC_RST_POS)|(eLoadCmpd<<EPT_CMPD_RST_POS);
}

/** \brief EPT sync0 config
 * 			
 *  \param[in] eSyncMd : Sync Mode select : once or continus \ref ept_syncmd_e
 *  \param[in] eAutoRearm : Hardware Auto Rearm selection of sync0 ch: disable/ cnt=zreo/cnt=prd/cnt= zero or prd  \ref ept_arearm_e
 *  \param[in] eTrgo0Sel : Input trigger channel as ExtSync selection of TRGSRC0 \ref ept_trgoxsel_e
 *  \param[in] eTrgo1Sel : Input trigger channel as ExtSync selection of TRGSRC1 \ref ept_trgoxsel_e
 *  \param[in] eSync0En : Sync0 ch control :enable /disable \ref ept_syncxen_e
 * 			   
 *  \return none
 */  
void ept_syncr_configure(ept_syncmd_e eSyncMd , ept_arearm_e eAutoRearm, ept_trgoxsel_e eTrgo0Sel ,ept_trgoxsel_e eTrgo1Sel , ept_syncxen_e eSync0En)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->SYNCR = (EPT0->SYNCR&(~(EPT_OSTMD_MSK(0)|EPT_SYNC_MSK(0)|EPT_AREARM_MSK|EPT_TRGO0SEL_MSK|EPT_TRGO1SEL_MSK))) 
						|(eSync0En<<EPT_SYNC_POS(0))|(eSyncMd<<EPT_OSTMD_POS(0))|(eAutoRearm<<EPT_AREARM_POS)|(eTrgo0Sel<<EPT_TRGO0SEL_POS)
						|(eTrgo1Sel<<EPT_TRGO1SEL_POS);
}

/** \brief EPT dedband config
 * 			
 *  \param[in] eDbChSel : Deadband channel select: CHA/CHB/CHC \ref ept_dbsel_e
 *  \param[in] eDbChxInSel : Current deadband channel input pwm select \ref ept_dbchx_insel_e
 *  \param[in] eOutSel :Current deadband channel output select \ref ept_db_outsel_e
 *  \param[in] ePol : Output polarity select \ref ept_db_pol_e
 *  \param[in] eOutWrap : Deadband output switch control \ref ept_outwrap_e
 * 			   
 *  \return none
 */  
void ept_deadband_configure(ept_dbsel_e eDbChSel , ept_dbchx_insel_e eDbChxInSel , ept_db_outsel_e eOutSel , ept_db_pol_e ePol , ept_outwrap_e eOutWrap)
{	
	if(eDbChSel==EPT_DBSEL_CHA)
	{
		EPT0->DBCR=(EPT0->DBCR&(~(DB_CHA_INSEL_MSK|DB_CHA_OUTSEL_MSK|DB_CHA_POL_MSK|DB_CHA_OUTSWAP_MSK)))|(eDbChxInSel<<DB_CHA_INSEL_POS)
								|(eOutSel<<DB_CHA_OUTSEL_POS)|(ePol<<DB_CHA_POL_POS)|(eOutWrap<<DB_CHA_OUTSWAP_POS);
	}
	else if(eDbChSel==EPT_DBSEL_CHB)
	{
		EPT0->DBCR=(EPT0->DBCR&(~(DB_CHB_INSEL_MSK|DB_CHB_OUTSEL_MSK|DB_CHB_POL_MSK|DB_CHB_OUTSWAP_MSK)))|(eDbChxInSel<<DB_CHB_INSEL_POS)
								|(eOutSel<<DB_CHB_OUTSEL_POS)|(ePol<<DB_CHB_POL_POS)|(eOutWrap<<DB_CHB_OUTSWAP_POS);
	}
	else if(eDbChSel==EPT_DBSEL_CHC)
	{
		EPT0->DBCR=(EPT0->DBCR&(~(DB_CHC_INSEL_MSK|DB_CHC_OUTSEL_MSK|DB_CHC_POL_MSK|DB_CHC_OUTSWAP_MSK)))|(eDbChxInSel<<DB_CHC_INSEL_POS)
								|(eOutSel<<DB_CHC_OUTSEL_POS)|(ePol<<DB_CHC_POL_POS)|(eOutWrap<<DB_CHC_OUTSWAP_POS);
	}
	EPT0->DBCR|=EPT_DBCLK_DPSC<<EPT_DCKSEL_POS;
}

/** \brief EPT dedband clk config
 * 			
 *  \param[in] hwDpsc : Deadband clk division control ,range：0~0xffff
 * 					Fdbclk=Fhclk/(DPSC+1)	
 *  \param[in] hwDtr : Deadband raising edge timeout ,range：0~0xffff
 *  \param[in] hwDtf : Deadband falling edge timeout ,range：0~0xffff
 * 			   
 *  \return none
 */  
void ept_deadband_clk_configure(U16_T hwDpsc , U16_T hwDtr , U16_T hwDtf)
{
	EPT0->DPSCR=hwDpsc;
	EPT0->DBDTR=hwDtr;
	EPT0->DBDTF=hwDtf;
}

/** \brief EPT pwm1~4 output control
 * 			
 *  \param[in] ePwmxOut : Choose PWMx  channel to output \ref ept_pwm_out_e
 * 					Fdbclk=Fhclk/(DPSC+1)	
 *  \param[in] eC1Sel : C1 compare val select   \ref ept_cxsel_e
 *  \param[in] eC2Sel : C2 compare val select   \ref ept_cxsel_e
 * 	\param[in] eZeroAct : cnt = zero, pwmx channel wave out act \ref ept_pwm_act_e
 *  \param[in] ePrdAct :  cnt = PRDR, pwmx channel wave out act  \ref ept_pwm_act_e
 *  \param[in] eC1uAct : cnt = C1 AND  counter increase, pwmx channel wave out act   \ref ept_pwm_act_e
 *  \param[in] eC1dAct : cnt = C1 AND  counter decrease, pwmx channel wave out act   \ref ept_pwm_act_e
 *  \param[in] eC2uAct : cnt = C2 AND  counter increase, pwmx channel wave out act   \ref ept_pwm_act_e
 *  \param[in] eC2dAct : cnt = C2 AND  counter decrease, pwmx channel wave out act  \ref ept_pwm_act_e
 * 
 *  \return none
 */   
void ept_pwmx_output_control(ept_pwm_out_e ePwmxOut ,ept_cxsel_e eC1Sel , ept_cxsel_e eC2Sel , ept_pwm_act_e eZeroAct , ept_pwm_act_e ePrdAct , 
							 ept_pwm_act_e eC1uAct , ept_pwm_act_e eC1dAct ,ept_pwm_act_e eC2uAct , ept_pwm_act_e eC2dAct )
{
	if(ePwmxOut==EPT_PWM1)
	{
		EPT0->AQCR1=(eC1Sel <<EPT_C1SEL_POS)|(eC2Sel <<EPT_C2SEL_POS)|(eZeroAct<<EPT_ACT_ZRO_POS)|(ePrdAct<<EPT_ACT_PRD_POS)|(eC1uAct<<EPT_ACT_C1U_POS)
		|(eC1dAct<<EPT_ACT_C1D_POS)| (eC2uAct<<EPT_ACT_C2U_POS)|(eC2dAct<<EPT_ACT_C2D_POS);
	}
	else if(ePwmxOut==EPT_PWM2)
	{
		EPT0->AQCR2=(eC1Sel <<EPT_C1SEL_POS)|(eC2Sel <<EPT_C2SEL_POS)|(eZeroAct<<EPT_ACT_ZRO_POS)|(ePrdAct<<EPT_ACT_PRD_POS)|(eC1uAct<<EPT_ACT_C1U_POS)
		|(eC1dAct<<EPT_ACT_C1D_POS)| (eC2uAct<<EPT_ACT_C2U_POS)|(eC2dAct<<EPT_ACT_C2D_POS);
	}
	else if(ePwmxOut==EPT_PWM3)
	{
		EPT0->AQCR3=(eC1Sel <<EPT_C1SEL_POS)|(eC2Sel <<EPT_C2SEL_POS)|(eZeroAct<<EPT_ACT_ZRO_POS)|(ePrdAct<<EPT_ACT_PRD_POS)|(eC1uAct<<EPT_ACT_C1U_POS)
		|(eC1dAct<<EPT_ACT_C1D_POS)| (eC2uAct<<EPT_ACT_C2U_POS)|(eC2dAct<<EPT_ACT_C2D_POS);
	}
	else if(ePwmxOut==EPT_PWM4)
	{
		EPT0->AQCR4=(eC1Sel <<EPT_C1SEL_POS)|(eC2Sel <<EPT_C2SEL_POS)|(eZeroAct<<EPT_ACT_ZRO_POS)|(ePrdAct<<EPT_ACT_PRD_POS)|(eC1uAct<<EPT_ACT_C1U_POS)
		|(eC1dAct<<EPT_ACT_C1D_POS)| (eC2uAct<<EPT_ACT_C2U_POS)|(eC2dAct<<EPT_ACT_C2D_POS);
	}	
}

/** \brief EPT Phase Config
 * 			
 *  \param[in] ePhsEn : Phase control ： enable or disable  \ref ept_phsen_e
 *  \param[in] ePhsDir : Phase Direction Control   \ref ept_phsdir_e
 *  \param[in] hwPhsr : when phase function enable, phsr val  load to cnt to control phase of pwm,range:0~0xffff
 * 
 *  \return none
 */    
void ept_phase_configure(ept_phsen_e ePhsEn , ept_phsdir_e ePhsDir , U16_T hwPhsr)
{
	EPT0->CR=(EPT0->CR&(~EPT_PHSEN_MSK))|(ePhsEn<<EPT_PHSEN_POS);
	EPT0->PHSR=hwPhsr|(ePhsDir<<EPT_PHSDIR_POS);
}

/** \brief EPT PRDR CMPA CMPB CMPC CMPD_Config
 * 			
 *  \param[in] hwPrdr : PRDR val ,range: 0~0xffff
 *  \param[in] hwCmpa : Compare A val ,range: 0~0xffff
 *  \param[in] hwCmpb : Compare B val ,range: 0~0xffff
 *  \param[in] hwCmpc : Compare C val ,range: 0~0xffff
 *  \param[in] hwCmpd : Compare D val ,range: 0~0xffff
 * 
 *  \return none
 */    
void ept_prdr_pwmx_configure(U16_T hwPrdr , U16_T hwCmpa , U16_T hwCmpb , U16_T hwCmpc , U16_T hwCmpd)
{
	EPT0->PRDR=hwPrdr;
	EPT0->CMPA=hwCmpa;
	EPT0->CMPB=hwCmpb;
	EPT0->CMPC=hwCmpc;
	EPT0->CMPD=hwCmpd;
}

/** \brief the EPT SYNCR Rearm
 * 			
 *  \param[in] byRearmCh : Input trigger channel select: syncin0~syncin5 ,range :0~5 
 * 
 *  \return none
 */   
void ept_syncr_rearm(U8_T byRearmCh )
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->SYNCR = (EPT0->SYNCR&(~EPT_REARM_MSK(byRearmCh)))|EPT_REARM(byRearmCh) ;
}

/** \brief EPT Caputer Rearm:clear counter， enable CAPLDEN automatic
 * 			
 *  \param[in] none
 * 
 *  \return none
 */   
void ept_capture_rearm(void)
{
	EPT0->CR |=EPT_CAPREARM;
}

/** \brief  EPT Globle Event Load
 * 			
 *  \param[in] eOneShort: global one short load mode control :enable or disable \ref ept_gld_oneshort_e
 *  \param[in] eGldMd: global load trigger event select \ref ept_gldmd_sel_e
 *  \param[in] byGldPrd: global load trigger period select,  range: 0~0x7
 *  \param[in] hwGldCfg:  AQCRx, CMPx, ect  all channels  global load control ,range:0x0~0x3fff
 * 
 *  \return none
 */  
void ept_global_event_load_configure(ept_gld_oneshort_e eOneShort , ept_gldmd_sel_e eGldMd , U8_T byGldPrd , U16_T hwGldCfg)
{
	EPT0->GLDCR=EPT_GLDEN|(eOneShort<<EPT_GLDCR_OSTMD_POS)|(eGldMd <<EPT_GLDMD_POS)|(byGldPrd<<EPT_GLDPRD_POS);
	EPT0->GLDCFG=hwGldCfg;
	/*if(eGldMd==EPT_GLDMD_SEL_SW)
	{
		EPT0->REGPROT = (0xA55A<<16) | 0xC73A;
		EPT0->GLDCR2=0X02;
	}*/
}

/** \brief  EPT Globle SW Load
 * 			
 *  \param[in] none
 * 
 *  \return none
 */  
void ept_global_software_load(void)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->GLDCR2= EPT_OSREARM_EN|EPT_SW_GLD;
}

/** \brief  EPT PRDR Load 
 * 			
 *  \param[in] eLdPrdr: PRDR active register load control \ref ept_ldprdr_e
 * 
 *  \return none
 */  
void ept_prdr_load_configure(ept_ldprdr_e eLdPrdr)
{
	EPT0->GLDCR&=~EPT_GLDEN;	//Use independent configurations
	EPT0->CR=(EPT0->CR&(~EPT_PRDLD_MSK))|(eLdPrdr<<EPT_PRDLD_POS);
}

/** \brief  EPT CMPX Load Config
 * 			
 *  \param[in] eCmpLdr: CMPX load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_cmp_load_configure(ept_ldr_e eCmpLdr)
{
	EPT0->GLDCR&=~EPT_GLDEN;		//Use independent configurations
	if(eCmpLdr==EPT_LDR_DIS)
	{
		EPT0->CMPLDR=EPT_LDR_DIS;
	}
	else if(eCmpLdr==EPT_LDR_IM)
	{
		EPT0->CMPLDR=(EPT_CMPLD_IMM<<EPT_CMPA_LD_POS)|(EPT_CMPLD_IMM<<EPT_CMPB_LD_POS)|(EPT_CMPLD_IMM<<EPT_CMPC_LD_POS)|(EPT_CMPLD_IMM<<EPT_CMPD_LD_POS);
	}
	else if(eCmpLdr==EPT_LDR_ZRO)
	{
		EPT0->CMPLDR=(EPT_LDXMD_ZRO<<EPT_CMPA_LDTIME_POS)|(EPT_LDXMD_ZRO<<EPT_CMPB_LDTIME_POS)|(EPT_LDXMD_ZRO<<EPT_CMPC_LDTIME_POS)|(EPT_LDXMD_ZRO<<EPT_CMPD_LDTIME_POS);	
	}
	else if(eCmpLdr==EPT_LDR_PRD)
	{
		EPT0->CMPLDR=(EPT_LDXMD_PRD<<EPT_CMPA_LDTIME_POS)|(EPT_LDXMD_PRD<<EPT_CMPB_LDTIME_POS)|(EPT_LDXMD_PRD<<EPT_CMPC_LDTIME_POS)|(EPT_LDXMD_PRD<<EPT_CMPD_LDTIME_POS);
	}
	else if(eCmpLdr==EPT_LDR_EXI_SYNC)
	{
		EPT0->CMPLDR=(EPT_LDXMD_EXI_SYNC<<EPT_CMPA_LDTIME_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_CMPB_LDTIME_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_CMPC_LDTIME_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_CMPD_LDTIME_POS);
	}
}

/** \brief  EPT AQCRX Load Config
 * 			
 *  \param[in] eAqcrLdr: AQCRX load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_aqcr_load_configure(ept_ldr_e eAqcrLdr)
{
	EPT0->GLDCR&=~EPT_GLDEN;		//Use independent configurations
	if(eAqcrLdr==EPT_LDR_DIS)
	{
		EPT0->AQLDR=EPT_LDR_DIS;
	}
	else if(eAqcrLdr==EPT_LDR_IM)
	{
		EPT0->AQLDR=(EPT_AQCR_SHDW<<EPT_AQCR1_SHDWEN_POS)|(EPT_AQCR_SHDW<<EPT_AQCR2_SHDWEN_POS)|(EPT_AQCR_SHDW<<EPT_AQCR3_SHDWEN_POS)|(EPT_AQCR_SHDW<<EPT_AQCR4_SHDWEN_POS);
	}
	else if(eAqcrLdr==EPT_LDR_ZRO)
	{
		EPT0->AQLDR=(EPT_LDXMD_ZRO<<EPT_LDAMD_POS)|(EPT_LDXMD_ZRO<<EPT_LDBMD_POS)|(EPT_LDXMD_ZRO<<EPT_LDCMD_POS)|(EPT_LDXMD_ZRO<<EPT_LDDMD_POS);		
	}
	else if(eAqcrLdr==EPT_LDR_PRD)
	{
		EPT0->AQLDR=(EPT_LDXMD_PRD<<EPT_LDAMD_POS)|(EPT_LDXMD_PRD<<EPT_LDBMD_POS)|(EPT_LDXMD_PRD<<EPT_LDCMD_POS)|(EPT_LDXMD_PRD<<EPT_LDDMD_POS);
	}
	else if(eAqcrLdr==EPT_LDR_EXI_SYNC)
	{
		EPT0->AQLDR=(EPT_LDXMD_EXI_SYNC<<EPT_LDAMD_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_LDBMD_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_LDCMD_POS)|(EPT_LDXMD_EXI_SYNC<<EPT_LDDMD_POS);
	}
}

/** \brief   EPT DB Load Config
 * 			
 *  \param[in] eDbLdr: DBCR,DBDTR,DBDTF,DPSCR load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_deadband_load_configure(ept_ldr_e eDbLdr)
{
	EPT0->GLDCR&=~EPT_GLDEN;		//Use independent configurations
	if(eDbLdr==EPT_LDR_DIS)
	{
		EPT0->DBLDR=(EPT_DBLDR_SHD<<EPT_DBCR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTF_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DCKPSC_SHDWEN_POS);
	}
	else if(eDbLdr==EPT_LDR_IM)
	{
		EPT0->DBLDR=(EPT_DBLDR_IMM<<EPT_DBCR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTF_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DCKPSC_SHDWEN_POS);
	}
	else if(eDbLdr==EPT_LDR_ZRO)
	{
		EPT0->DBLDR=(EPT_DBLDR_SHD<<EPT_DBCR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTF_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DCKPSC_SHDWEN_POS)
							|(EPT_DBLDR_MD_ZRO<<EPT_CRLDMODE_POS)|(EPT_DBLDR_MD_ZRO<<EPT_LDDTRMD_POS)|(EPT_DBLDR_MD_ZRO<<EPT_LDDTFMD_POS)|(EPT_DBLDR_MD_ZRO<<EPT_LDPSCMD_POS);
	}
	else if(eDbLdr==EPT_LDR_PRD)
	{
		EPT0->DBLDR=(EPT_DBLDR_SHD<<EPT_DBCR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTF_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DCKPSC_SHDWEN_POS)
							|(EPT_DBLDR_MD_PRD<<EPT_CRLDMODE_POS)|(EPT_DBLDR_MD_PRD<<EPT_LDDTRMD_POS)|(EPT_DBLDR_MD_PRD<<EPT_LDDTFMD_POS)|(EPT_DBLDR_MD_PRD<<EPT_LDPSCMD_POS);
	}
	else if(eDbLdr==EPT_LDR_EXI_SYNC)
	{
		EPT0->DBLDR=(EPT_DBLDR_SHD<<EPT_DBCR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTR_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DBDTF_SHDWEN_POS)|(EPT_DBLDR_SHD<<EPT_DCKPSC_SHDWEN_POS)
							|(EPT_DBLDR_MD_ZRO_PRD<<EPT_CRLDMODE_POS)|(EPT_DBLDR_MD_ZRO_PRD<<EPT_LDDTRMD_POS)|(EPT_DBLDR_MD_ZRO_PRD<<EPT_LDDTFMD_POS)|(EPT_DBLDR_MD_ZRO_PRD<<EPT_LDPSCMD_POS);
	}
}

/** \brief   EPT EVTRG Config
 * 			
 *  \param[in] eTrg: Trigger event select \ref ept_trg_e
 *  \param[in] eTrgSrc: Trigger event source select \ref ept_trgsrc_e
 *  \param[in] eTrgoutEn: Trigger event enable or disable control \ref ept_trgout_md_e
 *  \param[in] eTrgSrc: Trigger event source select \ref ept_trgsrc_e
 * 
 *  \return none
 */  
void ept_event_trigger_configure(ept_trgsrc_e eTrg , ept_trgsrc_e eTrgSrc , ept_trgout_md_e eTrgoutEn )
{
	if(eTrg==EPT_TRG0)
	{
		EPT0->EVTRG=(EPT0->EVTRG&(~(EPT_SEL_MSK_TRG(EPT_TRG0)|EPT_OUTEN_MSK_TRG(EPT_TRG0))))|(eTrgSrc<<EPT_SEL_POS_TRG(EPT_TRG0))|(eTrgoutEn<<EPT_OUTEN_POS_TRG(EPT_TRG0));
	}
	else if(eTrg==EPT_TRG1)
	{
		EPT0->EVTRG=(EPT0->EVTRG&(~(EPT_SEL_MSK_TRG(EPT_TRG1)|EPT_OUTEN_MSK_TRG(EPT_TRG1))))|(eTrgSrc<<EPT_SEL_POS_TRG(EPT_TRG1))|(eTrgoutEn<<EPT_OUTEN_POS_TRG(EPT_TRG1));
	}
	else if(eTrg==EPT_TRG2)
	{
		EPT0->EVTRG=(EPT0->EVTRG&(~(EPT_SEL_MSK_TRG(EPT_TRG2)|EPT_OUTEN_MSK_TRG(EPT_TRG2))))|(eTrgSrc<<EPT_SEL_POS_TRG(EPT_TRG2))|(eTrgoutEn<<EPT_OUTEN_POS_TRG(EPT_TRG2));
	}
	else if(eTrg==EPT_TRG3)
	{
		EPT0->EVTRG=(EPT0->EVTRG&(~(EPT_SEL_MSK_TRG(EPT_TRG3)|EPT_OUTEN_MSK_TRG(EPT_TRG3))))|(eTrgSrc<<EPT_SEL_POS_TRG(EPT_TRG3))|(eTrgoutEn<<EPT_OUTEN_POS_TRG(EPT_TRG3));
	}
	EPT0->EVTRG|=EPT_CNTINIT_ALL_ENABLE;
}

/** \brief   EPT EVTRG software trigger
 * 			
 *  \param[in] eTrg: Trigger event select \ref ept_trg_e
 * 
 *  \return none
 */  
void ept_event_software_trigger(ept_trgsrc_e eTrg)
{
	if(eTrg==EPT_TRG0)
	{
		EPT0->EVSWF|=EPT_SWF_EV(EPT_TRG0);
	}
	else if(eTrg==EPT_TRG1)
	{
		EPT0->EVSWF|=EPT_SWF_EV(EPT_TRG1);
	}
	else if(eTrg==EPT_TRG2)
	{
		EPT0->EVSWF|=EPT_SWF_EV(EPT_TRG2);
	}
	else if(eTrg==EPT_TRG3)
	{
		EPT0->EVSWF|=EPT_SWF_EV(EPT_TRG3);
	}
}

/** \brief   EPT interrupt enable 
 * 			
 *  \param[in] eInt: type of interrupt \ref ept_int_e
 * 
 *  \return none
 */  
void ept_int_enable(ept_int_e eInt)
{
	EPT0->ICR 	= eInt;							//clear LVD INT status
	csi_vic_enable_irq(EPT0_INT);
	EPT0->IMCR  |= eInt;
}

/** \brief   EPT interrupt disable 
 * 			
 *  \param[in] eInt: type of interrupt \ref ept_int_e
 * 
 *  \return none
 */  
void ept_int_disable(ept_int_e eInt)
{
	EPT0->IMCR  &= ~eInt;
	EPT0->ICR= eInt;
}

/** \brief   EPT emergency interrupt enable 
 * 			
 *  \param[in] eEmInt: type of  emergency interrupt \ref ept_emint_e
 * 
 *  \return none
 */  
void ept_emint_enable(ept_emint_e eEmInt)
{
	EPT0->EMICR = eEmInt;							//clear LVD INT status
	EPT0->EMIMCR  |= eEmInt;
}

/** \brief   EPT emergency interrupt disable 
 * 			
 *  \param[in] eEmInt: type of  emergency interrupt \ref ept_emint_e
 * 
 *  \return none
 */  
void ept_emint_disable(ept_emint_e eEmInt)
{
	EPT0->EMIMCR  &= ~eEmInt;
}

/** \brief   EPT EP0~EP1 config
 * 			
 *  \param[in] eEpx: EPT emergency port select \ref ept_ep_e
 *  \param[in] eEpInput: epx input select \ref ept_ep_input_e
 *  \param[in] eEpFlt: epx digital filter check period \ref ept_epflt_e
 *  \param[in] byOr0Epx: OR0 input enable or disable control  ,range: 0~0x3f
 *  \param[in] bOr1Epx: OR1input enable or disable control  ,range: 0~0x3f
 * 
 *  \return none
 */  
void ept_emergency_port_configure(ept_ep_e eEpx , ept_ep_input_e eEpInput , ept_epflt_e eEpFlt  , U8_T byOr0Epx , U8_T byOr1Epx)
{
	EPT0->REGPROT = EPT_REGPROT;
	if(eEpx==EPT_EP0)
	{
		EPT0->EMSRC=(EPT0->EMSRC&(~EPT_SEL_MSK_EP(EPT_EP0)))|(eEpInput<<EPT_SEL_POS_EP(EPT_EP0));
	}
	else if(eEpx==EPT_EP1)
	{
		EPT0->EMSRC=(EPT0->EMSRC&(~EPT_SEL_MSK_EP(EPT_EP1)))|(eEpInput<<EPT_SEL_POS_EP(EPT_EP1));
	}

	EPT0->REGPROT = EPT_REGPROT;
	EPT0->EMSRC2=byOr0Epx|(byOr1Epx<<EPT_ORL1_POS)|(eEpFlt<<EPT_EPPACE0_POS);
}

/** \brief   EPT EMPOL config
 * 			
 *  \param[in] byEbiPol: EBIX polarity setting (0:Active high 1:Active low)  ,range: 0~0x3f
 * 
 *  \return none
 */  
void ept_emergency_polarity_configure(U8_T byEbiPol)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->EMPOL=byEbiPol;
}

/** \brief   EPT EMECR config
 * 			
 *  \param[in] eLckSrc: ept LKCR source select \ref ept_lkcr_src_e
 *  \param[in] eLckCr:  EPT LKCR Mode Select	 \ref ept_lckcr_e
 * 
 *  \return none
 */ 
void ept_emergency_lock_configure(ept_lkcr_src_e eLckSrc , ept_lckcr_e eLckCr)
{
	EPT0->REGPROT =EPT_REGPROT;
	EPT0->EMECR|=(EPT_EMSOR_SHDWEN)|(EM_OSRLD_ZRO<<EPT_OSRLDMD_POS)|(EM_SLCLR_ZRO_PRD<<EPT_SLCK_CLRMD_POS);			//EMOSR CNT=ZRO load，Automatically clear soft lock when CNT=ZRO&PRD
	EPT0->REGPROT =EPT_REGPROT;
	if(eLckSrc==EPT_LKCR_TRG_CPU_FAULT)
	{
		if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_EN)
		{
			EPT0->EMECR|=(EPT_FAULT_ENABLE<<EPT_CPUFAULT_HLCK_POS);
		}
		else if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_DIS)
		{
			EPT0->EMECR&=~(EPT_FAULT_ENABLE<<EPT_CPUFAULT_HLCK_POS);
		}
	}
	else if(eLckSrc==EPT_LKCR_TRG_MEM_FAULT)
	{
		if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_EN)
		{
			EPT0->EMECR|=(EPT_FAULT_ENABLE<<EPT_MEMFAULT_HLCK_POS);
		}
		else if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_DIS)
		{
			EPT0->EMECR&=~(EPT_FAULT_ENABLE<<EPT_MEMFAULT_HLCK_POS);
		}
	}
	else if(eLckSrc==EPT_LKCR_TRG_EOM_FAULT)
	{
		if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_EN)
		{
			EPT0->EMECR|=(EPT_FAULT_ENABLE<<EPT_EOMFAULT_HLCK_POS);
		}
		else if(eLckCr==EPT_LKCR_TRG_X_FAULT_HLOCK_DIS)
		{
			EPT0->EMECR&=~(EPT_FAULT_ENABLE<<EPT_EOMFAULT_HLCK_POS);
		}
	}
	else
	{
		EPT0->EMECR|=(eLckCr<<(eLckSrc))|(EPT_EMASYNC_DISABLE<<EPT_EPASYNC_POS);
	}
}

/** \brief   EPT SHLOCK output config
 * 			
 *  \param[in] eOutCh: ept output channel select \ref ept_outch_e
 *  \param[in] eShLck: ept shlock output state setting \ref ept_shlock_e
 * 
 *  \return none
 */ 
void ept_emergency_lock_output_set(ept_outch_e eOutCh , ept_shlock_e eShLck)
{
	EPT0->REGPROT = EPT_REGPROT;
	EPT0->EMOSR|=eShLck<<eOutCh;
}

/** \brief   EPT software lock clr
 * 			
 *  \param[in] eEmInt: em interrupt : only  EP0 & EP1\ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_emergency_software_lock_clear(ept_emint_e eEmInt)
{
	EPT0->EMSLCLR|=eEmInt;
}

/** \brief   EPT hardware lock clr
 * 			
 *  \param[in] eEmInt: em interrupt  \ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_emergency_hardware_lock_clear(ept_emint_e eEmInt)
{
	EPT0->EMHLCLR|=eEmInt;
}
/** \brief   EPT software set lock
 * 			
 *  \param[in] eEmInt: em interrupt : only  EP0 & EP1 \ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_software_trigger_epx(ept_emint_e eEmInt)
{
	EPT0->REGPROT =EPT_REGPROT;
	EPT0->EMFRCR|=eEmInt;
}
/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/