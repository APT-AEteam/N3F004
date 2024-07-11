/***********************************************************************//** 
 * \file  ifc.c
 * \brief  IFC driver
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"



volatile unsigned char f_Drom_writing=0;


/* externs--------------------------------------------------------------------*/
/* private function-----------------------------------------------------------*/
static void apt_ifc_step_sync(ifc_cmd_e eCmd, uint32_t wPageStAddr);
/* global variablesr----------------------------------------------------------*/
volatile bool g_bFlashPgmDne = 1;
/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/** \brief Chip(PROM + UserOption + Protection) Erase
 * 
 *  \param[in] none
 *  \return none
 */ 
void chip_erase(void)
{
	apt_ifc_step_sync(IFC_CHIP_ERASE, 0);

}


/** \brief erase one page(DFLASH or PFLASH). 
 *  \brief NOTE!!! Extra ERASE is NOT needed before programming, otherwise, endurance would decrease.
 *  \param[in] wPageStAddr: Page start address
 *  \return none
 */
void page_erase(U32_T wPageStAddr)
{
	if (((wPageStAddr < DFLASH_BASE) && ((wPageStAddr )>PFLASH_LIMIT) )|| ((wPageStAddr>=DFLASH_BASE)&& ((wPageStAddr )> DFLASH_LIMIT))) {
		return;
	}
	apt_ifc_step_sync(IFC_PAGE_ERASE, wPageStAddr);
	
}


/** \brief 		write n words within a page  (Not Support across page writing!!!)
 *              CPU would halt for around 4.2ms when IFC programming is excecuted.

 *  \param[in] 	wAddr:		PGM start address
 * 	\param[in] 	wDataNum:	number of words to be written
 *  \param[in]	pwData:		point points to data to be written
 *  \return error code:		return CSI_ERROR when PGM verify fails \ref csi_error_t	
 */

void page_program_u32(U32_T wAddr, U32_T wDataNum,U32_T *pwData)
{
	
	
	U32_T i,j,wPageStAddr,wBuff[PFLASH_PAGESIZE/4] = {0};
	U8_T byPageSize;
	
	g_bFlashPgmDne = 0;
	if (wAddr >= DFLASH_BASE) {
		wPageStAddr = wAddr & DFLASH_PAGE_MSK; 
		byPageSize = DFLASH_PAGESIZE/4;
	}
	else {
		wPageStAddr = wAddr & PFLASH_PAGE_MSK;
		byPageSize = PFLASH_PAGESIZE/4;
	}
	
	wAddr -= wPageStAddr;
	wAddr = wAddr >> 2;	

	///step1
	apt_ifc_step_sync( IFC_PAGE_LAT_CLR, wPageStAddr);
	///step2
	for(i=0; i< byPageSize; i++) {
      if( i == wAddr )
	  {
		for(j = 0; j<wDataNum; j++)
			wBuff[i++] = pwData[j];
		i--;
	  }
      else {
        wBuff[i] = *(uint32_t *)(wPageStAddr+4*i);
      }
    }
	
	for(i=0; i<byPageSize; i++) {
        *(uint32_t *)(wPageStAddr+4*i) = wBuff[i];
    }
	///step3
	apt_ifc_step_sync( IFC_PRE_PGM, wPageStAddr);

	///step4
	apt_ifc_step_sync( IFC_PROGRAM, wPageStAddr);

	
	///step5
	apt_ifc_step_sync( IFC_PAGE_ERASE, wPageStAddr);
	///step6
	apt_ifc_step_sync( IFC_PROGRAM, wPageStAddr);

	g_bFlashPgmDne = 1;
	
}

/** \brief 		write n bytes within a page  (Not Support across page writing!!!)
 *              1) CPU would halt for around 4.2ms when IFC programming is excecuted.
				2) Start Address has to be word alligned
 *  \param[in] 	wAddr:		PGM start address
 * 	\param[in] 	wDataNum:	number of words to be written
 *  \param[in]	pwData:		point points to data to be written
 *  \return error code:		return CSI_ERROR when PGM verify fails \ref csi_error_t	
 */
