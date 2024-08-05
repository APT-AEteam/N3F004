/***********************************************************************//** 
 * \file  etcb.h
 * \brief  ETCB description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ETCB_H
#define _ETCB_H

/* Includes ------------------------------------------------------------------*/
#include "n3f004_top.h"
#include "types_local.h"

#define ET_RESET_VALUE  (0x00000000)


/******************************************************************************
* ETCB Register Structure
******************************************************************************/
typedef struct
 {
    __IOM U32_T  EN;            	/* 0x00 ETCB Enable                            */
    __IOM U32_T  SWTRG;          /* 0x04 ETCB Software Trigger Generator         */
     __IOM U32_T  CH0CON0;       /* 0x08 ETCB Channel 0 Control Register 0       */
     __IOM U32_T  CH0CON1;       /* 0x0C ETCB Channel 0 Control Register 1       */
     __IOM U32_T  CH1CON0;       /* 0x10 ETCB Channel 1 Control Register 0       */
     __IOM U32_T  CH1CON1;       /* 0x14 ETCB Channel 1 Control Register 1       */
     __IOM U32_T  CH2CON0;       /* 0x18 ETCB Channel 2 Control Register 0       */
     __IOM U32_T  CH2CON1;       /* 0x1C ETCB Channel 2 Control Register 1       */
	 __IOM U32_T  _RSVD[4];
     __IOM U32_T  CH3CON;       /*  0x30 ETCB Channel 3 Control Register        */
	 __IOM U32_T  CH4CON;       /*  0x34 ETCB Channel 3 Control Register        */
	 __IOM U32_T  CH5CON;       /*  0x38 ETCB Channel 3 Control Register        */

 } csp_etcb_t; 
 
 
#define ETCB_CH(val)	val
typedef enum
{
    ET_CH3 = 0,
	ET_CH4 = 1,
	ET_CH5 = 2,
}etcb_chx_e;

/******************************************************************************
*SWTRG : ETCB Software Trigger Register
******************************************************************************/
#define ETCB_SWTRG_CH(n) (0x1<<n)


#define	ETCB_CH_EN_POS			(0U)	//CH(0->5) enable/disable		
#define	ETCB_CH_EN_MSK			(0x01ul << ETCB_CH_EN_POS)
#define	ETCB_CH_TRG_MODE_POS	(1U)		//CH(0->7) trigger mode select
#define	ETCB_CH_TRG_MODE_MSK	(0x01ul << ETCB_CH_TRG_MODE_POS)
typedef enum
{
    TRG_HW = (0X00<<1),
	TRG_SW = (0X01<<1),
}etcb_ch_trg_mode_e;

/******************************************************************************
*CH0CON0 : ETCB Channel0 Control Register0
******************************************************************************/
//source 0
#define	ETCB_CH0_SRC0_EN_POS		(0U)	//CH0 trigger source0 enable/disable		
#define	ETCB_CH0_SRC0_EN_MSK		(0x01ul << ETCB_CH0_SRC0_EN_POS)
#define	ETCB_CH0_TRG_SRC0_POS		(1U)	//CH0 trigger source0 select
#define	ETCB_CH0_TRG_SRC0_MSK		(0xFFul << ETCB_CH0_TRG_SRC0_POS)
#define	ETCB_CH0_TRG_SRC0(val)		(((val) & 0xFFul) << ETCB_CH0_TRG_SRC0_POS)
//source 1
#define	ETCB_CH0_SRC1_EN_POS		(10U)	//CH0 trigger source1 enable/disable		
#define	ETCB_CH0_SRC1_EN_MSK		(0x01ul << ETCB_CH0_SRC1_EN_POS)
#define	ETCB_CH0_TRG_SRC1_POS		(11U)	//CH0 trigger source1 select
#define	ETCB_CH0_TRG_SRC1_MSK		(0xFFul << ETCB_CH0_TRG_SRC1_POS)
#define	ETCB_CH0_TRG_SRC1(val)		(((val) & 0xFFul) << ETCB_CH0_TRG_SRC1_POS)
//source 2
#define	ETCB_CH0_SRC2_EN_POS		(20U)	//CH0 trigger source2 enable/disable		
#define	ETCB_CH0_SRC2_EN_MSK		(0x01ul << ETCB_CH0_SRC2_EN_POS)
#define	ETCB_CH0_TRG_SRC2_POS		(21U)	//CH0 trigger source2 select
#define	ETCB_CH0_TRG_SRC2_MSK		(0xFFul << ETCB_CH0_TRG_SRC2_POS)
#define	ETCB_CH0_TRG_SRC2(val)		(((val) & 0xFFul) << ETCB_CH0_TRG_SRC2_POS)

