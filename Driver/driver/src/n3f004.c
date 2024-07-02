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

CSP_IFC_T   	*IFC     = (CSP_IFC_T    *)APB_IFCBase ;
CSP_SYSCON_T 	*SYSCON = (CSP_SYSCON_T *)APB_SYSCONBase ;

//CSP_TKEY_T  	*TKEY    = (CSP_TKEY_T  *)APB_TKEYBase ;
//CSP_TKEYBUF_T   *TKEYBUF = (CSP_TKEYBUF_T  *)APB_TKEYBUFBase;
//CSP_ADC12_T 	*ADC0    = (CSP_ADC12_T  *)APB_ADC0Base ;

CSP_GPIO_T  	*GPIOA0   = (CSP_GPIO_T  *)APB_GPIOA0Base ; // A0
CSP_GPIO_T  	*GPIOB0   = (CSP_GPIO_T  *)APB_GPIOB0Base ; // B0
CSP_IGRP_T  	*GPIOGRP  = (CSP_IGRP_T *)APB_IGRPBase;

//CSP_UART_T  	*UART0    = (CSP_UART_T  *)APB_UART0Base ;
//CSP_UART_T  	*UART1    = (CSP_UART_T  *)APB_UART1Base ;
//
//CSP_SSP_T   	*SPI0     = (CSP_SSP_T   *)APB_SPI0Base ;
//CSP_I2C_T   	*I2C0     = (CSP_I2C_T   *)APB_I2C0Base ;
//
//CSP_CA_T    	*CA0      = (CSP_CA_T    *)APB_CNTABase ;
//
//CSP_GPT_T		*GPT0	  =	(CSP_GPT_T *)APB_GPT0Base;
//CSP_EPT_T   	*EPT0     = (CSP_EPT_T  *)APB_EPT0Base ;
//CSP_ETCB_T  	*ETCB     = (CSP_ETCB_T *)APB_ETCBBase ;
//
CSP_BT_T    	*BT0      = (CSP_BT_T   *)APB_BT0Base ;
CSP_BT_T    	*BT1      = (CSP_BT_T   *)APB_BT1Base ;
//CSP_CRC_T   	*CRC      = (CSP_CRC_T  *)AHB_CRCBase ;

/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/