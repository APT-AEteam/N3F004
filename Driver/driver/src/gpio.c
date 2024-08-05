/***********************************************************************//** 
 * \file  gpio.c
 * \brief  gpio driver
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



/** \brief Deinitialize GPIO registers to their reset status
 * 
 *  \param[in] none
 *  \return none
 */ 
void gpio_deinit(void)
{
    GPIOA0->CONLR &= 0xFF000000;                     
    GPIOA0->CONHR = GPIO_RESET_VALUE;
    GPIOB0->CONLR = GPIO_RESET_VALUE;                     
    GPIOB0->CONHR = GPIO_RESET_VALUE;
    GPIOA0->WODR  = GPIO_RESET_VALUE; 
    GPIOB0->WODR  = GPIO_RESET_VALUE;
    GPIOA0->SODR  = GPIO_RESET_VALUE; 
    GPIOB0->SODR  = GPIO_RESET_VALUE;
    GPIOA0->CODR  = GPIO_RESET_VALUE; 
    GPIOB0->CODR  = GPIO_RESET_VALUE;
	GPIOA0->FLTEN = 0xffff;
	GPIOB0->FLTEN = 0x3f;
    GPIOA0->PUDR  = GPIO_RESET_VALUE; 
    GPIOB0->PUDR  = GPIO_RESET_VALUE;
    GPIOA0->DSCR  = GPIO_RESET_VALUE;
    GPIOB0->DSCR  = GPIO_RESET_VALUE;
	GPIOA0->OMCR  = GPIO_RESET_VALUE;
    GPIOB0->OMCR  = GPIO_RESET_VALUE;
    GPIOA0->IECR  = GPIO_RESET_VALUE;
    GPIOB0->IECR  = GPIO_RESET_VALUE;
    GPIOGRP->IGRPL  = GPIO_RESET_VALUE;
	GPIOGRP->IGRPH  = GPIO_RESET_VALUE;
	GPIOGRP->IGREX  = GPIO_RESET_VALUE;
	GPIOGRP->IO_CLKEN = 0xf;
} 

/** \brief port initialization to GPIO input/output or AF functions
 *  The operation changes all the 8 ports simutaneously for higher efficiency
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eByte: either lower 8 pins or higher 8 pins \ref gpio_byte_e
 * 	\param[in] val: 0x00000000 ~ 0xffffffff, refer to chapter2 Pin Configruation in datasheet for AF assignment
 *  \return none
 */  
void gpio_port_init(csp_gpio_t *ptGpioBase,gpio_byte_e eByte,U32_T wValue)
{
    if (eByte==0)
    {
        (ptGpioBase)->CONLR = wValue;
    }
    else if(eByte==1)
    {
        (ptGpioBase)->CONHR = wValue;
    }
}



/** \brief Set a specific pin to either input or output
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 * 	\param[in] eIoMux: GPIO input/output/AFs \ref io_mux_e
 *  \return none
 */ 
void gpio_init(csp_gpio_t *ptGpioBase,uint8_t byPinNum,io_mux_e eIoMux)
{
    U32_T wPinMsk;
    uint8_t byPin;
	
	
	
    if(byPinNum<8)
    {    
        wPinMsk = (0xf << (byPinNum * 4)); 
		(ptGpioBase)->CONLR &= ~(wPinMsk) | (eIoMux << (byPinNum * 4)); 
    }
    else if (byPinNum<16)
    {
		wPinMsk = (0xf << ((byPinNum - 8) * 4)); 
		(ptGpioBase)->CONHR &= ~(wPinMsk) | (eIoMux << (byPinNum * 4));  
		
    }
}


/** \brief Config pull-up or pull-down of a specific output pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eOutputMode: \ref gpio_pull_mode_e
 *  \return none
 */ 
void gpio_pull_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum, gpio_pull_mode_e ePullMode)
{
	ptGpioBase->PUDR  = (ptGpioBase->PUDR & ~(GPIO_PULL_MODE_MSK<<(byPinNum*2))) | (ePullMode<<(byPinNum*2)); 
}




/** \brief Config a specific output pin to opendrain or push-pull mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eOutputMode: \ref gpio_output_mode_e
 *  \return none
 */ 
