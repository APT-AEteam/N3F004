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
void clo_pin_init(clo_io_e eCloIo)
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

/** \brief set SPI io as NSS,MOSI,MISO,SCK
 * 
 *  \param[in] eSpiIo: SPI IO \ref spi_io_e
 *  \return none
 */ 
void spi_pin_config(spi_io_e eSpiIo)
{
	switch (eSpiIo) {
		case(SPI_NSS_PA06):gpio_init(GPIOA0, 6, PA06_SPI_NSS); break;
		case(SPI_SCK_PB02):gpio_init(GPIOB0, 2, PB02_SPI_SCK); break;
		case(SPI_MOSI_PB03):gpio_init(GPIOB0, 3, PB03_SPI_MOSI); break;
		case(SPI_MISO_PA08):gpio_init(GPIOA0, 8, PA08_SPI_MISO); break;
		case(SPI_SCK_PA09):gpio_init(GPIOA0, 9, PA09_SPI_SCK); break;
		case(SPI_MOSI_PA010):gpio_init(GPIOA0, 10, PA010_SPI_MOSI); break;
		case(SPI_MISO_PA011):gpio_init(GPIOA0, 11, PA011_SPI_MISO); break;
		case(SPI_MISO_PA05):gpio_init(GPIOA0, 5, PA05_SPI_MISO); break;
		case(SPI_MOSI_PA012):gpio_init(GPIOA0, 12, PA012_SPI_MOSI); break;
		case(SPI_SCK_PA02):gpio_init(GPIOA0, 2, PA02_SPI_SCK); break;
		default: break;
	}
}

/** \brief set i2c io as SCL ,SDA
 * 
 *  \param[in] eI2cIo: I2C IO \ref i2c_io_e
 *  \return none
 */ 
void i2c_pin_config(i2c_io_e eI2cIo)
{
	switch (eI2cIo) {
		case(I2C_SCL_PA06):gpio_init(GPIOA0, 6, PA06_I2C_SCL); break;
		case(I2C_SDA_PA07):gpio_init(GPIOA0, 7, PA07_I2C_SDA); break;
		case(I2C_SCL_PB02):gpio_init(GPIOB0, 2, PB02_I2C_SCL); break;
		case(I2C_SDA_PA09):gpio_init(GPIOA0, 9,PA09_I2C_SDA); break;
		case(I2C_SCL_PA010):gpio_init(GPIOA0, 10, PA010_I2C_SCL); break;
		case(I2C_SDA_PA013):gpio_init(GPIOA0, 13, PA013_I2C_SDA); break;
		case(I2C_SCL_PB00):gpio_init(GPIOB0, 0, PB00_I2C_SCL); break;
		case(I2C_SDA_PA00):gpio_init(GPIOA0, 0, PA00_I2C_SDA); break;
		case(I2C_SCL_PA01):gpio_init(GPIOA0, 1, PA01_I2C_SCL); break;
		case(I2C_SDA_PA01):gpio_init(GPIOA0, 1, PA01_I2C_SDA); break;
		case(I2C_SDA_PA03):gpio_init(GPIOA0, 3, PA03_I2C_SDA); break;
		case(I2C_SCL_PA04):gpio_init(GPIOA0, 4, PA04_I2C_SCL); break;
		case(I2C_SCL_PA02):gpio_init(GPIOA0, 2, PA02_I2C_SCL); break;
		default: break;
	}
}

/** \brief set ADC io as AINx, VREFP,VREFN
 * 
 *  \param[in] eAdcIo: adc IO \ref adc_io_e
 *  \return none
 */ 