void page_program_u8(U32_T wAddr,U32_T wDataNum, U8_T *pbyData)
{
	U32_T i,j,wPageStAddr;
	;
	U8_T byPageSize, byBuff[PFLASH_PAGESIZE];
	
		
	g_bFlashPgmDne = 0;
	if (wAddr >= DFLASH_BASE) {
		wPageStAddr = wAddr & DFLASH_PAGE_MSK; 
		byPageSize = DFLASH_PAGESIZE;
	}
	else {
		
		wPageStAddr = wAddr & PFLASH_PAGE_MSK;
		byPageSize = PFLASH_PAGESIZE;
	}
	
	wAddr -= wPageStAddr;

	///step1
	apt_ifc_step_sync( IFC_PAGE_LAT_CLR, wPageStAddr);
	///step2
	for(i=0; i< byPageSize; i++) {
      if( i == wAddr )
	  {
		j = 0;
		while(wDataNum > 0) {
			byBuff[i++] = pbyData[j++];  
			wDataNum --;
		}
		i -= 1;
	  }
      else {
        byBuff[i] = *(U8_T *)(wPageStAddr+i);
      }
    }
	
	for(i=0; i<byPageSize/4; i+=4) {
        *(U32_T *)(wPageStAddr+i) = byBuff[i] + (byBuff[i+1] << 8) + (byBuff[i+2] << 16) + (byBuff[i+3] <<24);
		
    }
	///step3
	apt_ifc_step_sync( IFC_PRE_PGM, wPageStAddr);

	///step4
	apt_ifc_step_sync( IFC_PROGRAM, wPageStAddr);

	///step5
	apt_ifc_step_sync( IFC_PAGE_ERASE, wPageStAddr);
	///step6
	apt_ifc_step_sync( IFC_PROGRAM, wPageStAddr);

	g_bFlashPgmDne = 1;
}


/** \brief Read data(byte) from Flash.
 *  \param[in] 	wAddr：		data address（(SHOULD BE WORD ALLIGNED)）
 *  \param[out] wData：		data  Pointer to a buffer storing the data read from Flash.
 *  \param[in] 	wDataNum：	number of data（WORDs）to read.
 *  \return none
 */
void read_data_array_u8(U32_T wRdStartAdd,U32_T wDataNum, U8_T * pbyData)
{
	U32_T i;
	for (i=0;i<wDataNum;i++)
	{
		if((i!=0)&&(i%4==0))
		{
			wRdStartAdd +=4;
		}	
		*pbyData=*(U8_T *)(wRdStartAdd+ (i%4));
		pbyData++;
	}
}

/** \brief Read data(word) from Flash.
 *  \param[in] 	wAddr：		data address（(SHOULD BE WORD ALLIGNED)）
 *  \param[out] wData：		data  Pointer to a buffer storing the data read from Flash.
 *  \param[in] 	wDataNum：	number of data（WORDs）to read.
 *  \return none
 */
 
void read_data_array_u32(U32_T wRdStartAdd,U32_T wDataNum,volatile U32_T *pbyData)
{
	U32_T i;
	for (i=0;i<wDataNum;i++)
	{
		*pbyData=*(U32_T *)(wRdStartAdd+4*i);
		pbyData++;
	}
}


/** \brief     IFC operation step, used for normal mode operations
 * 
 *  \param[in] eCmd:		ifc command \ref ifc_cmd_e
 *  \param[in] wPageStAddr:	page address
 *  \return none
 */
static void apt_ifc_step_sync(ifc_cmd_e eCmd, uint32_t wPageStAddr)
{
	IFC->CEDR = IFC_CLKEN;	
	SET_USER_KEY;	
	IFC->CMR = eCmd;
	IFC->ADDR = wPageStAddr;
	IFC->CR = IFC_START;
	while(IFC->CR != 0);
}



/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/