/***********************************************************************//** 
 * \file  n3f004.c
 * \brief chip level IP stucture definition
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

csp_ifc_t   	*IFC     = (csp_ifc_t    *)APB_IFCBASE ;
csp_syscon_t 	*SYSCON = (csp_syscon_t *)APB_SYSCONBASE ;

csp_adc_t 	*ADC0    = (csp_adc_t  *)APB_ADC0BASE ;

csp_gpio_t  	*GPIOA0   = (csp_gpio_t  *)APB_GPIOA0BASE ; // A0
csp_gpio_t  	*GPIOB0   = (csp_gpio_t  *)APB_GPIOB0BASE ; // B0
csp_igrp_t  	*GPIOGRP  = (csp_igrp_t *)APB_IGRPBASE;

csp_uart_t  	*UART0    = (csp_uart_t  *)APB_UART0BASE ;
csp_uart_t  	*UART1    = (csp_uart_t  *)APB_UART1BASE ;
//
csp_spi_t   	*SPI0     = (csp_spi_t   *)APB_SPI0BASE ;
csp_i2c_t   	*I2C0     = (csp_i2c_t   *)APB_I2C0BASE ;
//
//CSP_CA_T    	*CA0      = (CSP_CA_T    *)APB_CNTABASE ;
//
csp_gpta_t		*GPT0	  =	(csp_gpta_t *)APB_GPT0BASE;
csp_ept_t   	*EPT0     = (csp_ept_t  *)APB_EPT0BASE ;
csp_etcb_t  	*ETCB     = (csp_etcb_t *)APB_ETCBBASE ;
//
csp_bt_t    	*BT0      = (csp_bt_t   *)APB_BT0BASE ;
csp_bt_t    	*BT1      = (csp_bt_t   *)APB_BT1BASE ;
csp_crc_t   *CRC      = (csp_crc_t  *)AHB_CRCBASE ;

/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/