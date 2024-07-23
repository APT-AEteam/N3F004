/***********************************************************************//** 
 * \file  bt.h
 * \brief BT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-01 <td>V2_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BT_H
#define _BT_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"

/// \struct csp_bt_t
/// \brief BT reg description      
 typedef struct
 {
   __IOM U32_T	RSSR;				//0x0000	Reset/Start Control
   __IOM U32_T	CR;					//0x0004	General Control
   __IOM U32_T	PSCR;				//0x0008	Prescaler
   __IOM U32_T	PRDR; 			//0x000C	Period
   __IOM U32_T	CMP;				//0x0010	Compare
   __IOM U32_T	CNT;				//0x0014	Counter
   __IOM U32_T	EVTRG;			//0x0018	Event Trigger
   __IOM U32_T  RCR;				//0x001C   Continuous count control
   __IOM U32_T	_RSVD;  		    //0x0020	Reserved
   __IOM U32_T  EVSWF;     	    //0x0024    Software force Event Trigger
   __IM  U32_T	RISR;   			//0x0028    Raw Interrupt 
   __IOM U32_T	IMCR;     		//0x002C    Interrupt Mask Control
   __IM  U32_T	MISR;  			//0x0030	Mask Interrupt Status
   __OM  U32_T	ICR;    				//0x0034	Interrupt clear
   
} csp_bt_t; 

/*****************************************************************************
************************** bt Function defined *******************************
******************************************************************************/
#define BT_RESET_VALUE  (0x00000000)

/******************************************************************************
* RSSR : BT Start/Stop/Reset Control Register
******************************************************************************/
#define	BT_CTRL_POS			(0)
#define	BT_CTRL_MSK			(0x01ul << BT_CTRL_POS)
#define  BT_START					(0x01ul << BT_CTRL_POS)
#define  BT_STOP					(0x00ul << BT_CTRL_POS)
//typedef enum
//{
//	BT_STOP			= 0,	
//	BT_START		
//}bt_ctrl_e;

#define	BT_SRR_POS				(12)
#define	BT_SRR_MSK			(0x0Ful << BT_SRR_POS)
#define	BT_SRR_EN				(0x05ul<< BT_SRR_POS)

/******************************************************************************
* CR : BT Control Register
******************************************************************************/
#define BT_CLK_POS				(0)
#define BT_CLK_MSK				(0x01ul << BT_CLK_POS)
typedef enum
{
	BTCLK_DIS		= 0,
    BTCLK_EN           
}bt_clk_e;

#define BT_UPDATA_POS		(2)
#define BT_UPDATA_MSK		(0x01ul << BT_UPDATA_POS)
#define BT_UPDATE_EN			(0x01ul)

#define	BT_DBG_EN				(0x01ul << 1)

#define BT_SHDW_POS			(3)
#define BT_SHDW_MSK			(0x01ul << BT_SHDW_POS)
typedef enum
{
	BT_SHDOW		= 0,
    BT_IMMEDIATE          
}bt_shdw_e;

#define BT_OPM_POS			(4)
#define BT_OPM_MSK			(0x01ul << BT_OPM_POS)
typedef enum
{
	BT_CONTINUOUS	= 0,
    BT_ONCE          
}bt_opm_e;

#define BT_EXTCKM_POS		(5)
#define BT_EXTCKM_MSK		(0x01ul << BT_EXTCKM_POS)
typedef enum
{
	BT_PCLKDIV		= 0,
    BT_SYNCTRG            
}bt_extckm_e;


#define BT_SYNC_POS(n)		(8 + n)    //n=0/1/2
#define BT_SYNC_MSK(n)		(0x01ul << BT_SYNC_POS(n))
typedef enum
{
    BT_SYNC_DIS		= 0,    
	BT_SYNC_EN       
}bt_sync_e;

#define BT_AREARM_POS(n)	(18 +  (2 * n))
#define BT_AREARM_MSK(n)	(0x03ul << BT_AREARM_POS(n))
typedef enum
{
	BT_AREARM_AUTO 	= 1,
    BT_AREARM_SYNC            
}bt_arearm_e;

#define BT_SYNCCMD_POS	(15)
#define BT_SYNCCMD_MSK	(0x01ul << BT_SYNCCMD_POS)
typedef enum
{
	BT_SYNCMD_UPD 	= 0,
    BT_SYNCMD_RST           
}bt_synccmd_e;

