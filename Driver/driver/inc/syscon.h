/***********************************************************************//** 
 * \file  syscon.h
 * \brief  syscon description and static inline functions at Registerister level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSCON_H
#define _SYSCON_H

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/// \struct csp_syscon_t
/// \brief SYSCON Register description
typedef volatile struct {                   	  /*!< SYSCON Structure                         */
	__IOM U32_T	IDCCR;                        /*!< 0x000: Identification & System Controller Clock Control Register */
	__OM  U32_T	GCER;                         /*!< 0x004: System Controller General Control Enable Register */
	__OM  U32_T	GCDR;                         /*!< 0x008: System Controller General Control Disable Register */
	__IM  U32_T	GCSR;                         /*!< 0x00C: System Controller General Control Status Register */
	__IM  U32_T	CKST;                         /*!< 0x010*/
	__IM U32_T	RSVD0[2];                     /*!< 0x014 ~ 0x018*/
	__IOM U32_T	SCLKCR;                       /*!< 0x01C: System Controller System Clock Selection & Division Register */
	__IOM  U32_T	PCLKCR;                       /*!< 0x020: System Controller Peripheral Clock Selection & Division Register */
	__IM  U32_T	RSVD1;                        /*!< 0x024*/
	__OM  U32_T	PCER0;                        /*!< 0x028: System Controller Peripheral Clock Enable Register */
	__OM  U32_T	PCDR0;                        /*!< 0x02C: System Controller Peripheral Clock Disable Register */
	__IM  U32_T	PCSR0;                        /*!< 0x030: System Controller Peripheral Clock Status Register */
	__OM  U32_T	PCER1;                        /*!< 0x034: System Controller Peripheral Clock Enable Register */
	__OM  U32_T	PCDR1;                        /*!< 0x038: System Controller Peripheral Clock Disable Register */
	__IM  U32_T	PCSR1;                        /*!< 0x03C: System Controller Peripheral Clock Status Register */
	__IOM U32_T	OSTR;                         /*!< 0x040: System Controller External OSC Stable Time Control Register */
	__IOM U32_T	PLLCR;                        /*!< 0x044: System Controller PLL Stable Time Control Register */
	__IM  U32_T	RSVD2;                        /*!< 0x048: System Controller PLL PMS Value Control Register */
	__IOM U32_T	LVDCR;                        /*!< 0x04C: System Controller LVD Control Register */
	__IOM U32_T	CLCR;                         /*!< 0x050: System Controller IMOSC Fine Adjustment Register*/
	__IOM U32_T	PWRCR;                        /*!< 0x054: System Controller Power Control Register */
	__IOM U32_T	PWRKEY;                       /*!< 0x058: System Controller Power Control Register */
	__IM  U32_T	RSVD3[2];                     /*!< 0x05C ~0x060: */
	__IOM U32_T	OPT1;                         /*!< 0x064: System Controller OSC Trim Control Register */
	__IM  U32_T	OPT0;                         /*!< 0x068: System Controller Protection Control Register */
	__IOM U32_T	WKCR;                         /*!< 0x06C: System Controller Clock Quality Check Control Register */
	__IM  U32_T	RSVD4;                        /*!< 0x070: System Controller Clock Quality Check Control Register */
	__OM  U32_T	IMER;                         /*!< 0x074: System Controller Interrupt Enable Register */
	__OM  U32_T	IMDR;                         /*!< 0x078: System Controller Interrupt Disable Register */
	__IOM U32_T	IMCR;                         /*!< 0x07C: System Controller Interrupt Mask Register */
	__OM  U32_T	IAR;                          /*!< 0x080: System Controller Interrupt Active Register */
	__OM  U32_T	ICR;                          /*!< 0x084: System Controller Clear Status Register */
	__IM  U32_T	RISR;                         /*!< 0x088: System Controller Raw Interrupt Status Register */
	__IM  U32_T	MISR;                         /*!< 0x08C: System Controller Raw Interrupt Status Register */
	__IOM U32_T	RSR;                          /*!< 0x090: System Controller Raw Interrupt Status Register */
	__IOM U32_T	EXIRT;                        /*!< 0x094: System Controller Reset Status Register */
	__IOM U32_T	EXIFT;                        /*!< 0x098: System Controller External Interrupt Mode 1 (Positive Edge) Register */
	__OM  U32_T	EXIER;                        /*!< 0x09C: System Controller External Interrupt Mode 2 (Negative Edge) Register */
	__OM  U32_T	EXIDR;                        /*!< 0x0A0: System Controller External Interrupt Enable Register */
	__IM  U32_T	EXIMR;                        /*!< 0x0A4: System Controller External Interrupt Disable Register */
	__IOM U32_T	EXIAR;                        /*!< 0x0A8: System Controller External Interrupt Mask Register */
	__IOM U32_T	EXICR;                        /*!< 0x0AC: System Controller External Interrupt Active Register */
	__IOM U32_T	EXIRS;                        /*!< 0x0B0: System Controller External Interrupt Clear Status Register */
	__IOM U32_T	IWDCR;                        /*!< 0x0B4: System Controller Independent Watchdog Control Register */
	__IOM U32_T	IWDCNT;                       /*!< 0x0B8: SystCem Controller Independent Watchdog Counter Value Register */
	__IOM U32_T	IWDEDR;                       /*!< 0x0BC: System Controller Independent Watchdog Enable/disable Register*/
	__IM  U32_T	RSVD5;                        /*!< 0x0C0: */
	__IOM U32_T	IOMAP1;                       /*!< 0x0C4: Customer Information Content mirror of 1st byte*/
	__IM  U32_T	RSVD6[7];                     /*!< 0x0C8 ~ 0x0E0: */
	__IM  U32_T	UID0 ;                        /*!< 0x0E4: Customer Information Content mirror of 1st byte*/
	__IM  U32_T	UID1 ;                        /*!< 0x0E8: Customer Information Content mirror of 1st byte*/
	__IM  U32_T	UID2 ;                        /*!< 0x0EC: Customer Information Content mirror of 1st byte*/
	__IOM U32_T	PWROPT;                       /*!< 0x0F0: Power recovery timmming Control */
	__IOM U32_T	EVTRG;                        /*!< 0x0F4: Trigger gen                                    */
	__IOM U32_T	EVPS;                      	  /*!< 0x0F8: Trigger prs                                    */
	__OM  U32_T	EVSWF;                        /*!< 0x0FC: Trigger software force                         */
	__IOM U32_T	UREG0;                        /*!< 0x100: User defined Register0                              */
	__IOM U32_T	UREG1;                        /*!< 0x104: User defined Register1                              */
	__IOM U32_T	UREG2;                        /*!< 0x108: User defined Register0                              */
	__IOM U32_T	UREG3;                        /*!< 0x10C: User defined Register0                              */
	__IM  U32_T	RSVD7[6];                     /*!< 0x110 ~ 0x124: */
	__IOM U32_T	DBGCR;						  /*!< 0x128: Debug Control Register			   */
} csp_syscon_t; 

