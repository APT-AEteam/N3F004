/***********************************************************************//** 
 * \file  adc.c
 * \brief ADC function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-17 <td>V1_3_0  <td>GQQ  <td>initial
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


/** \brief adc deinit 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 * 			   
 *  \return none
 */ 
void adc_deinit(csp_adc_t *ptAdcBase)
{
	ptAdcBase->DCR	=	ADC_DCR_RST;                  	/**< DCR  reset value  */
	ptAdcBase->CR      = ADC_CR_RST;
	ptAdcBase->CSR	=   ADC_RST;                  	/**< CSR  reset value  */
	ptAdcBase->IER 	=	ADC_RST;                	/**< IER  reset value  */
	ptAdcBase->IDR 	=	ADC_RST;              		/**< IDR  reset value  */
	ptAdcBase->SEQ[0]=	ADC_SEQ_RST;             		/**< SEQ0  reset value */
	ptAdcBase->SEQ[1]=	ADC_SEQ_RST;             		/**< SEQ1  reset value */
	ptAdcBase->SEQ[2]=	ADC_SEQ_RST;             		/**< SEQ2  reset value */
	ptAdcBase->SEQ[3]=	ADC_SEQ_RST;             		/**< SEQ3  reset value */
	ptAdcBase->SEQ[4]=	ADC_SEQ_RST;             		/**< SEQ4  reset value */
	ptAdcBase->SEQ[5]=	ADC_SEQ_RST;             		/**< SEQ5  reset value */
	ptAdcBase->SEQ[6]=	ADC_SEQ_RST;             		/**< SEQ6  reset value */
	ptAdcBase->SEQ[7]=	ADC_SEQ_RST;             		/**< SEQ7  reset value */
	ptAdcBase->PRI = ADC_RST;
	ptAdcBase->TDL0 = ADC_RST;
	ptAdcBase->TDL1 = ADC_RST;
	ptAdcBase->SYNCR = ADC_RST;
	ptAdcBase->EVTRG = ADC_RST;
	ptAdcBase->DRMASK= ADC_RST;
}  

/** \brief adc control :enable ,disable ,start /stop, swrst, swtrg
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eCmd:  ADC control command: enable ,disable ,start /stop, swrst, swtrg \ref adc_control_e
 * 			   
 *  \return none
 */ 
void adc_control(csp_adc_t *ptAdcBase, adc_control_e eCmd )
{
	ptAdcBase->CR |= eCmd;					
}

/** \brief adc int enable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return none
 */ 
void adc_int_enable( csp_adc_t *ptAdcBase, adc_int_e eInt)
{
	ptAdcBase->CSR	= eInt;
	ptAdcBase->IER  |= eInt;						//SET
} 
/** \brief adc int disable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return none
 */ 
void adc_int_disable( csp_adc_t *ptAdcBase, adc_int_e eInt)
{
	ptAdcBase->IDR  |= eInt;						
	ptAdcBase->CSR	= eInt;
} 

/** \brief read adc interrupt enable status
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return ENABLE or DISABLE
 */ 
uint8_t adc_read_inten_status(csp_adc_t *ptAdcBase,adc_int_e eInt)
{
	bool  bStatus = DISABLE;
	
    if ((ptAdcBase->IMR&eInt) == eInt)								
	{
	    bStatus = ENABLE;
	} 
    return bStatus;
}
 
/** \brief read adc clk/debug enable/disable control
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eAdcClk:  adc clk or debug select \ref adc_clk_e
 *  \param[in] bState:  State to be set	
 *		   
 *  \return none
 */  
void adc_clk_debug_configure(csp_adc_t *ptAdcBase, adc_clk_e eAdcClk , bool bState)
{
	if (bState != DISABLE)
	{
		ptAdcBase->ECR  |= eAdcClk;						//ENABLE
		while(!(ptAdcBase->PMSR&eAdcClk));
	}
	else
	{
		ptAdcBase->DCR  |= eAdcClk;						//DISABLE
		while(ptAdcBase->PMSR&eAdcClk);
	}
}

/** \brief adc software reset
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */   
void adc_software_reset(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |=ADC_SWRST;
}