typedef enum
{
    ET_SRC0 = 0,
	ET_SRC1 = 1,
	ET_SRC2 = 2,
}etcb_ch0_src_e;

/******************************************************************************
*CH0CON1 : ETCB Channel0 Control Register1
******************************************************************************/
#define	ETCB_CH0_TRG_DST_POS		(26U)	//CH0 trigger destination select
#define	ETCB_CH0_TRG_DST_MSK		(0x3Ful << ETCB_CH0_TRG_DST_POS)
#define	ETCB_CH0_TRG_DST(val)		(((val) & 0x7Ful) << ETCB_CH0_TRG_DST_POS)



/******************************************************************************
*CHxCON0 : ETCB Channel x Control Register0,(x = 1->2)
******************************************************************************/
//destination 0
#define	ETCB_CH1_2_DST0_EN_POS		(0U)	//CH1_2 trigger destination0 enable/disable		
#define	ETCB_CH1_2_DST0_EN_MSK		(0x01ul << ETCB_CH1_2_DST0_EN_POS)
#define	ETCB_CH1_2_TRG_DST0_POS		(1U)	//CH1_2trigger destination0 select
#define	ETCB_CH1_2_TRG_DST0_MSK		(0xFFul << ETCB_CH1_2_TRG_DST0_POS)
#define	ETCB_CH1_2_TRG_DST0(val)	(((val) & 0xFFul) << ETCB_CH1_2_TRG_DST0_POS)
//destination 1
#define	ETCB_CH1_2_DST1_EN_POS		(10U)	//CH1_2 trigger destination1 enable/disable		
#define	ETCB_CH1_2_DST1_EN_MSK		(0x01ul << ETCB_CH1_2_DST1_EN_POS)
#define	ETCB_CH1_2_TRG_DST1_POS		(11U)	//CH1_2 trigger destination1 select
#define	ETCB_CH1_2_TRG_DST1_MSK		(0xFFul << ETCB_CH1_2_TRG_DST1_POS)
#define	ETCB_CH1_2_TRG_DST1(val)	(((val) & 0xFFul) << ETCB_CH1_2_TRG_DST1_POS)
//destination 2
#define	ETCB_CH1_2_DST2_EN_POS		(20U)	//CH1_2 trigger destination2 enable/disable		
#define	ETCB_CH1_2_DST2_EN_MSK		(0x01ul << ETCB_CH1_2_DST2_EN_POS)
#define	ETCB_CH1_2_TRG_DST2_POS		(21U)	//CH1_2 trigger destination2 select
#define	ETCB_CH1_2_TRG_DST2_MSK		(0xFFul << ETCB_CH1_2_TRG_DST2_POS)
#define	ETCB_CH1_2_TRG_DST2(val)	(((val) & 0xFFul) << ETCB_CH1_2_TRG_DST2_POS)

typedef enum
{
    ET_DST0 = 0,
	ET_DST1 = 1,
	ET_DST2 = 2,
}etcb_ch1_des_e;

/******************************************************************************
*CHxCON1 : ETCB Channel x Control Register1,(x = 0->2)
******************************************************************************/
#define	ETCB_CH1_2_TRG_SRC_POS		(26U)	//CH1_2 trigger source select
#define	ETCB_CH1_2_TRG_SRC_MSK		(0x3Ful << ETCB_CH1_2_TRG_SRC_POS)
#define	ETCB_CH1_2_TRG_SRC(val)		(((val) & 0x7Ful) << ETCB_CH1_2_TRG_SRC_POS)


