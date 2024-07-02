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
#ifndef _N3F104_H
#define _N3F104_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"
#include "core_801.h"
#include "csi_gcc.h"
//#include "adc.h"
#include "bt.h"
#include "coret.h"
//#include "countera.h"
//#include "crc.h"
//#include "ept.h"
//#include "et.h"
#include "gpio.h"
//#include "gpt.h"
//#include "i2c.h"
#include "ifc.h"
//#include "lpt.h"
//#include "rtc.h"
//#include "sio.h"
//#include "spi.h"
#include "syscon.h"
//#include "uart.h"
//#include "wwdt.h"
#include "types_local.h"

#define CK_CPU_ENALLNORMALIRQ		__enable_irq()
#define CK_CPU_DISALLNORMALIRQ		__disable_irq()


	
 #define FLASHBase 0x00000000
 #define FLASHSize 0x00010000
 #define FLASHLimit (FLASHBase + FLASHSize) 
 #define DFLASHBase 0x10000000
 #define DFLASHSize 0x10001000
 #define DFLASHLimit (FLASHBase + FLASHSize) 

#ifdef REMAP
  #define SRAMBase 0x00000000
  #define SRAMSize 0x00000800
  #define SRAMLimit (SRAMBase + SRAMSize) 
  #define MEMVectorBase 0x00000700
  #define MEMVectorSize (0x50<<2)
#else
  #define SRAMBase 0x20000000
  #define SRAMSize 0x00001000
  #define SRAMLimit (SRAMBase + SRAMSize) 
  #define MEMVectorBase 0x20000F00
  #define MEMVectorSize (0x50<<2)
#endif

//--Peripheral Address Setting
#define APBPeriBase     0x40000000 

//--Each Peripheral Address Setting
//#define APB_SFMBase     (APBPeriBase + 0x10000)
#define APB_IFCBase    	(APBPeriBase + 0x10000)
#define APB_SYSCONBase  (APBPeriBase + 0x11000)
#define APB_ETCBBase    (APBPeriBase + 0x12000)

#define APB_TKEYBase    (APBPeriBase + 0x20000)
#define APB_TKEYBUFBase	(APBPeriBase + 0x21000)
#define APB_ADC0Base    (APBPeriBase + 0x30000)

#define AHBGPIOBase 	0x60000000
#define APB_GPIOA0Base  (AHBGPIOBase + 0x0000) //A0  
#define APB_GPIOB0Base  (AHBGPIOBase + 0x2000) //B0 
#define APB_IGRPBase	(AHBGPIOBase + 0xF000)

#define APB_BT1Base      (APBPeriBase + 0x52000)
#define APB_BT0Base      (APBPeriBase + 0x51000)
#define APB_CNTABase    (APBPeriBase + 0x50000)

#define APB_GPT0Base    (APBPeriBase + 0x55000)

#define APB_EPT0Base    (APBPeriBase + 0x59000)

#define APB_RTCBase     (APBPeriBase + 0x60000)
#define APB_LPTBase     (APBPeriBase + 0x61000)
#define APB_WWDTBase	(APBPeriBase + 0x62000)

#define APB_UART0Base   (APBPeriBase + 0x80000)
#define APB_UART1Base   (APBPeriBase + 0x81000)
#define APB_UART2Base   (APBPeriBase + 0x82000)

#define APB_SPI0Base    (APBPeriBase + 0x90000)
#define APB_SIO0Base    (APBPeriBase + 0xB0000)

#define APB_I2C0Base    (APBPeriBase + 0xA0000)



#define AHB_CRCBase     0x50000000
#define APB_HWDBase		0x70000000		

