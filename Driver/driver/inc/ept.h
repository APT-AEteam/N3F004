/***********************************************************************//** 
 * \file  ept.h
 * \brief EPT description and  functions declare
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-2 <td>V1_3_0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _EPT_H
#define _EPT_H

#include "types_local.h"

/******************************************************************************
************************* EPWM Structure Definition ***********************
******************************************************************************/
/**
*******************************************************************como.************
@brief EPWM bits Structure
*******************************************************************************
*/


 typedef struct
 {
   __IOM  U32_T	CEDR;  		//0x0000	Clock control & ID
   __IOM  U32_T	RSSR;			//0x0004	Start & Stop Ctrl
   __IOM  U32_T	PSCR;			//0x0008	Clock prescaler
   __IOM  U32_T	CR;  			//0x000C	Control register
   __IOM  U32_T	SYNCR;		//0x0010	Synchronization control reg
   __IOM  U32_T	GLDCR;		//0x0014	Global load control reg
   __IOM  U32_T	GLDCFG; 	//0x0018	Global load config
   __IOM  U32_T	GLDCR2;	//0x001C	Global load control reg2
   __IOM  U32_T	_RSVD0;     //0x0020	
   __IOM  U32_T	PRDR;    		//0x0024	Period reg
   __IOM  U32_T	PHSR;     	//0x0028	Phase control reg
   __IOM  U32_T	CMPA;  		//0x002C	Compare Value A
   __IOM  U32_T	CMPB;   		//0x0030	Compare Value B
   __IOM  U32_T	CMPC;     	//0x0034	Compare Value C 
   __IOM  U32_T	CMPD;  		//0x0038	Compare Value D
   __IOM  U32_T	CMPLDR;	//0x003C	Cmp reg load control
   __IOM  U32_T	CNT;      		//0x0040	Counter reg
   __IOM  U32_T	AQLDR; 		//0x0044	AQ reg load control
   __IOM  U32_T	AQCR1;      //0x0048	Action qualify of pwm1
   __IOM  U32_T	AQCR2;    	//0x004C	Action qualify of pwm2
   __IOM  U32_T	AQCR3; 		//0x0050	Action qualify of pwm3
   __IOM  U32_T	AQCR4;  	//0x0054	Action qualify of pwm4
   __IOM  U32_T	_RSVD1;   	//0x0058	
   __IOM  U32_T	AQOSF; 		//0x005C	AQ output one-shot software forcing
   __IOM  U32_T	AQCSF;      //0x0060	AQ output conti-software forcing
   __IOM  U32_T	DBLDR;      //0x0064	Deadband control reg load control
   __IOM  U32_T	DBCR;      	//0x0068	Deadband control reg
   __IOM  U32_T	DPSCR;		//0x006C	Deadband clock prescaler
   __IOM  U32_T	DBDTR;		//0x0070	Deadband rising delay control
   __IOM  U32_T	DBDTF; 		//0x0074	Deadband falling delay control
   __IOM  U32_T	_RSVD2;  	//0x0078	
   __IOM  U32_T	EMSRC; 		//0x007C	EM source setting
   __IOM  U32_T	EMSRC2;	//0x0080	EM source setting
   __IOM  U32_T	EMPOL; 		//0x0084	EM polarity setting
   __IOM  U32_T	EMECR; 		//0x0088	EM enable control
   __IOM  U32_T	EMOSR;     //0x008C	EM trip out status setting
   __IOM  U32_T	_RSVD3;		//0x0090	Reserved
   __IOM  U32_T	EMSLSR;     //0x0094	Softlock status
   __IOM  U32_T	EMSLCLR;   //0x0098	Softlock clear
   __IOM  U32_T   EMHLSR;      //0x009C    Hardlock status
   __IOM  U32_T   EMHLCLR;    //0x00A0    Hardlock clear
   __IOM  U32_T   EMFRCR;      //0x00A4    Software forcing EM
   __IOM  U32_T   EMRISR;       //0x00A8    EM RISR
   __IOM  U32_T   EMMISR;     //0x00AC    EM MISR
   __IOM  U32_T   EMIMCR;     //0x00B0    EM masking enable
   __OM   U32_T   EMICR;         //0x00B4    EM pending clear
   __IOM  U32_T   _RSVD4;      //0x00B8    
   __IOM  U32_T   _RSVD5;      //0x00BC    
   __IOM  U32_T   EVTRG;       //0x00C0    Event trigger setting
   __IOM  U32_T  _RSVD6;      //0x00C4    
   __IOM  U32_T  _RSVD7;  	  //0x00C8    
   __IOM  U32_T	EVSWF;	  //0x00CC 
   __IM     U32_T  	RISR;        //0x00D0    Interrupt RISR
   __IM     U32_T  	MISR;       //0x00D4    Interrupt MISR
   __IOM  U32_T    IMCR;         //0x00D8    Interrupt IMCR
   __IOM  U32_T    ICR;             //0x00DC    Interrupt clear
   __IOM  U32_T   _RSVD8;		//0x00e0	                                     
   __IOM  U32_T   _RSVD9;		//0x00e4	                                        
   __IOM  U32_T   REGPROT;    //0x00e8 

} csp_ept_t;


/******************************************************************************
************************** EPT Registers Definition ****************************
******************************************************************************/

/******************************************************************************
* CEDR : ID and clock control register
******************************************************************************/
#define EPT_CLKEN_MSK           (1ul)
#define EPT_CLKEN           			(1ul)
#define EPT_DBGEN_POS			(1)
#define EPT_DBGEN_MSK 			(1ul << EPT_DBGEN_POS)
#define EPT_DBGEN           			(1ul << EPT_DBGEN_POS)
#define EPT_CKSRC_POS			(3)
#define EPT_CKSRC_MSK			(1ul << EPT_CKSRC_POS)
typedef enum{
	EPT_SELECT_PCLK = 0,
	EPT_SELECT_SYNCUSR3
}ept_clksel_e;


#define EPT_START_POS		(6)
#define EPT_START_MSK		(0x1ul << EPT_START_POS)
#define EPT_START_SHD       (0ul << EPT_START_POS)
#define EPT_START_IMM      (1ul << EPT_START_POS)
#define EPT_FLTPRS_POS		(8)
#define EPT_FLTPRS_MSK		(0xfful << EPT_FLTPRS_POS)


/******************************************************************************
* RSSR : start and stop control register
******************************************************************************/
#define EPT_START					(0x1ul)
#define EPT_CNTDIR_POS		(3)
#define EPT_CNTDIR_MSK	(0x1 << EPT_CNTDIR_POS)
#define EPT_RESET_POS		(12)
#define EPT_RESET_MSK		(0xf << EPT_RESET_POS)
#define EPT_RESET					(0x5ul << EPT_RESET_POS)

/******************************************************************************
* CR :  control register
******************************************************************************/
#define EPT_CNTMD_MSK	(3ul)
typedef enum{
	EPT_CNTMD_UP = 0,
	EPT_CNTMD_DN,
	EPT_CNTMD_UP_DN
}ept_cntmd_e;

