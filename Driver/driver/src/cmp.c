/***********************************************************************//** 
 * \file  cmp.c
 * \brief  Comparator driver
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


/** \brief software reset
 * 
 *  \param[in] none
 *  \return none
 */  
void cmp_software_reset(csp_cmp_t *ptCmpBase )
{
	ptCmpBase ->CEDR |= CMP_SOFTRESET;
}

/** \brief enable/disable cmp clock for register configuraiton
 * 
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \return none
 */ 
void cmp_clk_cmd(csp_cmp_t *ptCmpBase , functional_status_e eNewState)
{
	ptCmpBase -> CEDR &= (~CMP_CLK_MSK) | (eNewState << CMP_CLK_POS);
}

/** \brief enable cmp module (digital + analog)
 * 
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \return none
 */ 
void cmp_open(csp_cmp_t *ptCmpBase)
{
	ptCmpBase -> CR |= CMP_AEN;
	delay_nus(10);				//analog stablization time
	ptCmpBase -> CR |= CMP_EN;
	
}

/** \brief disable cmp module (digital + analog)
 * 
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \return none
 */ 
void cmp_close(csp_cmp_t *ptCmpBase)
{
	ptCmpBase -> CR &= ~CMP_EN;
	ptCmpBase -> CR &= ~CMP_AEN;
}


/** \brief cmp positive and negative input configuration
 * 
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \return none
 */
void cmp_inpcr_configure(csp_cmp_t *ptCmpBase , nsel_e eNSel , psel_e ePSel )
{
	ptCmpBase->INPCR &= (~CMP_NSEL_SET_MSK) & (~CMP_PSEL_SET_MSK)| (eNSel << CMP_NSEL_SET_POS) | (ePSel << CMP_PSEL_SET_POS);
}


/** \brief cmp voltage reference selection
 * 
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eVref: internal VREF or VDD from outside \ref cmp_vref_e
 *  \return none
 */
void cmp_set_vref(csp_cmp_t *ptCmpBase, cmp_vref_e eVref)
{
	uint32_t wPselRd = (ptCmpBase->INPCR & CMP_PSEL_RD_MSK) >> (CMP_PSEL_RD_POS - CMP_PSEL_SET_POS);
	ptCmpBase->INPCR &= (~CMP_REFSEL_MSK) | (eVref << CMP_REFSEL_POS)| wPselRd;
}

/** \brief Enable/Disable integrated BEMF detection (for motor control)
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \return none
 */
void cmp_intbemf_cmd(csp_cmp_t *ptCmpBase, functional_status_e eNewState)
{
	uint32_t wPselRd = (ptCmpBase->INPCR & CMP_PSEL_RD_MSK) >> (CMP_PSEL_RD_POS - CMP_PSEL_SET_POS);
	ptCmpBase->INPCR &= (~CMP_INTBEMF_ENABLE_MSK) | (eNewState << CMP_INTBEMF_ENABLE_POS)| wPselRd;
}


/** \brief CR Configuration
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eCmpIntPol: interrupt polarity \ref filters bypass
 *  \param[in] ePHyst: positive input hysteresis \ref cmp_physt_e
 *  \param[in  eNHyst: negative input hysteresis \ref cmp_nhyst_e
 *  \param[in] eCmpOutSel: filters bypass \ref cmp_nhyst_e
 *  \param[in] eCmpOutPol: output polarity \ref cmpout_pol_e
 *  \return none
 */
void cmp_cr_configure(csp_cmp_t *ptCmpBase , cmpint_pol_e eCmpIntPol, cmp_physt_e ePHyst, cmp_nhyst_e eNHyst,  
				   cmp_cposel_e eCmpOutSel, cmpout_pol_e eCmpOutPol)
{
	ptCmpBase->CR &= (~CMPINT_POL_MSK) & (~CMP_PHYST_MSK) & (~CMP_NHYST_MSK) & (~CMP_CPOSEL_MSK) & (~CMPO_POL_MSK)
					| (eCmpIntPol<<CMPINT_POL_POS) | (ePHyst << CMP_PHYST_POS) | (eNHyst << CMP_NHYST_POS) 
					| (eCmpOutSel << CMP_CPOSEL_POS) | (eCmpOutPol << CMPO_POL_POS);
}

