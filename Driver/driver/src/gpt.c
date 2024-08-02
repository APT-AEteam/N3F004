/***********************************************************************//** 
 * \file  gpt.c
 * \brief gpt function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-5<td>V3_0_0  <td>GQQ  <td>initial
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


/** \brief deinit gpt registers 
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 			   
 *  \return none
 */ 
void gpt_deinit(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->CEDR 		= 0xBE980000;
	ptGptaBase->RSSR 		= GPT_RESET_VALUE;
	ptGptaBase->PSCR 		= GPT_RESET_VALUE;
	ptGptaBase->CR 				= GPT_RESET_VALUE;
	ptGptaBase->SYNCR 		= GPT_RESET_VALUE;
	ptGptaBase->PRDR 		= GPT_RESET_VALUE;
	ptGptaBase->CMPA 		= GPT_RESET_VALUE;
	ptGptaBase->CMPB 		= GPT_RESET_VALUE;
	ptGptaBase->CMPLDR 	= 0X00000090;
	ptGptaBase->CNT 			= GPT_RESET_VALUE;
	ptGptaBase->AQLDR 		= 0X00000024;
	ptGptaBase->AQCR1 		= GPT_RESET_VALUE;
	ptGptaBase->EVTRG 		= GPT_RESET_VALUE;
	ptGptaBase->EVSWF 		= GPT_RESET_VALUE;
	ptGptaBase->IMCR 		= GPT_RESET_VALUE;
	ptGptaBase->ICR 			= GPT_RESET_VALUE;
}


/** \brief gpt init, clk enable/disable, clk source select, stop mode config and clk div setting
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eClkEn: GPT clk control :enable or disable \ref gpt_state_e
 *  \param[in] eClkSrc: gpt clk source select \ref gpt_clksrc_e
 *  \param[in] eStopMd: gpt stop mode select: shadow or immediate  \ref gpta_stopmode_e
 *  \param[in] hwPscr: clk div setting ,range :0 ~0xffff . FTCLK = FPCLK / (PSC+1)
 * 			   
 *  \return none
 */ 
void gpt_configure(csp_gpta_t *ptGptaBase,gpta_state_e eClkEn,gpt_clksrc_e eClkSrc,gpta_stopmode_e eStopMd,U16_T hwPscr)
{
	ptGptaBase->CEDR = (eClkEn<<GPTA_CLKEN_POS)| (eClkSrc<<GPTA_CSS_POS)|(eStopMd<<GPTA_STOPMD_POS);
	ptGptaBase->PSCR=hwPscr;
}

/** \brief gpt wave control configure
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eStartMd: gpt software start control  \ref gpta_startmode_e
 *  \param[in] eIdleSt: gpt idle state select \ref gpta_stpst_e
 *  \param[in] ePrdrLd: gpt prdr active register load control  \ref gpta_ldprdr_e
 *  \param[in] eRunMd:  gpt counter run mode select \ref gpta_runmode_e
 *  \param[in] eBurstEn:  gpt burst control : enable or disable \ref gpta_state_e
 *  \param[in] eCks:  gpt sample clk control \ref gpta_cks_e
 *  \param[in] eCgflt:  gpt gate input digital filter control \ref gpta_cgflt_e
 *  \param[in] ePscld:  gpt pscr active register load control \ref gpta_pscld_e
 *  \param[in] eWaveType:  gpt wave type select \ref gpta_wave_e
 * 			   
 *  \return none
 */ 
void gpt_wavectrl_configure(csp_gpta_t *ptGptaBase,gpta_startmode_e eStartMd,gpta_stpst_e eIdleSt,gpta_ldprdr_e ePrdrLd,gpta_runmode_e eRunMd,
						gpta_state_e eBurstEn,gpta_cks_e eCks, gpta_cgflt_e eCgflt,gpta_pscld_e ePscld,gpta_wave_e eWaveType)
{
	ptGptaBase->CR =(eStartMd<<GPTA_STARTMODE_POS)|(eIdleSt<<GPTA_STPST_POS)|(ePrdrLd<<GPTA_PRDLD_POS)|(eRunMd<<GPTA_RUNMODE_POS)
										|(eBurstEn<<GPTA_BURST_POS)|(eCks<<GPTA_CKS_POS)|(eCgflt<<GPTA_CGFLT_POS)|(ePscld<<GPTA_PSCLD_POS)|(eWaveType<<GPTA_CAP_WAVE_POS);
}

