/***********************************************************************//** 
 * \file  gpta.h
 * \brief  headfile for GPTA in csp level
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-5 <td>V3_0_0 <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _GPTA_H
#define _GPTA_H

#include "types_local.h"

typedef struct
{
   __IOM  U32_T	CEDR;  		      //0x0000	  Clock control & ID
   __IOM  U32_T	RSSR;		     	  //0x0004	  Start & Stop Ctrl
   __IOM  U32_T	PSCR;		      	  //0x0008	  Clock prescaler
   __IOM  U32_T	CR;  		    	  //0x000C	  Control register
   __IOM  U32_T	SYNCR;		      //0x0010	  Synchronization control reg
   __IOM  U32_T	_RSVD0[4];       //0x0014~0x0020 
   __IOM  U32_T	PRDR;   	           //0x0024	  Period reg
   __IOM  U32_T	_RSVD1;     	   //0x0028	  
   __IOM  U32_T	CMPA;  		       //0x002C	  Compare Value A
   __IOM  U32_T	CMPB;   	    	   //0x0030	  Compare Value B
   __IOM  U32_T	_RSVD2[2];		//0x0034~0x0038
   __IOM  U32_T	CMPLDR;	        //0x003C	  Cmp reg load control
   __IOM  U32_T	CNT;      	     	    //0x0040	  Counter reg
   __IOM  U32_T	AQLDR; 		       //0x0044	  AQ reg load control
   __IOM  U32_T	AQCR1;             //0x0048	  Action qualify of ch-1
   __IM     U32_T	_RSVD3[29];	   //0x004C ~0x00BC
   __IOM  U32_T    EVTRG;               //0x00C0    Event trigger setting
   __IOM  U32_T    _RSVD4[2];        //0x00C4 ~0x00C8
   __IOM  U32_T	EVSWF;		       //0x00CC    event counter software trigger control register
   __IM     U32_T     RISR;                 //0x00D0    Interrupt RISR
   __IM     U32_T     MISR;                //0x00D4    Interrupt MISR
   __IOM  U32_T     IMCR;                //0x00D8    Interrupt IMCR
   __OM   U32_T     ICR;                   //0x00DC    Interrupt clear
   __IOM  U32_T     REGLK;                //0x00E0  register link 
   __IM     U32_T	_RSVD5;	   			//0x00E4
   __IOM  U32_T     PORT;                //0x00E8  write ptotect
   __IM     U32_T	_RSVD6[464];   //0x00EC ~0x0828
   __IM     U32_T 	CMPAA;	          //0x082C	  cmpa active reg for capture mode
   __IM     U32_T 	CMPBA;	          //0x0830	  cmpb active reg for capture mode
} csp_gpta_t;


/******************************************************************************
************************** GPTA Registers Definition ****************************
******************************************************************************/
#define GPT_RESET_VALUE  (0x00000000)
/******************************************************************************
* GPTA Regiser
******************************************************************************/
typedef enum 
{	GPTA_CHA	= 0,
	GPTA_CHB,
}gpta_chtype_e;

typedef enum
{
    GPT_DISABLE = 0,
	GPT_ENABLE = 1,
}gpta_state_e;

/******************************************************************************
* IO enum
******************************************************************************/
typedef enum
{
	GPT_CHA_PB01    =	0,  
	GPT_CHA_PA09   	=	1,      
	GPT_CHA_PA010   =	2, 
	GPT_CHB_PA010	=	3,  
	GPT_CHB_PA011   =	4,      
	GPT_CHB_PB00    =	5,
	GPT_CHB_PB01    =	6,
}GPT_IOSET_TypeDef; 

/******************************************************************************
* CEDR : Clock control & ID
******************************************************************************/
#define GPTA_CLKEN_POS         	  	 (0)
#define GPTA_CLKEN_MSK          		 (0x1ul << GPTA_CLKEN_POS)
#define GPTA_DBGEN_POS		    	 (1)
#define GPTA_DBGEN_MSK         		 (0x1ul << GPTA_DBGEN_POS)
#define GPTA_CSS_POS		    			 (3)
#define GPTA_CSS_MSK		   		 	 (0x1ul << GPTA_CSS_POS)
typedef enum{
    GPT_CLKSRC_PCLK = 0,
	GPT_CLKSRC_TRGUSR3 ,
}gpt_clksrc_e;