#define EPT_STARTSRC_POS	(2)
#define EPT_STARTSRC_MSK (0x1ul << EPT_STARTSRC_POS)
typedef enum{
	EPT_SW_START = 0,
	EPT_SYNC_START
}ept_startsrc_e;

#define EPT_STPST_POS	(3)
#define EPT_STPST_MSK (0x1 << EPT_STPST_POS)
typedef enum{
	EPT_STPST_HZ = 0,
	EPT_STPST_LOW
}ept_stpst_e;


#define EPT_PRDLD_POS			(4)
#define EPT_PRDLD_MSK			(0x3ul << EPT_PRDLD_POS)
typedef enum {
	EPT_LDPRDR_PRD = 0,
	EPT_LDPRDR_LD_SYNC,
	EPT_LDPRDR_ZRO_LD_SYNC,
	EPT_LDPRDR_IMMD
}ept_ldprdr_e;

#define EPT_OPMD_POS	(6)
#define EPT_OPMD_MSK	(0x1 << EPT_OPMD_POS)
typedef enum{
	EPT_OPM_CONTINUE = 0,
	EPT_OPM_ONCE,
}ept_opmd_e;


#define EPT_PHSEN_POS       (7)
#define EPT_PHSEN_MSK		(0x1ul << EPT_PHSEN_POS)
typedef enum{
	EPT_PHSEN_DIS,
	EPT_PHSEN_EN
}ept_phsen_e;

#define EPT_CAPLD_POS	(8)
#define EPT_CAPLD_MSK  (1ul << EPT_CAPLD_POS)
typedef enum{
	EPT_CAPLD_DIS =0,
	EPT_CAPLD_EN
} ept_capld_e;

#define EPT_BURST_POS      (9)
#define EPT_BURST_MSK      (1ul << EPT_BURST_POS)
typedef enum {
	EPT_BURST_DIS =0,
	EPT_BURST_EN
}ept_burst_e;

#define EPT_FLT_INIT       (1ul << 10)
#define EPT_FLT_INIT_POS      (10)
#define EPT_FLT_INIT_MSK      (1ul << EPT_FLT_INIT_POS)

#define EPT_CGSRC_POS	(11)
#define EPT_CGSRC_MSK	(0x3 << EPT_CGSRC_POS)
typedef enum {
	EPT_CGSRC_SEL_CHAX = 0,
	EPT_CGSRC_SEL_CHBX,
	EPT_CGSRC_SEL_TIN,
	EPT_CGSRC_SEL_DIS,
}ept_cgsrc_sel_e;

typedef enum {
	EPT_CGSRC_CHAX = 0,
	EPT_CGSRC_CHBX,
	EPT_CGSRC_DIS,
}ept_cgsrc_e;

#define EPT_CGFLT_POS	(13)
#define EPT_CGFLT_MSK	(0x7 << EPT_CGFLT_POS)
typedef enum {
	EPT_CGFLT_BP = 0,
	EPT_CGFLT_2,
	EPT_CGFLT_4,
	EPT_CGFLT_6,
	EPT_CGFLT_8,
	EPT_CGFLT_16,
	EPT_CGFLT_32,
	EPT_CGFLT_64
}ept_cnflt_e;

#define EPT_PSCLD_POS		(16)
#define EPT_PSCLD_MSK		(0x3 << EPT_PSCLD_POS)
typedef enum {
	EPT_PSCLD_ZRO =0,
	EPT_PSCLD_PRD,
	EPT_PSCLD_ZRO_PRD,
	EPT_PSCLD_DIS
} ept_pscld_e;

#define EPT_MODE_POS		(18)
#define EPT_MODE_MSK    	(1ul << EPT_MODE_POS)
typedef enum{
	EPT_MODE_CAP = 0,
	EPT_MODE_OUT
}ept_md_e;

#define EPT_CAPREARM  		 (1ul << 19)

#define EPT_CAPMD_POS    	 (20)
#define EPT_CAPMD_MSK	 (0x1 << EPT_CAPMD_POS)
typedef enum {
	EPT_CAPMD_CONTINUE =0,
	EPT_CAPMD_ONCE
}ept_capmd_e;

#define EPT_STOPWRAP_POS	(21)
#define EPT_STOPWRAP_MSK	(0x3 << EPT_STOPWRAP_POS)

#define EPT_CMPA_RST_POS	(23)
#define EPT_CMPA_RST_MSK	(0x1 << EPT_CMPA_RST_POS) 	
#define EPT_CMPB_RST_POS	(24)
#define EPT_CMPB_RST_MSK	(0x1 << EPT_CMPB_RST_POS) 	
#define EPT_CMPC_RST_POS	(25)
#define EPT_CMPC_RST_MSK	(0x1 << EPT_CMPC_RST_POS) 	
#define EPT_CMPD_RST_POS	(26)
#define EPT_CMPD_RST_MSK	(0x1 << EPT_CMPD_RST_POS) 

typedef enum{
	EPT_LDXRST_EN =0,
	EPT_LDXRST_DIS
} ept_ldxrst_e;


/******************************************************************************
* SYNCR :  sync control register
******************************************************************************/
typedef enum{
	EPT_SYNCIN0 =0,
	EPT_SYNCIN1,
	EPT_SYNCIN2,
	EPT_SYNCIN3,
}ept_syncin_e;

#define EPT_SYNC_POS(ch)	(ch)
#define EPT_SYNC_MSK(ch)	(1<<ch)

typedef enum {
	EPT_SYNCXDIS =0,
	EPT_SYNCXEN
}ept_syncxen_e;

#define EPT_OSTMD_POS(ch)		(ch+8)
#define EPT_OSTMD_MSK(ch)		(1<<(EPT_OSTMD_POS(ch)))

typedef enum {
	EPT_OSTMD_CONTINUE = 0,
	EPT_OSTMD_ONCE
}ept_syncmd_e;

#define EPT_REARM_POS(ch)		(ch+16)
#define EPT_REARM_MSK(ch)		(1<<(ch+16))
#define EPT_REARM(ch) 				(1<<(ch+16))

#define EPT_TRGO0SEL_POS		(24)
#define EPT_TRGO0SEL_MSK		(0x7<<EPT_TRGO0SEL_POS)

#define EPT_TRGO1SEL_POS		(27)
#define EPT_TRGO1SEL_MSK		(0x7<<EPT_TRGO1SEL_POS)

typedef enum {
	EPT_TRGOXSEL_SYNC0 =0,
	EPT_TRGOXSEL_SYNC1 =1,
	EPT_TRGOXSEL_SYNC2 =2,
	EPT_TRGOXSEL_SYNC3 =3,
	EPT_TRGOXSEL_SYNC4 =4,
	EPT_TRGOXSEL_SYNC5 =5,
}ept_trgoxsel_e;

#define EPT_AREARM_POS		(30)
#define EPT_AREARM_MSK		(0x3<<EPT_AREARM_POS)
typedef enum{
	EPT_AREARM_DIS = 0,
	EPT_AREARM_ZRO,
	EPT_AREARM_PRD,
	EPT_AREARM_ZRO_PRD
}ept_arearm_e;

