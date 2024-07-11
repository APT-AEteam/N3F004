/***********************************************************************//** 
 * \file  iomux.c
 * \brief  io mux configuration
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
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

/** \brief Set a specific pin to EXI input
 * 
 *  \param[in] eExiPin: EXI0~EXI15 \ref exi_e
 *  \return none
 */ 
void exi_pin_init(csp_gpio_t *ptGpioBase, U8_T byPinNum)
{
    gpio_init(ptGpioBase,byPinNum, PIN_INPUT);
	
}

/** \brief Set specific pins to EMOSC IN and OUT
 * 			PA03,PA04 in case of N3F004
 *  \param[in] none
 *  \return none
 */ 
void emosc_pin_init(void)
{
	gpio_init(GPIOA0,3, PA03_OSC_XI);
	gpio_init(GPIOA0,4, PA04_OSC_XO);
	
}

/** \brief set PA0.2/PA0.8/PA0.9 as CLO output 
 * 
 *  \param[in] eCloIo: CLO IO \ref clo_io_e
 *  \return none
 */ 
void syscon_clo_pin_config(clo_io_e eCloIo)
{
	switch (eCloIo)
	{
		case (CLO_PA02): gpio_init(GPIOA0, 2, PA02_CLO); break;
		case (CLO_PA08): gpio_init(GPIOA0, 8, PA08_CLO); break;
		case (CLO_PA09): gpio_init(GPIOA0, 9, PA09_CLO); 
		default: break;
	}
}

/** \brief set ept io as CHAX,CHAY,CHBX,CHBY,CHCX,CHCY,CHD
 * 
 *  \param[in] eEptIo: EPT IO \ref ept_io_e
 *  \return none
 */ 
void ept_pin_config(ept_io_e eEptIo)
{
	switch (eEptIo)
	{
		case (EPT_CHAX_PA07): gpio_init(GPIOA0, 7, PA07_EPT_CHAX); break;
		case (EPT_CHBX_PB02): gpio_init(GPIOB0, 2, PB02_EPT_CHBX); break;
		case (EPT_CHCX_PB03): gpio_init(GPIOB0, 3, PB03_EPT_CHCX); break;
		case (EPT_CHAY_PB03): gpio_init(GPIOB0, 3, PB03_EPT_CHAY); break;
		case (EPT_CHD_PB03): gpio_init(GPIOB0, 3, PB03_EPT_CHD); break;
		case (EPT_CHD_PA08): gpio_init(GPIOA0, 8, PA08_EPT_CHD); break;
		case (EPT_CHBY_PA08): gpio_init(GPIOA0, 8, PA08_EPT_CHBY); break;
		case (EPT_CHCY_PA09): gpio_init(GPIOA0, 9, PA09_EPT_CHCY); break;
		case (EPT_CHAX_PA010): gpio_init(GPIOA0,10, PA010_EPT_CHAX); break;
		case (EPT_CHBX_PA011): gpio_init(GPIOA0, 11, PA011_EPT_CHBX); break;
		case (EPT_CHAX_PA011): gpio_init(GPIOA0,11 , PA011_EPT_CHAX); break;
		case (EPT_CHBY_PA05): gpio_init(GPIOA0, 5, PA05_EPT_CHBY); break;
		case (EPT_CHAY_PA012): gpio_init(GPIOA0, 12, PA012_EPT_CHAY); break;
		case (EPT_CHCY_PA013): gpio_init(GPIOA0, 13, PA013_EPT_CHCY); break;
		case (EPT_CHCX_PB00): gpio_init(GPIOB0, 0, PB00_EPT_CHCX); break;
		case (EPT_CHD_PB01): gpio_init(GPIOB0, 1, PB01_EPT_CHD); break;
		case (EPT_CHAY_PB01): gpio_init(GPIOB0, 1, PB01_EPT_CHAY); break;
		case (EPT_CHBX_PA00): gpio_init(GPIOA0, 0, PA00_EPT_CHBX); break;
		case (EPT_CHCX_PA03): gpio_init(GPIOA0, 3, PA03_EPT_CHCX); break;
		case (EPT_CHCY_PA04): gpio_init(GPIOA0, 4, PA04_EPT_CHCY); break;
		case (EPT_EBI0_PA07): gpio_init(GPIOA0, 7, PA07_EBI0); break;
		case (EPT_EBI1_PA013): gpio_init(GPIOA0, 13, PA013_EBI1); break;
		case (EPT_EBI2_PB03): gpio_init(GPIOB0, 3, PB03_EBI2); break;
		case (EPT_EBI3_PB02): gpio_init(GPIOB0, 2, PB02_EBI3); break;
		default: break;
	}
}