#define GPTA_STOPMD_POS		     (6)
#define GPTA_STOPMD_MSK		     (0x1ul << GPTA_STOPMD_POS)
typedef enum{
	GPTA_STOP_SHDW = 0,
	GPTA_STOP_IMMEDIATE
}gpta_stopmode_e;

#define GPTA_FLTPRS_POS		       (8)
#define GPTA_FLTPRS_MSK		       (0xfful << GPTA_FLTPRS_POS)

/******************************************************************************
* RSSR : Start & Stop Ctrl
******************************************************************************/
#define GPTA_START_POS		     (0)
#define GPTA_START			            (0x1ul  << GPTA_START_POS)
#define GPTA_RESET_POS	        	 (12)
#define GPTA_RESET_MSK	         (0xful  << GPTA_RESET_POS)
#define GPTA_RESET				        (0x5ul  << GPTA_RESET_POS)

/******************************************************************************
* CR : Control register
******************************************************************************/

#define GPTA_STARTMODE_POS	     (2)
#define GPTA_STARTMODE_MSK         (0x1ul << GPTA_STARTMODE_POS)
typedef enum{
	GPTA_SW_START = 0,
	GPTA_SYNC_START
}gpta_startmode_e;
#define GPTA_STPST_POS	         (3)
#define GPTA_STPST_MSK           (0x1 << GPTA_STPST_POS)
typedef enum
{
	GPTA_STPST_HZ = 0,
	GPTA_STPST_LOW
}gpta_stpst_e;
#define GPTA_PRDLD_POS	         (4)
#define GPTA_PRDLD_MSK		     (0x3ul << GPTA_PRDLD_POS)
typedef enum 
{
	GPTA_LDPRDR_PEND = 0,
	GPTA_LDPRDR_LOAD_SYNC,
	GPTA_LDPRDR_PEND_LOAD_SYNC,
	GPTA_LDPRDR_IMMD
}gpta_ldprdr_e;
#define GPTA_RUNMODE_POS	     (6)
#define GPTA_RUNMODE_MSK	     (0x1 << GPTA_RUNMODE_POS)
typedef enum
{
	GPTA_RUNMODE_CONT = 0,
	GPTA_RUNMODE_ONCE,
}gpta_runmode_e;
#define GPTA_PHSEN_POS		     (7)
#define GPTA_PHSEN_MSK		     (0x1 << GPTA_PHSEN_POS)
#define GPTA_CAPLD_POS	         (8)
#define GPTA_CAPLD_MSK	         (0x1 << GPTA_CAPLD_POS)
#define GPTA_BURST_POS           (9)
#define GPTA_BURST_MSK           (1ul << GPTA_BURST_POS)
#define GPTA_FLT_INIT_POS        (10)
#define GPTA_FLT_INIT_MSK        (1ul << GPTA_FLT_INIT_POS)
#define GPTA_CKS_POS					(10)
#define GPTA_CKS_MSK				(0x1ul << GPTA_CKS_POS)
typedef enum{
	GPTA_CK_PCLK =0,
	GPTA_CK_PCLK_DIV2
}gpta_cks_e;

#define GPTA_CGFLT_POS	         (13)
#define GPTA_CGFLT_MSK	         (0x7 << GPTA_CGFLT_POS)
typedef enum 
{
	GPTA_FLT_BP = 0,
	GPTA_FLT_2,
	GPTA_FLT_4,
	GPTA_FLT_6,
	GPTA_FLT_8,
	GPTA_FLT_16,
	GPTA_FLT_32,
	GPTA_FLT_64
}gpta_cgflt_e;
#define GPTA_PSCLD_POS	         (16)
#define GPTA_PSCLD_MSK	         (0x3 << GPTA_PSCLD_POS)
typedef enum{
	GPTA_PSCLD_ZRO =0,
	GPTA_PSCLD_PRD,
	GPTA_PSCLD_ZRO_PRD,
	GPTA_PSCLD_DIS
}gpta_pscld_e;