/******************************************************************************
* GLDCR :  global load  control register
******************************************************************************/
#define EPT_GLDEN_POS	(0)
#define EPT_GLDEN_MSK	(0x1)
#define EPT_GLDEN	(0x1ul << EPT_GLDEN_POS)
#define EPT_GLDMD_POS	(1)
#define EPT_GLDMD_MSK	(0xf << EPT_GLDMD_POS)

typedef enum		
{
	EPT_GLDMD_SEL_ZRO	=	0,
	EPT_GLDMD_SEL_PRD	,
	EPT_GLDMD_SEL_ZRO_PRD	,
	EPT_GLDMD_SEL_ZRO_EXI_SYNC		,
	EPT_GLDMD_SEL_PRD_EXI_SYNC		,
	EPT_GLDMD_SEL_ZRO_PRD_EXI_SYNC,
	EPT_GLDMD_Selecte_SW  = 0xf
}ept_gldmd_sel_e;

#define EPT_GLDCR_OSTMD_POS  (5)
#define EPT_GLDCR_OSTMD_MSK	(0x1 << EPT_GLDCR_OSTMD_POS)
typedef enum{
	EPT_GLD_ONESHORT_DIS = 0,
	EPT_GLD_ONESHORT_EN,
}ept_gld_oneshort_e;

#define EPT_GLDPRD_POS	(7)
#define EPT_GLDPRD_MSK	(0x7 << EPT_GLDPRD_POS)

#define EPT_GLDCNT_POS	(10)
#define EPT_GLDCNT_MSK	(0x7 << EPT_GLDCNT_POS)

/******************************************************************************
* GLDCFG :  global load  config register
******************************************************************************/
#define EPT_LD_PRDR_POS 		(0)
#define EPT_LD_PRDR_MSK		(0x1 << EPT_LD_PRDR_POS)
#define EPT_LD_CMPA_POS		(1)
#define EPT_LD_CMPA_MSK		(0x1 << EPT_LD_CMPA_POS)
#define EPT_LD_CMPB_POS 		(2)
#define EPT_LD_CMPB_MSK		(0x1 << EPT_LD_CMPB_POS)
#define EPT_LD_CMPC_POS 		(3)
#define EPT_LD_CMPC_MSK		(0x1 << EPT_LD_CMPC_POS)
#define EPT_LD_CMPD_POS 		(4)
#define EPT_LD_CMPD_MSK		(0x1 << EPT_LD_CMPD_POS)
#define EPT_LD_DBDTR_POS 	(5)
#define EPT_LD_DBDTR_MSK	(0x1 << EPT_LD_DBDTR_POS)
#define EPT_LD_DBDTF_POS 	(6)
#define EPT_LD_DBDTF_MSK	(0x1 << EPT_LD_DBDTF_POS)
#define EPT_LD_DBCR_POS 		(7)
#define EPT_LD_DBCR_MSK		(0x1 << EPT_LD_DBCR_POS)
#define EPT_LD_AQCRA_POS 	(8)
#define EPT_LD_AQCRA_MSK	(0x1 << EPT_LD_AQCRA_POS)
#define EPT_LD_AQCRB_POS	(9)
#define EPT_LD_AQCRB_MSK	(0x1 << EPT_LD_AQCRB_POS)
#define EPT_LD_AQCRC_POS 	(10)
#define EPT_LD_AQCRC_MSK	(0x1 << EPT_LD_AQCRC_POS)
#define EPT_LD_AQCRD_POS 	(11)
#define EPT_LD_AQCRD_MSK	(0x1 << EPT_LD_AQCRD_POS)
#define EPT_LD_AQCSF_POS	(12)
#define EPT_LD_AQCSF_MSK	(0x1 << EPT_LD_AQCSF_POS)
#define EPT_LD_EMOSR_POS 	(13)
#define EPT_LD_EMOSR_MSK	(0x1 << EPT_LD_EMOSR_POS)
typedef enum{
	EPT_LD_NOTGLD = 0,
	EPT_LD_GLD
}ept_gldmd_e;

/******************************************************************************
* GLDCR2 :  global load  control register2
******************************************************************************/
#define EPT_OSREARM_EN	(0x1)
#define EPT_SW_GLD		(0x2)


/******************************************************************************
* PHSR :  phase setting register
******************************************************************************/
#define EPT_PHSR_POS	(0)
#define EPT_PHSR_MSK	(0xffff)
#define EPT_PHSDIR_POS	(31)
#define EPT_PHSDIR_MSK	(0x1 << EPT_PHSDIR_POS)
typedef enum{
	EPT_PHSDIR_DN = 0,
	EPT_PHSDIR_UP
}ept_phsdir_e;

/******************************************************************************
* CMPA/B/C/D : compare val A/B/C/D register
******************************************************************************/
#define EPT_CMPDATA_MSK	(0xffff)	
#define EPT_CMPDATA_OVWRT (0x1 << 31)

/******************************************************************************
* CMPLDR : compare val load control register
******************************************************************************/
typedef enum		
{
	EPT_LDR_DIS								=		0,
	EPT_LDR_IM								=		1,
	EPT_LDR_ZRO							=		2,
	EPT_LDR_PRD							=		3,
	EPT_LDR_EXI_SYNC					=		4
}ept_ldr_e;

#define EPT_CMPA_LD_POS		(0)
#define EPT_CMPA_LD_MSK		(0x1 << EPT_CMPA_LD_POS)
#define EPT_CMPB_LD_POS		(1)
#define EPT_CMPB_LD_MSK		(0x1 << EPT_CMPB_LD_POS)
#define EPT_CMPC_LD_POS		(2)
#define EPT_CMPC_LD_MSK		(0x1 << EPT_CMPC_LD_POS)
#define EPT_CMPD_LD_POS		(3)
#define EPT_CMPD_LD_MSK		(0x1 << EPT_CMPD_LD_POS)
typedef enum {
	EPT_CMPLD_SHDW = 0,
	EPT_CMPLD_IMM
}ept_cmpdata_ldmd_e;

#define EPT_CMPA_LDTIME_POS		(4)
#define EPT_CMPA_LDTIME_MSK	(0x7 << EPT_CMPA_LDTIME_POS)
#define EPT_CMPB_LDTIME_POS		(7)
#define EPT_CMPB_LDTIME_MSK	(0x7 << EPT_CMPB_LDTIME_POS)
#define EPT_CMPC_LDTIME_POS		(10)
#define EPT_CMPC_LDTIME_MSK	(0x7 << EPT_CMPC_LDTIME_POS)
#define EPT_CMPD_LDTIME_POS		(13)
#define EPT_CMPD_LDTIME_MSK	(0x7 << EPT_CMPD_LDTIME_POS)
typedef enum{
	EPT_LDXMD_DIS =0,
	EPT_LDXMD_ZRO =1,
	EPT_LDXMD_PRD = 2,
	EPT_LDXMD_EXI_SYNC =4,
} ept_ldxmd_e;


#define EPT_SHDWAFULL 	(0x1 <<20)
#define EPT_SHDWBFULL 		(0x1 <<21)