/******************************************************************************
*CHxCON : ETCB Channel x Control Register,(x = 3->31)
******************************************************************************/
//source 
#define	ETCB_CHX_TRG_SRC_POS		(12U)	//CHx(3->31) trigger source select
#define	ETCB_CHX_TRG_SRC_MSK		(0x7Ful << ETCB_CHX_TRG_SRC_POS)
#define	ETCB_CHX_TRG_SRC(val)		(((val) & 0x7Ful) << ETCB_CHX_TRG_SRC_POS)

//destination
#define	ETCB_CHX_TRG_DST_POS		(24U)	//CHx(3->31) trigger destination select
#define	ETCB_CHX_TRG_DST_MSK		(0xFFul << ETCB_CHX_TRG_DST_POS)
#define	ETCB_CHX_TRG_DST(val)		(((val) & 0xFFul) << ETCB_CHX_TRG_DST_POS)

//dma
#define	ETCB_CHX_DMA_EN_POS			(2U)	//CHx(20->31) trigger destination select
#define	ETCB_CHX_DMA_EN_MSK			(0x01ul << ETCB_CHX_DMA_EN_POS)
#define	ETCB_CHX_DMA_EN				(0x01ul)



/******************************************************************************
ETCB Functions Declaration 
******************************************************************************/
/** \brief Deinitializes ETCB registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */ 
void etcb_deinit(void);

/** \brief Enable ETCB
 * 
 *  \param[in] none
 *  \return none
 */ 
void etcb_enable(void);

/** \brief Disable ETCB
 * 
 *  \param[in] none
 *  \return none
 */ 

void etcb_disable(void);

/** \brief tigger ETCB manually, usually for debugging
 * 
 *  \param[in] byChNum: ETCB channel number
 *  \return none
 */ 
void etcb_swtrg(U8_T byChNum);

/** \brief Select a trigger source for CH0
 *  \param[in] eCh0SrcNum: SRC0~3, CH0 can have 3 trigger sources at the same time \ref etcb_ch0_src_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \param[in] eNewState: src ENABLE/DISABLE
 *  \return none
 */  
void etcb_ch0_src_sel(etcb_ch0_src_e eCh0SrcNum,etcb_trgsrc_e eTrgSrc, functional_status_e eNewState);

/** \brief  Select the trigger destination/trigger mode for CH0 and enable/dissable CH0
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void etcb_ch0_configure(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgdes_e eTrgDes);

/** \brief Select a trigger destination for CH1 and enable/disable the corresponding channel
 *  \param[in] eCh1DesNum: ETCB_DST0~DST2 \ref etcb_ch1_des_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \return none
 */  
void etcb_ch1_dst_sel(etcb_ch1_des_e eCh1DesNum,etcb_trgdes_e eTrgDes,functional_status_e eNewState);

/** \brief Select the trigger srouce/trigger mode for CH1 and enable/dissable the corresponding channel
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \return none
 */   
void etcb_ch1_configure(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc);

/** \brief Select a trigger destination for CH2 and enable/disable the corresponding channel
 *  \param[in] eCh1DesNum: ET_DST0~ET_DST2 \ref etcb_ch1_des_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \return none
 */  
void etcb_ch2_dst_sel(etcb_ch1_des_e eCh1DesNum,etcb_trgdes_e eTrgDes, functional_status_e eNewState);

/** \brief Select the trigger srouce/trigger mode for CH2 and enable/dissable the corresponding channel
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \return none
 */   
void etcb_ch2_configure(functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc);

/** \brief Select the trigger srouce、trigger destination、trigger mode and enable/dissable the corresponding channel
 *  \param[in] byChNum: channel number > 3
 *  \param[in] eNewState: ENABLE/DISABLE
 * 	\param[in] eTrgMode: trigger mode \ref etcb_ch_trg_mode_e
 *  \param[in] eTrgSrc: trigger source \ref etcb_trgsrc_e
 *  \param[in] eTrgDes: trigger destination \ref etcb_trgdes_e
 *  \return none
 */  
void etcb_chx_configure(etcb_chx_e eChNum,functional_status_e eNewState,etcb_ch_trg_mode_e eTrgMode,etcb_trgsrc_e eTrgSrc,etcb_trgdes_e eTrgDes);

#endif   /**< ETCB_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/