#define GPTA_CAPMD_SEL_POS       (19)
#define GPTA_CAPMD_SEL_MSK       (1ul << GPTA_CAPMD_SEL_POS)
typedef enum
{
	GPTA_MERGE_CAP = 0,
	GPTA_SEPARATE_CAP
}gpta_capmdsel_e;

#define GPTA_CAPREARM_POS        (20)
#define GPTA_CAPREARM       			(1ul << GPTA_CAPREARM_POS)
#define GPTA_CAPMD_POS           (21)
#define GPTA_CAPMD_MSK	         (0x1 << GPTA_CAPMD_POS)
typedef enum{
	GPTA_CAPMD_CONTINOUS =0,
	GPTA_CAPMD_ONCE
}gpta_capmd_e;

#define GPTA_STOPWRAP_POS	     (22)
#define GPTA_STOPWRAP_MSK	     (0x3 << GPTA_STOPWRAP_POS)
#define GPTA_CMPA_RST_POS	     (24)
#define GPTA_CMPA_RST_MSK	     (0x1 << GPTA_CMPA_RST_POS) 	
#define GPTA_CMPB_RST_POS	     (25)
#define GPTA_CMPB_RST_MSK	     (0x1 << GPTA_CMPB_RST_POS) 
#define GPTA_CMPAA_RST_POS	     (26)
#define GPTA_CMPAA_RST_MSK	     (0x1 << GPTA_CMPAA_RST_POS) 
#define GPTA_CMPBA_RST_POS	     (27)
#define GPTA_CMPBA_RST_MSK	     (0x1 << GPTA_CMPBA_RST_POS) 
typedef enum{
	GPTA_LDRST_DIS =0,
	GPTA_LDRST_EN
}gpta_ldxrst_e;

#define GPTA_CAP_WAVE_POS		(30)
#define GPTA_CAP_WAVE_MSK		(0x3 <<GPTA_CAP_WAVE_POS)
typedef enum{
	GPTA_BCAP_ACAP =0,
	GPTA_BWAV_ACAP,
	GPTA_BCAP_AWAV,
	GPTA_BWAV_AWAV,
}gpta_wave_e;

/******************************************************************************
* SYNCR : Synchronization control reg
******************************************************************************/
#define GPTA_SYNC_POS(ch)	     (ch)
#define GPTA_SYNC_MSK(ch)	     (0x1 <<(GPTA_SYNC_POS(ch)))
typedef enum
{
	GPTA_SYNCIN_0	= 0,			
	GPTA_SYNCIN_1,						
	GPTA_SYNCIN_2,						
	GPTA_SYNCIN_3,			
	GPTA_SYNCIN_4,
//	GPTA_SYNCIN_5,
//    GPTA_SYNCIN_6		
}gpta_syncin_e;
#define GPTA_OSTMD_POS(ch)	     (ch+8)
#define GPTA_OSTMD_MSK(ch)	     (0x1 <<(GPTA_OSTMD_POS(ch)))
typedef enum 
{
	GPTA_OSTMD_CONT = 0,
	GPTA_OSTMD_ONCE
}gpta_syncmd_e;

#define GPTA_REARM_POS(ch)	     (ch+15)
#define GPTA_REARM_MSK(ch)	     (0x1 <<(GPTA_REARM_POS(ch)))
#define GPTA_REARM_EN	     			  0x1 


#define GPTA_TRGO0SEL_POS	    	 (24)
#define GPTA_TRGO0SEL_MSK	     (0x7 << GPTA_TRGO0SEL_POS)
#define GPTA_TRGO1SEL_POS	     	(27)
#define GPTA_TRGO1SEL_MSK	     (0x7 << GPTA_TRGO1SEL_POS)
typedef enum
{
	GPTA_TRGSRC_SYNC0	= 0,			
	GPTA_TRGSRC_SYNC1,						
	GPTA_TRGSRC_SYNC2,						
	GPTA_TRGSRC_SYNC3,			
	GPTA_TRGSRC_SYNC4,
//	GPTA_SYNCIN_5,
//    GPTA_SYNCIN_6		
}gpta_trgsel_e;

#define GPTA_AREARM_POS		     (30)
#define GPTA_AREARM_MSK		     (0x3 << GPTA_AREARM_POS)
typedef enum
{
	GPTA_AREARM_DIS = 0,
	GPTA_AREARM_ZRO,
	GPTA_AREARM_PRD,
	GPTA_AREARM_ZRO_PRD
}gpta_arearm_e;