/** \brief set gpt io as CHA
 * 
 *  \param[in] eGptaIo: GPT IO \ref gpta_io_e
 *  \return none
 */ 
void gpt_pin_config(gpta_io_e eGptaIo)
{
	switch (eGptaIo)
	{
		case (GPTA_CHA_PA06): gpio_init(GPIOA0, 6, PA06_GPTA_CHA); break;
		case (GPTA_CHA_PA09): gpio_init(GPIOA0, 9,PA09_GPTA_CHA); break;
		case (GPTA_CHA_PA010): gpio_init(GPIOA0, 10, PA010_GPTA_CHA); break;
		case (GPTA_CHA_PA011): gpio_init(GPIOA0, 11, PA011_GPTA_CHA); break;
		case (GPTA_CHA_PB01): gpio_init(GPIOB0, 1, PB01_GPTA_CHA); break;
		case (GPTA_CHA_PA01): gpio_init(GPIOA0, 1, PA01_GPTA_CHA); break;
		case (GPTA_CHA_PA03): gpio_init(GPIOA0, 3, PA03_GPTA_CHA); break;
		default: break;
	}
}

/** \brief set uart0 io as TX,RX
 * 
 *  \param[in] eUart0Io: UART0 IO \ref uart0_io_e
 *  \return none
 */ 
void uart0_pin_config(uart0_io_e eUart0Io)
{
	switch (eUart0Io) {
		case(UART0_TX_PA06):gpio_init(GPIOA0, 6, PA06_UART0_TX); break;
		case(UART0_RX_PA07):gpio_init(GPIOA0, 7, PA07_UART0_RX); break;
		case(UART0_TX_PB02):gpio_init(GPIOB0, 2, PB02_UART0_TX); break;
		case(UART0_RX_PA05):gpio_init(GPIOA0, 5, PA05_UART0_RX); break;
		case(UART0_TX_PA012):gpio_init(GPIOA0, 12, PA012_UART0_TX); break;
		case(UART0_TX_PA00):gpio_init(GPIOA0, 0, PA00_UART0_TX); break;
		case(UART0_RX_PA01):gpio_init(GPIOA0, 1, PA01_UART0_RX); break;
		default: break;
	}
}

/** \brief set uart1 io as TX,RX
 * 
 *  \param[in] eUart1Io: UART1 IO \ref uart1_io_e
 *  \return none
 */ 
void uart1_pin_config(uart1_io_e eUart1Io)
{
	switch (eUart1Io) {
		case(UART1_RX_PA011):gpio_init(GPIOA0, 11, PA011_UART1_RX); break;
		case(UART1_RX_PA013):gpio_init(GPIOA0, 13, PA013_UART1_RX); break;
		case(UART1_TX_PB00):gpio_init(GPIOB0, 0, PB00_UART1_TX); break;
		case(UART1_RX_PB01):gpio_init(GPIOB0, 1, PB01_UART1_RX); break;
		case(UART1_TX_PA00):gpio_init(GPIOA0, 0, PA00_UART1_TX); break;
		case(UART1_TX_PA03):gpio_init(GPIOA0, 3, PA03_UART1_TX); break;
		case(UART1_RX_PA04):gpio_init(GPIOA0, 4, PA04_UART1_RX); break;
		case(UART1_TX_PA02):gpio_init(GPIOA0, 2, PA02_UART1_TX); break;
		default: break;
	}
}

/** \brief iomap configuration
 * 
 *  \param[in] eCloIo: CLO IO \ref clo_io_e
 *  \return none
 */ 
void gpio_remap(csp_gpio_t * ptGpioBase,U8_T byPinNum, ioremap_e eCfgVal)
{
	if(ptGpioBase == GPIOB0 || byPinNum > 7)
		return;
	gpio_init(ptGpioBase, byPinNum, PA06_G1); 
	syscon_ioremap(byPinNum, eCfgVal);

}