/** \brief adc analog module enable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_enable(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |=ADC_ADCEN;				//ADC12 ENABLE
	while(!(ptAdcBase->SR &ADC_ADCEN));
}

/** \brief adc analog module disable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_disable(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |=ADC_ADCDIS;				//ADC12 DISABLE
	while(!(ptAdcBase->SR &ADC_ADCDIS));
}

/** \brief  wait for adc ready singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_ready_wait(csp_adc_t *ptAdcBase)  
{
	while(!(ptAdcBase->SR&ADC_READY));   				
}

/** \brief  wait for adc end of convert (EOC) singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_eoc_wait(csp_adc_t *ptAdcBase)  
{
	while(!(ptAdcBase->SR&ADC_EOC));   				
}

/** \brief  wait for adc SEQx end of convert  singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byCh:  SEQ No.  range :0~0x7
 *		   
 *  \return none
 */ 
void adc_seqend_wait(csp_adc_t *ptAdcBase,U8_T byCh)
{
	while(!(ptAdcBase->SR & ADC_SEQ_MSK(byCh)));			
}  

/** \brief  read one channel  of DRx
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byCh:  DR No.  range :0~0x7
 *		   
 *  \return none
 */ 
U16_T adc_data_output(csp_adc_t *ptAdcBase, U8_T byCh )
{
	return(ptAdcBase->DR[byCh]);
} 
/** \brief  adc configure
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eMode:  adc run mode select \ref adc_runmode_e
 *  \param[in] byPriorty:  adc convert priority  . range : 0~7
 * 						 -note : when seq number < byPriorty, seqs have higher priority, but these chs do NOTconvert ,until  the coresponding trigger events occur,
 * 									in another word ,these chs do NOT in convertion seq
 *	 \param[in] byShr:  adc sample & hold period , range : 3~255
 *  \param[in] PreDiv:  pclk division ,range :0~31
 * 						-PreDiv=0,  fadc= pclk
 * 						-PreDiv!=0,  fadc= pclk/(2*PreDiv)
 *  \param[in] byNbrch:  the max channel of convert seq ,range :0~7
 * 					note: number of chs in convertion seq = byNbrch- byPriorty+1
 *	   
 *  \return none
 */ 
void  adc_mode_configure(csp_adc_t *ptAdcBase, adc_runmode_e  eMode  , U8_T byPriorty, U8_T byShr , U8_T PreDiv , U8_T byNbrch ) 
{
	ptAdcBase->MR=PreDiv|((byNbrch)<<ADC_NBRCH_POS);
	if(eMode==ADC_MODE_ONESHOT)
	{
		ptAdcBase->MR&=~(ADC_MODE_CONTINUE<<ADC_MODE_POS);								//one short mode
		while(ptAdcBase->SR&ADC_CTCVS);							
	}
	else if(eMode==ADC_MODE_CONTINUE)
	{
		ptAdcBase->MR|=ADC_MODE_CONTINUE<<ADC_MODE_POS;								//Continuous mode
		while(!(ptAdcBase->SR&ADC_CTCVS));							
	}
	adc_enable(ptAdcBase);									//ptAdcBase enable

	ptAdcBase->CR|=ADC_ACCURACY_12BIT;
	
	//ptAdcBase->CR|=ADC_VREF_VREFP_VSS<<ADC_VREF_POS;
	ptAdcBase->PRI=byPriorty;
	ptAdcBase->SHR=byShr;								//adc Sampling & Holding cycles
} 


/** \brief  adc reference voltage configure
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eVref:  voltage reference select \ref adc_vref_e
 *  \param[in] eInvrefLvl:  internal voltage reference level \ref adc_intvref_lvl_e
 *	   
 *  \return none
 */ 
void adc_vref_configure(csp_adc_t *ptAdcBase,  adc_vref_e eVref, adc_intvref_lvl_e eInvrefLvl )
{	
	ptAdcBase->CR=(ptAdcBase->CR&(~(ADC_VREF_MSK|ADC_INTVREF_OUTEN_MSK|ADC_INTVREF_LVL_MSK)))|(eVref<<ADC_VREF_POS)
									|(ADC_INTVREF_OUT_DIS<<ADC_INTVREF_OUTEN_POS)|(eInvrefLvl<<ADC_INTVREF_LVL_POS);
}