/******************************************************************************
* CMPA/B : Compare Value A/B
******************************************************************************/
#define GPTA_CMPDATA_MSK	     (0xffff)	
#define GPTA_CMPDATA_OVWRT       (0x1 << 31)
typedef enum
{
    GPTA_CMPA=0,
	GPTA_CMPB,
}gpta_comp_e;

/******************************************************************************
* CMPLDR : Cmp reg load control
******************************************************************************/
#define GPTA_CMPA_LD_POS	     (0)
#define GPTA_CMPA_LD_MSK         (0x1 << GPTA_CMPA_LD_POS)
#define GPTA_CMPB_LD_POS	     (1)
#define GPTA_CMPB_LD_MSK         (0x1 << GPTA_CMPB_LD_POS)
typedef enum 
{
	GPTA_CMPLD_SHD = 0,
	GPTA_CMPLD_IMM
}gpta_ldmd_e;
#define GPTA_CMPA_LDTIME_POS     (4)
#define GPTA_CMPA_LDTIME_MSK     (0x7 << GPTA_CMPA_LDTIME_POS)
#define GPTA_CMPB_LDTIME_POS     (7)
#define GPTA_CMPB_LDTIME_MSK     (0x7 << GPTA_CMPB_LDTIME_POS)
typedef enum
{
	GPTA_LDCMP_DIS= 0,
	GPTA_LDCMP_ZRO,
	GPTA_LDCMP_PRD,
	GPTA_LDCMP_EXI_SYNC = 4,
}gpta_shdwldmd_e;
#define GPTA_SHDWAFULL 	         (0x1 <<20)
#define GPTA_SHDWBFULL 	         (0x1 <<21)

/******************************************************************************
* AQLDR : AQ reg load control
******************************************************************************/
#define GPTA_AQCR1_SHDWEN_POS	 (0)
#define GPTA_AQCR1_SHDWEN_MSK	 (0x1 << GPTA_AQCR1_SHDWEN_POS)
typedef enum{
	GPTA_LDAQ_IMM =0,
	GPTA_LDAQ_SHD
}gpta_ldaqcr_e;

#define GPTA_LDAMD_POS		     (2)
#define GPTA_LDAMD_MSK		     (0x7 << GPTA_LDAMD_POS)
typedef enum{
	GPTA_SHDLD_DIS  =0,
	GPTA_SHDLD_ZRO =1,
	GPTA_SHDLD_PRD = 2 ,
	GPTA_SHDLD_EXI_SYNC = 4
}gpta_shadowld_e;

/******************************************************************************
* AQCR1 : Action qualify of ch-1
******************************************************************************/
#define GPTA_ACT_ZRO_POS	     (0)
#define GPTA_ACT_ZRO_MSK	     (0x3 << GPTA_ACT_ZRO_POS)
#define GPTA_ACT_PRD_POS	     (2)
#define GPTA_ACT_PRD_MSK	     (0x3 << GPTA_ACT_PRD_POS)
#define GPTA_ACT_C1U_POS	     (4)
#define GPTA_ACT_C1U_MSK	     (0x3 << GPTA_ACT_C1U_POS)
#define GPTA_ACT_C2U_POS	     (8)
#define GPTA_ACT_C2U_MSK	     (0x3 << GPTA_ACT_C2U_POS)
typedef enum{
	GPTA_ACT_DIS =0,
	GPTA_ACT_LOW,
	GPTA_ACT_HIGH,
	GPTA_ACT_REVERSE
}gpta_act_e;

#define GPTA_C1SEL_POS	         (20)
#define GPTA_C1SEL_MSK	         (0x3 << GPTA_C1SEL_POS)
#define GPTA_C2SEL_POS	         (22)
#define GPTA_C2SEL_MSK	         (0x3 << GPTA_C2SEL_POS)
typedef enum{
	GPTA_CXSEL_CMPA=0,
	GPTA_CXSEL_CMPB,
}gpta_cxsel_e;


