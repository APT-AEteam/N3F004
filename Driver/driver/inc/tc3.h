/***********************************************************************
 * \file  tc3.h
 * \brief  tc3 description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-18 <td>V1_3_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TC3_H
#define _TC3_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"


/// \struct csp_tc3_t
/// \brief TC3 reg description
typedef struct
{
	__IM     U32_T  IDR;			//0x0000	ID code register		 
	__IOM  U32_T  CSSR;		//0x0004	clock source select register 
	__IOM  U32_T  CEDR; 		//0x0008	clock enable/disable control register 
	__IOM  U32_T  SRR;			//0x000C	software reset register 
	__IOM  U32_T  CR;			//0x0010	control register         
	__IOM  U32_T  PRDR;		//0x0014	period setting register    
	__OM 	 U32_T  TIMDR;	//0x0018	timer data register   
	__IOM  U32_T  IMCR;		//0x001C	interrupt enable control register  
	__IM     U32_T  RISR;		//0x0020	raw Interrupt status register 
    __IM  	 U32_T  MISR;       //0x0024    mask interrupt status register
	__OM   U32_T  ICR;			//0x0028	interrupt clear register
} csp_tc3_t;

/******************************************************************************
* TC3 Registers RST  Value
******************************************************************************/

#define   TC3_CSSR_RST        (0x00000001)				/**< CSSR reset value    */
#define 	TC3_PRDR_RST		(0x00000001)				/**< PRDR reset value    */
#define 	TC3_RST_VALUE		(0x00000000)				/**< TIMDR reset value   */

/******************************************************************************
* CSSR : TC3 clock source select register
******************************************************************************/
typedef enum{
	TC3_CLKSRC_EMOSC = 0,
	TC3_CLKSRC_ISOSC
}tc3_clksrc_e;

/******************************************************************************
* CEDR : TC3 clock enable/disable register
******************************************************************************/
#define TC3_CLKEN_POS 	0
#define TC3_CLKEN_MSK	(0x1ul <<TC3_CLKEN_POS)
#define TC3_CLKEN	(0x1ul <<TC3_CLKEN_POS)

#define TC3_DBGEN_POS 	1
#define TC3_DBGEN_MSK	(0x1ul <<TC3_DBGEN_POS)
#define TC3_DBGEN	(0x1ul <<TC3_DBGEN_POS)

/******************************************************************************
* SRR : TC3 software reset register
******************************************************************************/
#define TC3_SOFTWARE_RST	(0x1ul )

/******************************************************************************
* CR : TC3 control register
******************************************************************************/
#define TC3_WTEN_POS 		0
#define TC3_WTEN_MSK		(0x1ul <<TC3_WTEN_POS)
#define TC3_WTEN					(0x1ul <<TC3_WTEN_POS)

#define TC3_BCSDIV_POS 		1
#define TC3_BCSDIV_MSK		(0x3Ful <<TC3_BCSDIV_POS)

#define TC3_MODE_POS 		7
#define TC3_MODE_MSK		(0x1ul <<TC3_MODE_POS)

typedef enum{
	TC3_MODE_NORMAL =0,
	TC3_MODE_PERIOD
} tc3_mode_e;

/******************************************************************************
* CR : IMCR/RISR/MISR/ICR register
******************************************************************************/

typedef enum
{
	CTC_INT_PEND    =     (0x01ul<<0),     
	CTC_INT_OVF    	=     (0x01ul<<1)      
}tc3_int_e;

/*****************************************************************************
******************** CTC External Functions Declaration **********************
******************************************************************************/
/** \brief tc3 deinit
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
void tc3_deinit(csp_tc3_t *ptTc3Base)	;

/** \brief tc3 clock enable 
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
 void ct3_clk_enable(csp_tc3_t *ptTc3Base);
 
  /** \brief tc3 clock disable 
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
 void ct3_clk_disable(csp_tc3_t *ptTc3Base);
 
 /** \brief tc3 int enable
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eInt: tc3 interrupt \ref tc3_int_e
 * 			   
 *  \return none
 */ 
 void ct3_int_enable(csp_tc3_t *ptTc3Base, tc3_int_e eInt);
 
 /** \brief tc3 int disable
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eInt: tc3 interrupt \ref tc3_int_e
 * 			   
 *  \return none
 */ 
 void ct3_int_disable(csp_tc3_t *ptTc3Base, tc3_int_e eInt);
 
 /** \brief tc3 config
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eClkSrc: tc3 clock source select \ref tc3_clksrc_e
 *  \param[in] byBcsDiv: tc3 buzzer division ,range : 1~0x3f
 *  \param[in] eMode: tc3 work mode select  \ref tc3_mode_e
 * 			   
 *  \return none
 */ 
void tc3_configure(csp_tc3_t *ptTc3Base, tc3_clksrc_e eClkSrc , U8_T byBcsDiv , tc3_mode_e eMode);

/** \brief tc3 software reset: CLKEN status will NOT be reset!!!
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_software_reset(csp_tc3_t *ptTc3Base);

/** \brief tc3 start
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_start(csp_tc3_t *ptTc3Base);

/** \brief tc3 stop
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_stop(csp_tc3_t *ptTc3Base);

/** \brief tc3 write prdr
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] hwPrdr:  timer period  ,range : 1~0xffff
 * 			   
 *  \return none
 */
void tc3_write_prdr(csp_tc3_t *ptTc3Base,U16_T hwPrdr);

/** \brief tc3 write timdr
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] hwTimdr:  timer data,range : 1~0xffff
 * 			   
 *  \return none
 */
void tc3_write_timdr(csp_tc3_t *ptTc3Base,U16_T hwTimdr);



#endif   /**< apt32f172_tc3_ctc_H */

/******************* (C) COPYRIGHT 2018 APT Chip *****END OF FILE****/


