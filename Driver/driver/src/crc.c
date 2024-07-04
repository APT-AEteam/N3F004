/***********************************************************************//** 
 * \file  crc.c
 * \brief BT function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-04<td>V1_0_0  <td>GQQ  <td>initial
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


/** \brief CRC enable/disable
 * 
 *  \param[in] eStatus:CRC enable or disable control \ref crc_funcen_e
 * 			   
 *  \return none
 */ 
void CRC_CMD(crc_funcen_e eStatus)
{
	if (eStatus != DISABLE)
	{
		CRC->CEDR  =CRC_CLKEN;						//SET
	}
	else
	{
		CRC->CEDR  =~CRC_CLKEN;						//CLR
	}
}

/** \brief CRC software reset
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void CRC_Soft_Reset(void)
{
	CRC->SRR = CRC_SWRST;
}


/** \brief CRC CR config
 * 
 *  \param[in] eXorIn : XOR of input data control :enable or disable \ref  crc_funcen_e
 * \param[in] eXorOut : XOR of output data control :enable or disable \ref  crc_funcen_e
 * \param[in] eRefIn:  REF of input data control :enable or disable \ref  crc_funcen_e
 * \param[in] eRefOut:  REF of output data control :enable or disable \ref  crc_funcen_e
 * \param[in] ePoly: POLY select \ref  crc_poly_e
 *
 *  \return none
 */ 
void CRC_Configure(crc_funcen_e eXorIn,crc_funcen_e eXorOut,crc_funcen_e eRefIn,crc_funcen_e eRefOut, crc_poly_e ePoly)
{
	CRC->CR = (eXorIn<< CRC_XORIN_POS)|(eXorOut<<CRC_XOROUT_POS) |(eRefIn<<CRC_REFIN_POS) |(eRefOut<<CRC_REFOUT_POS)| (ePoly<<CRC_POLY_POS);
}


/** \brief CRC seed write
 * 
 *  \param[in] wSeedVal: seed val, range :0~0xffffffff
 *
 *  \return none
 */ 
void CRC_Seed_Write(U32_T wSeedVal)
{
	CRC->SEED = wSeedVal;
}

/** \brief CRC seed read
 * 
 *  \param[in] none
 *
 *  \return seed val
 */ 
U32_T CRC_Seed_Read(void)
{
	return CRC->SEED;
}

/** \brief CRC input data write
 * 
 *  \param[in] wDataIn: crc input data , range :0~0xffffffff
 *
 *  \return none
 */ 
void CRC_Datain(U32_T wDataIn)
{
	CRC->DATAIN=wDataIn;
}

/** \brief CRC output data read
 * 
 *  \param[in] none
 *
 *  \return CRC output data
 */ 
U32_T CRC_Result_Read(void)
{
	return CRC->DATAOUT;
}

/** \brief CRC calc 32bit input
 * 
 *  \param[in] ptData : pointer of 32bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC32(U32_T *ptData, U32_T wNum)
{
	while (wNum > 0) {
		CRC_Datain(*ptData);
		ptData++;
		wNum--;
	}
	return CRC_Result_Read();
}

/** \brief CRC calc 16bit input
 * 
 *  \param[in] ptData : pointer of 16bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC16(U16_T *ptData, U32_T wNum)
{
	U32_T i,j;
	U8_T data_temp;
	for (i=0; i<wNum; i++)
	{
		for(j=0;j<=1;j++)
		{
			if(j==0)data_temp=*ptData>>8;
			if(j==1)data_temp=*ptData&0xff;
			*(U8_T *)(AHB_CRCBase + 0x14 + (i%4)) = data_temp;
		}
		ptData++;
	}
	return CRC_Result_Read();
}

/** \brief CRC calc 8bit input
 * 
 *  \param[in] ptData : pointer of 8bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC8(U8_T *ptData, U32_T wNum)
{
	U32_T i;
	for (i=0; i<wNum; i++)
	{
		*(U8_T *)(AHB_CRCBase + 0x14 + (i%4)) = *ptData;
		ptData++;
	}
	return CRC_Result_Read();
}