/** \brief gpt wave load control
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eLdAqcr: gpt shadow of aqcr regiaster  control \ref gpta_ldaqcr_e
 *  \param[in] eShdLd: shadow mode, active aqcr load from active register  \ref gpta_shadowld_e
 * 			   
 *  \return none
 */ 
void gpt_waveload_configure(csp_gpta_t *ptGptaBase,gpta_ldaqcr_e eLdAqcr ,gpta_shadowld_e eShdLd)
{
	ptGptaBase->AQLDR=(eLdAqcr<<GPTA_AQCR1_SHDWEN_POS)|(eShdLd<<GPTA_LDAMD_POS);
}

/** \brief gpt wave out init
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eC1Sel: gpt c1 compare value select \ref gpta_cxsel_e
 *  \param[in] eC2Sel: gpt c2 compare value select \ref gpta_cxsel_e
 *  \param[in] eZeroAct:  cnt = zero, pwm1 output act select \ref gpta_act_e
 *  \param[in] ePrdAct: cnt = prdr, pwm1 output act select \ref gpta_act_e
 *  \param[in] eC1uAct: cnt = c1, pwm1 output act select \ref gpta_act_e
 *  \param[in] eC2uAct: cnt = c2, pwm1 output act select \ref gpta_act_e
 * 			   
 *  \return none
 */ 
void gpt_waveout_configure(csp_gpta_t *ptGptaBase,gpta_cxsel_e eC1Sel,gpta_cxsel_e eC2Sel, gpta_act_e eZeroAct, gpta_act_e ePrdAct,gpta_act_e eC1uAct,gpta_act_e eC2uAct)
{
	ptGptaBase->AQCR1=(eC1Sel<<GPTA_C1SEL_POS)|(eC2Sel<<GPTA_C2SEL_POS)|(eZeroAct<<GPTA_ACT_ZRO_POS)|(ePrdAct<<GPTA_ACT_PRD_POS)|(eC1uAct<<GPTA_ACT_C1U_POS)
											|(eC2uAct<<GPTA_ACT_C2U_POS);
}

/** \brief gpt capture config
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eCapMdSel: gpt capture mode select: merge or seperate  \ref gpta_capmdsel_e
 *  \param[in] eCapMd: gpt capture mode :once or continous  \ref gpta_capmd_e
 *  \param[in] eCapldEn: capture load control :enable or disable \ref gpta_state_e
 *  \param[in] eLdARst: gpt  counter reset  after cmpa (shadow) load \ref gpta_state_e
 *  \param[in] eLdBRst:  gpt  counter reset  after cmpb (shadow) load  \ref gpta_state_e
 *  \param[in] eLdAARst:  gpt  counter reset  after cmpa (active) load  \ref gpta_state_e
 *  \param[in] eLdBARst:  gpt  counter reset  after cmpb (active) load \ref gpta_state_e
 *  \param[in] byStopWrap:  capture mode, counter period setting , range : 0~0x3
 *  \param[in] eWaveType:  gpt wave type select \ref gpta_wave_e
 * 			   
 *  \return none
 */ 
void gpt_capture_configure(csp_gpta_t *ptGptaBase, gpta_capmdsel_e eCapMdSel,gpta_capmd_e eCapMd , gpta_state_e eCapldEn , gpta_state_e eLdARst , gpta_state_e eLdBRst , gpta_state_e eLdAARst , gpta_state_e eLdBARst, 
												U8_T byStopWrap,gpta_wave_e eWave )
{
	ptGptaBase->CR=(ptGptaBase->CR&(~(GPTA_STARTMODE_MSK|GPTA_PRDLD_MSK|GPTA_CAPLD_MSK|GPTA_CAPMD_SEL_MSK|GPTA_PSCLD_MSK|GPTA_CAPMD_MSK|GPTA_CMPA_RST_MSK|GPTA_CAPMD_MSK
									|GPTA_CMPB_RST_MSK|GPTA_CMPAA_RST_MSK|GPTA_CMPBA_RST_MSK|GPTA_CAP_WAVE_MSK)))|(GPTA_SW_START<<GPTA_STARTMODE_POS)|(GPTA_LDPRDR_PEND<<GPTA_PRDLD_POS)
									|(eCapldEn<<GPTA_CAPLD_POS)|(eCapMdSel<<GPTA_CAPMD_SEL_POS)|(GPTA_PSCLD_ZRO<<GPTA_PSCLD_POS)|(byStopWrap<<GPTA_CAPMD_POS)|(eLdARst<<GPTA_CMPA_RST_POS)
									|(eLdBRst<<GPTA_CMPB_RST_POS)|(eLdAARst<<GPTA_CMPAA_RST_POS)|(eLdBARst<<GPTA_CMPBA_RST_POS)|(eWave<<GPTA_CAP_WAVE_POS)|(eCapMd<<GPTA_CAPMD_POS);
}