/******************************************************************************
************************* syscon Registers Definition *************************
******************************************************************************/
/** @addtogroup SYSCON Registers Reset Value
  * @{
  */



#define SYSCON_SCLKCR_RST      	(0xD22Dul<<16)
#define SYSCON_PCLKCR_RST     	(0x00000100)

#define SYSCON_OSTR_RST  		(0x70ff3bff)
#define SYSCON_PLLCR_RST  		(0x00000000)
#define SYSCON_LVDCR_RST  		(0x0000000a)
#define	SYSCON_CLCR_RST			(0x00000100)
#define	SYSCON_PWRCR_RST		(0x141f1f00)
#define	SYSCON_OPT1_RST			(0x00000000)
#define	SYSCON_WKCR_RST			(0x00000000)
#define	SYSCON_IMCR_RST			(0x00000000)

#define	SYSCON_RSR_RST			(0x00000000)
#define	SYSCON_EXIRT_RST		(0x00000000)
#define	SYSCON_EXIFT_RST		(0x00000000)

#define	SYSCON_EXIMR_RST		(0x00000000)
#define	SYSCON_EXIAR_RST		(0xffffffff)
#define	SYSCON_EXICR_RST		(0x00000000)
#define	SYSCON_EXIRS_RST		(0x00000000)
#define	SYSCON_IWDCR_RST		(0x0000070C)
#define	SYSCON_IWDCNT_RST		(0x000003fe)
#define	SYSCON_PWROPT_RST		(0x00004040)
#define	SYSCON_EVTRG_RST		(0x00000000)
#define	SYSCON_EVPS_RST			(0x00000000)