/******************************************************************************
* AQLDR : wave output load control register
******************************************************************************/
#define EPT_AQCR1_SHDWEN_POS	(0)
#define EPT_AQCR1_SHDWEN_MSK	(0x1)
#define EPT_AQCR2_SHDWEN_POS	(1)
#define EPT_AQCR2_SHDWEN_MSK	(0x1 << EPT_AQCR2_SHDWEN_POS)
#define EPT_AQCR3_SHDWEN_POS	(8)
#define EPT_AQCR3_SHDWEN_MSK	(0x1 << EPT_AQCR3_SHDWEN_POS)
#define EPT_AQCR4_SHDWEN_POS	(9)
#define EPT_AQCR4_SHDWEN_MSK	(0x1 << EPT_AQCR4_SHDWEN_POS)

typedef enum {
	EPT_AQCR_IMM = 0,
	EPT_AQCR_SHDW
}ept_aqcr_ldmd_e;

#define EPT_LDAMD_POS			(2)
#define EPT_LDAMD_MSK		(0x7 << EPT_LDAMD_POS)
#define EPT_LDBMD_POS			(5)
#define EPT_LDBMD_MSK			(0x7 << EPT_LDBMD_POS)

#define EPT_LDCMD_POS			(10)
#define EPT_LDCMD_MSK			(0x7 << EPT_LDCMD_POS)
#define EPT_LDDMD_POS			(13)
#define EPT_LDDMD_MSK		(0x7 << EPT_LDDMD_POS)


/******************************************************************************
* AQCR1/2/3/4 : PWM1/2/3/4 wave output control register
******************************************************************************/
typedef enum{
	EPT_PWM1 =0,
	EPT_PWM2,
	EPT_PWM3,
	EPT_PWM4
}ept_pwm_out_e;

#define EPT_ACT_ZRO_POS		(0)
#define EPT_ACT_ZRO_MSK		(0x3 << EPT_ACT_ZRO_POS)
#define EPT_ACT_PRD_POS		(2)
#define EPT_ACT_PRD_MSK		(0x3 << EPT_ACT_PRD_POS)
#define EPT_ACT_C1U_POS		(4)
#define EPT_ACT_C1U_MSK		(0x3 << EPT_ACT_C1U_POS)
#define EPT_ACT_C1D_POS		(6)
#define EPT_ACT_C1D_MSK		(0x3 << EPT_ACT_C1D_POS)
#define EPT_ACT_C2U_POS		(8)
#define EPT_ACT_C2U_MSK		(0x3 << EPT_ACT_C2U_POS)
#define EPT_ACT_C2D_POS		(10)
#define EPT_ACT_C2D_MSK		(0x3 << EPT_ACT_C2D_POS)

typedef enum{
	EPT_PWM_ACT_DIS =0,
	EPT_PWM_ACT_LOW,
	EPT_PWM_ACT_HIGH,
	EPT_PWM_ACT_REVERSE
} ept_pwm_act_e;

#define EPT_C1SEL_POS	(20)
#define EPT_C1SEL_MSK	(0x3<<EPT_C1SEL_POS)
#define EPT_C2SEL_POS	(22)
#define EPT_C2SEL_MSK	(0x3<<EPT_C2SEL_POS)
typedef enum{
	EPT_CXSEL_CMPA				=	0,
	EPT_CXSEL_CMPB	,
	EPT_CXSEL_CMPC	,
	EPT_CXSEL_CMPD	
}ept_cxsel_e;

/******************************************************************************
* AQOSF : oneshort software control of  wave output  register
******************************************************************************/
#define EPT_OSTSFAX		(1)
#define EPT_ACTAX_POS	(1)
#define EPT_ACTAX_MSK	(0x3 << EPT_ACTAX_POS)
#define EPT_OSTSFAY		(0x1 << 3)
#define EPT_ACTAY_POS	(4)
#define EPT_ACTAY_MSK	(0x3 << EPT_ACTAY_POS)
#define EPT_OSTSFBX		(0x1 << 6)
#define EPT_ACTBX_POS	(7)
#define EPT_ACTBX_MSK	(0x3 << EPT_ACTBX_POS)
#define EPT_OSTSFBY		(0x1 << 9)
#define EPT_ACTBY_POS	(10)
#define EPT_ACTBY_MSK	(0x3 << EPT_ACTBY_POS)
#define EPT_OSTSFCX		(0x1 << 12)
#define EPT_ACTCX_POS	(13)
#define EPT_ACTCX_MSK	(0x3 << EPT_ACTCX_POS)
#define EPT_OSTSFCY		(0x1 << 15)
#define EPT_ACTCY_POS	(16)
#define EPT_ACTCY_MSK	(0x3 << EPT_ACTCY_POS)
#define EPT_OSTSFD			(0x1 << 18)
#define EPT_ACTD_POS		(19)
#define EPT_ACTD_MSK	(0x3 << EPT_ACTD_POS)


#define EPT_RLDCSF_POS	 (21)
#define EPT_RLDCSF_MSK (0x3 << EPT_RLDCSF_POS)

/******************************************************************************
* AQCSF : continus software control of  wave output  register
******************************************************************************/
#define EPT_CSFAX_POS	(0)
#define EPT_CSFAX_MSK	(0x3 << EPT_CSFAX_POS)
#define EPT_CSFAY_POS	(2)
#define EPT_CSFAY_MSK	(0x3 << EPT_CSFAY_POS)
#define EPT_CSFBX_POS	(4)
#define EPT_CSFBX_MSK	(0x3 << EPT_CSFBX_POS)
#define EPT_CSFBY_POS	(6)
#define EPT_CSFBY_MSK	(0x3 << EPT_CSFBY_POS)
#define EPT_CSFCX_POS	(8)
#define EPT_CSFCX_MSK	(0x3 << EPT_CSFCX_POS)
#define EPT_CSFCY_POS	(10)
#define EPT_CSFCY_MSK	(0x3 << EPT_CSFCY_POS)
#define EPT_CSFD_POS		(12)
#define EPT_CSFD_MSK		(0x3 << EPT_CSFD_POS)

/******************************************************************************
* DBLDR : deadband configurations load control  register
******************************************************************************/
#define EPT_DBCR_SHDWEN_POS	(0)
#define EPT_DBCR_SHDWEN_MSK	(0x1)
#define EPT_DBDTR_SHDWEN_POS	(3)
#define EPT_DBDTR_SHDWEN_MSK	(0x3 << EPT_DBDTR_SHDWEN_POS)
#define EPT_DBDTF_SHDWEN_POS	(6)
#define EPT_DBDTF_SHDWEN_MSK	(0x3 << EPT_DBDTF_SHDWEN_POS)
#define EPT_DCKPSC_SHDWEN_POS	(9)
#define EPT_DCKPSC_SHDWEN_MSK	(0x3 << EPT_DCKPSC_SHDWEN_POS)
typedef enum{
	EPT_DBLDR_IMM =0,
	EPT_DBLDR_SHD
}ept_dbldr_e;

