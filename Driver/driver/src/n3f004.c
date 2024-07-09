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

CSP_IFC_T   	*IFC     = (CSP_IFC_T    *)APB_IFCBASE ;
csp_syscon_t 	*SYSCON = (csp_syscon_t *)APB_SYSCONBASE ;

//CSP_ADC12_T 	*ADC0    = (CSP_ADC12_T  *)APB_ADC0BASE ;

csp_gpio_t  	*GPIOA0   = (csp_gpio_t  *)APB_GPIOA0BASE ; // A0
csp_gpio_t  	*GPIOB0   = (csp_gpio_t  *)APB_GPIOB0BASE ; // B0
csp_igrp_t  	*GPIOGRP  = (csp_igrp_t *)APB_IGRPBASE;

//CSP_UART_T  	*UART0    = (CSP_UART_T  *)APB_UART0BASE ;
//CSP_UART_T  	*UART1    = (CSP_UART_T  *)APB_UART1BASE ;
//
//CSP_SSP_T   	*SPI0     = (CSP_SSP_T   *)APB_SPI0BASE ;
//CSP_I2C_T   	*I2C0     = (CSP_I2C_T   *)APB_I2C0BASE ;
//
//CSP_CA_T    	*CA0      = (CSP_CA_T    *)APB_CNTABASE ;
//
//CSP_GPT_T		*GPT0	  =	(CSP_GPT_T *)APB_GPT0BASE;
//CSP_EPT_T   	*EPT0     = (CSP_EPT_T  *)APB_EPT0BASE ;
csp_etcb_t  	*ETCB     = (csp_etcb_t *)APB_ETCBBASE ;
//
CSP_BT_T    	*BT0      = (CSP_BT_T   *)APB_BT0BASE ;
CSP_BT_T    	*BT1      = (CSP_BT_T   *)APB_BT1BASE ;
CSP_CRC_T   	*CRC      = (CSP_CRC_T  *)AHB_CRCBASE ;

/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/