/******************************************************************************
*IDCCR : CHIP ID/SYSCON Control Register
******************************************************************************/
#define SYSCON_SWRST_POS 		(7)
#define SYSCON_IDCCR_KEY_POS	(16)	
#define	SWRST					(0x01ul<<SYSCON_SWRST_POS)
#define IDCCR_KEY 				(0xE11Eul<<SYSCON_IDCCR_KEY_POS)
#define	SYSCON_CLKEN			(0x01ul)
#define	CPUFTRST_EN				(0x00<<1)
#define	CPUFTRST_DIS			(0xA<<1)


/******************************************************************************
*GCER/GCER/GCSR : Gerneral enable/disbale Control/status Register
******************************************************************************/
typedef enum
{
	ENDIS_ISOSC			=	 	(0x01 << 0),
	ENDIS_IMOSC 		=		(0x01 << 1),
	ENDIS_EMOSC 		=		(0x01 << 3),
	ENDIS_PLL 			=		(0x01 << 5),

//	ENDIS_IDLE_PCLK 	=		(8),
//	ENDIS_SYSTICK 		=		(11)
}osc_enable_e;

typedef enum{
	PCLK_IDLE = (0x01<< 8),
	HCLK_IDLE = (0x01<< 9),
	ISOSC_STP = (0x01<< 12), 
	IMOSC_STP = (0x01 << 13),
	ESOSC_STP = (0x01 << 14),
	EMOSC_STP = (0x01 << 15),
}clk_pm_e;

#define ES_CM_EN 	(0x01ul<<16)
#define ES_CMRST 	(0x01ul<<17)

#define EM_CM_EN 	(0x01ul<<18)
#define EM_CMRST 	(0x01ul<<19)

/******************************************************************************
*CKST : clock Status Registerister
******************************************************************************/
#define SYSCLK_STABLE		(0x01ul << 8)


/******************************************************************************
*SCLKCR : system clock Control Register
******************************************************************************/
#define SCLKCR_KEY_POS	(16)
#define SCLKCR_KEY 		(0xD22Dul<<SCLKCR_KEY_POS)

#define SCLK_SEL_POS	 8
typedef enum
{
	SYSCLK_IMOSC	=		0x0ul<<SCLK_SEL_POS,				
	SYSCLK_EMOSC	=		0x1ul<<SCLK_SEL_POS,				
	SYSCLK_PLL		=		0x3ul<<SCLK_SEL_POS,				  
	SYSCLK_ISOSC 	=		0x4ul<<SCLK_SEL_POS				
}sycclk_sel_e;

#define HCLK_DIV_POS	 8
typedef enum
{
	HCLK_DIV_1   =		(0x1ul<<HCLK_DIV_POS),				
	HCLK_DIV_2   =		(0x2ul<<HCLK_DIV_POS),
	HCLK_DIV_3   =		(0x3ul<<HCLK_DIV_POS),
	HCLK_DIV_4   =		(0x4ul<<HCLK_DIV_POS),
	HCLK_DIV_5   =		(0x5ul<<HCLK_DIV_POS),
	HCLK_DIV_6   =		(0x6ul<<HCLK_DIV_POS),
	HCLK_DIV_7   =		(0x7ul<<HCLK_DIV_POS),
	HCLK_DIV_8   =		(0x8ul<<HCLK_DIV_POS),
	HCLK_DIV_12  =		(0x9ul<<HCLK_DIV_POS),
	HCLK_DIV_16  =		(0xAul<<HCLK_DIV_POS),
	HCLK_DIV_24  =		(0xBul<<HCLK_DIV_POS),
	HCLK_DIV_32  =		(0xCul<<HCLK_DIV_POS),
	HCLK_DIV_64  =		(0xDul<<HCLK_DIV_POS),
	HCLK_DIV_128 =		(0xEul<<HCLK_DIV_POS),
	HCLK_DIV_256 =		(0xFul<<HCLK_DIV_POS)
}hclk_div_e;

typedef enum
{
	F_0_8MHz = 0,
	F_8_16MHz,
	F_16_24MHz,
	F_24_48MHz
}sysclk_freq_e;