#define EPT_CRLDMODE_POS 	     (1)
#define EPT_CRLDMODE_MSK 	(0x3ul <<EPT_CRLDMODE_POS)
#define EPT_LDDTRMD_POS 	     (4)
#define EPT_LDDTRMD_MSK	(0x3ul <<EPT_LDDTRMD_POS)
#define EPT_LDDTFMD_POS 	    (7)
#define EPT_LDDTFMD_MSK	(0x3ul <<EPT_LDDTFMD_POS)
#define EPT_LDPSCMD_POS 	    (10)
#define EPT_LDPSCMD_MSK	(0x3ul <<EPT_LDPSCMD_POS)

typedef enum{
	EPT_DBLDR_MD_DIS =0,
	EPT_DBLDR_MD_ZRO,
	EPT_DBLDR_MD_PRD,
	EPT_DBLDR_MD_ZRO_PRD
}ept_dbldr_md_e;

/******************************************************************************
* DBCR : deadband control  register
******************************************************************************/
typedef enum{
	EPT_DBSEL_CHA =0,
	EPT_DBSEL_CHB ,
	EPT_DBSEL_CHC,
}ept_dbsel_e;

#define DB_CHA_OUTSEL_POS			(0)
#define DB_CHA_OUTSEL_MSK		(0x3) 
#define DB_CHB_OUTSEL_POS			(8)
#define DB_CHB_OUTSEL_MSK		(0x3 << DB_CHB_OUTSEL_POS) 
#define DB_CHC_OUTSEL_POS			(16)
#define DB_CHC_OUTSEL_MSK		(0x3 << DB_CHC_OUTSEL_POS) 
typedef enum {
	EPT_DBOUT_DELAY_DIS = 0,    		
	EPT_DBOUT_DELAY_FALL,         		
	EPT_DBOUT_DELAY_RISE,        		
	EPT_DBOUT_DELAY_RISE_FALL     	  
}ept_db_outsel_e;

#define DB_CHA_POL_POS	(2)
#define DB_CHA_POL_MSK	(0x3 << DB_CHA_POL_POS)
#define DB_CHB_POL_POS	(10)
#define DB_CHB_POL_MSK	(0x3 << DB_CHB_POL_POS)
#define DB_CHC_POL_POS	(18)
#define DB_CHC_POL_MSK	(0x3 << DB_CHC_POL_POS)
typedef enum {
	EPT_DB_POL_DIS = 0,
	EPT_DB_POLX_REVERSE,
	EPT_DB_POLY_REVERSE,
	EPT_DB_POLXY_REVERSE
}ept_db_pol_e;       
#define DB_CHA_INSEL_POS		(4)
#define DB_CHA_INSEL_MSK	(0x3 << DB_CHA_INSEL_POS)
typedef enum {
	EPT_DBAIN_PWMA_RISE_FALL = 0,  //CHA
	EPT_DBAIN_PWMB_RISE_PWMA_FALL,
	EPT_DBAIN_PWMA_RISE_PWMB_FALL,
	EPT_DBAIN_PWMB_RISE_FALL,
	EPT_DBBIN_PWMB_RISE_FALL = 0, //CHB
	EPT_DBBIN_PWMC_RISE_PWMB_FALL,
	EPT_DBBIN_PWMB_RISE_PWMC_FALL,
	EPT_DBBIN_PWMC_RISE_FALL,
	EPT_DBCIN_PWMC_RISE_FALL = 0, //CHC
	EPT_DBCIN_PWMD_RISE_PWMC_FALL,
	EPT_DBCIN_PWMC_RISE_PWMD_FALL,
	EPT_DBCIN_PWMD_RISE_FALL,
}ept_dbchx_insel_e;

#define DB_CHA_OUTSWAP_POS	(6)
#define DB_CHA_OUTSWAP_MSK	(0x3 << DB_CHA_OUTSWAP_POS)

#define DB_CHB_OUTSWAP_POS	(14)
#define DB_CHB_OUTSWAP_MSK	(0x3 << DB_CHB_OUTSWAP_POS)

#define DB_CHC_OUTSWAP_POS	(22)
#define DB_CHC_OUTSWAP_MSK	(0x3 << DB_CHC_OUTSWAP_POS)

typedef enum	
{
	EPT_PATOCHX_PBTOCHY					=		0,
	EPT_PBTOCHX_PBTOCHY					,
	EPT_PATOCHX_PATOCHY					,
	EPT_PBTOCHX_PATOCHY				
}ept_outwrap_e;

#define DB_CHB_INSEL_POS		(12)
#define DB_CHB_INSEL_MSK	(0x3 << DB_CHB_INSEL_POS)

#define DB_CHC_INSEL_POS		(20)
#define DB_CHC_INSEL_MSK	(0x3 << DB_CHC_INSEL_POS)


#define EPT_DCKSEL_POS			(24)
#define EPT_DCKSEL_MSK		(0x1 << EPT_DCKSEL_POS)
typedef enum {
	EPT_DBCLK_TCLK = 0,
	EPT_DBCLK_DPSC
}ept_dbclksrc_e;

#define EPT_CHA_DEDB_POS	(25)
#define EPT_CHA_DEDB_MSK	(0x1 << EPT_CHA_DEDB_POS)
#define EPT_CHB_DEDB_POS	(26)
#define EPT_CHB_DEDB_MSK	(0x1 << EPT_CHB_DEDB_POS)
#define EPT_CHC_DEDB_POS	(27)
#define EPT_CHC_DEDB_MSK	(0x1 << EPT_CHC_DEDB_POS)
typedef enum {
	DB_AR_BF = 0,
	DB_BR_BF
}ept_dedb_e;

/******************************************************************************
* EMSRC : emergency status input control  register
******************************************************************************/
#define EPT_SEL_POS_EP(n)	((n) << 2)
#define EPT_SEL_MSK_EP(n)	(0xf << EPT_SEL_POS_EP(n))
typedef enum{
	EPT_EP0 = 0,
	EPT_EP1,
}ept_ep_e;

typedef enum	
{
	EPT_EP_INPUT_EBI0			=	1,		
	EPT_EP_INPUT_EBI1			=	2,		
	EPT_EP_INPUT_EBI2	,		
	EPT_EP_INPUT_EBI3	,		
	EPT_EP_INPUT_EBI4_LVD,		
	EPT_EP_INPUT_CMP0	,		
	EPT_EP_INPUT_CMP1	,		
	EPT_EP_INPUT_ORL0 =0xe	,	
	EPT_EP_INPUT_ORL1 =0xf	,
}ept_ep_input_e;

/******************************************************************************
* EMSRC2 config ORL0, ORL1 and input Filters
******************************************************************************/
#define EPT_ORL0_POS			(0)
#define EPT_ORL1_POS			(16)

#define EPT_EPPACE0_POS	(8)
#define EPT_EPPACE0_MSK	(0xf << EPT_EPPACE0_POS)

typedef enum{
	EPT_EPFLT0_DIS = 0,
	EPT_EPFLT0_2P,
	EPT_EPFLT0_4P,
	EPT_EPFLT0_6P,
	EPT_EPFLT0_8P,
	EPT_EPFLT0_16P,
	EPT_EPFLT0_32P,
	EPT_EPFLT0_64P
}ept_epflt_e;