void gpio_output_mode_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_output_mode_e eOutputMode)
{
	if (eOutputMode == OUTPUT_MODE_PUSHPULL_NORMAL) 
	{
		ptGpioBase->OMCR  &= ~(0x01<<byPinNum);
		ptGpioBase->DSCR  &=  ~(0x01<<(byPinNum*2));
	}
	else if (eOutputMode == OUTPUT_MODE_PUSHPULL_STRONG)
	{
		ptGpioBase->OMCR  &= ~(0x01<<byPinNum);
		ptGpioBase->DSCR  = ((ptGpioBase)->DSCR) | (0x01<<(byPinNum*2));
	}
	else if (eOutputMode == OUTPUT_MODE_OPENDRAIN)
	{
		ptGpioBase->OMCR  = ((ptGpioBase)->OMCR) | (0x01<<byPinNum);
	}
		
}




/** \brief Config a specific input pin to TTL or CMOS mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eInputMode: \ref gpio_input_mode_e
 *  \return none
 */ 
void gpio_input_mode_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_input_mode_e eInputMode)
{
	if(eInputMode==INPUT_MODE_CMOS)
	{
		(ptGpioBase)->DSCR  = ((ptGpioBase)->DSCR) & ~(0x01<<(byPinNum*2+1));
	}
	else
	{
		(ptGpioBase)->DSCR  = ((ptGpioBase)->DSCR) | (0x01<<(byPinNum*2+1));
		if(eInputMode==INPUT_MODE_TTL1)
		{
			(ptGpioBase)->OMCR  = ((ptGpioBase)->OMCR) | (0x01<<(byPinNum+16));
		}
		else if(eInputMode==INPUT_MODE_TTL2)
		{
			(ptGpioBase)->OMCR  = ((ptGpioBase)->OMCR) & ~(0x01<<(byPinNum+16));
		}
	}
}


/** \brief IO Group configuration
 *  There are 20 possible groups seperately connecting to EXI0~19 in SYSCON 
 *  This function assigns a specific input pin to one of EXI0~19 where:
 * 	- EXI0 could be PA0.0/PB0.0
 *  - ...
 *  - EXI15 could be PA0.15/PB0.15
 *  - EXI16/17 could be PA0.0~ PA0.7
 *  - EXI18/19 could be PB0.0~PB0.3
 *  \param[in] eGroup: GPIOA/GPIOB... \ref gpio_group_e
 *  \param[in] byPinNum: 0~15
 *  \param[in] eExiGroup: SELECT_EXI_GROUP0~19 \ref exipin_e
 *  \return err_status_e
 */ 
err_status_e gpio_igroup_set(exi_grp_e eExiGroup,gpio_group_e eGroup , uint8_t byPinNum)
{	
	U32_T byMaskShift,byMask;
	if (eExiGroup < 16) {
		if ((uint8_t)eExiGroup != byPinNum)
			return ERROR;
		
		if(byPinNum < 8)
		{
			byMaskShift = (byPinNum << 2);
			byMask = ~(0x0Ful << byMaskShift);
			GPIOGRP->IGRPL = ((GPIOGRP->IGRPL) & byMask) | (eGroup << byMaskShift);
		}
		else if(byPinNum < 16)
		{
			byMaskShift = ((byPinNum-8) << 2);
			byMask = ~(0x0Ful << byMaskShift);
			GPIOGRP->IGRPH = ((GPIOGRP->IGRPH) & byMask) | (eGroup << byMaskShift);
		}
		else
			return ERROR;
	}
	else {
		switch(eExiGroup)
		{
			case (EXI_GRP16): 
			case (EXI_GRP17): if ((eGroup != GPIOA) || (eGroup == GPIOA && (byPinNum>7)))
															return ERROR;
														break;
			case (EXI_GRP18): 
			case (EXI_GRP19): if ((eGroup != GPIOB) || (eGroup == GPIOB && (byPinNum>3)))
															return ERROR;
			default: return ERROR; break;
		}
		
		byMaskShift = (eExiGroup - EXI_GRP15) << 2;
		byMask = ~(0x0Ful << byMaskShift);
		GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | (byPinNum << byMaskShift);
	} 
		
	return SUCCESS;
	
}



