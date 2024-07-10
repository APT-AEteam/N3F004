/***********************************************************************//** 
 * \file  cmp.h
 * \brief  gpio description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CMP_H
#define _CMP_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"


/******************************************************************************
* CMP Register Structure
******************************************************************************/
typedef struct
{
   __IOM U32_T  CEDR;  		//0x0000	Clock control & ID
   __IOM U32_T  CR;		    //0x0004	Start & Stop Ctrl
   __IOM U32_T  DFCR1;		//0x0008	Digital filter 1 control register 
   __IOM U32_T  HWFCR; 		//0x000C	Digital filter 2 control register 
   __IOM U32_T  SWFCR;		//0x0010	control register
   __IOM U32_T  INPCR;   	//0x0014	Input control register
   __IM  U32_T  RISR;      	//0x0018    Interrupt RISR
   __IOM U32_T  IMCR;       //0x001c    Interrupt IMCR
   __IM  U32_T  MISR;       //0x0020    Interrupt MISR
   __OM  U32_T  ICR;        //0x0024    Interrupt clear
} csp_cmp_t;
 

/******************************************************************************
* CEDR : Clock control, IP Reset and ID Code
******************************************************************************/
#define	CMP_IDCODE_POS			(8)
#define	CMP_IDCODE_MSK			(0xFFFFFFul << CMP_CLK_POS)

#define	CMP_SWRST_POS           (7)
#define CMP_SOFTRESET           (0x01<<CMP_SWRST_POS)

#define	CMP_CLK_POS			    (0)
#define	CMP_CLK_MSK			    (0x01ul << CMP_CLK_POS)
#define	CMP_CLK_EN			    (0x01ul << CMP_CLK_POS)

/******************************************************************************
* CR : Start & Stop Ctrl
******************************************************************************/
#define	CMP_EN_POS	        (0)
#define	CMP_EN_MSK		    (0x01ul << CMP_EN_POS)
#define	CMP_EN		    	(0x01ul << CMP_EN_POS)


#define	CMP_AEN_POS	        (0)
#define	CMP_AEN_MSK		    (0x01ul << CMP_AEN_POS)
typedef enum
{
	CMP_ADIS	= 0x00,
	CMP_AEN,				
}cmp_aen_e;


#define	CMP_PHYST_POS	    (2)
#define	CMP_PHYST_MSK		(0x1ul << CMP_PHYST_POS)
typedef enum
{
	PHYST_0MV	= 0x00,
	PHYST_10MV,			
}cmp_physt_e;

#define	CMPO_POL_POS		(6)
#define	CMPO_POL_MSK		(0x01ul << CMPO_POL_POS)
typedef enum
{
    CMPO_DIRECT     = 0x00,
	CMPO_REVERSE            
}cmpout_pol_e;

#define	CMP_TRGOE_POS		    (7)
#define	CMP_TRGOE_MSK		    (0x01ul << CMP_TRGOE_POS)
typedef enum
{
	TRGOE_DIS	= 0x00,
	TRGOE_EN,				
}cmp_trgoe_e;

#define	CMPIN_POL_POS		    (8)
#define	CMPIN_POL_MSK		    (0x03ul << CMPIN_POL_POS)
typedef enum
{
	CMPIN_POL_F	= 0x00,
	CMPIN_POL_R,
	CMPIN_POL_BOTH,
}cmpin_pol_e;

#define	CMP_DF1EN_POS		    (10)
#define	CMP_DF1EN_MSK		    (0x01ul << CMP_DF1EN_POS)

#define	CMP_HWFEN_POS		    (11)
#define	CMP_HWFEN_MSK		    (0x01ul << CMP_HWFEN_POS)

#define	CMP_SWFEN_POS		    (12)
#define	CMP_SWFEN_MSK		    (0x01ul << CMP_SWFEN_POS)

#define	CMP_SWFALIGN_POS		(13)
#define	CMP_SWFALIGN_MSK		(0x01ul << CMP_SWFALIGN_POS)

#define	CMP_HWFALIGN_POS		(14)
#define	CMP_HWFALIGN_MSK		(0x01ul << CMP_HWFALIGN_POS)

typedef enum
{
	NEW_TRG_INVALID    = 0x00,
	NEW_TRG_VALID             
}cmp_wf_align_e;


#define	CMP_WFENDEVT_POS	    (15)
#define	CMP_WFENDEVT_MSK	    (0x03ul << CMP_WFENDEVT_POS)
typedef enum
{
	END_SW      = 0x00,
	END_HW,
	END_BOTH                
	
}cmp_wf_endevt_e;


#define	CMP_NHYST_POS	    (18)
#define	CMP_NHYST_MSK		(0x03ul << CMP_NHYST_POS	)
typedef enum
{
	NHYST_0MV	= 0x00,
	NHYST_10MV,			
}cmp_nhyst_e;

#define	CMP_CPOSEL_POS		    (23)
#define	CMP_CPOSEL_MSK		    (0x01ul << CMP_CPOSEL_POS)

typedef enum
{
	CPO_FLT_BYPASS		      = 0x00,
	CPO_FLT_OUT				         
}cmp_cposel_e;

#define	CMP_CPOUT0_POS		    (24)
#define	CMP_CPOUT0_MSK		    (0x01ul << CMP_CPOUT0_POS)

