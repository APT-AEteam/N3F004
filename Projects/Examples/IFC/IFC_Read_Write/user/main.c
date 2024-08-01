/***********************************************************************//** 
 * \file  main.c
 * \brief IFC 示例代码的main函数
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
/* global variables----------------------------------------------------------*/
/* Private variables---------------------------------------------------------*/
U8_T byWriteData[5] = {1,2,3,4,5};
U32_T wWriteData[8] = {[0 ... 3] = 0x55555555, [4 ... 7] = 0xaaaaaaaa };

U8_T byReadData[5] = {0};
U32_T wReadData[8] = {0};

/* defines -------------------------------------------------------------------*/


/*************************************************************/
//main
/*************************************************************/
int main(void) 
{
	
	
	page_program_u32(0x10000004,8,wWriteData);	 	//写入word据类型，起始地址必须是4的倍数
	read_data_array_u32(0x10000004, 8, wReadData);	//回读word数据类型，起始地址必须是4的倍数
	
	for (U8_T i = 0; i<8; i++)
	{
		if (wWriteData[i] != wReadData[i]) {		//回读校验，如果有错，记录在SYSCON[UREG0/1]
			syscon_ureg_write(USER_REG0, i);
			syscon_ureg_write(USER_REG1, 0xee);
			break;
		}
	}
	page_program_u8(0x10000001,5,byWriteData);		//写入byte数据类型
	read_data_array_u8(0x10000001, 5, byReadData);	//回读byte数据类型
	for (U8_T i = 0; i<5; i++)
	{
		if (byWriteData[i] != byReadData[i]) {		//回读校验，如果有错，记录在SYSCON[UREG2/3]
			syscon_ureg_write(USER_REG2, i);
			syscon_ureg_write(USER_REG3, 0xee);
			break;
		}
	}
	
	
    while(1)
	{
		syscon_iwdt_reload();  
		//......
    }
}
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/