/** \brief  adc seqx  analog input configure
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eAinSel:  adc analog input channel  \ref adc_ainsel_e
 *  \param[in] bySeq:  seq no. range :0~7
 *	   
 *  \return none
 */ 
void adc_ain_configure(csp_adc_t *ptAdcBase, adc_ainsel_e eAinSel , U8_T bySeq)
{
	for(U8_T i=0;i<7;i++)
	{
		ptAdcBase->SEQ[i] &=~(0x01<<7);
	}
	ptAdcBase->SEQ[bySeq] &= 0;
	ptAdcBase->SEQ[bySeq] |= (eAinSel<<ADC_AIN_POS) ;
}

/** \brief set adc sync 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eSyncSrc: ADC sync source select  \ref adc_sync_source_e
 *  \param[in] bySeq:  seqx used to sync ADC. range :0~7
 *  \param[in] eSyncIn: sync(0~5) of adc input channels  \ref adc_sync_in_e
 *  \param[in] eOstMd: adc sync mode, continuous/once \ref adc_ostmd_e
 *  \param[in] byDelay: adc input delay, delay timer =  (trg_delay+1)*4 PCLK
 *  \return none
 */
void adc_set_sync(csp_adc_t *ptAdcBase, adc_sync_source_e eSyncSrc, U8_T bySeq, adc_sync_in_e eSyncIn, adc_ostmd_e eOstMd, uint8_t byDelay)
{
	//set sync delay
    if(eSyncIn < ADC_SYNCEN3)		
	{
		ptAdcBase->TDL0 = (ptAdcBase->TDL0 & ~(0xFFul << (eSyncIn * 8))) | byDelay;
	}
	else// if(eSyncIn <= ADC_SYNCEN5)
	{
		ptAdcBase->TDL1 = (ptAdcBase->TDL1 & ~(0xFFul << ((eSyncIn - 3)  * 8))) | byDelay;
	}
	//set sync source and mode
	ptAdcBase->SYNCR =(ptAdcBase->SYNCR & (~ADC_OSTMD_MSK(eSyncIn))) | ((0x01ul << eSyncIn) | (eOstMd << (8 + eSyncIn)));
	ptAdcBase->SEQ[bySeq] =(ptAdcBase->SEQ[bySeq] & (~ADC_SYNCSRC_MSK))|(eSyncSrc<<ADC_SYNCSRC_POS);
	
}

/** \brief rearm adc sync
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eSyncIn: adc sync evtrg input channel(0~5)
 *  \return none
 */
void adc_sync_rearm(csp_adc_t *ptAdcBase, adc_sync_in_e eSyncIn)
{
	ptAdcBase->SYNCR |= (0x1 << (eSyncIn + ADC_REARM_POS(eSyncIn)));
}

/** \brief set adc evtrg output
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \param[in] eTrgSrc: adc evtrg source(0~23) 
 *  \param[in] byPeriod: The event triggers the count 
 *  \return none
 */
void  adc_set_evtrg(csp_adc_t *ptAdcBase, adc_evtrg_src_e eTrgSrc, adc_evtrg_out_e eTrgOut)
{	
	ptAdcBase->EVTRG = ptAdcBase->EVTRG & (~(ADC_TRGSRC_MSK(eTrgOut))) | eTrgSrc<<ADC_TRGSRC_POS(eTrgOut);
}

/** \brief  adc evtrg enable
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \return none
 */
void  adc_evtrg_enable(csp_adc_t *ptAdcBase,adc_evtrg_out_e eTrgOut)
{	
	ptAdcBase->EVTRG |=  ADC_TRGOE_MSK(eTrgOut) ;
}

/** \brief  adc evtrg disable
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \return none
 */
void  adc_evtrg_disable(csp_adc_t *ptAdcBase,adc_evtrg_out_e eTrgOut)
{	
	ptAdcBase->EVTRG &=  ~ADC_TRGOE_MSK(eTrgOut);
}