#define	CMP_CPOUT1_POS		    (25)
#define	CMP_CPOUT1_MSK		    (0x01ul << CMP_CPOUT1_POS)

#define	CMP_CPOUT_ALL_POS		(24)
#define	CMP_CPOUT_ALL_MSK		(0x0fful << CMP_CPOUT_ALL_POS)
/******************************************************************************
* DFCR1 : Digital Filter 1 Control Register 
******************************************************************************/
#define	CMP_DF1_DEPTH_POS		    (0)
#define	CMP_DF1_DEPTH_MSK		    (0x07ul << CMP_DF1_DEPTH_POS)
typedef enum
{
	DEPTH1_8        =   0,
	DEPTH1_16       =   1,
	DEPTH1_32       =   2,
	DEPTH1_64       =   3,
	DEPTH1_128      =   4,
	DEPTH1_256      =   5,
	DEPTH1_512      =   6,
	DEPTH1_1024     =   7
}cmp_df_depth_e;

#define	CMP_DF1_DIVN_POS		    (16)
#define	CMP_DF1_DIVN_MSK		    (0x1ful << CMP_DF1_DIVN_POS)

#define	CMP_DF1_DIVM_POS		    (8)
#define	CMP_DF1_DIVM_MSK		    (0xfful << CMP_DF1_DIVM_POS)


/******************************************************************************
* HWFCR/SWFCR : Hard/Soft Window Control Register 
******************************************************************************/
#define	CMP_WCNT_POS		    (0)
#define	CMP_WCNT_MSK		    (0xfful << CMP_WCNT_POS)

#define	CMP_WF_DIVN_POS		    (16)
#define	CMP_WF_DIVN_MSK		    (0x1ful << CMP_WF_DIVN_POS)

#define CMP_SWFORCE_POS			(16)
#define CMP_SWFORCE_MSK			(0x1ul << CMP_SWFORCE_POS)

/******************************************************************************
* INPCR : 
******************************************************************************/
//CMP_INPCR register
#define	CMP_NSEL_SET_POS		    (0)
#define	CMP_NSEL_SET_MSK		    (0x1ful << CMP_NSEL_SET_POS)
typedef enum
{
	
	NSEL_CP1       =  0,
	NSEL_CP2,
	NSEL_CP3,	
	NSEL_CP4,
	NSEL_INTREF1,
	NSEL_INTREF2,
	NSEL_INTREF3,
	NSEL_INTREF4,
	NSEL_INTREF5,
	NSEL_INTREF6,
	NSEL_INTREF7,
	NSEL_INTREF8,
	NSEL_INTREF9,
	NSEL_INTREF10,
	NSEL_INTREF11,
	NSEL_INTREF12,
	NSEL_INTREF13,
	NSEL_INTREF14,
	NSEL_INTREF15,
	NSEL_INTREF16
}nsel_e;

#define	CMP_PSEL_SET_POS		    (8)
#define	CMP_PSEL_SET_MSK		    (0x3ul << CMP_PSEL_SET_POS)
typedef enum
{
	PSEL_CP1       = 0,
	PSEL_CP2,
	PSEL_CP3,	
	PSEL_CP4,
}psel_e;

#define	CMP_PSEL_RD_POS		    (11)
#define	CMP_PSEL_RD_MSK		    (0x3ul << CMP_PSEL_SET_POS)

#define	CMP_REFSEL_POS		    (23)
#define	CMP_REFSEL_MSK		    (0x1ul << CMP_REFSEL_POS)
typedef enum
{
	CMP_VREF_INTERNAL = 0,
	CMP_VREF_VDD
}cmp_vref_e;

#define	CMP_INTBEMF_ENABLE_POS	 (25)
#define	CMP_INTBEMF_ENABLE_MSK	 (0x1ul << CMP_INTBEMF_ENABLE_POS)

/******************************************************************************
* RISR/MISR : Interrupt Raw/Masked Status Register
******************************************************************************/
#define	CMP_EDGEDET0_POS		     (0)
#define	CMP_EDGEDET0_MSK		     (0x1ul << CMP_EDGEDET0_POS)

#define	CMP_EDGEDET1_POS		     (1)
#define	CMP_EDGEDET1_MSK		     (0x1ul << CMP_EDGEDET1_POS)

#define	CMP_WINDEND0_POS		     (8)
#define	CMP_WINDEND0_MSK		     (0x1ul << CMP_WINDEND0_POS)

#define	CMP_WINDEND1_POS		     (9)
#define	CMP_WINDEND1_MSK		     (0x1ul << CMP_WINDEND1_POS)

/******************************************************************************
* IMCR/ICR : Interrupt Control Register/Interrupt Clear Register
******************************************************************************/
#define	CMP_EDGEDET_POS		     (0)
#define	CMP_EDGEDET_MSK		     (0x1ul << CMP_EDGEDET_POS)

#define	CMP_WEND_POS		     (1)
#define	CMP_WEND_MSK		     (0x1ul << CMP_WEND_POS)
typedef enum
{
	CMP_EDGEDET_INT      = 0, 
	CMP_WIEND_INT   	
}cmp_int_e;

/******************************************************************************
* CMP Related Function Declaration
******************************************************************************/

#endif /**< CMP_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/