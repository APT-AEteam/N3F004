/***********************************************************************//** 
 * \file  syscon.c
 * \brief  syscon driver including clock, IWDT, EXI, LVD,etc.,
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



/** \brief Deinitializes SYSCON registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */   
void syscon_deinit(void)									//reset value
{

	SYSCON->SCLKCR=SYSCON_SCLKCR_RST;
	SYSCON->PCLKCR=SYSCON_PCLKCR_RST;
	SYSCON->OSTR=SYSCON_OSTR_RST;
	SYSCON->LVDCR=SYSCON_LVDCR_RST;
	SYSCON->EXIRT=SYSCON_EXIRT_RST;
	SYSCON->EXIFT=SYSCON_EXIFT_RST;
	SYSCON->IWDCR=SYSCON_IWDCR_RST;
	SYSCON->IWDCNT=SYSCON_IWDCNT_RST;
	SYSCON->EVTRG=SYSCON_EVTRG_RST;
	SYSCON->EVPS=SYSCON_EVPS_RST;

}
 
/** \brief EMOSC configuration: workmode/filter/gain/stablization counter
 * 
 *  \param[in] hwEMCnt: 0~0x3FF, the bigger the num, the slower the stablization time
 *  \param[in] byEMGain: 0~0x1F, the faster the Femosc, the larger the gain
 *  \param[in] eEmWkMd: EM_HIGHF/EM_LOWF \ref em_lfsel_e
 *  \param[in] eEMFltEnable: ENABLE/DISABLE \ref functional_status_e
 *  \param[in] eEMFlt: EM_FLSEL_5NS~EM_FLSEL_20NS \ref em_fltsel_e
 *  \return none
 */ 
void syscon_emosc_configure(U16_T hwEmCnt, U8_T byEmGain ,em_lfsel_e eEmWkMd, functional_status_e eEmFltEnable, em_fltsel_e eEMFlt)
{
	SYSCON->OSTR= (hwEmCnt << EM_CNT_POS)|(byEmGain<<EM_GMCTL_POS)| (eEmWkMd << EM_LFSEL_POS) | (eEmFltEnable << EM_FLT_EN_POS) | (eEMFlt << EM_FLTSEL_POS);
}


/** \brief Enable OSC
 * 
 *  \param[in] eOscEnable:ENDIS_ISOSC/ENDIS_IMOSC/ENDIS_EMOSC/ENDIS_PLL \ref osc_enable_e
 *  \return none
 */
void syscon_osc_enable(osc_enable_e eOscEnable )
{
	SYSCON->GCER |= eOscEnable;													//enable 	
	while(!(SYSCON->CKST & eOscEnable));

}

/** \brief Disable OSC
 * 
 *  \param[in] eOscEnable:ENDIS_ISOSC/ENDIS_IMOSC/ENDIS_EMOSC/ENDIS_PLL \ref osc_enable_e
 *  \return none
 */
void syscon_osc_disable(osc_enable_e eOscEnable )
{
	SYSCON->GCDR |= eOscEnable;													//disable
	
}


/** \brief PLL configuration
 *  \param[in] eType: PLL_TYPE_ANA/PLL_TYPE_DIG \ref pll_type_e
 *  \param[in] eSrc: PLL_SRC_IMOSC/PLL_SRC_EMOSC \ref pll_src_e
 *  \param[in] eOscEnable:ENDIS_ISOSC/ENDIS_IMOSC/ENDIS_EMOSC \ref osc_enable_e
 *  \return none
 */
void syscon_pll_configure(pll_type_e eType, pll_src_e eSrc, functional_status_e eUnlockRst)
{
	SYSCON ->PLLCR = (eType << PLL_TYPE_POS) | (eSrc << PLL_SRC_POS) | (eUnlockRst << PLL_UNLOCK_RST_EN_POS);
}