/******************************************************************************
* EMPOL :emergency status input polarity control register
******************************************************************************/
#define POL_POS_EBI(n)		(n)
#define POL_MSK_EBI(n)	(0x1 << POL_POS_EBI(n))
typedef enum {
	EPT_EBI_POL_HIGH = 0,
	EPT_EBI_POL_LOW
}ept_ebipol_e;

/******************************************************************************
* EMECR :emergency status enable control register
******************************************************************************/
#define EPT_LCKMD_POS_EP(n)	((n) << 1)
#define EPT_LCKMD_MSK_EP(n)	(0x3 << EPT_LCKMD_POS_EP(n))

#define EPT_EMOSR_SHDWEN_POS 	(21)
#define EPT_EMSOR_SHDWEN_MSK  (0x1 << EPT_EMOSR_SHDWEN_POS)
#define EPT_EMSOR_SHDWEN				 (0x1 << EPT_EMOSR_SHDWEN_POS)

#define EPT_OSRLDMD_POS    			  22                                            
#define EPT_OSRLDMD_MSK    			 (0x3UL << EPT_OSRLDMD_POS)     
typedef enum{
	EM_OSRLD_DIS=0,
	EM_OSRLD_ZRO ,
	EM_OSRLDPRD,
	EM_OSRLD_ZRO_PRD,	
}ept_emosrld_e;         

#define EPT_SLCK_CLRMD_POS	(24)
#define EPT_SLCK_CLRMD_MSK	(0x3 << EPT_SLCK_CLRMD_POS)

typedef enum{
	EM_SLCLR_ZRO =0,
	EM_SLCLR_PRD,
	EM_SLCLR_ZRO_PRD,
	EM_SLCLR_DIS
}ept_emslclr_e;

#define EPT_EPASYNC_POS 		(26)
#define EPT_EPASYNC_MSK 	(1ul << 26)
typedef enum{
	EPT_EMASYNC_ENABLE =0,
	EPT_EMASYNC_DISABLE
}ept_emasync_e;

#define EPT_HLCRV_POS	(27)
#define EPT_HLCRV_MSK	(0x1 << EPT_HLCRV_POS)

typedef enum{
	EPT_HLCRV_MD_STOP = 0,
	EPT_HLCRV_MD_CONT,
}ept_hlcrvmd_e;

#define EPT_CPUFAULT_HLCK_POS	(28)
#define EPT_CPUFAULT_HLCK_MSK	(0x1 << EPT_CPUFAULT_HLCK_POS)
#define EPT_MEMFAULT_HLCK_POS	(29)
#define EPT_MEMFAULT_HLCK_MSK	(0x1 << EPT_MEMFAULT_HLCK_POS)
#define EPT_EOMFAULT_HLCK_POS	(30)
#define EPT_EOMFAULT_HLCK_MSK	(0x1 << EPT_EOMFAULT_HLCK_POS)
typedef enum{
	EPT_FAULT_DISABLE =0,
	EPT_FAULT_ENABLE
}ept_fault_e;

typedef enum
{
	EPT_LKCR_LOCK_DIS		=0,
	EPT_LKCR_SLOCK_EN		,
	EPT_LKCR_HLOCK_EN		,
	EPT_LKCR_TRG_X_FAULT_HLOCK_EN		,
	EPT_LKCR_TRG_X_FAULT_HLOCK_DIS		,
}ept_lckcr_e;

typedef enum
{
	EPT_LKCR_TRG_EP0			=		0,
	EPT_LKCR_TRG_EP1			=		2,
	EPT_LKCR_TRG_CPU_FAULT		=		28,
	EPT_LKCR_TRG_MEM_FAULT		=		29,
	EPT_LKCR_TRG_EOM_FAULT		=		30
}ept_lkcr_src_e;

/******************************************************************************
* EMOSR :emergency status output control register
******************************************************************************/
#define EPT_EMCHAX_O_POS		(0)
#define EPT_EMCHAX_O_MSK		(0x3)
#define EPT_EMCHBX_O_POS		(2)
#define EPT_EMCHBX_O_MSK		(0x3 << EPT_EMCHBX_O_POS)
#define EPT_EMCHCX_O_POS		(4)
#define EPT_EMCHCX_O_MSK		(0x3 << EPT_EMCHCX_O_POS)
#define EPT_EMCHD_O_POS			(6)
#define EPT_EMCHD_O_MSK		(0x3 << EPT_EMCHD_O_POS)
#define EPT_EMCHAY_O_POS		(8)
#define EPT_EMCHAY_O_MSK		(0x3 << EPT_EMCHAY_O_POS)
#define EPT_EMCHBY_O_POS		(10)
#define EPT_EMCHBY_O_MSK		(0x3 << EPT_EMCHBY_O_POS)
#define EPT_EMCHCY_O_POS		(12)
#define EPT_EMCHCY_O_MSK		(0x3 << EPT_EMCHCY_O_POS)

typedef enum
{
	EPT_OUTPUT_CHAX		=		0,
	EPT_OUTPUT_CHBX		=		2,
	EPT_OUTPUT_CHCX		=		4,
	EPT_OUTPUT_CHD			=		6,
	EPT_OUTPUT_CHAY		=		8,
	EPT_OUTPUT_CHBY		    =		10,
	EPT_OUTPUT_CHCY		=		12
}ept_outch_e;

typedef enum
{
	EPT_SHLOCK_OUTPUT_HZ		=	0,
	EPT_SHLOCK_OUTPUT_HIGH				=	1,
	EPT_SHLOCK_OUTPUT_LOW				=	2,
	EPT_SHLOCK_OUTPUT_NOCHANGE			=	3
}ept_shlock_e;

/******************************************************************************
* EMSLSR, EMSLCLR, EMHLSR, EMHLCLR EMRISR, EMMISR, EMIMCR, EMICR :  EM int
********************************************************************************/
typedef enum {
	EPT_EMINT_EP0 = 0x1,
	EPT_EMINT_EP1 = 0x1 << 1,
	EPT_EMINT_CPUF= 0x1 << 8,
	EPT_EMINT_MEMF= 0x1 << 9,
	EPT_EMINT_EOMF= 0x1 << 10
}ept_emint_e;
/******************************************************************************
* EVTRG :  event trigger select register
*******************************************************************************/
typedef enum{
	EPT_TRG0			=		0,
	EPT_TRG1			=		1,
	EPT_TRG2			=		2,
	EPT_TRG3			=		3
}ept_trg_e;

#define EPT_SEL_POS_TRG(n)	(n << 2)
#define EPT_SEL_MSK_TRG(n)	(0xf << EPT_SEL_POS_TRG(n))
typedef enum{
	EPT_TRGSRC_DIS = 0,
	EPT_TRGSRC_ZRO,
	EPT_TRGSRC_PRD,
	EPT_TRGSRC_ZRO_PRD,
	EPT_TRGSRC_CMPA_RISE,
	EPT_TRGSRC_CMPA_FALL,
	EPT_TRGSRC_CMPB_RISE,
	EPT_TRGSRC_CMPB_FALL,
	EPT_TRGSRC_CMPC_RISE,
	EPT_TRGSRC_CMPC_FALL,
	EPT_TRGSRC_CMPD_RISE,
	EPT_TRGSRC_CMPD_FALL,
	EPT_TRGSRC_SYNC =0xc,
	EPT_TRGSRC_PRD_END=0xc,
	EPT_TRGSRC_EP0 = 0xd,
	EPT_TRGSRC_EP1,
	EPT_TRGSRC_EP2
}ept_trgsrc_e;