/******************************************************************************
*PCLKCR : peripheral clock Control Register
******************************************************************************/
#define PCLKCR_KEY_POS	(16)
#define PCLKCR_KEY 	 	(0xC33Cul<<PCLKCR_KEY_POS)
#define PCLK_DIV_POS	 8
typedef enum
{
	PCLK_DIV_1   =		(0x00ul<<PCLK_DIV_POS),				
	PCLK_DIV_2   =		(0x01ul<<PCLK_DIV_POS),
	PCLK_DIV_4   =		(0x02ul<<PCLK_DIV_POS),
	PCLK_DIV_8   =		(0x04ul<<PCLK_DIV_POS),
	PCLK_DIV_16  =		(0x08ul<<PCLK_DIV_POS)
}pclk_div_e;


/******************************************************************************
*OSTR : EMOSC Control Register
******************************************************************************/
#define EM_FLTSEL_POS	26
#define EM_FLTSEL_MSK	(0x3<<EM_FLTSEL_POS)
typedef enum
{
	EM_FLSEL_5NS	=	(0x0ul),
	EM_FLSEL_10NS	=	(0x1ul),
	EM_FLSEL_15NS	=	(0x2ul),
	EM_FLSEL_20NS	=	(0x3ul)
}em_fltsel_e;

#define EM_FLT_EN_POS	25
#define EM_GMCTL_POS	11
#define EM_GMCTL_MSK	(0x1f <<EM_GMCTL_POS)
#define EM_LFSEL_POS	10
#define EM_LFSEL_MSK	(0x1 << EM_LFSEL_POS)
typedef enum
{
	EM_HIGHF	=	0,
	EM_LOWF		=	1
}em_lfsel_e;
#define EM_CNT_POS	0
#define EM_CNT_MSK	(0x3ff << EM_CNT_POS)

/******************************************************************************
*PLLCR : PLL Control Register
******************************************************************************/
#define PLL_SRC_POS		0x0
#define PLL_SRC_MSK		(0x3<<PLL_SRC_POS)
typedef enum
{
	PLL_SRC_IMOSC = 1,
	PLL_SRC_EMOSC = 3,
}pll_src_e;

#define PLL_UNLOCK_RST_POS 15
#define PLL_UNLOCK_RST_MSK (0x1<<PLL_UNLOCK_RST_POS)

#define PLL_TYPE_POS	16
#define PLL_TYPE_MSK	(0x1 << PLL_TYPE_MSK)
typedef enum
{
	PLL_TYPE_ANA = 0,
	PLL_TYPE_DIG = 1,
}pll_type_e;

typedef  enum
{
	PLL_UNLOCK_RST_DIS = 0,
	PLL_UNLOCK_RST_EN = 1,
}pll_rst_e;

/******************************************************************************
*WKCR : Wakeup Source Control Register
******************************************************************************/
typedef enum {
	WKUP_IWDT = 8,
	WKUP_RTC,
	WKUP_LPT,
	WKUP_LVD
}wakeup_src_e;



/******************************************************************************
* IECR : Interrupt Enable
* IEDR : Interrupt Disable
* IAR  : Interrupt Active 
* ICR  : Interrupt Clear
* IMER : Interrupt Mask Enable Status
* IMDR : Interrupt Mask Disable Status
* RISR : Raw Interrupt Status
* MISR : Masked Interrupt Status
******************************************************************************/
typedef enum{
	ISOSC_INT 		= (0x1<<0),
	IMOSC_INT 		= (0x1<<1),
	EMOSC_INT 		= (0x1<<3),
	PLL_INT	    	= (0x1<<5),
	SYSTICK_INT 	= (0x1<<7),
	IWDT_INT 		= (0x1<<8),
	LVD_INT 		= (0x1<<11),
	OPL_ERR_INT 	= (0x1<<14),
	PLL_UNLOCK_INT 	= (0x1<<15),
	EMFAIL_INT 		= (0x1<<18),
	EV0TRG_INT 		= (0x1<<19),
	EV1TRG_INT 		= (0x1<<20),
	EV2TRG_INT 		= (0x1<<21),
	EV3TRG_INT 		= (0x1<<22),
	CMD_ERR_INT		= (0x1<<29),
	SYSCON_INT_ALL  = ISOSC_INT | IMOSC_INT | EMOSC_INT | PLL_INT | SYSTICK_INT | IWDT_INT | LVD_INT 
					| OPL_ERR_INT | PLL_UNLOCK_INT | EMFAIL_INT | EV0TRG_INT | EV1TRG_INT |EV2TRG_INT 
					|EV3TRG_INT |CMD_ERR_INT,
}syscon_int_e;