/** \brief System clock/peripheral clock configuration
 *  WARNING: This function can only be safely called when changing hclk frequence from low to high.
 * 			 Call systemclk_clear() first when change hclk frequence from high to low
 *  \param[in] eSysclk: select system clock srouce \ref sycclk_sel_e
 *  \param[in] eHclkDiv: select HCLK DIV. HCLK = systemclock/eHclkDiv \ref hclk_div_e
 *  \param[in] ePclkDiv: select PCLK DIV. PCLK = HCLK/eHclkDiv \ref pclk_div_e
 *  \param[in] eFreq:  HCLK clock frequence range \ref sysclk_freq_e
 *  \return none
 */
void syscon_hclk_pclk_configure(sycclk_sel_e eSysclk , hclk_div_e eHclkDiv , pclk_div_e ePclkDiv , sysclk_freq_e eFreq)
{
	IFC->CEDR=0x01;						//IFC CLKEN
	if(eFreq == F_24_48MHz)
	{
		IFC->MR = 0x04|(0x00<<16);			//High speed mode
	}
	if(eFreq == F_16_24MHz)
	{
		IFC->MR = 0x02|(0x00<<16);			//Medium speed mode
	}
	if(eFreq == F_8_16MHz)
	{
		IFC->MR = 0x01|(0x00<<16);			//Low speed mode
	}
	if(eFreq == F_0_8MHz)
	{
		IFC->MR = 0x00|(0x00<<16);			//Low speed mode
	}
	SYSCON->SCLKCR = SCLKCR_KEY | eHclkDiv| eSysclk;
	while (!(SYSCON->CKST & (SYSCLK_STABLE))); 									// waiting for sysclk stable
	SYSCON->PCLKCR = PCLKCR_KEY|ePclkDiv;										
}


/** \brief Set sysclk to a lower frequence: HCLK = IMOSC/3 = 8MHz
 * 	 Call this function first when change hclk frequence from high to low
 *  \return none
 */
void sysclk_clear(void)
{
	SYSCON->SCLKCR = HCLK_DIV_6;	
}

/** \brief IWDT enable 
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_enable(void)
{
	SYSCON->IWDEDR= IWDEDR_KEY|EN_IWDT;
	while(!(SYSCON->IWDCR & IWDT_BUSY));
}

/** \brief IWDT disable 
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_disable(void)
{
	SYSCON->IWDEDR = IWDEDR_KEY|DIS_IWDT;	
	while(!(SYSCON->IWDCR & IWDT_BUSY));
}


/** \brief IWDT reload， feed IWDT
 *  \param[in]none
 *  \return none
 */
void syscon_iwdtcnt_reload(void)
{
	SYSCON->IWDCNT = CLR_IWDT;
	while((SYSCON->IWDCNT & IWDT_CLR_BUSY) == IWDT_CLR_BUSY);
}


/** \brief config IWDT interval time and overtime time 
 *  \param[in] eOvTime: overtime(reset) time \ref iwdt_ovt_e
 * 	\param[in] eIntvTime: interval(interrupt) time \ref iwdt_intv_e
 *  \return none
 */

void syscon_iwdt_config(iwdt_ovt_e eOvTime , iwdt_intv_e eIntvTime )
{
	SYSCON->IWDCR = IWDCR_KEY | (eOvTime << IWDT_OVT_POS) | (eIntvTime << IWDT_INTV_POS);
}


/** \brief LVR confiuration
 *  \param[in] eLvdEnable: LVD IP enable/disable \ref functional_status_e
 * 	\param[in] eLvd: LVD interrupt level \ref lvd_level_e
 *  \param[in] eLvr: LVR reset level  \ref 	lvr_level_e
 *  \param[in] ePol: interrupt polarity \ref lvdint_pol_e
 *  \return none
 */
void syscon_lvd_configure(functional_status_e eLvdEnable , lvd_level_e eLvd , lvr_level_e eLvr, lvdint_pol_e ePol)
{
	U32_T wTemp = LVD_DIS;
	if (eLvdEnable)
		wTemp = LVD_EN;
    
	SYSCON->LVDCR = LVD_KEY| wTemp | (eLvd << LVD_LV_POS) |( eLvr << LVR_LV_POS) | (ePol << LVDINT_POL_POS);
}