#define EPT_OUTEN_POS_TRG(n)	(20+n)
#define EPT_OUTEN_MSK_TRG(n)	(0x1 << (EPT_OUTEN_POS_TRG(n)))
typedef enum{
	EPT_TRGOUT_DIS =0,
	EPT_TRGOUT_EN
}ept_trgout_md_e;

///EVSWF
/******************************************************************************
* EVSWF :  event counter software trigger control register
*******************************************************************************/
#define EPT_SWF_EV(n)	(0x1 << n)

/******************************************************************************
* RISR,MISR,IMCR,ICR: ept interrupt
******************************************************************************/
typedef enum{
	EPT_INT_TRGEV0 	= 0x1 << 0,
	EPT_INT_TRGEV1 	= 0x1 << 1,
	EPT_INT_TRGEV2 	= 0x1 << 2,
	EPT_INT_TRGEV3 	= 0x1<< 3,
	EPT_INT_CAPLD0 	= 0x1 << 4,
	EPT_INT_CAPLD1 	= 0x1 << 5,
	EPT_INT_CAPLD2 	= 0x1 << 6,
	EPT_INT_CAPLD3 	= 0x1 << 7,
	EPT_INT_CAU 	= 0x1 << 8,
	EPT_INT_CAD 	= 0x1 << 9,
	EPT_INT_CBU 	= 0x1 << 10,
	EPT_INT_CBD 	= 0x1 << 11,
	EPT_INT_CCU 	= 0x1 << 12,	
	EPT_INT_CCD 	= 0x1 << 13,
	EPT_INT_CDU 	= 0x1 << 14,
	EPT_INT_CDD 	= 0x1 << 15,
	EPT_INT_PEND 	= 0x1 << 16,
	EPT_INT_PRD   = 0x1 << 17,
	EPT_INT_ZRO   = 0x1 << 18,
	EPT_INT_CHAPROT = 0x1 << 19,
	EPT_INT_CHBPROT = 0x1 << 20,
	EPT_INT_CHCPROT = 0x1 << 21,
	EPT_INT_ALL = 0x3fffff,
}ept_int_e;

#define EPT_INT_EV(n)		(0x1 << n)
#define EPT_INT_CAPLD(n)	(0x1 << (n+4))

/******************************************************************************
*  REGPROT: register write protection register
******************************************************************************/
#define EPT_REGPROT			(0xa55a << 16 | 0xc73a)

/*****************************************************************************
 * functions
 ****************************************************************************/
/** \brief EPT software reset
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void ept_software_reset(void);
/** \brief EPT start
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void ept_start(void);
/** \brief EPT stop
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */  
void ept_stop(void);

/** \brief EPT PWM  Basic Configuration :clk , counter mode, operation  mode  ect.
 * 			
 *  \param[in] eClk : source clk select : PCLK OR SYNCIN3 \ref ept_clksel_e
 *  \param[in] eCntMd : Counter mode config :  increase ,decrease or increase_decrease  \ref ept_cntmd_e
 *  \param[in] eOpMd : Counter  operation mode : once or continus \ref ept_opmd_e
 *  \param[in] hwPscr : clk division control, range: 0~0XFFFF, :  Fclk=Fpclk/(PSCR+1)
 * 			   
 *  \return none
 */  
void ept_pwm_configure(ept_clksel_e eClk , ept_cntmd_e eCntMd  , ept_opmd_e eOpMd, U16_T hwPscr);
/** \brief EPT Clock Gate Filter Configuration :Clock Gate source select, filter div ,filter cnt , burst ect.
 * 			
 *  \param[in] eCgsrcSel : Clock Gate source select : DIS/CHAX/CHBX \ref ept_cgsrc_e
 *  \param[in] byCgfltDiv : Clock Gate Filter DIv Setting, range: 0~0xff 
 *  \param[in] byCgfltCnt : Clock Gate Filter Cnt Setting , range: 0~0x7
 *  \param[in] eBurst : Burst enable or disable control \ref ept_burst_e
 * 			   
 *  \return none
 */  
void ept_clockgate_configure(ept_cgsrc_e eCgsrcSel , U8_T byCgfltDiv , U8_T byCgfltCnt , ept_burst_e eBurst);
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
					, ept_ldxrst_e eLoadCmpa, ept_ldxrst_e eLoadCmpb, ept_ldxrst_e eLoadCmpc, ept_ldxrst_e eLoadCmpd,  U8_T byStopWrap , U16_T hwPscr);
/** \brief EPT syncx config
 * 			
 *  \param[in] eSycin : Syncin channel select \ref ept_syncin_e
 *  \param[in] eSyncMd : Sync Mode select : once or continus \ref ept_syncmd_e
 *  \param[in] eAutoRearm : Hardware Auto Rearm selection of sync0 ch: disable/ cnt=zreo/cnt=prd/cnt= zero or prd  \ref ept_arearm_e
 *  \param[in] eTrgo0Sel : Input trigger channel as ExtSync selection of TRGSRC0 \ref ept_trgoxsel_e
 *  \param[in] eTrgo1Sel : Input trigger channel as ExtSync selection of TRGSRC1 \ref ept_trgoxsel_e
 *  \param[in] eSync0En : Sync0 ch control :enable /disable \ref ept_syncxen_e
 * 			   
 *  \return none
 */  
void ept_syncr_configure(ept_syncin_e eSycin, ept_syncmd_e eSyncMd , ept_arearm_e eAutoRearm, ept_trgoxsel_e eTrgo0Sel ,ept_trgoxsel_e eTrgo1Sel , ept_syncxen_e eSync0En);
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
void ept_deadband_configure(ept_dbsel_e eDbChSel , ept_dbchx_insel_e eDbChxInSel , ept_db_outsel_e eOutSel , ept_db_pol_e ePol , ept_outwrap_e eOutWrap);
/** \brief EPT dedband clk config
 * 			
 *  \param[in] hwDpsc : Deadband clk division control ,range：0~0xffff
 * 					Fdbclk=Fhclk/(DPSC+1)	
 *  \param[in] hwDtr : Deadband raising edge timeout ,range：0~0xffff
 *  \param[in] hwDtf : Deadband falling edge timeout ,range：0~0xffff
 * 			   
 *  \return none
 */  
void ept_deadband_clk_configure(U16_T hwDpsc , U16_T hwDtr , U16_T hwDtf);
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
void ept_pwmx_output_control(
							 ept_pwm_out_e ePwmxOut ,ept_cxsel_e eC1Sel , ept_cxsel_e eC2Sel , ept_pwm_act_e eZeroAct , ept_pwm_act_e ePrdAct , 
							 ept_pwm_act_e eC1uAct , ept_pwm_act_e eC1dAct ,ept_pwm_act_e eC2uAct , ept_pwm_act_e eC2dAct 
							 );
