/***********************************************************************//** 
 * \file  coret.h
 * \brief  coret description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CORET_H
#define _CORET_H

/* Includes ------------------------------------------------------------------*/

/******************************************************************************
************************* coret Registers Definition *************************
******************************************************************************/
#define CORET_CSR_RST     	(0x00000004)
#define CORET_RVR_RST     	(0x00000000)
#define CORET_CVR_RST     	(0x00000000)
#define CORET_CALIB_RST     (0x00000000)




extern void CORET_DeInit(void);
extern void CORET_Int_Enable(void);
extern void CORET_Int_Disable(void);
extern void CORET_WakeUp_Enable(void);
extern void CORET_WakeUp_Disable(void);
extern void CORET_start(void);
extern void CORET_stop(void);
extern void CORET_CLKSOURCE_EX(void);
extern void CORET_CLKSOURCE_IN(void);
extern void CORET_TICKINT_Enable(void);
extern void CORET_TICKINT_Disable(void);
extern void CORET_reload(void);

#endif   /**< apt32f102_coret_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/