/** \brief gpt sync init
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eSyncIn: sync input channel  select \ref gpta_syncin_e
 *  \param[in] eOstMd: sync mode select  :once or continous  \ref gpta_syncmd_e
 *  \param[in] eTrg0Sel: as extsync , trigger 0 source select  \ref gpta_trgsel_e
 *  \param[in] eTrg1Sel: as extsync , trigger 1 source select  \ref gpta_trgsel_e
 *  \param[in] eArearm:  hardware auto rearm control  \ref gpta_arearm_e
 *  \return none
 */ 
void gpt_sync_configure(csp_gpta_t *ptGptaBase,gpta_syncin_e eSyncIn,gpta_syncmd_e eOstMd,gpta_trgsel_e eTrg0Sel,gpta_trgsel_e eTrg1Sel,gpta_arearm_e eArearm)
{
	ptGptaBase->SYNCR |= (GPT_ENABLE<<GPTA_SYNC_POS(eSyncIn))| (eOstMd<<GPTA_OSTMD_POS(eSyncIn))|(eTrg0Sel<<GPTA_TRGO0SEL_POS)|(eTrg1Sel<<GPTA_TRGO1SEL_POS)|(eArearm<<GPTA_AREARM_POS);
}

/** \brief gpt event trigger init
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eTrgSel0: source of trigger event 0 select  \ref gpta_trgsrc_e
 *  \param[in] eTrgSel1: source of trigger event 1 select  \ref gpta_trgsrc_e
 *  \param[in] eTrg0O: trigger event 0 output control :enable or disable  \ref gpta_state_e
 *  \param[in] eTrg1O: trigger event 1 output control :enable or disable  \ref gpta_state_e
 * 
 *  \return none
 */ 
void gpt_evtrg_configure(csp_gpta_t *ptGptaBase,gpta_trgsrc_e eTrgSel0,gpta_trgsrc_e eTrgSel1,gpta_state_e eTrg0O,gpta_state_e eTrg1O)
{
	ptGptaBase->EVTRG = (eTrgSel0<<GPTA_TRG0SEL_POS) |(eTrgSel1<<GPTA_TRG1SEL_POS)|(eTrg0O<<GPTA_TRG0OE_POS)|(eTrg1O<<GPTA_TRG1OE_POS);

}

/** \brief GPT Wave Compare Load Init
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eCmpALd: cmpa shadow function control : shadow or immediate  \ref gpta_ldmd_e
 *  \param[in] eCmpBLd: cmpb shadow function control : shadow or immediate  \ref gpta_ldmd_e
 *  \param[in] eCmpAMd: shadow mode, active cmpa load mode  \ref gpta_shdwldmd_e
 *  \param[in] eCmpBMd: shadow mode, active cmpb load mode  \ref gpta_shdwldmd_e
 * 
 *  \return none
 */ 
void gpt_cmpload_configure(csp_gpta_t *ptGptaBase,gpta_ldmd_e eCmpALd,gpta_ldmd_e eCmpBLd,gpta_shdwldmd_e eCmpAMd,gpta_shdwldmd_e eCmpBMd)
{
	ptGptaBase->CMPLDR=(eCmpALd<<GPTA_CMPA_LD_POS)|(eCmpBLd<<GPTA_CMPB_LD_POS)|(eCmpAMd<<GPTA_CMPA_LDTIME_POS)|(eCmpBMd<<GPTA_CMPB_LDTIME_POS);
}

/** \brief GPT debug mode control
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eDebugEn:   Debug mode control  \ref gpt_debug_e
 * 
 *  \return none
 */ 
void gpt_debug_mode(csp_gpta_t *ptGptaBase,gpt_debug_e eDebugEn)
{
	ptGptaBase->CEDR  =(ptGptaBase->CEDR &(~GPTA_DBGEN_MSK))| (GPT_ENABLE<<GPTA_DBGEN_POS);						
}

