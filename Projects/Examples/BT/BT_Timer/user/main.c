/***********************************************************************//** 
 * \file  main.c
 * \brief main function
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

extern void n3f004_init(void);

/****************************************************
//define
*****************************************************/

/****************************************************
//extern
*****************************************************/
extern void delay_nms(unsigned int t);
extern void APT32F102_init(void);
extern void my_printf(const char *fmt, ...);	

/*************************************************************/
//main
/*************************************************************/
int main(void) 
{
//	delay_nms(1000);
	n3f004_init();

    while(1)
	{
		syscon_iwdtcnt_reload();  
		//......
    }
}
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/