#define BT_CNTRLD_POS		(16)
#define BT_CNTRLD_MSK		(0x01ul << BT_CNTRLD_POS)
typedef enum
{
	BT_CNTRLD_EN 	= 0,
    BT_CNTRLD_DIS           
}bt_cntrld_e;

#define BT_OSTMD_POS(n)	(24 + n)  //n=bt_sync_in_e
#define BT_OSTMD_MSK(n)	(0x01ul << BT_OSTMD_POS(n))
typedef enum
{
	BT_OSTMDX_CONTINUE = 0,
    BT_OSTMDX_ONCE            
}bt_ostmd_e;

#define BT_REARM_POS(n)	(28 + n) //n=bt_sync_in_e
#define BT_REARM_MSK(n) 	(0x01 << BT_REARM_POS(n))
#define BT_REARM_EN			(0x01ul)
typedef enum{
	BT_SYNCEN0		= 0,
	BT_SYNCEN1,
	BT_SYNCEN2		
}bt_sync_in_e;

/******************************************************************************
* PSCR : BT PCLK Frequency Division Register
******************************************************************************/
#define	BT_PSCR_POS			(0)
#define	BT_PSCR_MSK			(0xFFFFul << BT_PSCR_POS)

/******************************************************************************
* PRDR : BT Period Register
******************************************************************************/
//#define	BT_PRDR_POS			(0)
//#define	BT_PRDR_MSK			(0xFFFFul << BT_PRDR_POS)

#define BT_CMPLINK_POS	(31)
#define BT_CMPLINK_MSK	(0x01ul << BT_CMPLINK_POS)
#define BT_CMPLINK				(0x01ul)

/******************************************************************************
* CMP : BT CMP Register
******************************************************************************/
//#define	BT_CMP_POS			(0)
//#define	BT_CMP_MSK			(0xFFFFul << BT_CMP_POS)

/******************************************************************************
* CNT : BT CNT Register
******************************************************************************/
//#define	BT_CNT_POS				(0)
//#define	BT_CNT_MSK			(0xFFFFul << BT_CNT_POS)

/******************************************************************************
* EVTRG : BT EVTRG Register
******************************************************************************/
#define	BT_TRG0_SEL_POS		(0)
#define	BT_TRG0_SEL_MSK		(0x0Ful << BT_TRG0_SEL_POS)

#define	BT_TRG1_SEL_POS		(4)
#define	BT_TRG1_SEL_MSK		(0x0Ful << BT_TRG1_SEL_POS)
typedef enum
{
	BT_EVTRG_DIS	= 0,  	       
	BT_EVTRG_PEND,	
	BT_EVTRG_CMP,	
	BT_EVTRG_OVF         
}bt_evtrg_src_e;

#define	BT_TRG0_PRD_POS		(8)
#define	BT_TRG0_PRD_MSK 	(0x0Ful << BT_TRG0_PRD_POS)

#define	BT_TRG1_PRD_POS		(12)
#define	BT_TRG1_PRD_MSK	(0x0Ful << BT_TRG1_PRD_POS)

#define	BT_TRGOE0_POS			(20)
#define	BT_TRGOE0_MSK			(0x01ul << BT_TRGOE0_POS)

#define	BT_TRGOE1_POS			(21)
#define	BT_TRGOE1_MSK			(0x01ul << BT_TRGOE1_POS)
typedef enum
{
	BT_TRGOE_DIS	= 0,  	       
	BT_TRGOE_EN
}bt_trgoe_e;

//#define	BT_TRG0_CNT_POS		(22)
//#define	BT_TRG0_CNT_MSK 	(0x0Ful << BT_TRG0_CNT_POS)
//
//#define	BT_TRG1_CNT_POS		(26)
//#define	BT_TRG1_CNT_MSK	(0x0Ful << BT_TRG1_CNT_POS)

/******************************************************************************
* RCR 
******************************************************************************/
#define BT_RMODE_POS			(0)
#define BT_RMODE_MSK			(0x01ul<<BT_RMODE_POS)
typedef enum
{
	BT_RMODE_DIS = 0,
	BT_RMODE_EN
}bt_rmode_e;

#define BT_CROSSMD_POS		(1)
#define BT_CROSSMD_MSK		(0x01ul<<BT_CROSSMD_POS)
typedef enum
{
	BT_CROSSMD_DIS = 0,
	BT_CROSSMD_EN
}bt_crossmd_e;

