/***********************************************************************//**
 * \file  adc.h
 * \brief  ADC description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-16 <td>V1_3_0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ADC_H
#define _ADC_H

/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"

/// \struct csp_adc_t
/// \brief ADC Reg Description
 typedef struct
 {
    __OM   U32_T  ECR;		//0x0000 Clock Enable Register             
    __OM   U32_T  DCR;       //0x0004 Clock Disable Register            
    __IM   U32_T  PMSR;      //0x0008 Power Management Status Register  
    __IM   U32_T  _RSVD0;
    __IOM  U32_T  CR;        //0x0010 Control Register                  
    __IOM  U32_T  MR;        //0x0014 Mode Register                     
    __IOM  U32_T  SHR;		//0x0018 Sample Hold Period Register
    __OM   U32_T  CSR;       //0x001C Clear Status Register             
    __IM   U32_T  SR;        //0x0020 Status Register                   
    __IOM  U32_T  IER;      //0x0024 Interrupt Enable Register         
    __OM   U32_T  IDR;     //0x0028 Interrupt Disable Register        
    __IM   U32_T  IMR;      //0x002C Interrupt Enable Status Register           
    __IOM  U32_T  SEQ[8];   //0x0030~4C Conversion Mode Register 0~11    
	__IM   U32_T  _RSVD1[8];  //0x0050~6C
    __IOM  U32_T  PRI;       //0x0070 Conversion Priority Register      
    __IOM  U32_T  TDL0;      //0x0074 Trigger Delay control Register    
    __IOM  U32_T  TDL1;      //0x0078 Trigger Delay control Register    
    __IOM  U32_T  SYNCR;     //0x007C Sync Control Register             
    __IM   U32_T  RSVD2[2];         
    __IOM  U32_T  EVTRG;     //0x0088 Event Trigger Control  Register        
    __IOM  U32_T  RSVD3[29];
    __IM   U32_T  DR[8];    //0x0100~11C Convert Data Register             
    __IM  U32_T  _RSVD4[10];    //0X120~0X144
	__IOM  U32_T  DRMASK;	//0x0148 Disable Conversion Data Updata Register
 } csp_adc_t;
 
#define ADC_DCR_RST 	0x2
#define ADC_CR_RST 0x80000800
#define ADC_MR_RST 0x1
#define ADC_SHR_RST 0x3
#define ADC_SEQ_RST 0x9F
#define ADC_RST 0
 
/******************************************************************************
* TS : Temperature sensor Registers
******************************************************************************/
#define CALIBRATION_TS1  *((uint32_t *)(0x00080140))
#define CALIBRATION_IR1  *((uint32_t *)(0x00080144))
#define CALIBRATION_TS2  *((uint32_t *)(0x00080180))
#define CALIBRATION_IR2  *((uint32_t *)(0x00080184))

/******************************************************************************
* ECR, DCR, PMSR : ADC Power Management Registers
******************************************************************************/

#define ADC_IPIDCODE_MSK  	(0x3FFFFFFul << 4)

typedef enum{
	ADC_CLKEN=(0x01ul << 1) ,
	ADC_DBGEN  =(0x01ul << 31)
} adc_clk_e;

/******************************************************************************
* CR : ADC Control Register
******************************************************************************/
typedef enum{
	ADC_SWRST	= (0x1 << 0) ,           
	ADC_ADCEN  = (0x1 << 1),            
	ADC_ADCDIS = (0x1 << 2) ,           
	ADC_START 	= (0x1 << 3)  ,         
	ADC_STOP    =  (0x1 << 4)  ,
	ADC_SWTRG = (0x1 << 5)
} adc_control_e;


#define ADC_VREF_POS 		(6) 
#define ADC_VREF_MSK 		(0x0ful << ADC_VREF_POS) 
typedef enum{
	ADC_VERF_VDD_VSS 		= 	(0x00ul),
	ADC_VREF_VREFP_VSS		= 	(0x01ul),
	ADC_VREF_INTVREF_VSS	= 	(0x02ul),
	ADC_VREF_VDD_VREFN	= 	(0x03ul),
	ADC_VREF_VREFP_VREFN	= 	(0x04ul),
	ADC_VREF_INTVREF_VREFN	= 	(0x08ul),
}adc_vref_e;

#define ADC_INTVREF_OUTEN_POS	(16)
#define ADC_INTVREF_OUTEN_MSK	(0x1 <<ADC_INTVREF_OUTEN_POS)

typedef enum {
	ADC_INTVREF_OUT_DIS =0,
	ADC_INTVREF_OUT_EN
}adc_intvref_out_e;


