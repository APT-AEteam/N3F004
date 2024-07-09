/***********************************************************************//** 
 * \file  etcb.c
 * \brief  ETCB driver
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


/** \brief Deinitializes ETCB registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */ 
void ET_DeInit(void)
{
	ETCB->EN 			= ET_RESET_VALUE;
	ETCB->SWTRG 		= ET_RESET_VALUE;
	ETCB->CH0CON0 		= ET_RESET_VALUE;
	ETCB->CH0CON1	  	= ET_RESET_VALUE;
	ETCB->CH1CON0 		= ET_RESET_VALUE;
	ETCB->CH1CON1 		= ET_RESET_VALUE;
	ETCB->CH2CON0 		= ET_RESET_VALUE;
	ETCB->CH2CON1 		= ET_RESET_VALUE;
	ETCB->CH3CON	 	= ET_RESET_VALUE;
	ETCB->CH4CON	 	= ET_RESET_VALUE;
	ETCB->CH5CON	 	= ET_RESET_VALUE;
}

/** \brief Enable ETCB
 * 
 *  \param[in] none
 *  \return none
 */ 
void ET_ENABLE(void)
{
	ETCB->EN	=	ENABLE;
}

/** \brief Disable ETCB
 * 
 *  \param[in] none
 *  \return none
 */ 

void ET_DISABLE(void)
{
	ETCB->EN	=	DISABLE;
}

/** \brief tigger ETCB manually, usually for debugging
 * 
 *  \param[in] eChSwTrg: ET_SWTRG_CH0 ~5 \ref etcb_ch_swtrg_e
 *  \return none
 */ 
void ET_SWTRG_CMD(etcb_ch_swtrg_e eChSwTrg)
{

	ETCB->SWTRG  |= eChSwTrg;						
	
}

/** \brief Select a trigger source for CH0
 *  \param[in] eCh0SrcNum: SRC0~3, CH0 can have 3 trigger sources at the same time \ref etcb_ch0_src_e
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \return none
 */  
void ET_CH0_SRCSEL(etcb_ch0_src_e eCh0SrcNum,functional_status_e eNewState,etcb_trgsrc_e eTrgSrc)
{
	switch(eCh0SrcNum)
	{
		case (SRC0): ETCB->CH0CON0 = ETCB->CH0CON0 & ~(ETCB_CH0_SRC0_EN_MSK) & ~(ETCB_CH0_TRG_SRC0_MSK) 
									| (eTrgSrc<<ETCB_CH0_TRG_SRC0_POS) | (eNewState << ETCB_CH0_SRC0_EN_POS);
					break;
		case (SRC1): ETCB->CH0CON0 = ETCB->CH0CON0 & ~(ETCB_CH0_SRC1_EN_MSK) & ~(ETCB_CH0_TRG_SRC1_MSK) 
									| (eTrgSrc<<ETCB_CH0_TRG_SRC1_POS) | (eNewState << ETCB_CH0_SRC1_EN_POS);
					break;
		case (SRC2): ETCB->CH0CON0 = ETCB->CH0CON0 & ~(ETCB_CH0_SRC2_EN_MSK) & ~(ETCB_CH0_TRG_SRC2_MSK) 
									| (eTrgSrc<<ETCB_CH0_TRG_SRC2_POS) | (eNewState << ETCB_CH0_SRC2_EN_POS);
					break;
		default: break;
	}
	
}


/** \brief  Select the trigger destination/trigger mode for CH0 and enable/dissable CH0
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void ET_CH0_CONTROL(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgdes_e eTrgDes)
{

	ETCB->CH0CON1 = ETCB->CH0CON1 & ~(ETCB_CH0_TRG_DST_MSK) & ~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CH_EN_MSK)
					| (eTrgDes << ETCB_CH0_TRG_DST_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eNewState << ETCB_CH_EN_POS);
	
}


/** \brief Select a trigger destination for CH1 and enable/disable the corresponding channel
 *  \param[in] eCh1DesNum: ET_DST0~ET_DST2 \ref etcb_ch1_des_e
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void ET_CH1_SRCSEL(etcb_ch1_des_e eCh1DesNum,functional_status_e eNewState,etcb_trgdes_e eTrgDes)
{
	switch(eCh1DesNum)
	{
		case (ET_DST0): ETCB->CH1CON0 = ETCB->CH1CON0 & ~(ETCB_CH1_2_DST0_EN_MSK) & ~(ETCB_CH1_2_TRG_DST0_MSK) 
									| (eNewState<<ETCB_CH1_2_DST0_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST0_POS);
					break;
		case (ET_DST1): ETCB->CH1CON0 = ETCB->CH1CON0 & ~(ETCB_CH1_2_DST1_EN_MSK) & ~(ETCB_CH1_2_TRG_DST1_MSK) 
									| (eNewState<<ETCB_CH1_2_DST1_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST1_POS);
					break;
		case (ET_DST2): ETCB->CH1CON0 = ETCB->CH1CON0 & ~(ETCB_CH1_2_DST2_EN_MSK) & ~(ETCB_CH1_2_TRG_DST2_MSK) 
									| (eNewState<<ETCB_CH1_2_DST2_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST2_POS);
					break;
		default: break;
	}	
	
}

/** \brief Select the trigger srouce/trigger mode for CH1 and enable/dissable the corresponding channel
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \return none
 */   