/** \brief digital filter(Integrating filter) Configuration, including:
 *  - interating depth: the filter changes output only when the accumulated depth is met
 *  - sampling clock = PCLK * 2^ byDivN/ (byDivM+1)
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eDepth: accumulated depth, \ref cmp_df_depth_e
 *  \param[in] byDivN: 0~0x1f  
 *  \param[in] byDivM: 0~0xff
 *  \return none
 */
void cmp_dflt_configure(csp_cmp_t *ptCmpBase,cmp_df_depth_e eDepth, U8_T byDivN, U8_T byDivM)
{
	ptCmpBase -> DFCR1 = (eDepth << CMP_DF1_DEPTH_POS) | ((byDivN & CMP_DF1_DIVN_MSK) << CMP_DF1_DIVN_POS) | ((byDivM & CMP_DF1_DIVM_MSK) << CMP_DF1_DIVM_POS);
}


/** \brief hard window filter configuration, including:
 *  - window width
 *  - clock = PCLK/byDiv
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] byWCnt: 0~0xff, window width = byWcnt/clock 
 *  \param[in] byDiv: 0~0xf, clock = PCLK/byDiv 
 *  \return none
 */
void cmp_hwflt_configure(csp_cmp_t *ptCmpBase, U8_T byWCnt, U8_T byDiv, cmp_wf_align_e eNewTrigEffect)
{
	ptCmpBase -> HWFCR = (byWCnt << CMP_WCNT_POS) | (byDiv << CMP_WF_DIVN_POS);
	ptCmpBase -> CR &= (~CMP_HWFALIGN_MSK) | ( eNewTrigEffect << CMP_HWFALIGN_POS);
}

/** \brief soft window filter configuration, including:
 *  - window width
 *  - clock = PCLK/byDiv
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] byWCnt: 0~0xff, window width = byWcnt/clock 
 *  \param[in] byDiv: 0~0xf, clock = PCLK/byDiv 
 *  \param[in] eNewTrigEffect： effect when new trigger arrives before previous window completion
 *  \param[in] eSwSetVal: filter output status when window is valid
 *  \return none
 */
void cmp_swflt_configure(csp_cmp_t *ptCmpBase, U8_T byWCnt, U8_T byDiv, cmp_wf_align_e eNewTrigEffect, cmp_swsetval_e eSwSetVal)
{
	ptCmpBase -> SWFCR &= (~CMP_WCNT_MSK) & (~CMP_WF_DIVN_MSK) & (~CMP_SWSET_MSK)
						|(byWCnt << CMP_WCNT_POS) | (byDiv << CMP_WF_DIVN_POS) | (eSwSetVal << CMP_SWSET_POS);
	ptCmpBase -> CR &= (~CMP_SWFALIGN_MSK) | ( eNewTrigEffect << CMP_SWFALIGN_POS);
}



/** \brief CMP interrupt enable
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eIntSrc :interrupt source \ref cmp_int_e
 *  \return none
 */
void cmp_int_enable(csp_cmp_t *ptCmpBase, cmp_int_e eIntSrc)
{
	ptCmpBase->ICR = eIntSrc;
	csi_vic_enable_irq(CMP0_INT);	
	ptCmpBase->IMCR  |= eIntSrc;	
} 

/** \brief CMP interrupt disable
 *  \param[in] ptCmpBase: pointer of CMP register structure
 *  \param[in] eIntSrc :interrupt source \ref cmp_int_e
 *  \return none
 */
void cmp_int_disable(csp_cmp_t *ptCmpBase, cmp_int_e eIntSrc)
{
	ptCmpBase -> IMCR &= (~eIntSrc);
	ptCmpBase -> ICR |= eIntSrc;
	
} 


/** \brief simutaneously get outputs of all CMPs
 *  \param[in] none
 *  \return cmp outputs
 */
U8_T cmp_get_all_output(void)
{
	return ((CMP0 -> CR & (CMP_CPOUT_ALL_MSK)) >> CMP_CPOUT_ALL_POS);
}

/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/