/** \brief LVD interrupt enable
 *  \param[in] none
 *  \return none
 */

void syscon_lvd_int_enable(void)
{
	SYSCON->ICR = LVD_INT;				//clear LVD INT status
	SYSCON->IMER  |= LVD_INT;
	csi_vic_enable_irq(SYSCON_INT);
}

/** \brief LVD interrupt disable
 *  \param[in] none
 *  \return none
 */
void syscon_lvd_int_disable(void)
{
	SYSCON->IMDR  |= LVD_INT;
	SYSCON->ICR = LVD_INT;				//clear LVD INT status
}


/** \brief IWDT interrupt enable
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_int_enable(void)
{
	SYSCON->ICR = IWDT_INT;				//clear LVD INT status
	SYSCON->IMER  |= IWDT_INT;
	csi_vic_enable_irq(SYSCON_INT);
}

/** \brief IWDT interrupt disable
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_int_disable(void)
{
	SYSCON->IMDR  |= IWDT_INT;
	SYSCON->ICR = IWDT_INT;				//clear LVD INT status
}


/** \brief read reset status
 *  \param[in] none
 *  \return reset source
 */
U32_T read_reset_status(void)
{
	return (SYSCON->RSR & 0x1ff);
}



/** \brief external interrupt configuration
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] byExiGrpNum: EXI group number \ref exi_igrp_e
 *  \param[in] eMode: falling/rising/both falling and risiing \ref exi_trigger_e
 *  \return none
 */
void exi_trigger_cmd(functional_status_e eNewState , exi_igrp_e eExiGrpNum , exi_trigger_e eMode)
{
	U32_T wPinMsak = (0x01ul << eExiGrpNum);
	
	if (eNewState) {
		switch(eMode)
		{
			case EXI_EDGE_R: 	SYSCON->EXIRT |= wPinMsak;
								SYSCON->EXIFT &= (~wPinMsak);break;
			case EXI_EDGE_F:    SYSCON->EXIFT |= wPinMsak;
								SYSCON->EXIRT &= (~wPinMsak);break;
			
			case EXI_EDGE_BOTH: SYSCON->EXIRT |= wPinMsak;
								SYSCON->EXIFT |= wPinMsak; break;
			
			default: 	SYSCON->EXIRT &= (~wPinMsak);					
						SYSCON->EXIFT &= (~wPinMsak);
						break;
		}
	}
	else {
		switch(eMode)
		{
			case EXI_EDGE_R: 	SYSCON->EXIRT &= (~wPinMsak);break;
			case EXI_EDGE_F:    SYSCON->EXIFT &= (~wPinMsak);break;
			
			case EXI_EDGE_BOTH: 			
			default: 	SYSCON->EXIRT &= (~wPinMsak);					
						SYSCON->EXIFT &= (~wPinMsak);
						break;
		}
	}
	
}


/** \brief external interrupt enable, disable control
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] byExiGrpNum: EXI group number \ref exi_igrp_e
 *  \return none
 */

void exi_interrupt_cmd(functional_status_e eNewState , exi_igrp_e eExiGrpNum)
{
	if(eNewState != DISABLE){
		SYSCON->EXICR |=  0x1 << eExiGrpNum;							// Clear EXI status bit
		SYSCON->EXIER |= 0x1 << eExiGrpNum;	
		
	}
	else {
		SYSCON->EXIDR |= 0x1 << eExiGrpNum;
		SYSCON->EXICR |= 0x1 << eExiGrpNum;								// Clear EXI status bit
	}
}




/** \brief chip enter idle mode: CPU clock shuts down
 *  \param[in] none
 *  \return none
 */
void pm_goto_idle_mode(void)
{
	asm ("doze");											// Enter sleep mode
}  

/** \brief chip enter deepsleep(stop) mode: CPU clock shuts down && PCLK shuts down exception for some specific wakeup source IPs
 *  \param[in] none
 *  \return none
 */