/** \brief EPT PHSEN Config
 * 			
 *  \param[in] ePhsEn : Phase control ： enable or disable  \ref ept_phsen_e
 *  \param[in] ePhsDir : Phase Direction Control   \ref ept_phsdir_e
 *  \param[in] hwPhsr : when phase function enable, phsr val  load to cnt to control phase of pwm,range:0~0xffff
 * 
 *  \return none
 */    
void ept_phase_configure(ept_phsen_e ePhsEn , ept_phsdir_e ePhsDir , U16_T hwPhsr);
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
void ept_prdr_pwmx_configure(U16_T hwPrdr , U16_T hwCmpa , U16_T hwCmpb , U16_T hwCmpc , U16_T hwCmpd);

/** \brief the EPT SYNCR Rearm
 * 			
 *  \param[in] byRearmCh : Input trigger channel select: syncin0~syncin5 ,range :0~5 
 * 
 *  \return none
 */   
void ept_syncr_rearm(U8_T byRearmCh );

/** \brief EPT Caputer Rearm:clear counter， enable CAPLDEN automatic
 * 			
 *  \param[in] none
 * 
 *  \return none
 */   
void ept_capture_rearm(void);

/** \brief  EPT Globle Event Load
 * 			
 *  \param[in] eOneShort: global one short load mode control :enable or disable \ref ept_gld_oneshort_e
 *  \param[in] eGldMd: global load trigger event select \ref ept_gldmd_sel_e
 *  \param[in] byGldPrd: global load trigger period select,  range: 0~0x7
 *  \param[in] hwGldCfg:  AQCRx, CMPx, ect  all channels  global load control ,range:0x0~0x3fff
 * 
 *  \return none
 */  
void ept_global_event_load_configure(ept_gld_oneshort_e eOneShort , ept_gldmd_sel_e eGldMd , U8_T byGldPrd , U16_T hwGldCfg);

/** \brief  EPT Globle SW Load
 * 			
 *  \param[in] none
 * 
 *  \return none
 */  
void ept_global_software_load(void);
/** \brief  EPT PRDR Load 
 * 			
 *  \param[in] eLdPrdr: PRDR active register load control \ref ept_ldprdr_e
 * 
 *  \return none
 */  
void ept_prdr_load_configure(ept_ldprdr_e eLdPrdr);
/** \brief  EPT CMPX Load Config
 * 			
 *  \param[in] eCmpLdr: CMPX load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_cmp_load_configure(ept_ldr_e eCmpLdr);
/** \brief  EPT AQCRX Load Config
 * 			
 *  \param[in] eAqcrLdr: AQCRX load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_aqcr_load_configure(ept_ldr_e eAqcrLdr);

/** \brief   EPT DB Load Config
 * 			
 *  \param[in] eDbLdr: DBCR,DBDTR,DBDTF,DPSCR load mode select \ref ept_ldr_e
 * 
 *  \return none
 */  
void ept_deadband_load_configure(ept_ldr_e eDbLdr);

 /** \brief   EPT EVTRG Config
 * 			
 *  \param[in] eTrg: Trigger event select \ref ept_trg_e
 *  \param[in] eTrgSrc: Trigger event source select \ref ept_trgsrc_e
 *  \param[in] eTrgoutEn: Trigger event enable or disable control \ref ept_trgout_md_e
 *  \param[in] eTrgSrc: Trigger event source select \ref ept_trgsrc_e
 * 
 *  \return none
 */  
void ept_event_trigger_configure(ept_trg_e eTrg , ept_trgsrc_e eTrgSrc , ept_trgout_md_e eTrgoutEn );

/** \brief   EPT EVTRG software trigger
 * 			
 *  \param[in] eTrg: Trigger event select \ref ept_trg_e
 * 
 *  \return none
 */  
void ept_event_software_trigger(ept_trg_e eTrg);

/** \brief   EPT interrupt enable 
 * 			
 *  \param[in] eInt: type of interrupt \ref ept_int_e
 * 
 *  \return none
 */  
void ept_int_enable(ept_int_e eInt);
/** \brief   EPT interrupt disable 
 * 			
 *  \param[in] eInt: type of interrupt \ref ept_int_e
 * 
 *  \return none
 */  
void ept_int_disable(ept_int_e eInt);
/** \brief   EPT emergency interrupt enable 
 * 			
 *  \param[in] eEmInt: type of  emergency interrupt \ref ept_emint_e
 * 
 *  \return none
 */  
void ept_emint_enable(ept_emint_e eEmInt);
/** \brief   EPT emergency interrupt disable 
 * 			
 *  \param[in] eEmInt: type of  emergency interrupt \ref ept_emint_e
 * 
 *  \return none
 */  
void ept_emint_disable(ept_emint_e eEmInt);

/** \brief   EPT EP0~EP1 config
 * 			
 *  \param[in] eEpx: EPT emergency port select \ref ept_ep_e
 *  \param[in] eEpInput: epx input select \ref ept_ep_input_e
 *  \param[in] eEpFlt: epx digital filter check period \ref ept_epflt_e
 *  \param[in] byOr0Epx: OR0 input enable or disable control  ,range: 0~0x3f
 *  \param[in] byOr1Epx: OR1input enable or disable control  ,range: 0~0x3f
 * 
 *  \return none
 */  
void ept_emergency_port_configure(ept_ep_e eEpx , ept_ep_input_e eEpInput , ept_epflt_e eEpFlt  , U8_T byOr0Epx , U8_T byOr1Epx);
/** \brief   EPT EMPOL config
 * 			
 *  \param[in] byEbiPol: EBIX polarity setting (0:Active high 1:Active low)  ,range: 0~0x3f
 * 
 *  \return none
 */  
void ept_emergency_polarity_configure(U8_T byEbiPol);
/** \brief   EPT EMECR config
 * 			
 *  \param[in] eLckSrc: ept LKCR source select \ref ept_lkcr_src_e
 *  \param[in] eLckCr:  EPT LKCR Mode Select	 \ref ept_lckcr_e
 * 
 *  \return none
 */ 
void ept_emergency_lock_configure(ept_lkcr_src_e eLckSrc , ept_lckcr_e eLckCr);
/** \brief   EPT SHLOCK output config
 * 			
 *  \param[in] eOutCh: ept output channel select \ref ept_outch_e
 *  \param[in] eShLck: ept shlock output state setting \ref ept_shlock_e
 * 
 *  \return none
 */ 
void ept_emergency_lock_output_set(ept_outch_e eOutCh , ept_shlock_e eShLck);
/** \brief   EPT software lock clr
 * 			
 *  \param[in] eEmInt: em interrupt : only  EP0 & EP1\ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_emergency_software_lock_clear(ept_emint_e eEmInt);
/** \brief   EPT hardware lock clr
 * 			
 *  \param[in] eEmInt: em interrupt  \ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_emergency_hardware_lock_clear(ept_emint_e eEmInt);
/** \brief   EPT software set lock
 * 			
 *  \param[in] eEmInt: em interrupt : only  EP0 & EP1 \ref ept_emint_e
 * 
 *  \return none
 */ 
void ept_software_trigger_epx(ept_emint_e eEmInt);

#endif   /* EPT_H */