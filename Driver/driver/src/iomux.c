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