void pm_goto_deepsleep_mode(void)
{
	asm ("stop");
}  


/**
  \brief     Config the wakeup source
   * 		 EXI always exists as wakeup sources, no need to config here
  \param[in] eNewState: ENABLE/DISABLE
  \param[in] eWkupSrc: a specific wakeup source
  \return    none
*/
void pm_set_wakeup_src(functional_status_e eNewState, wakeup_src_e eWkupSrc)
{
	SYSCON -> WKCR &= ~(0x1<< eWkupSrc) | (eNewState << eWkupSrc);
}


/**
  \brief     CLO configuration
  \param[in] eSrc: clock source of CLO \ref clo_src_e
  \param[in] eDiv: CLO output div \ref clo_div_e
  \return    none
*/
void syscon_clo_src_set(clo_src_e eSrc,clo_div_e eDiv)
{
	SYSCON->OPT1 &= ~(CLO_SRC_MSK) & ~(CLO_DIV_MSK) | (eSrc << CLO_SRC_POS) | (eDiv << CLO_DIV_POS);
}



/**
  \brief     system reset
  \param[in] none
  \return    none
*/
void syscon_software_reset(void)
{
	SYSCON->IDCCR = IDCCR_KEY | SWRST;
}


/**
  \brief     set all interrupt priority to lowest level)
  \param[in] none
  \return    none
*/
void syscon_int_priority(void)
{
	U8_T i;
	U8_T ePrio = 3;
	for(i = 0; i < 8; i++)
	{
		VIC->IPR[i] = (ePrio << 6) | (ePrio << 14) | (ePrio << 22) | (ePrio << 30);
	}
}


/**
  \brief     Config IO Remap
  \param[in] none
  \return    none
*/
void syscon_ioremap(U8_T byIndex, ioremap_e eCfgVal)
{
	if (byIndex > 7)
		return;
	else {
		SYSCON -> IOMAP1 &= ~(IOMAP_MSK(byIndex) | IOMAP_MSK_POS(byIndex));
	}
}


/** \brief Write User Registers
 *   UREG0~1 : 32bit
 *   UREG2~3 ：16bit
 *  \param[in] eUreg: UREG0~3
 *  \param[in] wValue: value to be written
 *  \return error code
 */
void syscon_ureg_write(user_reg_e eUreg, U32_T wValue)
{
	
	if(eUreg > USER_REG3)
		return;
	else {
		*(U32_T *)((U32_T)&SYSCON->UREG0 + (eUreg * 4)) = wValue;
	}
}
/** \brief Read User Registers
 * 
 *  \param[in] eUreg: UREG0~2
 *  \return value being read out
 */
U32_T syscon_ureg_read(user_reg_e eUreg)
{
	if(eUreg > USER_REG2)
		return 0;
	else
		return (*(U32_T *)((U32_T)&SYSCON->UREG0 + (eUreg * 4)));
}

/** \brief SWD Lock: valid SWDIOs are locked, thus can not be configufed to other AF
 * 
 *  \param[in]  none
 *  \return  none
 */
void syscon_swd_lock(void)
{
	SYSCON->DBGCR = SWD_LOCK;
}

/** \brief SWD Unlock: valid SWDIOs can be configured to other AF
			Once changed, swd connection would be lost.
 * 
 *  \param[in]  none
 *  \return  none
 */
void syscon_swd_unlock(void)
{
	SYSCON->DBGCR = SWD_UNLOCK;
}


/** \brief configure wakeup source 
 *  \param[in] eWkupSrc: wakup source \ref syscon_wksrc_e
 *  \param[in] eNewState: ENABLE/DSIABLE
 *  \return  none
 */
void pm_wakupsrc_cmd(syscon_wksrc_e eWkupSrc, functional_status_e eNewState)
{
	SYSCON->WKCR &= ~(0x1 << eWkupSrc) | (eNewState << eWkupSrc);
}



/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/