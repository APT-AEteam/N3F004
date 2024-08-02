/***********************************************************************//** 
 * \file  tc3.c
 * \brief tc3 function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-18<td>V1_3_0  <td>GQQ  <td>initial
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


/** \brief tc3 deinit
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
void tc3_deinit(csp_tc3_t *ptTc3Base)									
{
   	ptTc3Base->CSSR	=	TC3_CSSR_RST;		 				/**< CSSR reset value     */	
   	ptTc3Base->CEDR	=	TC3_RST_VALUE;						/**< CEDR reset value     */
	ptTc3Base->SRR		=	TC3_RST_VALUE;						/**< SRR reset value      */
	ptTc3Base->CR		=	TC3_RST_VALUE;						/**< CR reset value       */
	ptTc3Base->PRDR	=	TC3_PRDR_RST;						/**< PRDR reset value     */
	ptTc3Base->TIMDR	=	TC3_RST_VALUE;						/**< TIMDR reset value    */
	ptTc3Base->IMCR	=	TC3_RST_VALUE;						/**< IMCR reset value     */
	ptTc3Base->ICR		=	TC3_RST_VALUE;						/**< ICR reset value      */
}

/** \brief tc3 clock enable 
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
 void ct3_clk_enable(csp_tc3_t *ptTc3Base)
 {
	ptTc3Base->CEDR |= TC3_CLKEN|TC3_DBGEN;
 }
 
 /** \brief tc3 clock disable 
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */ 
 void ct3_clk_disable(csp_tc3_t *ptTc3Base)
 {
	ptTc3Base->CEDR &= ~TC3_CLKEN;
 }
 
/** \brief tc3 int enable
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eInt: tc3 interrupt \ref tc3_int_e
 * 			   
 *  \return none
 */ 
 void ct3_int_enable(csp_tc3_t *ptTc3Base, tc3_int_e eInt)
 {
	ptTc3Base->ICR |= eInt;
	ptTc3Base->IMCR |= eInt;
 }
 
/** \brief tc3 int disable
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eInt: tc3 interrupt \ref tc3_int_e
 * 			   
 *  \return none
 */ 
 void ct3_int_disable(csp_tc3_t *ptTc3Base, tc3_int_e eInt)
 {
	ptTc3Base->IMCR &= ~eInt;
	ptTc3Base->ICR |= eInt;
 }

/** \brief tc3 config
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] eClkSrc: tc3 clock source select \ref tc3_clksrc_e
 *  \param[in] byBcsDiv: tc3 buzzer division ,range : 1~0x3f
 *  \param[in] eMode: tc3 work mode select  \ref tc3_mode_e
 * 			   
 *  \return none
 */ 
void tc3_configure(csp_tc3_t *ptTc3Base, tc3_clksrc_e eClkSrc , U8_T byBcsDiv , tc3_mode_e eMode)
{
	ptTc3Base->CSSR=eClkSrc;			
	ptTc3Base->CR=(byBcsDiv<<TC3_BCSDIV_POS)|(eMode<<TC3_MODE_POS);
}

/** \brief tc3 software reset: CLKEN status will NOT be reset!!!
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_software_reset(csp_tc3_t *ptTc3Base)
{
	ptTc3Base->SRR=TC3_SOFTWARE_RST;
} 

/** \brief tc3 start
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_start(csp_tc3_t *ptTc3Base)
{
	delay_nms(100);
	ptTc3Base->CR|=TC3_WTEN;
}

/** \brief tc3 stop
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 * 			   
 *  \return none
 */
void tc3_stop(csp_tc3_t *ptTc3Base)
{
	delay_nms(100);
	ptTc3Base->CR&=~TC3_WTEN;
}


/** \brief tc3 write prdr
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] hwPrdr:  timer period  ,range : 1~0xffff
 * 			   
 *  \return none
 */
void tc3_write_prdr(csp_tc3_t *ptTc3Base,U16_T hwPrdr)
{
	ptTc3Base->PRDR=hwPrdr;
}

/** \brief tc3 write timdr
 * 
 *  \param[in] ptTc3Base: pointer of tc3 register structure
 *  \param[in] hwTimdr:  timer data,range : 1~0xffff
 * 			   
 *  \return none
 */
void tc3_write_timdr(csp_tc3_t *ptTc3Base,U16_T hwTimdr)
{
	ptTc3Base->TIMDR=hwTimdr;
}
/******************* (C) COPYRIGHT 2018 APT Chip *****END OF FILE****/