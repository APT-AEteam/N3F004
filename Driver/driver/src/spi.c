/***********************************************************************//** 
 * \file  spi.c
 * \brief spi function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-12<td>V2_0_0  <td>GQQ  <td>initial
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


/** \brief SPI deinit
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_deinit(csp_spi_t *ptSpiBase)
{
    ptSpiBase->CR0   	= SPI_CR0_RST;
    ptSpiBase->CR1   	= SPI_CR1_RST;
    ptSpiBase->DR   		= SPI_DR_RST;
    ptSpiBase->CPSR  	= SPI_CPSR_RST;
    ptSpiBase->IMCR  	= SPI_IMCR_RST;
    ptSpiBase->ICR	 	= SPI_ICR_RST;
}

/** \brief SPI init as master
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eDataLen: data length select \ref spi_data_len_e
 *  \param[in] eWorkMd: work mode config : CPOL & CPHA \ref spi_work_mode_e
 *  \param[in] eLbm: loopback function control  \ref spi_lbm_e
 *  \param[in] eRxFifo: Rx fifo  trigger point of interrupt   \ref spi_rxifl_e
 *  \param[in] bySclkDiv: Serial clk divsion ,range: 0~0xff
 *  \param[in] byPclkDiv: PCLK division , must be even !!!  range : 0x2~0xfe 
 * 					spi bit rate = FPCLK/ (byPclkDiv *(1 + bySclkDiv))
 * 			   
 *  \return none
 */ 
void spi_master_init(csp_spi_t *ptSpiBase,spi_data_len_e eDataLen , spi_work_mode_e eWorkMd , spi_lbm_e eLbm , spi_rxifl_e eRxFifo , U8_T bySclkDiv, U8_T byPclkDiv )
{
	ptSpiBase->CPSR=byPclkDiv;
	
	ptSpiBase->CR0=(ptSpiBase->CR0&(~(SPI_DATA_LEN_MSK|SPI_WORK_MODE_MSK|SPI_SCR_MSK)))|(eDataLen<<SPI_DATA_LEN_POS)|(eWorkMd<<SPI_WORK_MODE_POS)|(bySclkDiv<<SPI_SCR_POS);
	ptSpiBase->CR1=(ptSpiBase->CR1&(~(SPI_SSE_MSK|SPI_LBM_MSK|SPI_MODE_MSK|SPI_RXIFL_MSK)))|SPI_SSE_EN|(eLbm<<SPI_LBM_POS)|(SPI_MASTER<<SPI_MODE_POS)|(eRxFifo<<SPI_RXIFL_POS);
}

/** \brief SPI init as slave
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eDataLen: data length select \ref spi_data_len_e
 *  \param[in] eWorkMd: work mode config : CPOL & CPHA \ref spi_work_mode_e
 *  \param[in] eRxFifo: Rx fifo  trigger point of interrupt   \ref spi_rxifl_e
 *  \param[in] bySclkDiv: Serial clk divsion ,range: 0~0xff
 *  \param[in] byPclkDiv: PCLK division , must be even !!!  range : 0x2~0xfe 
 * 					spi bit rate = FPCLK/ (byPclkDiv *(1 + bySclkDiv))
 * 			   
 *  \return none
 */ 
void spi_slave_init(csp_spi_t *ptSpiBase,spi_data_len_e eDataLen , spi_work_mode_e eWorkMd ,  spi_rxifl_e eRxFifo , U8_T bySclkDiv, U8_T byPclkDiv)
{
	ptSpiBase->CR0=(ptSpiBase->CR0&(~(SPI_DATA_LEN_MSK|SPI_WORK_MODE_MSK|SPI_SCR_MSK)))|(eDataLen<<SPI_DATA_LEN_POS)|(eWorkMd<<SPI_WORK_MODE_POS)|(bySclkDiv<<SPI_SCR_POS);
	ptSpiBase->CPSR=byPclkDiv;
	ptSpiBase->CR1=(ptSpiBase->CR1&(~(SPI_SSE_MSK|SPI_LBM_MSK|SPI_MODE_MSK|SPI_RXIFL_MSK)))|SPI_SSE_EN|(SPI_SLAVE<<SPI_MODE_POS)|(eRxFifo<<SPI_RXIFL_POS);
}

/** \brief SPI write data
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] hwData: data to be sent
 * 			   
 *  \return none
 */ 
void spi_write_data(csp_spi_t *ptSpiBase, U16_T hwData)
{
	while(((ptSpiBase->SR) & SPI_TNF) != SPI_TNF);	
	ptSpiBase->DR = hwData;
	while(((ptSpiBase->SR) & SPI_BSY) == SPI_BSY);		//wait for transmition finish
}

/** \brief SPI read data
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] hwData: data to be sent
 *  \param[out] ptData: pointer of received data
 *  \param[in] byNum: number of receive data
 * 			   
 *  \return none
 */ 
void spi_read_data(csp_spi_t *ptSpiBase, U16_T hwData ,volatile U16_T *ptData , U8_T byNum)
{
	U8_T byCnt;
	while(((ptSpiBase->SR) & SPI_TNF) != SPI_TNF);		//Transmit FIFO is not full？
	ptSpiBase->DR = hwData;
	while(((ptSpiBase->SR) & SPI_BSY) == SPI_BSY);		//Send or receive over？
	delay_nus(1);
	*ptData = ptSpiBase->DR;
	for(byCnt=0;byCnt<byNum;byCnt++)
	{
		while(((ptSpiBase->SR) & SPI_TNF) != SPI_TNF);	
		ptSpiBase->DR=0;
		while(((ptSpiBase->SR) & SPI_BSY) == SPI_BSY);
		*(ptData+byCnt) = ptSpiBase->DR;  	//get data from FIFO
	}
}

/** \brief SPI interrupt enable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eInt: interrupt select \ref spi_int_e
 * 			   
 *  \return none
 */ 
void spi_int_enable(csp_spi_t *ptSpiBase,  spi_int_e eInt)
{
	ptSpiBase->ICR = eInt;
	ptSpiBase->IMCR  |= eInt;						//SET
}   

/** \brief SPI interrupt disable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eInt: interrupt select \ref spi_int_e
 * 			   
 *  \return none
 */ 
void spi_int_disable(csp_spi_t *ptSpiBase,  spi_int_e eInt)
{
	ptSpiBase->IMCR  &= ~eInt;	
	ptSpiBase->ICR = eInt;
}
/** \brief SPI wakeup enable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_wakeup_enable(csp_spi_t *ptSpiBase)
{ 
	csi_vic_set_wakeup_irq(SPI_INT);
}

/** \brief SPI wakeup disable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_wakeup_disable(csp_spi_t *ptSpiBase)
{ 
	csi_vic_clear_wakeup_irq(SPI_INT);
}
/******************* (C) COPYRIGHT 2018 APT Chip *****END OF FILE****/