/******************************************************************************
* Exernal Interrupt Related: 
* EXIRT: Rising Edge Enable/Disable
* EXIFT: Falling Edge Enable/Disable
* EXIER: External Interrupt Enable
* EXIDR: External Interrupt Disable
* EXIMR: External Interrupt Enable Status
******************************************************************************/
#define SYSCON_EXI_POS(n)	(n)
#define SYSCON_EXI_MSK(n)	(0x1 << SYSCON_EXI_POS(n))
typedef enum
{
	EXI_EDGE_R	= 0,
	EXI_EDGE_F	= 1,	
	EXI_EDGE_BOTH	= 2
}exi_trigger_e;

typedef enum
{
	EXI_IGRP0		= (0),						
	EXI_IGRP1		= (1),
	EXI_IGRP2		= (2),
	EXI_IGRP3		= (3),
	EXI_IGRP4		= (4),
	EXI_IGRP5		= (5),
	EXI_IGRP6		= (6),
	EXI_IGRP7		= (7),
	EXI_IGRP8		= (8),
	EXI_IGRP9		= (9),
	EXI_IGRP10		= (10),
	EXI_IGRP11		= (11),
	EXI_IGRP12		= (12),
	EXI_IGRP13		= (13),
	EXI_IGRP14		= (14),
	EXI_IGRP15		= (15),
	EXI_IGRP16		= (16),
	EXI_IGRP17		= (17),
	EXI_IGRP18		= (18),
	EXI_IGRP19		= (19)
}exi_igrp_e;


/******************************************************************************
*RSR : Reset Source Register
******************************************************************************/
#define RSR_MSK		(0xffff)
typedef enum{
	POR_RST			= (0x1ul <<0),
	LVR_RST			= (0x1ul <<1),
	EXT_RST			= (0x1ul <<2),
	IWDT_RST		= (0x1ul <<4),
	EMCM_RST 		= (0x1ul <<6),
	CPU_RST			= (0x1ul <<7),
	SW_RST			= (0x1ul <<8),
	CPUFAULT_RST	= (0x1ul <<9),
	PLLUNLOCKRST	= (0x1ul <<10),
	ALL_RST 		= 0xFFFF
}rst_st_e;


/******************************************************************************
*IWDCR : IWDT Control Register
******************************************************************************/
#define IWDCR_KEY_POS 	(16)
#define IWDCR_KEY 		(0x8778ul << IWDCR_KEY_POS)

#define IWDT_INTV_POS	(2)
#define IWDT_INTV_MSK 	(0x3f << IWDT_INTV_POS)

typedef enum{
	IWDT_INTW_7_8 = 0,
	IWDT_INTW_6_8,
	IWDT_INTW_5_8, 
	IWDT_INTW_4_8, 
	IWDT_INTW_3_8, 
	IWDT_INTW_2_8, 
	IWDT_INTW_1_8
}iwdt_intv_e;

#define IWDT_OVT_POS	(8)
#define IWDT_OVT_MSK 	(0x7 << IWDT_OVT_POS)
typedef enum{
	IWDT_TIME_0128 = 0x0,
	IWDT_TIME_0256,
	IWDT_TIME_0512,
	IWDT_TIME_1000,
	IWDT_TIME_2000,
	IWDT_TIME_3100,
	IWDT_TIME_4100,
	IWDT_TIME_8200
}iwdt_ovt_e;

#define IWDT_DBGEN_POS (11)
#define IWDT_DBGEN_MSK (0x1 << IWDT_DBGEN_POS)
#define IWDT_BUSY_POS (12)
#define IWDT_BUSY	(0x1 << IWDT_BUSY_POS)


/******************************************************************************
*IWDCNT : IWDT Count Register
******************************************************************************/
#define IWDT_CLR_POS		(24)
#define IWDT_CLR_BUSY		(0x1<<IWDT_CLR_POS)
#define IWDT_CLR			(0x5a)
#define	CLR_IWDT			(IWDT_CLR<<IWDT_CLR_POS)
#define IWDT_CNT_MSK		(0xfff)