void adc_pin_config(adc_io_e eAdcIo)
{
	switch (eAdcIo) {
		case(ADC_AIN0_PB01):gpio_init(GPIOB0, 1, PB01_AIN0); break;
		case(ADC_AIN1_PA00):gpio_init(GPIOA0, 0, PA00_AIN1); break;
		case(ADC_AIN2_PA01):gpio_init(GPIOA0, 1, PA01_AIN2); break;
		case(ADC_AIN3_VREFN_PA03):gpio_init(GPIOA0, 3,PA03_AIN3_VREFN); break;
		case(ADC_AIN4_PA05):gpio_init(GPIOA0, 5, PA05_AIN4); break;
		case(ADC_AIN5_PB02):gpio_init(GPIOB0, 2, PB02_AIN5); break;
		case(ADC_AIN6_PB03):gpio_init(GPIOB0, 3, PB03_AIN6); break;
		case(ADC_AIN7_PA08):gpio_init(GPIOA0, 8, PA08_AIN7); break;
		case(ADC_AIN8_PA09):gpio_init(GPIOA0, 9, PA09_AIN8); break;
		case(ADC_AIN9_PA010):gpio_init(GPIOA0, 10, PA010_AIN9); break;
		case(ADC_AIN10_PA013):gpio_init(GPIOA0, 13, PA013_AIN10); break;
		case(ADC_AIN11_PB00):gpio_init(GPIOB0, 0, PB00_AIN11); break;
		case(ADC_VREFP_BUF_PA02):gpio_init(GPIOA0, 2, PA02_VREFP_BUF); break;
		default: break;
	}
}

/** \brief set tc3 io as buzzer out
 * 
 *  \param[in] eTc3Io: tc3 IO \ref tc3_io_e
 *  \return none
 */ 
void tc3_pin_config(tc3_io_e eTc3Io)
{
	switch (eTc3Io) {
		case(TC3_BUZZ_PA010):gpio_init(GPIOA0, 10, PA010_TC3_BUZZ); break;
		case(TC3_BUZZ_PA012):gpio_init(GPIOA0, 12, PA012_TC3_BUZZ); break;
		case(TC3_BUZZ_PB00):gpio_init(GPIOB0, 0, PB00_TC3_BUZZ); break;
		case(TC3_BUZZ_PB01):gpio_init(GPIOB0, 1, PB01_TC3_BUZZ); break;
		case(TC3_BUZZ_PA01):gpio_init(GPIOA0, 1, PA01_TC3_BUZZ); break;
		default: break;
	}
}

/** \brief cmp io configuration
 * 
 *  \param[in] eCmpIo: CMP IO \ref cmp_io_e
 *  \return none
 */
void cmp_io_init(cmp_io_e eCmpIo)
{
	switch(eCmpIo)
	{
		case (CMPIN1P_PA08): gpio_init(GPIOA0, 8, PA08_CMPIN1P); break;
		case (CMPIN1N_PA09): gpio_init(GPIOA0, 9 , PA09_CMPIN1N); break;
		case (CMPIN2P_PA013): gpio_init(GPIOA0, 13, PA013_CMPIN2P); break;
		case (CMPIN2N_PB00): gpio_init(GPIOB0, 0, PB00_CMPIN2N); break;
		case (CMPIN3P_PB01):gpio_init(GPIOB0, 1, PB01_CMPIN3P); break;
		case (CMPIN3N_PA00):gpio_init(GPIOA0, 0, PA00_CMPIN3N); break;
		case (CMPIN4P_PB02):gpio_init(GPIOB0, 2, PB02_CMPIN4P); break;
		case (CMPIN4N_PB03):gpio_init(GPIOB0, 3, PB03_CMPIN4N); break;
		case (CMP0OUT_PA03):gpio_init(GPIOA0, 3, PA03_CMP0_OUT); break;
		case (CMP0OUT_PA06):gpio_init(GPIOA0, 6, PA06_CMP0_OUT); break;
		case (CMP1OUT_PA07):gpio_init(GPIOA0, 7, PA07_CMP1_OUT); break;
		case (CMP1OUT_PA012):gpio_init(GPIOA0, 12, PA012_CMP1_OUT); break;
		default:break;
	}
}

/** \brief iomap configuration
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eCfgVal: remap function configuration \ref ioremap_e
 *  \return none
 */ 
void ioremap_configure(csp_gpio_t * ptGpioBase,U8_T byPinNum, ioremap_e eCfgVal)
{
	if(ptGpioBase == GPIOB0 || byPinNum > 7)
		return;
	gpio_init(ptGpioBase, byPinNum, PA06_G1); 
	syscon_ioremap(byPinNum, eCfgVal);
}