/******************************************************************************
* EVTRG : Event trigger setting
******************************************************************************/
#define GPTA_TRG0SEL_POS	0
#define GPTA_TRG0SEL_MSK  (0xf << GPTA_TRG0SEL_POS)
#define GPTA_TRG1SEL_POS	4
#define GPTA_TRG1SEL_MSK  (0xf << GPTA_TRG1SEL_POS)
typedef enum
{
	GPTA_TRG01_DIS = 0,
	GPTA_TRG01_ZRO,
	GPTA_TRG01_PRD,
	GPTA_TRG01_ZRO_PRD,
	GPTA_TRG01_CMPA_R,
	GPTA_TRG01_CMPB_R=6,
	GPTA_TRG01_SYNC = 0xc
}gpta_trgsrc_e;

#define GPTA_TRG0OE_POS 	20
#define GPTA_TRG0OE_MSK  (0x1 << GPTA_TRG0OE_POS)
#define GPTA_TRG1OE_POS	 21
#define GPTA_TRG1OE_MSK  (0x1 << GPTA_TRG1OE_POS)
/******************************************************************************
* EVSWF 
******************************************************************************/
#define GPTA_SWF_EV(n)	        (0x1 << n)

/******************************************************************************
* REGLK 
******************************************************************************/
#define GPTA_PRDR_POS	          (0)
#define GPTA_PRDR_MSK           (0xf << GPTA_PRDR_POS)
#define GPTA_CMPA_POS	          (4)
#define GPTA_CMPA_MSK          (0xf << GPTA_CMPA_POS)
#define GPTA_CMPB_POS	          (8)
#define GPTA_CMPB_MSK          (0xf << GPTA_CMPB_POS)
#define GPTA_RSSR_POS	          (24)
#define GPTA_RSSR_MSK            (0xf << GPTA_RSSR_POS)	
typedef enum{
	GPTA_REGLK_DIS,
	GPTA_REGLK_EPT,
	GPTA_REGLK_GPT
}gpt_reglk_e;

/******************************************************************************
* Interrupt Related
******************************************************************************/
typedef enum
{
	GPTA_INT_TRGEV0 = 0x1 << 0,
	GPTA_INT_TRGEV1 = 0x1 << 1,
	GPTA_INT_CAPLD0 = 0x1 << 4,
	GPTA_INT_CAPLD1 = 0x1 << 5,
	GPTA_INT_CAPLD2 = 0x1 << 6,
	GPTA_INT_CAPLD3 = 0x1 << 7,
	GPTA_INT_CAU    = 0x1 << 8,
	GPTA_INT_CBU    = 0x1 << 10,
	GPTA_INT_PEND   = 0x1 << 16,	
	GPTA_INT_ALL    = 0x1FFFF
}gpta_int_e;

#define GPTA_INT_EV(n)		    (0x1 << n)
#define GPTA_INT_CAPLD(n)	    (0x1 << (n+4))

/******************************************************************************
* REGPROT
******************************************************************************/
#define GPTA_REGPROT	        (0xa55a << 16 | 0xc73a)

/*****************************************************************************
 * gpt functions declaration
 ****************************************************************************/

/** \brief deinit gpt registers 
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 			   
 *  \return none
 */ 
void gpt_deinit(csp_gpta_t *ptGptaBase);
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
void gpt_configure(csp_gpta_t *ptGptaBase,gpta_state_e eClkEn,gpt_clksrc_e eClkSrc,gpta_stopmode_e eStopMd,U16_T hwPscr);

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
						gpta_state_e eBurstEn,gpta_cks_e eCks, gpta_cgflt_e eCgflt,gpta_pscld_e ePscld,gpta_wave_e eWaveType);

/** \brief gpt wave load control
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eLdAqcr: gpt shadow of aqcr regiaster  control \ref gpta_ldaqcr_e
 *  \param[in] eShdLd: shadow mode, active aqcr load from active register  \ref gpta_shadowld_e
 * 			   
 *  \return none
 */ 
