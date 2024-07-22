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
    syscon_config();                                               //syscon相关初始化
	CK_CPU_ENALLNORMALIRQ;                                         //enable all IRQ

}

void syscon_config(void)
{
		
	/*------------  系统时钟和外设时钟设置  --------------------------------*/	
	syscon_osc_enable(ENDIS_IMOSC);												//使能IMOSC
	syscon_pll_configure(PLL_TYPE_DIG, PLL_SRC_IMOSC, ENABLE);					//设置IMOSC为PLL的源，使用digital PLL，PLL失锁时产生系统复位
	syscon_osc_enable(ENDIS_PLL);												//使能pll
	syscon_hclk_pclk_configure(SYSCLK_PLL, HCLK_DIV_1,PCLK_DIV_1,F_24_48MHz);   //将PLL作为系统时钟，HCLK = PLLCLK, PCLK = HCLK/1,系统时钟频率在24～48MHz之间
	
	syscon_iwdt_disable();														//disable IWDT	
  
}


/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/