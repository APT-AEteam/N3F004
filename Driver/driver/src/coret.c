/***********************************************************************//** 
 * \file  coret.c
 * \brief  coret driver
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
/* global variablesr----------------------------------------------------------*/
/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/** \brief Deinitializes coret registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */  
void CORET_DeInit(void)
{
	CORET->CTRL = CORET_CSR_RST;
	CORET->LOAD = CORET_RVR_RST;
	CORET->VAL = CORET_CVR_RST;
}

/** \brief Enable CORET Interrupt (VIC level)
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_Int_Enable(void)
{
    CORET->LOAD = 0x0;							// Clear counter and flag
	csi_vic_enable_irq(CORET_INT);    
}

/** \brief Disable CORET Interrupt (VIC level)
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_Int_Disable(void)
{
	csi_vic_disable_irq(CORET_INT);   
}

/** \brief Start CORET 
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_start(void)
{
	CORET->CTRL|=0x01;
}

/** \brief Stop CORET 
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_stop(void)
{
	CORET->CTRL&=0Xfffffffe;
}


/** \brief Select HCLK/8 as CORET working clock
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_CLKSOURCE_EX(void)
{
	CORET->CTRL&=0Xfffffffb;
}


/** \brief Select HCLK as CORET working clock
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_CLKSOURCE_IN(void)
{
	CORET->CTRL|=0x04;
}

/** \brief Enable CORET interrupt(IP level)
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_TICKINT_Enable(void)
{
    CORET->CTRL|=0x02;
}

/** \brief Disable CORET interrupt(IP level)
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_TICKINT_Disable(void)
{
   CORET->CTRL&=0Xfffffffd;
}

/** \brief Reload CORET
 * 
 *  \param[in] none
 *  \return none
 */
void CORET_reload(void)
{
	CORET->LOAD = 0x0;							// Clear counter and flag
}

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/