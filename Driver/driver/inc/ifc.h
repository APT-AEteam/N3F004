/***********************************************************************//** 
 * \file  ifc.h
 * \brief  ifc description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _IFC_H
#define _IFC_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"


typedef volatile struct {
        __IM uint32_t IDR ;
        __IOM uint32_t CEDR ;
        __IOM uint32_t SRR ;
        __IOM uint32_t CMR ;
        __IOM uint32_t CR ;
        __IOM uint32_t MR ;
        __IOM uint32_t ADDR ;
        uint32_t RESERVED ;
        __OM uint32_t KR ;
        __IOM uint32_t IMCR ;
        __IM uint32_t RISR ;
        __IM uint32_t MISR ;
        __OM uint32_t ICR ;
} csp_ifc_t ;

typedef enum{
	IFC_PFLASH = 0,
	IFC_DFLASH
}ifc_type_e;

/******************************************************************************
* CEDR : Clock control
******************************************************************************/
#define  IFC_CLKEN  (0x01ul) 

/******************************************************************************
* CMR : IFC Command Regsiter
******************************************************************************/
#define  IFC_HIDM0  ((0x0ul)<<8) 
#define  IFC_HIDM1  ((0x1ul)<<8) 

typedef enum{
	IFC_SWDP	= 0x1 << 19,
	IFC_RDP		= 0x1 << 18,
	IFC_HDP_32K	= 0x1 << 22,
	IFC_HDP_16K	= 0x1 << 21,
	IFC_HDP_8K	= 0x1 << 16,
	IFC_HDP_FULL= 0x1 << 17,
}ifc_prot_e;

typedef enum{
	IFC_PROGRAM = 1,
	IFC_PAGE_ERASE = 2,
	IFC_PAGE_ERASE_HIDM1 = IFC_PAGE_ERASE | IFC_HIDM1,
	IFC_CHIP_ERASE = 4,
	IFC_USEROPTION_ERASE = 5|IFC_HIDM1,
	IFC_PRE_PGM = 6,
	IFC_PRE_PGM_HIDM1 = IFC_PRE_PGM | IFC_HIDM1,
	IFC_PAGE_LAT_CLR = 7,
	IFC_PAGE_LAT_CLR_HIDM1 = IFC_PAGE_LAT_CLR | IFC_HIDM1,
	IFC_SWDREMAP_ERASE = 0xd|IFC_HIDM1,
	IFC_SWDREMAP_ENABLE = 0xe|IFC_HIDM1,
	IFC_USEROPTION_PGM = 0xf|IFC_HIDM1
}ifc_cmd_e;

/******************************************************************************
* MR : IFC Operation Mode 
******************************************************************************/
#define  IFC_START  (0x01ul) 

///MR: IFC operation mode
#define  IFC_PF_WAIT_POS (0)
#define  IFC_PF_WAIT_MSK (0x7ul << IFC_PF_WAIT_POS)
#define  IFC_PF_WAIT0 (0x0ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT1 (0x1ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT2 (0x2ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT3 (0x3ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT4 (0x4ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT5 (0x5ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT6 (0x6ul << IFC_PF_WAIT_POS) 
#define  IFC_PF_WAIT7 (0x7ul << IFC_PF_WAIT_POS) 

#define  IFC_DFLASH_PMODE_POS 	8
#define  IFC_DFLASH_PMODE_MSK 	(0x1 <<IFC_DFLASH_PMODE_POS)
#define  IFC_DFLASH_PMODE 		(0x1 <<IFC_DFLASH_PMODE_POS)

#define  IFC_PF_SPEED_POS 	(16)
#define  IFC_PF_SPEED_MSK 	(0x1<<IFC_PF_SPEED_POS)
#define  IFC_HIGH_SPEED 	(0x1ul)
#define  IFC_LOW_SPEED 		(0x0ul)


/******************************************************************************
* KR: ISP key
******************************************************************************/
#define  IFC_USER_KEY 		(0x5A5A5A5Aul)
#define  SET_USER_KEY 		(IFC->KR = IFC_USER_KEY)



/******************************************************************************
 ifc Function Declaration
******************************************************************************/
/** \brief Chip(PROM + UserOption + Protection) Erase
 * 
 *  \param[in] none
 *  \return none
 */ 
void chip_erase(void);


/** \brief erase one page(DFLASH or PFLASH). 
 *  \brief NOTE!!! Extra ERASE is NOT needed before programming, otherwise, endurance would decrease.
 *  \param[in] wPageStAddr: Page start address
 *  \return none
 */
void page_erase(U32_T wPageStAddr);


/** \brief 		write n words within a page  (Not Support across page writing!!!)
 *              CPU would halt for around 4.2ms when IFC programming is excecuted.

 *  \param[in] 	wAddr:		PGM start address
 * 	\param[in] 	wDataNum:	number of words to be written
 *  \param[in]	pwData:		point points to data to be written
 *  \return error code:		return CSI_ERROR when PGM verify fails \ref csi_error_t	
 */

void page_program_u32(U32_T wAddr, U32_T wDataNum, U32_T *pwData);

/** \brief 		write n bytes within a page  (Not Support across page writing!!!)
 *              1) CPU would halt for around 4.2ms when IFC programming is excecuted.
				2) Start Address has to be word alligned
 *  \param[in] 	wAddr:		PGM start address
 * 	\param[in] 	wDataNum:	number of words to be written
 *  \param[in]	pwData:		point points to data to be written
 *  \return error code:		return CSI_ERROR when PGM verify fails \ref csi_error_t	
 */
void page_program_u8(U32_T wAddr,U32_T wDataNum, U8_T *pbyData);


/** \brief Read data(byte) from Flash.
 *  \param[in] 	wAddr：		data address（(SHOULD BE WORD ALLIGNED)）
 *  \param[out] wData：		data  Pointer to a buffer storing the data read from Flash.
 *  \param[in] 	wDataNum：	number of data（WORDs）to read.
 *  \return none
 */
void read_data_array_u8(U32_T wRdStartAdd,U32_T wDataNum, U8_T * pbyData);

/** \brief Read data(word) from Flash.
 *  \param[in] 	wAddr：		data address（(SHOULD BE WORD ALLIGNED)）
 *  \param[out] wData：		data  Pointer to a buffer storing the data read from Flash.
 *  \param[in] 	wDataNum：	number of data（WORDs）to read.
 *  \return none
 */
 
void read_data_array_u32(U32_T wRdStartAdd,U32_T wDataNum,volatile U32_T *pbyData);




#endif   /**< IFC_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/