#define ADC_INTVREF_LVL_POS	(17)
#define ADC_INTVREF_LVL_MSK	(0x1 <<ADC_INTVREF_LVL_POS)

typedef enum {
	ADC_INTVREF_LVL_1V2 =0,
	ADC_INTVREF_LVL_2V5
}adc_intvref_lvl_e;


#define ADC_ACCURACY_POS 		(31) 
#define ADC_ACCURACY_12BIT		(0x01ul << ADC_ACCURACY_POS) 


/******************************************************************************
* MR : ADC Mode Register
******************************************************************************/
#define ADC_PRLVAL_POS      (0) 
#define ADC_PRLVAL_MASK     (0x1Ful << ADC_PRLVAL_POS)  
#define ADC_NBRCH_POS       (10)      			    
#define ADC_NBRCH_MSK       (0x7ul << ADC_NBRCH_POS) 

#define ADC_MODE_POS 			(31) 
#define ADC_MODE_MSK 		(0x01ul << ADC_MODE_POS) 
typedef enum{
	ADC_MODE_ONESHOT		=   (0x00ul),
	ADC_MODE_CONTINUE		= 	(0x01ul),
}adc_runmode_e;

/******************************************************************************
* SHR : ADC Sample hode Registers 
******************************************************************************/
#define ADC_SHR_POS	 		(0)
#define ADC_SHR_MSK	 		(0xFFul << ADC_SHR_POS)

/******************************************************************************
* CSR, SR, IMCR, MISR : ADC Status Registers and Interrupt Registers
******************************************************************************/
#define ADC_SEQ_POS(n)			(16+n)
#define ADC_SEQ_MSK(n) 		(0x1 << ADC_SEQ_POS(n))

#define ADC_SEQ_IDX_POS		(10)
#define ADC_SEQ_IDX_MSK 	(0x0F << ADC_SEQ_IDX_POS)

typedef enum{
	ADC_EOC				= 	(0x01uL << 0),
	ADC_READY			= 	(0x01uL << 1),
	ADC_OVR				= 	(0x01uL << 2),
	ADC_ADCENS    		= 	(0x01uL << 8),  		
	ADC_CTCVS     		= 	(0x01uL << 9), 				
	ADC_SEQ0			= 	(0x01uL << 16),			
	ADC_SEQ1  			= 	(0x01uL << 17),     
	ADC_SEQ2  			= 	(0x01uL << 18),     
	ADC_SEQ3  			= 	(0x01uL << 19),     
	ADC_SEQ4  			= 	(0x01uL << 20),     
	ADC_SEQ5  			= 	(0x01uL << 21),     
	ADC_SEQ6 	 		= 	(0x01uL << 22),     
	ADC_SEQ7  			= 	(0x01uL << 23),     
}adc_sr_e;

typedef enum{
	ADC_INT_EOC			= 	(0x01uL << 0),
	ADC_INT_READY		= 	(0x01uL << 1),
	ADC_INT_OVR			= 	(0x01uL << 2),
	ADC_INT_SEQ0			= 	(0x01uL << 16),			
	ADC_INT_SEQ1  		= 	(0x01uL << 17),     
	ADC_INT_SEQ2  		= 	(0x01uL << 18),     
	ADC_INT_SEQ3  		= 	(0x01uL << 19),     
	ADC_INT_SEQ4  		= 	(0x01uL << 20),     
	ADC_INT_SEQ5  		= 	(0x01uL << 21),     
	ADC_INT_SEQ6 	 	= 	(0x01uL << 22),     
	ADC_INT_SEQ7  		= 	(0x01uL << 23),     
}adc_int_e;

/******************************************************************************
* SEQx : ADC Conversion Mode Register
******************************************************************************/
#define ADC_AIN_POS		(0)
#define ADC_AIN_MSK	   	(0x1Ful << ADC_AIN_POS)
typedef enum{
	ADC_ADCINA0		= 0x0,
	ADC_ADCINA1,
	ADC_ADCINA2,
	ADC_ADCINA3,
	ADC_ADCINA4,
	ADC_ADCINA5,
	ADC_ADCINA6,
	ADC_ADCINA7,
	ADC_ADCINA8,
	ADC_ADCINA9,
	ADC_ADCINA10,
	ADC_ADCINA11,
	ADC_INTVREF = 0x1C,
	ADC_ADCIN_1_5VDD = 0x1D,
	ADC_ADCIN_VSS
}adc_ainsel_e;