/** \brief Enable a specific gpio group signal output to SYSCON module
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: pin number
 *  \return none
 */ 
void gpio_exi_enable(csp_gpio_t *ptGpioBase,U8_T byPinNum)
{
    (ptGpioBase)->IECR  |= 1<<byPinNum;
}

/** \brief disable a specific gpio group signal output to SYSCON module
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: pin number
 *  \return none
 */ 
void gpio_exi_disable(csp_gpio_t *ptGpioBase,U8_T byPinNum)
{
    (ptGpioBase)->IEDR  |= 1<<byPinNum;
}


/** \brief simultaneouly external interrupt enable, disable control in GPIO
 *  \param[in] hwExiMsk: EXI pin mask, 0'b  for disable, 1'b for enable
 *  \return none
 */
void gpio_exi_port_cmd(csp_gpio_t * ptGpioBase,U16_T hwExiMsk)
{
	ptGpioBase ->IECR = hwExiMsk;
}




/** \brief Set/Clear a specific output pin
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_write_high(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
	(ptGpioBase)->SODR = (1ul<<byPinNum);
}
void gpio_write_low(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
    (ptGpioBase)->CODR = (1ul<<byPinNum);
}

/** \brief simultaneouly port write
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] hwExiMsk: pin mask, 0'b  for disable, 1'b for enable
 *  \return none
 */ 
void gpio_port_write(csp_gpio_t * ptGpioBase,U16_T hwExiMsk)
{
	ptGpioBase ->WODR = hwExiMsk;
}


/** \brief Set a specific output pin to a specific level
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] bValue: 0 or 1
 *  \return none
 */ 
void gpio_write(csp_gpio_t *ptGpioBase,uint8_t byPinNum, bool bValue)
{
    if (bValue == (bool)1)
    {
        (ptGpioBase)->SODR = (1ul<<byPinNum);
    }
    else 
    {
        (ptGpioBase)->CODR = (1ul<<byPinNum);
    }
}


/** \brief Toggle a specific output pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_reverse(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
     U32_T dat = 0;
     dat=((ptGpioBase)->ODSR>>byPinNum)&1ul;
     {
       if (dat==1)  
       {
           (ptGpioBase)->CODR = (1ul<<byPinNum);
           return;
       }
       if (dat==0)
       {
           (ptGpioBase)->SODR = (1ul<<byPinNum);
           return;
       }
     }
}


/** \brief Read port status info from a specific pin
 *  this pin does not have to be an output pin
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return byValue: 
 */ 
uint8_t gpio_read_status(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
    uint8_t byValue = 0;
    U32_T wData = 0;
    wData=((ptGpioBase)->PSDR)&(1<<byPinNum);
    if (wData == (1<<byPinNum))								
	{
	    byValue = 1;
	} 
    return byValue;
}


/** \brief Read output status info from a specific pin
 *  The real level measured on this pin does not neccessarily be the same as output status
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
uint8_t gpio_read_output(csp_gpio_t *ptGpioBase,uint8_t byPinNum)
{
    uint8_t byValue = 0;
    U32_T wData = 0;
    wData=((ptGpioBase)->ODSR)&(1<<byPinNum);
    if (wData == (1<<byPinNum))								
	{
	    byValue = 1;
	} 
    return byValue;
}


/** \brief port mode configuration, an alternative function for port configurations
 * 	The operation changes all the 8 ports simutaneously
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eMode:   PUDR(IO PULL UP/DOWN Configuration)
						DSCR(IO DRIVE STRENGHT Configuration)
						OMCR(OUTPUT MODE Configuration)
						IECR(IO INT ENABLE/DISABLE)
 * 	\param[in] wValue: 0x00000000 ~ 0xffffffff, refer to Chapter GPIO in user maunal for Mode definition
 *  \return none
 */ 
void gpio_port_mode_init(csp_gpio_t *ptGpioBase,gpio_mode_e eMode,U32_T wValue)
{
        switch (eMode)
        {
            case PUDR:(ptGpioBase)->PUDR  = wValue;break;               
            case DSCR:(ptGpioBase)->DSCR  = wValue;break;
            case OMCR:(ptGpioBase)->OMCR  = wValue;break;
            case IECR:(ptGpioBase)->IECR  = wValue;break;
        }
}
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/