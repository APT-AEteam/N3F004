/***********************************************************************//** 
 * \file  crc.h
 * \brief  CRC description and  functions at register level 
 * \copyright Copyright (C) 2015-2024@ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-4 <td>V1_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/


#ifndef _CRC_H
#define _CRC_H

#include "types_local.h"

typedef struct
{
    __IM	U32_T RSVD;
	__IOM	U32_T CEDR;            /**< Clock Enable/Disable Register	     */
	__OM	U32_T SRR;             /**< Software Reset Register	     */
	__IOM	U32_T CR;              /**< Control Register	             */
	__IOM	U32_T SEED;            /**< Seed Value Register	             */
	__OM	U32_T DATAIN;          /**< Data in Value Register	             */
	__IM	U32_T DATAOUT;         /**< Data out Value Register	     */
} CSP_CRC_T;

/******************************************************************************
************************* CRC Registers Definition ****************************
******************************************************************************/


/******************************************************************************
*  CEDR : Clock Enable/Disable Register
*******************************************************************************/
#define CRC_CLKEN          (0x01ul << 0)         /**< IP Clock             */

/******************************************************************************
*  SRR : Software Reset Register
 ********************************************************************************/
#define CRC_SWRST          (0x01ul << 31)         /**< Software Reset         */

/******************************************************************************
*  CR : CRC Control Register
 *********************************************************************************/
#define CRC_XORIN_POS	(0ul)
#define CRC_XORIN_MSK	(0x1)
#define CRC_XOROUT_POS	(1ul)
#define CRC_XOROUT_MSK	(0x1 << CRC_XOROUT_POS)
#define CRC_REFIN_POS	(2ul)
#define CRC_REFIN_MSK	(0x1 << CRC_REFIN_POS)
#define CRC_REFOUT_POS	(3ul)
#define CRC_REFOUT_MSK	(0x1 << CRC_REFOUT_POS)
#define CRC_POLY_POS	(4ul)
#define CRC_POLY_MSK	(0x3 << CRC_POLY_POS)
typedef enum{
	CRC_DISABLE =0,
	CRC_ENABLE
}crc_funcen_e;

typedef enum
{
    POLY_CCITT = 0,
	POLY_16 = 2,
	POLY_32 = 3,
}crc_poly_e;

/******************************************************************************
*************************   CRC  functions  declare ****************************
******************************************************************************/
/** \brief CRC enable/disable
 * 
 *  \param[in] eStatus:CRC enable or disable control \ref crc_funcen_e
 * 			   
 *  \return none
 */ 
void CRC_CMD(crc_funcen_e eStatus);
/** \brief CRC software reset
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void CRC_Soft_Reset(void);
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
void CRC_Configure(crc_funcen_e eXorIn,crc_funcen_e eXorOut,crc_funcen_e eRefIn,crc_funcen_e eRefOut, crc_poly_e ePoly);

/** \brief CRC seed write
 * 
 *  \param[in] wSeedVal: seed val, range :0~0xffffffff
 *
 *  \return none
 */ 
void CRC_Seed_Write(U32_T wSeedVal);

/** \brief CRC seed read
 * 
 *  \param[in] none
 *
 *  \return seed val
 */ 
U32_T CRC_Seed_Read(void);

/** \brief CRC input data write
 * 
 *  \param[in] wDataIn: crc input data , range :0~0xffffffff
 *
 *  \return none
 */ 
void CRC_Datain(U32_T wDataIn);
/** \brief CRC output data read
 * 
 *  \param[in] none
 *
 *  \return CRC output data
 */ 
U32_T CRC_Result_Read(void);
/** \brief CRC calc 32bit input
 * 
 *  \param[in] ptData : pointer of 32bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC32(U32_T *ptData, U32_T wNum);
/** \brief CRC calc 16bit input
 * 
 *  \param[in] ptData : pointer of 16bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC16(U16_T *ptData, U32_T wNum);
/** \brief CRC calc 8bit input
 * 
 *  \param[in] ptData : pointer of 8bit input data
 *  \param[in] wNum : input data num
 *
 *  \return CRC output data
 */ 
U32_T Chip_CRC_CRC8(U8_T *ptData, U32_T wNum);



#endif /* CSP_CRC_H */