#define ADC_SYNCSRC_POS			(17)
#define ADC_SYNCSRC_MSK		(0x07ul << ADC_SYNCSRC_POS)
typedef enum{
	ADC_SYNC_NONE		= 0,
	ADC_SYNC_SWTGR		,
	ADC_SYNC_SRC0		,
	ADC_SYNC_SRC1		,
	ADC_SYNC_SRC2		,
	ADC_SYNC_SRC3		,
	ADC_SYNC_SRC4		,
	ADC_SYNC_SRC5		
}adc_sync_source_e;

/******************************************************************************
* DR : ADC Convert Data Register
******************************************************************************/
#define ADC_DATA_POS      	(0)    
#define ADC_DATA_MASK     	(0xFFFul << ADC_DATA_POS)   

/******************************************************************************
* PRI: SDC Convert Priority Select Register
******************************************************************************/
#define ADC_PRI_POS		(0)
#define ADC_PRI_MSK		(0x0ful <<ADC_PRI_POS)

/******************************************************************************
* TDLx : ADC Trigger Delay Control Register
******************************************************************************/
#define ADC_TDL_SOC0_3_MSK	(0xfful)
#define ADC_TDL_SOC1_4_MSK	(0xfful<<8)
#define ADC_TDL_SOC2_5_MSK	(0xfful<<16)
//#define ADC_SOC0_TDL(val)   (((val) & 0xff) << 0)
//#define ADC_SOC1_TDL(val)   (((val) & 0xff) << 8)
//#define ADC_SOC2_TDL(val)   (((val) & 0xff) << 16)
//#define ADC_SOC3_TDL(val)   (((val) & 0xff) << 0)
//#define ADC_SOC4_TDL(val)   (((val) & 0xff) << 8)
//#define ADC_SOC5_TDL(val)   (((val) & 0xff) << 16)

/******************************************************************************
* SYNCR
******************************************************************************/
#define ADC_SYNC_POS(n)		(0 + n)
#define ADC_SYNC_MSK(n)		(0x01ul << ADC_SYNC_POS(n))
typedef enum{
	ADC_SYNCEN0			= 0,
	ADC_SYNCEN1,		
	ADC_SYNCEN2,	
	ADC_SYNCEN3,	
	ADC_SYNCEN4,		
	ADC_SYNCEN5,
}adc_sync_in_e;

#define ADC_OSTMD_POS(n)	(8 + n)
#define ADC_OSTMD_MSK(n)	(0x01ul << ADC_OSTMD_POS(n))
typedef enum{
	ADC_OSTMD_CONTINUE = 0,
    ADC_OSTMD_ONCE   				
}adc_ostmd_e;

#define ADC_REARM_POS(n)	(16 + n)
#define ADC_REARM_MSK(n) 	(0x01 << ADC_REARM_POS(n))
#define ADC_REARM_EN		(0x01ul)
/******************************************************************************
* EVTRG 
******************************************************************************/
typedef enum{
	ADC_TRGSRC_NONE			= 0,
	ADC_TRGSRC_EOC,		
	ADC_TRGSRC_READY,	
	ADC_TRGSRC_OVR,	
	ADC_TRGSRC_SEQEND0,	
	ADC_TRGSRC_SEQEND1,
	ADC_TRGSRC_SEQEND2,	
	ADC_TRGSRC_SEQEND3,
	ADC_TRGSRC_SEQEND4,	
	ADC_TRGSRC_SEQEND5,
	ADC_TRGSRC_SEQEND6,	
	ADC_TRGSRC_SEQEND7,
}adc_evtrg_src_e;

typedef enum{
	ADC_TRG0_SEL			= 0,
	ADC_TRG1_SEL		
}adc_evtrg_out_e;

#define ADC_TRGSRC0_POS			(0)
#define ADC_TRGSRC0_MSK		(0x1Ful << ADC_TRGSRC0_POS)
#define ADC_TRGSRC1_POS			(8)
#define ADC_TRGSRC1_MSK		(0x1Ful << ADC_TRGSRC1_POS)
#define ADC_TRGSRC_POS(n)		(8 * (n))
#define ADC_TRGSRC_MSK(n)		(0x1Ful << ADC_TRGSRC_POS(n))

#define ADC_TRG0OE       		(0x01ul <<20)
#define ADC_TRG1OE       		(0x01ul <<21)
#define ADC_TRGOE_POS(n)      	(20 + (n))
#define ADC_TRGOE_MSK(n) 		(0x01ul << ADC_TRGOE_POS(n)) 

/******************************************************************************
* DRMASK
******************************************************************************/
#define ADC_DRMASK_POS(n)	 (n)
#define ADC_DRMASK(n)			(0x1ul <<ADC_DRMASK_POS(n))

/******************************************************************************
********************* ADC Functions Declaration **********************
******************************************************************************/
/** \brief adc deinit 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 * 			   
 *  \return none
 */ 