void ET_CH1_CONTROL(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc)
{
	ETCB->CH1CON1 = ETCB->CH1CON1 & ~(ETCB_CH1_2_TRG_SRC_MSK) & ~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CH_EN_MSK)
					| (eTrgSrc << ETCB_CH1_2_TRG_SRC_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eNewState << ETCB_CH_EN_POS);

	
}


/** \brief Select a trigger destination for CH2 and enable/disable the corresponding channel
 *  \param[in] eCh1DesNum: ET_DST0~ET_DST2 \ref etcb_ch1_des_e
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void ET_CH2_SRCSEL(etcb_ch1_des_e eCh1DesNum,functional_status_e eNewState,etcb_trgdes_e eTrgDes)
{
	switch(eCh1DesNum)
	{
		case (ET_DST0): ETCB->CH2CON0 = ETCB->CH2CON0 & ~(ETCB_CH1_2_DST0_EN_MSK) & ~(ETCB_CH1_2_TRG_DST0_MSK) 
									| (eNewState<<ETCB_CH1_2_DST0_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST0_POS);
					break;
		case (ET_DST1): ETCB->CH2CON0 = ETCB->CH2CON0 & ~(ETCB_CH1_2_DST1_EN_MSK) & ~(ETCB_CH1_2_TRG_DST1_MSK) 
									| (eNewState<<ETCB_CH1_2_DST1_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST1_POS);
					break;
		case (ET_DST2): ETCB->CH2CON0 = ETCB->CH2CON0 & ~(ETCB_CH1_2_DST2_EN_MSK) & ~(ETCB_CH1_2_TRG_DST2_MSK) 
									| (eNewState<<ETCB_CH1_2_DST2_EN_POS) | (eTrgDes << ETCB_CH1_2_TRG_DST2_POS);
					break;
		default: break;
	}	
	
}

/** \brief Select the trigger srouce/trigger mode for CH2 and enable/dissable the corresponding channel
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \return none
 */   
void ET_CH2_CONTROL(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc)
{
	ETCB->CH2CON1 = ETCB->CH2CON1 & ~(ETCB_CH1_2_TRG_SRC_MSK) & ~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CH_EN_MSK)
					| (eTrgSrc << ETCB_CH1_2_TRG_SRC_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eNewState << ETCB_CH_EN_POS);

	
}



/** \brief Select the trigger srouce、trigger destination、trigger mode and enable/dissable the corresponding channel
 *  \param[in] byChNum: channel number > 3 \ref etcb_chx_e
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void ET_CHx_CONTROL(etcb_chx_e eChNum,functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc,etcb_trgdes_e eTrgDes)
{
	
	switch(eChNum)
	{
		case (ET_CH3): ETCB ->CH3CON = ETCB ->CH3CON & ~(ETCB_CH_EN_MSK) &~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CHX_TRG_SRC_MSK) & ~(ETCB_CHX_TRG_DST_MSK)
					   | (eNewState << ETCB_CH_EN_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eTrgSrc << ETCB_CHX_TRG_SRC_POS) | (eTrgDes << ETCB_CHX_TRG_DST_POS)	; 
					   break;
		case (ET_CH4): ETCB ->CH4CON = ETCB ->CH4CON & ~(ETCB_CH_EN_MSK) &~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CHX_TRG_SRC_MSK) & ~(ETCB_CHX_TRG_DST_MSK)
					   | (eNewState << ETCB_CH_EN_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eTrgSrc << ETCB_CHX_TRG_SRC_POS) | (eTrgDes << ETCB_CHX_TRG_DST_POS)	;
					   break;
		case (ET_CH5): ETCB ->CH5CON = ETCB ->CH5CON & ~(ETCB_CH_EN_MSK) &~(ETCB_CH_TRG_MODE_MSK) & ~(ETCB_CHX_TRG_SRC_MSK) & ~(ETCB_CHX_TRG_DST_MSK)
					   | (eNewState << ETCB_CH_EN_POS) | (eTrgMode << ETCB_CH_TRG_MODE_POS) | (eTrgSrc << ETCB_CHX_TRG_SRC_POS) | (eTrgDes << ETCB_CHX_TRG_DST_POS)	;
					   break;
		default: break;
					
	}
}	
	
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/