/******************************************************************************
*IWDEDR: IWDT enable Control Register
******************************************************************************/
#define IWDEDR_KEY_POS		(16)
#define IWDEDR_KEY			(0x7887 << IWDEDR_KEY_POS)
#define IWDT_EN_POS			(0)
#define DIS_IWDT			(0x55aa << IWDT_EN_POS)
#define EN_IWDT				(0x0 << IWDT_EN_POS)

/******************************************************************************
*LVDCR: LVD Control Register
******************************************************************************/
#define LVD_KEY 			(0xB44Bul<<16)
#define LVDEN_MSK 			(0xf)
#define LVD_DIS				(0xa)
#define LVD_EN 				(0x0ul<<0)
#define LVDINT_POL_POS 		(0x6)
#define LVDINT_POL_MSK 		(0x3 << LVDINT_POL_POS)
#define LVDINT_DET_POL(r) 	((r&0x3) << LVDINT_POL_POS)
#define LVD_FLAG_POS		(5)
#define LVD_FLAG    		(0x1 << LVD_FLAG_POS)

typedef enum {
	LVDINT_F = 1,
	LVDINT_R,
	LVDINT_BOTH	
}lvdint_pol_e;

#define LVD_LV_POS 	(0x8)
#define LVD_LV_MSK  (0x7 << LVD_LV_POS)
typedef enum{
	LVD21 = 0,
	LVD24,
	LVD27,
	LVD30,
	LVD33,
	LVD36,
	LVD39,
	LVDIN10	
}lvd_level_e;

#define LVR_SRT_POS	(4)
#define LVR_SRT_MSK	(0x01ul << LVR_SRT_POS)

#define LVR_LV_POS	(12)
#define LVR_LV_MSK  (0x7 << LVR_LV_POS)

typedef enum {
	LVR19 = 0,
	LVR22,
	LVR25,
	LVR28,
	LVR31,
	LVR34,
	LVR37,
	LVR40
}lvr_level_e;

/******************************************************************************
*OPT1: clo/osc freq/Flash LP mode/EXI filter/EM clock monitoring config
******************************************************************************/
#define CLO_SRC_POS (8)
#define CLO_SRC_MSK (0xful << CLO_SRC_POS)
typedef enum
{
	CLO_ISCLK		=	0,
	CLO_IMCLK		=	1,
	CLO_EMCLK		=	3,
	CLO_PLLCLK		=	4,
	CLO_PCLK		=	7,
	CLO_HCLK		=	8,
	CLO_IWDTCLK		=	9,
	CLO_SYSCLK		=	0x0D,
}clo_src_e;

#define CLO_DIV_MSK 	(0x7ul << CLO_DIV_POS)
#define CLO_DIV_POS 	(12)
typedef enum
{
	CLO_DIV4			=	0,
	CLO_DIV0			=	1,
	CLO_DIV2			=	2,
	CLO_DIV8			=	4,
	CLO_DIV16		    =	5,
}clo_div_e;


/******************************************************************************
*WKCR Wakeup Source Control Register
******************************************************************************/
typedef enum{
	IWDT_WKEN = 8,
	LVD_WKEN  = 11,
	TC3_WKEN  = 13
}syscon_wksrc_e;


/******************************************************************************
*IOMAP1: IOMAP1 configuration
******************************************************************************/
#define IOMAP_MSK_POS(n)	(n*4)
#define IOMAP_MSK(n)		(0xf << (IOMAP_MSK_POS(n)))


/******************************************************************************
*UREGx: User Register Operation, only reset after POR
******************************************************************************/
typedef enum{
	USER_REG0			= 0,
	USER_REG1,
	USER_REG2,
	USER_REG3,
}user_reg_e;

/******************************************************************************
*DBGCR: Debug Port Control Register, only reset by power on reset
******************************************************************************/
#define SWD_LOCK			0
#define SWD_UNLOCK			0x5a







/***********************************************************************
 
 * SYSCON related Function Declaration
 * 
 * *********************************************************************/