void gpt_waveload_configure(csp_gpta_t *ptGptaBase,gpta_ldaqcr_e eLdAqcr ,gpta_shadowld_e eShdLd);

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
void gpt_waveout_configure(csp_gpta_t *ptGptaBase,gpta_cxsel_e eC1Sel,gpta_cxsel_e eC2Sel, gpta_act_e eZeroAct, gpta_act_e ePrdAct,gpta_act_e eC1uAct,gpta_act_e eC2uAct);

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
												U8_T byStopWrap,gpta_wave_e eWave );
												
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
void gpt_sync_configure(csp_gpta_t *ptGptaBase,gpta_syncin_e eSyncIn,gpta_syncmd_e eOstMd,gpta_trgsel_e eTrg0Sel,gpta_trgsel_e eTrg1Sel,gpta_arearm_e eArearm);

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
void gpt_evtrg_configure(csp_gpta_t *ptGptaBase,gpta_trgsrc_e eTrgSel0,gpta_trgsrc_e eTrgSel1,gpta_state_e eTrg0O,gpta_state_e eTrg1O);

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
void gpt_cmpload_configure(csp_gpta_t *ptGptaBase,gpta_ldmd_e eCmpALd,gpta_ldmd_e eCmpBLd,gpta_shdwldmd_e eCmpAMd,gpta_shdwldmd_e eCmpBMd);

/** \brief GPT debug mode control
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eDebugEn:   Debug mode control : enable or disable \ref gpta_state_e
 * 
 *  \return none
 */ 
void gpt_debug_mode(csp_gpta_t *ptGptaBase,gpta_state_e eDebugEn);

/** \brief GPT start
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_start(csp_gpta_t *ptGptaBase);

/** \brief GPT stop
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_stop(csp_gpta_t *ptGptaBase);

/** \brief GPT software reset
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_software_reset(csp_gpta_t *ptGptaBase);

/** \brief GPT capture rearm
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
void gpt_cap_rearm(csp_gpta_t *ptGptaBase);

/** \brief GPT mode config
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eMode: gpta mode select : cmpa/cmpb capture or wave \ref gpta_wave_e
 * 
 *  \return none
 */ 
void gpt_mode_configure(csp_gpta_t *ptGptaBase,gpta_wave_e eMode);

/** \brief GPT soft reset at once sync mode
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eSync:  sync channel select \ref gpta_syncin_e
 * 
 *  \return none
 */ 
void gpt_rearm_write(csp_gpta_t *ptGptaBase, gpta_syncin_e eSync);

/** \brief GPT rearm read
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eSync:  sync channel select \ref gpta_syncin_e
 * 
 *  \return none
 */ 
U8_T gpt_rearm_read(csp_gpta_t *ptGptaBase,gpta_syncin_e eSync);

/** \brief GPT Period / Compare set
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] hwPrdr: prdr data setting ,range :0~0xffff
 *  \param[in] hwCmpa: cmpa data setting ,range :0~0xffff
 *  \param[in] hwCmpb: cmpb data setting ,range :0~0xffff
 * 
 *  \return none
 */ 
void gpt_period_cmp_write(csp_gpta_t *ptGptaBase,U16_T hwPrdr,U16_T hwCmpa,U16_T hwCmpb);

/** \brief read prdr val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_prdr_read(csp_gpta_t *ptGptaBase);

/** \brief read cmpa val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cmpa_read(csp_gpta_t *ptGptaBase);

/** \brief read cmpb val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cmpb_read(csp_gpta_t *ptGptaBase);

/** \brief read cnt val
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 * 
 *  \return none
 */ 
U16_T gpt_cnt_read(csp_gpta_t *ptGptaBase);

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
void gpt_reglink_configure(csp_gpta_t *ptGptaBase,gpt_reglk_e ePrdrLk, gpt_reglk_e eCmpaLk,gpt_reglk_e eCmpbLk,gpt_reglk_e eRssrLk);

/** \brief gpt interrupt ip level enable 
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eInt:  interrupt select \ref gpta_int_e
 * 
 *  \return none
 */ 
void gpt_int_enable(csp_gpta_t *ptGptaBase,gpta_int_e eInt);

/** \brief gpt interrupt disable
 * 
 *  \param[in] ptGptaBase: pointer of gpt register structure
 *  \param[in] eInt:  interrupt select \ref gpta_int_e
 * 
 *  \return none
 */ 
void gpt_int_disable(csp_gpta_t *ptGptaBase,gpta_int_e eInt);



#endif   /* CSP_GPTA_H */