/** \brief GPT start
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_start(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->RSSR |= GPTA_START;
}

/** \brief GPT stop
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_stop(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->RSSR &= ~GPTA_START;
}

/** \brief GPT software reset
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_software_reset(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->RSSR |= GPTA_RESET;
}

/** \brief GPT capture rearm
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_cap_rearm(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->CR |= GPTA_CAPREARM;
}

/** \brief GPT mode config
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eMode: gpta mode select : cmpa/cmpb capture or wave \ref gpta_wave_e
 * 
 *  \return none
 */ 
void gpt_mode_configure(csp_gpta_t *ptGptaBase,gpta_wave_e eMode)
{
	ptGptaBase->CR |= eMode<<GPTA_CAP_WAVE_POS;
}

/** \brief GPT soft reset at once sync mode
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eSync:  sync channel select \ref gpta_syncin_e
 * 
 *  \return none
 */ 
void gpt_rearm_write(csp_gpta_t *ptGptaBase, gpta_syncin_e eSync)
{
	ptGptaBase->SYNCR |= (GPTA_REARM_EN<<GPTA_REARM_POS(eSync));
}

/** \brief GPT rearm read
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eSync:  sync channel select \ref gpta_syncin_e
 * 
 *  \return none
 */ 
U8_T gpt_rearm_read(csp_gpta_t *ptGptaBase,gpta_syncin_e eSync)
{
	uint8_t value = 0;
    uint32_t dat = 0;
    dat=(ptGptaBase->SYNCR)&(GPTA_REARM_EN<<GPTA_REARM_POS(eSync));
    if (dat)								
	{
	    value = 1;
	} 
    return value;
}

/** \brief GPT Period / Compare set
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] hwPrdr: prdr data setting ,range :0~0xffff
 *  \param[in] hwCmpa: cmpa data setting ,range :0~0xffff
 *  \param[in] hwCmpb: cmpb data setting ,range :0~0xffff
 * 
 *  \return none
 */ 
void gpt_period_cmp_write(csp_gpta_t *ptGptaBase,U16_T hwPrdr,U16_T hwCmpa,U16_T hwCmpb)
{
	ptGptaBase->PRDR =hwPrdr;
	ptGptaBase->CMPA =hwCmpa;
	ptGptaBase->CMPB =hwCmpb;
}

/** \brief read prdr val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_prdr_read(csp_gpta_t *ptGptaBase)
{
    return ptGptaBase->PRDR;
}

/** \brief read cmpa val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cmpa_read(csp_gpta_t *ptGptaBase)
{
    return ptGptaBase->CMPA;
}

/** \brief read cmpb val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cmpb_read(csp_gpta_t *ptGptaBase)
{
    return ptGptaBase->CMPB;
}

/** \brief read cnt val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cnt_read(csp_gpta_t *ptGptaBase)
{
    return ptGptaBase->CNT;
}

/** \brief gpt register link configure
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] ePrdrLk:  prdr register link target select \ref gpt_reglk_e
 *  \param[in] eCmpaLk:  cmpa register link target select \ref gpt_reglk_e
 *  \param[in] eCmpbLk:  cmpb register link target select \ref gpt_reglk_e
 *  \param[in] eRssrLk:  rssr register link target select \ref gpt_reglk_e
 * 
 *  \return none
 */ 
void gpt_reglink_configure(csp_gpta_t *ptGptaBase,gpt_reglk_e ePrdrLk, gpt_reglk_e eCmpaLk,gpt_reglk_e eCmpbLk,gpt_reglk_e eRssrLk)
{
	ptGptaBase->REGLK = (ePrdrLk<<GPTA_PRDR_POS)|(eCmpaLk<<GPTA_CMPA_POS)|(eCmpbLk<<GPTA_CMPB_POS)|(eRssrLk<<GPTA_RSSR_POS);
}

/** \brief gpt interrupt ip level enable 
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eInt:  interrupt select \ref gpta_int_e
 * 
 *  \return none
 */ 
void gpt_int_enable(csp_gpta_t *ptGptaBase,gpta_int_e eInt)
{
	ptGptaBase->ICR = eInt;
	ptGptaBase->IMCR  |= eInt;				
}

/** \brief gpt interrupt disable
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eInt:  interrupt select \ref gpta_int_e
 * 
 *  \return none
 */ 
void gpt_int_disable(csp_gpta_t *ptGptaBase,gpta_int_e eInt)
{
	ptGptaBase->IMCR  &= ~eInt;		
	ptGptaBase->ICR = eInt;
}

	