/** \brief Deinitializes SYSCON registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */   
void syscon_deinit(void);

 
/** \brief EMOSC configuration: workmode/filter/gain/stablization counter
 * 
 *  \param[in] hwEMCnt: 0~0x3FF, the bigger the num, the slower the stablization time
 *  \param[in] byEMGain: 0~0x1F, the faster the Femosc, the larger the gain
 *  \param[in] eEmWkMd: EM_HIGHF/EM_LOWF \ref em_lfsel_e
 *  \param[in] eEMFltEnable: ENABLE/DISABLE \ref functional_status_e
 *  \param[in] eEMFlt: EM_FLSEL_5NS~EM_FLSEL_20NS \ref em_fltsel_e
 *  \return none
 */ 
void syscon_emosc_configure(U16_T hwEmCnt, U8_T byEmGain ,em_lfsel_e eEmWkMd, functional_status_e eEmFltEnable, em_fltsel_e eEMFlt);


/** \brief Enable OSC
 * 
 *  \param[in] eOscEnable:ENDIS_ISOSC/ENDIS_IMOSC/ENDIS_EMOSC/ENDIS_PLL \ref osc_enable_e
 *  \return none
 */
void syscon_osc_enable(osc_enable_e eOscEnable );


/** \brief Disable OSC
 * 
 *  \param[in] eOscEnable:ENDIS_ISOSC/ENDIS_IMOSC/ENDIS_EMOSC/ENDIS_PLL \ref osc_enable_e
 *  \return none
 */
void syscon_osc_disable(osc_enable_e eOscEnable );


/** \brief PLL configuration
 *  \param[in] eType: PLL_TYPE_ANA/PLL_TYPE_DIG \ref pll_type_e
 *  \param[in] eSrc: PLL_SRC_IMOSC/PLL_SRC_EMOSC \ref pll_src_e
 *  \param[in] eUnlockRst: \ref pll_rst_e
 *  \return none
 */
void syscon_pll_configure(pll_type_e eType, pll_src_e eSrc, pll_rst_e eUnlockRst);


/** \brief PLL configuration
 *  WARNING: This function can only be safely called when changing hclk frequence from low to high.
 * 			 Call systemclk_clear() first when change hclk frequence from high to low
 *  \param[in] eSysclk: select system clock srouce \ref sycclk_sel_e
 *  \param[in] eHclkDiv: select HCLK DIV. HCLK = systemclock/eHclkDiv \ref hclk_div_e
 *  \param[in] ePclkDiv: select PCLK DIV. PCLK = HCLK/eHclkDiv \ref pclk_div_e
 *  \param[in] eFreq:  HCLK clock frequence range \ref sysclk_freq_e
 *  \return none
 */
void syscon_hclk_pclk_configure(sycclk_sel_e eSysclk , hclk_div_e eHclkDiv , pclk_div_e ePclkDiv , sysclk_freq_e eFreq);


/** \brief Set sysclk to a lower frequence: HCLK = IMOSC/3 = 8MHz
 * 	 Call this function first when change hclk frequence from high to low
 *  \return none
 */
void sysclk_clear(void);

/** \brief IWDT enable 
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_enable(void);


/** \brief IWDT disable 
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_disable(void);


/** \brief IWDT reload， feed IWDT
 *  \param[in]none
 *  \return none
 */
void syscon_iwdt_reload(void);



/** \brief config IWDT interval time and overtime time 
 *  \param[in] eOvTime: overtime(reset) time \ref iwdt_ovt_e
 * 	\param[in] eIntvTime: interval(interrupt) time \ref iwdt_intv_e
 *  \return none
 */

void syscon_iwdt_config(iwdt_ovt_e eOvTime , iwdt_intv_e eIntvTime );


/** \brief LVR confiuration
 *  \param[in] eLvdEnable: LVD IP enable/disable \ref functional_status_e
 * 	\param[in] eLvd: LVD interrupt level \ref lvd_level_e
 *  \param[in] eLvr: LVR reset level  \ref 	lvr_level_e
 *  \param[in] ePol: interrupt polarity \ref lvdint_pol_e
 *  \return none
 */
void syscon_lvd_configure(functional_status_e eLvdEnable , lvd_level_e eLvd , lvr_level_e eLvr, lvdint_pol_e ePol);



/** \brief LVD interrupt enable
 *  \param[in] none
 *  \return none
 */

