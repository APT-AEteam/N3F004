/***********************************************************************//** 
 * \file  n3f004.h
 * \brief chip level information for N3F004
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/



/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef _N3F004_H
#define _N3F004_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"
#include "core_801.h"
#include "csi_gcc.h"
//#include "adc.h"
#include "bt.h"
#include "coret.h"
//#include "crc.h"
//#include "ept.h"
#include "etcb.h"
#include "gpio.h"
//#include "gpt.h"
//#include "i2c.h"
#include "ifc.h"
//#include "spi.h"
#include "syscon.h"
//#include "uart.h"
#include "n3f004_top.h"


#define CK_CPU_ENALLNORMALIRQ		__enable_irq()
#define CK_CPU_DISALLNORMALIRQ		__disable_irq()


	

/******************************************************************************
* IP instance declaration
******************************************************************************/
extern CSP_IFC_T 	*IFC;
extern csp_syscon_t *SYSCON  ;
extern csp_etcb_t   *ETCB ;
//extern CSP_ADC12_T 	*ADC0     ;
extern csp_gpio_t 	*GPIOA0   ;
extern csp_gpio_t 	*GPIOB0   ;
extern csp_igrp_t	*GPIOGRP  ;
//extern CSP_UART_T 	*UART0    ;
//extern CSP_UART_T 	*UART1    ;
//extern CSP_SSP_T  	*SPI0     ;
//extern CSP_I2C_T  	*I2C0     ;
//extern CSP_GPT_T 	*GPT0     ;
//extern CSP_EPT_T 	*EPT0     ;
extern CSP_BT_T  	*BT0      ;
extern CSP_BT_T  	*BT1      ;
//extern CSP_CRC_T 	*CRC      ;




/******************************************************************************
* ISR Definition for generating special interrupt related ASM (CK801), with compile option -mistack
******************************************************************************/
void MisalignedHandler(void) __attribute__((isr));
void IllegalInstrHandler(void) __attribute__((isr));
void AccessErrHandler(void) __attribute__((isr));
void BreakPointHandler(void) __attribute__((isr));
void UnrecExecpHandler(void) __attribute__((isr));
void Trap0Handler(void) __attribute__((isr));
void Trap1Handler(void) __attribute__((isr));
void Trap2Handler(void) __attribute__((isr));
void Trap3Handler(void) __attribute__((isr));
void PendTrapHandler(void) __attribute__((isr));
void CORETHandler(void) __attribute__((isr));
void SYSCONIntHandler(void) __attribute__((isr));
void IFCIntHandler(void) __attribute__((isr));
void ADCIntHandler(void) __attribute__((isr));
void EPT0IntHandler(void) __attribute__((isr));
void EXI0IntHandler(void) __attribute__((isr));
void EXI1IntHandler(void) __attribute__((isr));
void EXI2to3IntHandler(void) __attribute__((isr));
void EXI4to9IntHandler(void) __attribute__((isr));
void EXI10to15IntHandler(void) __attribute__((isr));
void UART0IntHandler(void) __attribute__((isr));
void UART1IntHandler(void) __attribute__((isr));
void I2CIntHandler(void) __attribute__((isr));
void GPT0IntHandler(void) __attribute__((isr));
void SPI0IntHandler(void) __attribute__((isr));
void BT0IntHandler(void) __attribute__((isr));
void BT1IntHandler(void) __attribute__((isr));

extern void delay_nms(unsigned int t);
extern void delay_nus(unsigned int t);

#endif

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/