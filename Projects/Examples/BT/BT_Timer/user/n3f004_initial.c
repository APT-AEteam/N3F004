/***********************************************************************//** 
 * \file  n3f004_initial.c
 * \brief initialization for all IPs
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/

/****************************************************
//include
*****************************************************/
#include "n3f004.h"

void syscon_config(void);



void n3f004_init(void)
{
//	VIC->ISER[0U] = (0xffffffff);									// 使能VIC层所有的中断，如果要响应IP的中断处理函数，还有另外两个使能开关
//																	// 1) 使能IP层中断：如 xx_IMER
//																	// 2) 使能总中断： CK_CPU_ENALLNORMALIRQ
 
    syscon_config();                                               //syscon相关初始化
	CK_CPU_ENALLNORMALIRQ;                                         //enable all IRQ
//------------------------------------------------------------/
//Other IP config
//------------------------------------------------------------/
	//GPIO_CONFIG();                                                //GPIO initial    
	//CORET_CONFIG();												//CORET initial 
	//EPT0_CONFIG();                                                //EPT0 initial 
	//GPT0_CONFIG();												//GPT0 initial
	//LPT_CONFIG();													//LPT initial	
	//BT_CONFIG();													//BT initial
	//COUNTA_CONFIG();                                              //CountA initial	
	//RTC_CONFIG();													//RCT initial		              
	//ET_CONFIG();													//ETCB initial
    //I2C_MASTER_CONFIG();                                          //I2C harware master initial 
	//I2C_SLAVE_CONFIG();                                           //I2C harware slave initial 
	//SPI_MASTER_CONFIG();											//SPI Master initial 	
	//SPI_SLAVE_CONFIG();											//SPI Slaver initial 
    //SIO_CONFIG();													//SIO initial
    //UART0_CONFIG();                                               //UART0 initial 
	//UART1_CONFIG();                                               //UART1 initial 
	//UART2_CONFIG();                                               //UART2 initial 
	//ADC12_CONFIG();                                               //ADC initial 
	//TK_CONFIG();													//Touch Key initial
}

void syscon_config(void)
{
		
/*------时钟切换前需要执行该函数，否则可能因为和flash的配置不匹配而出现跑飞的现象--------*/
	sysclk_clear();                                                       //
	
/*------------  EMOSC 相关  --------------------------------*/	
//	emosc_ostr_config(0xad, 0x1f, EM_HIGHF, ENABLE, EM_FLSEL_10NS);			//EMOSC工作在高频模式，10ns过滤使能，增益0x1f，振荡0xad后稳定位置起
//	emosc_pin_init();
//	syscon_general_cmd(ENABLE,ENDIS_EMOSC);									//使能EMOSC
	
/*------------  系统时钟和外设时钟设置  --------------------------------*/	
	syscon_general_cmd(ENABLE,ENDIS_IMOSC);									//使能IMOSC
	pll_config(PLL_TYPE_DIG, PLL_SRC_IMOSC, ENABLE);
	sysclk_hclk_pclk_config(SYSCLK_PLL, HCLK_DIV_1,PCLK_DIV_1,F_24_48MHz);  //
	
	
/*------------  IWDT FUNTION  --------------------------------*/
    syscon_general_cmd(ENABLE,ENDIS_ISOSC);									//使能ISOSC
	syscon_iwdt_config(IWDT_TIME_2000, IWDT_INTW_7_8);						//IWDT,复位时间2s，中断时间  2*7/8 (s)
    syscon_iwdt_cmd(DISABLE);												//enable/disable IWDT	
	syscon_iwdtcnt_reload();												//喂狗
	syscon_iwdt_int_enable();
													
/*------------  Clock Output(一般用于调试阶段) --------------------------------*/	
	clo_pin_init(CLO_PA08);													//CLO管脚设置
	syscon_clo_src_set(CLO_HCLK,CLO_DIV16);									//CLO输出时钟源及分频设置
	
	
/*------------  LVD FUNTION  --------------------------------*/ 
	syscon_lvd_config(ENABLE , LVD39, LVR19 , LVDINT_F);
	syscon_lvd_int_enable();
  
}


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/