void syscon_lvd_int_enable(void);


/** \brief LVD interrupt disable
 *  \param[in] none
 *  \return none
 */
void syscon_lvd_int_disable(void);


/** \brief IWDT interrupt enable
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_int_enable(void);


/** \brief IWDT interrupt disable
 *  \param[in] none
 *  \return none
 */
void syscon_iwdt_int_disable(void);


/** \brief read reset srouce
 *  \param[in] none
 *  \return reset source
 */
U32_T syscon_read_reset_src(void);



/** \brief external interrupt configuration
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] byExiGrpNum: EXI group number \ref exi_igrp_e
 *  \param[in] eMode: falling/rising/both falling and risiing \ref exi_trigger_e
 *  \return none
 */
void syscon_exi_trigger_cmd(functional_status_e eNewState , exi_igrp_e eExiGrpNum , exi_trigger_e eMode);



/** \brief external interrupt enable, disable control
 *  \param[in] eNewState: ENABLE/DISABLE
 *  \param[in] byExiGrpNum: EXI group number \ref exi_igrp_e
 *  \return none
 */

void syscon_exi_interrupt_cmd(functional_status_e eNewState , exi_igrp_e eExiGrpNum);




/** \brief chip enter idle mode: CPU clock shuts down
 *  \param[in] none
 *  \return none
 */
void pm_goto_idle_mode(void); 

/** \brief chip enter deepsleep(stop) mode: CPU clock shuts down && PCLK shuts down exception for some specific wakeup source IPs
 *  \param[in] none
 *  \return none
 */
void pm_goto_deepsleep_mode(void);

/**
  \brief     Config the wakeup source
   * 		 EXI always exists as wakeup sources, no need to config here
  \param[in] eNewState: ENABLE/DISABLE
  \param[in] eWkupSrc: a specific wakeup source
  \return    none
*/
void pm_set_wakeup_src(functional_status_e eNewState, wakeup_src_e eWkupSrc);


/**
  \brief     CLO configuration
  \param[in] eSrc: clock source of CLO \ref clo_src_e
  \param[in] eDiv: CLO output div \ref clo_div_e
  \return    none
*/
void syscon_clo_configure(clo_src_e eSrc,clo_div_e eDiv);



/**
  \brief     system reset
  \param[in] none
  \return    none
*/
void syscon_software_reset(void);

/**
  \brief     set all interrupt priority to lowest level)
  \param[in] none
  \return    none
*/
void SYSCON_INT_Priority(void);

#define SET_INT_PRIORITY csi_vic_set_prio


/**
  \brief     Config IO Remap
  \param[in] none
  \return    none
*/
void syscon_ioremap(U8_T byIndex, ioremap_e eCfgVal);


/** \brief Write User Registers
 *   UREG0~1 : 32bit
 *   UREG2~3 ：16bit
 *  \param[in] eUreg: UREG0~3
 *  \param[in] wValue: value to be written
 *  \return error code
 */
void syscon_ureg_write(user_reg_e eUreg, U32_T wValue);
/** \brief Read User Registers
 * 
 *  \param[in] eUreg: UREG0~2
 *  \return value being read out
 */
U32_T syscon_ureg_read(user_reg_e eUreg);

/** \brief SWD Lock
 * 
 *  \param[in]  none
 *  \return  none
 */
void syscon_swd_lock(void);

/** \brief SWD Unlock
 * 
 *  \param[in]  none
 *  \return  none
 */
void syscon_swd_unlock(void);

/** \brief configure wakeup source 
 *  \param[in] eWkupSrc: wakup source \ref syscon_wksrc_e
 *  \param[in] eNewState: ENABLE/DSIABLE
 *  \return  none
 */
void pm_wakupsrc_cmd(syscon_wksrc_e eWkupSrc, functional_status_e eNewState);

/** \brief SYSCON interrupt enable
 *  \param[in] eIntSrc :interrupt source \ref syscon_int_e
 *  \return none
 */
void syscon_int_enable(syscon_int_e eIntSrc);

/** \brief SYSCON interrupt disable
 *  \param[in] eIntSrc :interrupt source \ref syscon_int_e
 *  \return none
 */
void syscon_int_disable(syscon_int_e eIntSrc);

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/


#endif   /**< _SYSCON_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/