//--Interrupt Bit Position
#define CORET_INT   (0)       //IRQ0
#define SYSCON_INT  (1)       //IRQ1
#define IFC_INT     (2)       //IRQ2
#define ADC_INT     (3)       //IRQ3
#define EPT0_INT    (4)       //IRQ4
//DUMMY       //IRQ5
//DUMMY       //IRQ6
#define EXI0_INT    (7)       //IRQ7
#define EXI1_INT    (8)       //IRQ8
#define GPT0_INT    (9)       //IRQ9 
//DUMMY      //IRQ10
//DUMMY      //IRQ11
//DUMMY      //IRQ12
#define UART0_INT   (13)      //IRQ13
#define UART1_INT   (14)      //IRQ14
//DUMMY      //IRQ15
//DUMMY      //IRQ16
#define I2C_INT     (17)      //IRQ17
//DUMMY      //IRQ18
#define SPI_INT     (19)      //IRQ19
//DUMMY      //IRQ20
#define EXI2_INT    (21)      //IRQ21
#define EXI3_INT    (22)      //IRQ22
#define EXI4_INT    (23)      //IRQ23
#define TC3_INT     (24)      //IRQ24
#define CMP0_INT    (25)      //IRQ25
#define CMP1_INT    (26)      //IRQ26
//DUMMY      //IRQ27
#define BT0_INT     (28)      //IRQ28
#define BT1_INT     (29)      //IRQ29
//DUMMY      //IRQ30
//DUMMY      //IRQ31



extern CSP_IFC_T 	*IFC;

extern CSP_SYSCON_T *SYSCON   ;

//extern CSP_ETCB_T   *ETCB ;
//
//extern CSP_TKEY_T 	*TKEY     ;
//extern CSP_TKEYBUF_T 	*TKEYBUF     ;
//extern CSP_ADC12_T 	*ADC0     ;
//
extern CSP_GPIO_T 	*GPIOA0   ;
extern CSP_GPIO_T 	*GPIOB0   ;
extern CSP_IGRP_T	*GPIOGRP  ;
//
//extern CSP_UART_T 	*UART0    ;
//extern CSP_UART_T 	*UART1    ;
//
//extern CSP_SSP_T  	*SPI0     ;
//
//extern CSP_I2C_T  	*I2C0     ;
//extern CSP_CA_T  	*CA0      ;
//
//extern CSP_GPT_T 	*GPT0     ;
//
//extern CSP_EPT_T 	*EPT0     ;
//
//extern CSP_LPT_T 	*LPT      ;
//
extern CSP_BT_T  	*BT0      ;
extern CSP_BT_T  	*BT1      ;
//
//extern CSP_CRC_T 	*CRC      ;


//ISR Define for generating special interrupt related ASM (CK802), with compile option -mistack
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
void WWDTHandler(void) __attribute__((isr));
void EXI0IntHandler(void) __attribute__((isr));
void EXI1IntHandler(void) __attribute__((isr));
void EXI2to3IntHandler(void) __attribute__((isr));
void EXI4to9IntHandler(void) __attribute__((isr));
void EXI10to15IntHandler(void) __attribute__((isr));
void UART0IntHandler(void) __attribute__((isr));
void UART1IntHandler(void) __attribute__((isr));
void UART2IntHandler(void) __attribute__((isr));
void I2CIntHandler(void) __attribute__((isr));
void GPT0IntHandler(void) __attribute__((isr));
void LEDIntHandler(void) __attribute__((isr));
void TKEYIntHandler(void) __attribute__((isr));
void SPI0IntHandler(void) __attribute__((isr));
void SIO0IntHandler(void) __attribute__((isr));
void CNTAIntHandler(void) __attribute__((isr));
void RTCIntHandler(void) __attribute__((isr));
void LPTIntHandler(void) __attribute__((isr));
void BT0IntHandler(void) __attribute__((isr));
void BT1IntHandler(void) __attribute__((isr));

extern int __divsi3 (int a, int b);
extern unsigned int __udivsi3 (unsigned int a, unsigned int b);
extern int __modsi3 (int a, int b);
extern unsigned int __umodsi3 (unsigned int a, unsigned int b);
extern void delay_nms(unsigned int t);
extern void delay_nus(unsigned int t);

#endif

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/