#define BT_RPRD_POS				(8)
#define BT_RPRD_MSK				(0x0Ful<<BT_RPRD_POS)

#define BT_RCNT_POS				(16)
#define BT_RCNT_MSK				(0x07ul<<BT_RCNT_POS)

/******************************************************************************
* CEVTRG : BT EVSEF Register
******************************************************************************/
#define BT_EVSWF0_EN				(0x01ul)
#define BT_EVSWF1_EN				(0x02ul)

/******************************************************************************
* RISR/MISR/IMSCR/ICR : BT Interrupt Mask/Status Register
******************************************************************************/
typedef enum
{
	BT_PEND   	 =	(0x01ul << 0), 
	BT_CMP		 =	(0x01ul << 1),     
	BT_OVF     	 =	(0x01ul << 2),  
	BT_EVTRG   =	(0x01ul << 3),
	BT_RPEND   =	(0x01ul << 4),
	BT_INT_ALL    	 =	(0x1Ful << 0)
}bt_int_e;

/******************************************************************************
* function interface
******************************************************************************/

/** \brief bt deinit 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_deinit(csp_bt_t *ptBtBase);

/** \brief bt start
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_start(csp_bt_t *ptBtBase);

/** \brief bt stop
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_stop(csp_bt_t *ptBtBase);

/** \brief bt stop , BT_OUT stop level - high
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_stop_high(csp_bt_t *ptBtBase);

/** \brief bt stop , BT_OUT stop level - low
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_stop_low(csp_bt_t *ptBtBase);

/** \brief bt soft reset
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_soft_reset(csp_bt_t *ptBtBase);

/** \brief bt config 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eClkEn:  clk of bt enable / disable control \ref bt_clk_e
 *  \param[in] HwPscrData: PSCR data setting 
 *  \param[in] eShwdStp: shadow of start bit  enable/disable control  \ref bt_shdw_e
 *  \param[in] eOpm: bt work mode select : once or continus  \ref bt_opm_e
 *  \param[in] eExtCkm: clk of bt select  \ref bt_extckm_e
 * 			   
 *  \return none
 */ 
void bt_configure(csp_bt_t *ptBtBase, bt_clk_e eClkEn, U16_T hwPscrData , bt_shdw_e eShwdStp, bt_opm_e eOpm,bt_extckm_e eExtCkm);

/** \brief bt sync1 config - START
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eSync0: sync0  enable/disable  control , sync0 trigger bt start \ref bt_sync_e
 *  \param[in] eSyncCmd: bt sync result control  \ref bt_synccmd_e
 *  \param[in] eOstMd0: bt sync0 mode control  \ref bt_ostmd_e
 *  \param[in] eAreArm0: bt sync0 auto control  \ref bt_arearm_e
 *  \param[in] eCntRld: bt hardware auto reload cnt enable/disable control \ref bt_cntrld_e
 * 			   
 *  \return none
 */ 
void bt_sync0_configure(csp_bt_t *ptBtBase , bt_sync_e eSync0 ,bt_synccmd_e eSyncCmd, bt_ostmd_e eOstMd0 ,bt_arearm_e eAreArm0 ,bt_cntrld_e eCntRld);

/** \brief bt sync1 config - COUNTER +1
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eSync1: sync1 enable/disable  control , sync1 trigger bt start \ref bt_sync_e
 *  \param[in] eSyncCmd: bt sync result control  \ref bt_synccmd_e
 *  \param[in] eOstMd1: bt sync1 mode control  \ref bt_ostmd_e
 *  \param[in] eAreArm1: btsync1 auto rearm control  \ref bt_arearm_e
 *  \param[in] eCntRld: bt hardware auto reload cnt enable/disable control \ref bt_cntrld_e
 * 			   
 *  \return none
 */ 
void bt_sync1_configure(csp_bt_t *ptBtBase , bt_sync_e eSync1 ,bt_synccmd_e eSyncCmd, bt_ostmd_e eOstMd1 ,bt_arearm_e eAreArm1 ,bt_cntrld_e eCntRld);