void adc_deinit(csp_adc_t *ptAdcBase);

/** \brief adc control :enable ,disable ,start /stop, swrst, swtrg
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eCmd:  ADC control command: enable ,disable ,start /stop, swrst, swtrg \ref adc_control_e
 * 			   
 *  \return none
 */ 
void adc_control(csp_adc_t *ptAdcBase, adc_control_e eCmd );

  /** \brief adc int enable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return none
 */ 
void adc_int_enable( csp_adc_t *ptAdcBase, adc_int_e eInt);

/** \brief adc int disable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return none
 */ 
void adc_int_disable( csp_adc_t *ptAdcBase, adc_int_e eInt);

/** \brief read adc interrupt enable status
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eInt:  adc interrupt select  \ref adc_int_e
 * 			   
 *  \return ENABLE or DISABLE
 */ 
uint8_t adc_read_inten_status(csp_adc_t *ptAdcBase,adc_int_e eInt);

/** \brief read adc clk/debug enable/disable control
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eAdcClk:  adc clk or debug select \ref adc_clk_e
 *  \param[in] bState:  State to be set	
 *		   
 *  \return none
 */  
void adc_clk_debug_configure(csp_adc_t *ptAdcBase, adc_clk_e eAdcClk , bool bState);

/** \brief adc software reset
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */   
void adc_software_reset(csp_adc_t *ptAdcBase);

/** \brief adc analog module enable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_enable(csp_adc_t *ptAdcBase);

/** \brief adc analog module disable 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_disable(csp_adc_t *ptAdcBase);

/** \brief  wait for adc ready singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_ready_wait(csp_adc_t *ptAdcBase)  ;

/** \brief  wait for adc end of convert (EOC) singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *		   
 *  \return none
 */ 
void adc_eoc_wait(csp_adc_t *ptAdcBase) ;

/** \brief  wait for adc SEQx end of convert  singal 
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byCh:  SEQ No.  range :0~0x7
 *		   
 *  \return none
 */ 
void adc_seqend_wait(csp_adc_t *ptAdcBase,U8_T byCh);

/** \brief  read one channel  of DRx
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byCh:  DR No.  range :0~0x7
 *		   
 *  \return none
 */ 
U16_T adc_data_output(csp_adc_t *ptAdcBase, U8_T byCh );

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
void  adc_mode_configure(csp_adc_t *ptAdcBase, adc_runmode_e  eMode  , U8_T byPriorty, U8_T byShr , U8_T PreDiv , U8_T byNbrch ) ;

/** \brief  adc reference voltage configure
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eVref:  voltage reference select \ref adc_vref_e
 *  \param[in] eInvrefLvl:  internal voltage reference level \ref adc_intvref_lvl_e
 *	   
 *  \return none
 */ 
void adc_vref_configure(csp_adc_t *ptAdcBase,  adc_vref_e eVref, adc_intvref_lvl_e eInvrefLvl );

/** \brief  adc seqx  analog input configure
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eAinSel:  adc analog input channel  \ref adc_ainsel_e
 *  \param[in] bySeq:  seq no. range :0~7
 *	   
 *  \return none
 */ 
void adc_ain_configure(csp_adc_t *ptAdcBase, adc_ainsel_e eAinSel , U8_T bySeq);

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
void adc_set_sync(csp_adc_t *ptAdcBase, adc_sync_source_e eSyncSrc, U8_T bySeq, adc_sync_in_e eSyncIn, adc_ostmd_e eOstMd, uint8_t byDelay);

/** \brief rearm adc sync
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] eSyncIn: adc sync evtrg input channel(0~5)
 *  \return none
 */
void adc_sync_rearm(csp_adc_t *ptAdcBase, adc_sync_in_e eSyncIn);

/** \brief set adc evtrg output
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \param[in] eTrgSrc: adc evtrg source(0~23) 
 *  \param[in] byPeriod: The event triggers the count 
 *  \return none
 */
void  adc_set_evtrg(csp_adc_t *ptAdcBase, adc_evtrg_src_e eTrgSrc, adc_evtrg_out_e eTrgOut);

/** \brief  adc evtrg enable
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \return none
 */
void  adc_evtrg_enable(csp_adc_t *ptAdcBase,adc_evtrg_out_e eTrgOut);

/** \brief  adc evtrg disable
 * 
 *  \param[in] ptAdcBase: pointer of adc register structure
 *  \param[in] byTrgOut: adc evtrg out port (0~1)
 *  \return none
 */
void  adc_evtrg_disable(csp_adc_t *ptAdcBase,adc_evtrg_out_e eTrgOut);

#endif