/** \brief bt sync2 config - STOP
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eSync2: sync2 enable/disable  control , sync2 trigger bt start \ref bt_sync_e
 *  \param[in] eSyncCmd: bt sync result control  \ref bt_synccmd_e
 *  \param[in] eOstMd2: bt sync2 mode control  \ref bt_ostmd_e
 *  \param[in] eCntRld: bt hardware auto reload cnt enable/disable control \ref bt_cntrld_e
 * 			   
 *  \return none
 */ 
void bt_sync2_configure(csp_bt_t *ptBtBase, bt_sync_e eSync2 ,bt_synccmd_e eSyncCmd, bt_ostmd_e eOstMd2 ,bt_cntrld_e eCntRld);

/** \brief bt Period & Compare set
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] hwPrdrData:   PRDR data
 *  \param[in] hwCmpData:  CMP data
 * 			   
 *  \return none
 */ 
void bt_period_cmp_write(csp_bt_t *ptBtBase, U16_T hwPrdrData, U16_T hwCmpData);

/** \brief bt  counter set
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] hwPrdrData:   PRDR data
 *  \param[in] hwCmpData:  CMP data
 * 			   
 *  \return none
 */ 
void bt_cnt_write(csp_bt_t *ptBtBase,U16_T hwCntData);

/** \brief  read bt  prdr val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return prdr val
 */ 
U16_T bt_prdr_write(csp_bt_t *ptBtBase);

/** \brief  read bt  cmp val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return cmp val
 */ 
U16_T bt_cmp_read(csp_bt_t *ptBtBase);

/** \brief  read bt  cnt val
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return cnt val
 */ 
U16_T bt_cnt_read(csp_bt_t *ptBtBase);

/** \brief  bt  trigger event 0 init
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eEvTrg0:  trigger source of TRGEV0 event  select control \ref bt_evtrg_src_e
 *  \param[in] eTrgOe0: TRGOUT0 enable/disable control \ref  bt_trgoe_e
 * 			   
 *  \return none
 */ 
void bt_trgev0_configure(csp_bt_t *ptBtBase,bt_evtrg_src_e eEvTrg0,bt_trgoe_e eTrgOe0 );

/** \brief  bt  trigger event 1 init
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eEvTrg1:  trigger source of TRGEV1 event  select control \ref bt_evtrg_src_e
 *  \param[in] eTrgOe1: TRGOUT1 enable/disable control \ref  bt_trgoe_e
 * 			   
 *  \return none
 */ 
void bt_trgev1_configure(csp_bt_t *ptBtBase,bt_evtrg_src_e eEvTrg1,bt_trgoe_e eTrgOe1 );


/** \brief  bt  trigger_event0 counter period configure to trigger stop 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] byPrd:  TRGEV0 counter period ,  trigger BT STOP
 * 			   
 *  \return none
 */ 
 void  bt_trgev0_stop_configure(csp_bt_t *ptBtBase, U8_T byPrd);
 
  /** \brief  bt  trigger_event1 counter period configure to trigger stop 
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] byPrd:  TRGEV1 counter period ,  trigger BT STOP
 * 			   
 *  \return none
 */ 
 void  bt_trgev1_stop_configure(csp_bt_t *ptBtBase, U8_T byPrd);
  
  /** \brief  bt RPRD configure
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eRmode: continous period  counter control :enable or disable \ref bt_rmode_e
 *  \param[in] eCrossMd: continous period counter cross enable or disable  \ref  bt_crossmd_e
 *  \param[in] byRprd: continous period counter val ,range: 0~0x7			   
 * 
 *  \return none
 */ 
 void  bt_rprd_configure(csp_bt_t *ptBtBase, bt_rmode_e eRmode, bt_crossmd_e  eCrossMd, U8_T byRprd);
 
  /** \brief  read R_Counter
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return R_Counter
 */ 
 U8_T  bt_rcounter(csp_bt_t *ptBtBase);
 
 /** \brief  bt  trigger_event0 soft trigger
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_trgev0_soft_trigger(csp_bt_t *ptBtBase);

/** \brief  bt  trigger_event1 soft trigger
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 * 			   
 *  \return none
 */ 
void bt_trgev1_soft_trigger(csp_bt_t *ptBtBase);

/** \brief  bt  interrupt enable
 * 
 *  \param[in] ptBtBase: pointer of bt register structure
 *  \param[in] eImcr:  interrupt select \ref bt_int_e
 * 			   
 *  \return none
 */ 
void bt_int_enable(csp_bt_t *ptBtBase,bt_int_e eImcr);

#endif
