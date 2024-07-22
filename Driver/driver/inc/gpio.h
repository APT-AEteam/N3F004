/***********************************************************************//** 
 * \file  gpio.h
 * \brief  gpio description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GPIO_H
#define _GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"
#include "n3f004_top.h"


/// \struct csp_gpio_t
/// \brief GPIO Reg Description
typedef struct
{
	__IOM  U32_T  CONLR;		//0x0000	Control Low Register                
    __IOM  U32_T  CONHR;     //0x0004	Control High Register                
    __OM   U32_T  WODR;      //0x0008	Write Output Data Register                         
    __OM   U32_T  SODR;      //0x000C	Set Output Data (bit-wise) Register  
    __OM   U32_T  CODR;      //0x0010	Clear Output Data (bit-wise) Register
    __IM   U32_T  ODSR;      //0x0014	Output Data Status Register          
    __IM   U32_T  PSDR;      //0x0018	Pin Data Status Register                           
    __OM   U32_T  FLTEN;     //0x001C    Filtering Enable Control Register
    __IOM  U32_T  PUDR;      //0x0020	IO Pullup_Pulldown Register          
    __IOM  U32_T  DSCR;      //0x0024	Output Driving Strength Register     
    __IOM  U32_T  OMCR;      //0x0028	Slew-rate, Open-Drain Control          
    __IOM  U32_T  IECR;      //0x002C	EXI Enable Control Register                     
	__OM   U32_T  IEER;		//0x0030	EXI Enable Eet Register    
	__OM   U32_T  IEDR;		//0x0034	EXI Enable Clear Register
} csp_gpio_t; 


typedef volatile struct
{
	__IOM  U32_T  IGRPL;     //0x0000 	EXI Group Config Register L                  
    __IOM  U32_T  IGRPH;	    //0x0004	EXI Group Config Register H                   
	__IOM  U32_T  IGREX;		//0x0008	EXI Group Expand Config Register  
    __IOM  U32_T  IO_CLKEN;	//0x000C 	Gpio Group Clk Enable Control Register
} csp_igrp_t;    
 

#define GPIO_RESET_VALUE  (0x00000000)

//--------------------------------------------------------------------------------
//-----------------------------GPIO  value enum define--------------------------
//--------------------------------------------------------------------------------

#define PIN_MSK	(0xff)


/**
  * @brief  GPIO  high/low register
  */
typedef enum
{
    LOWBYTE = 0,
    HIGHBYTE = 1,
}gpio_byte_e;
/**
  * @brief  GPIO  IO status
  */
typedef enum
{
    GPIO_INPUT = 1,
    GPIO_OUTPUT = 2,
}gpio_dir_e;


/**
  * @brief  GPIO  IO mode
  */
typedef enum
{
    PUDR = 0,                       //pull high or low
    DSCR =1,                        //drive strenth
    OMCR =2,                        //open drain
    IECR =3,                        //int
}gpio_mode_e;
/**
  * @brief  GPIO  IO Group
  */
typedef enum
{
    PA0 = 0,
    PB0 = 2,
    GPIOA = 0,
    GPIOB = 2,
}gpio_group_e;

/**
  * @brief  GPIO  exi number
  */
typedef enum
{
    EXI0 = 0,
    EXI1 = 1,
    EXI2 = 2,
    EXI3 = 3,
    EXI4 = 4,
    EXI5 = 5,
    EXI6 = 6,
    EXI7 = 7,
    EXI8 = 8,
    EXI9 = 9,
    EXI10 = 10,
    EXI11 = 11,
    EXI12 = 12,
    EXI13 = 13,
	EXI14 = 14,
	EXI15 = 15,
}exi_e;

/**
  * @brief  EXI PIN
  */
typedef enum
{
	SELECT_EXI_GROUP0		=		(0),						
	SELECT_EXI_GROUP1		=		(1),
	SELECT_EXI_GROUP2		=		(2),
	SELECT_EXI_GROUP3		=		(3),
	SELECT_EXI_GROUP4		=		(4),
	SELECT_EXI_GROUP5		=		(5),
	SELECT_EXI_GROUP6		=		(6),
	SELECT_EXI_GROUP7		=		(7),
	SELECT_EXI_GROUP8		=		(8),
	SELECT_EXI_GROUP9		=		(9),
	SELECT_EXI_GROUP10	=		(10),
	SELECT_EXI_GROUP11	=		(11),
	SELECT_EXI_GROUP12	=		(12),
	SELECT_EXI_GROUP13	=		(13),
	SELECT_EXI_GROUP14	=		(14),
	SELECT_EXI_GROUP15	=		(15),
	SELECT_EXI_GROUP16	=		(16),
	SELECT_EXI_GROUP17	=		(17),
	SELECT_EXI_GROUP18	=		(18),
	SELECT_EXI_GROUP19	=		(19)
}exi_group_e;


/**
  * @brief  GPIO INPUT MODE SETECTED
  */
typedef enum
{
	INPUT_MODE_SETECTED_CMOS			=		0,
	INPUT_MODE_SETECTED_TTL1			=		1,
	INPUT_MODE_SETECTED_TTL2			=		2
}gpio_input_mode_e;



#define SETPA0(n)   (GPIOA0->SODR = (1ul<<n))
#define CLRPA0(n)   (GPIOA0->CODR = (1ul<<n))

#define SETPB0(n)   (GPIOB0->SODR = (1ul<<n))
#define CLRPB0(n)   (GPIOB0->CODR = (1ul<<n))

#define PA0IN(n)    (((GPIOA0->PSDR)>>n) & 1ul)
#define PB0IN(n)    (((GPIOB0->PSDR)>>n) & 1ul)


#define CSP_GPIO_SET_CONLR(gpio,val) ((gpio)->CONLR = val)
#define CSP_GPIO_GET_CONLR(gpio)     ((gpio)->CONLR)

#define CSP_GPIO_SET_CONHR(gpio,val) ((gpio)->CONHR = val)
#define CSP_GPIO_GET_CONHR(gpio)     ((gpio)->CONHR)

#define CSP_GPIO_SET_WODR(gpio,val) ((gpio)->WODR = val)
#define CSP_GPIO_SET_SODR(gpio,val) ((gpio)->SODR = val)
#define CSP_GPIO_SET_CODR(gpio,val) ((gpio)->CODR = val)
#define CSP_GPIO_GET_PSDR(gpio)     ((gpio)->PSDR)

#define CSP_GPIO_SET_PUDR(gpio,val) ((gpio)->PUDR = val)
#define CSP_GPIO_GET_PUDR(gpio)     ((gpio)->PUDR)

#define CSP_GPIO_SET_DSCR(gpio,val) ((gpio)->DSCR = val)
#define CSP_GPIO_GET_DSCR(gpio)     ((gpio)->DSCR)

#define CSP_GPIO_SET_OMCR(gpio,val) ((gpio)->OMCR = val)
#define CSP_GPIO_GET_OMCR(gpio)     ((gpio)->OMCR)

#define CSP_GPIO_SET_IECR(gpio,val) ((gpio)->IECR = val)
#define CSP_GPIO_GET_IECR(gpio)     ((gpio)->IECR)

#define CSP_GPIO_SET_IGRP(gpio,val) ((gpio)->IGRP = val)
#define CSP_GPIO_GET_IGRP(gpio)     ((gpio)->IGRP)


/******************************************************************************
************************** Exported functions ************************
******************************************************************************/
/** \brief Deinitialize GPIO registers to their reset value
 * 
 *  \param[in] none
 *  \return none
 */ 
void gpio_deinit(void);

/** \brief port initialization to GPIO input/output or AF functions
 *  The operation changes all the 8 ports simutaneously
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eByte: either lower 8 pins or higher 8 pins \ref gpio_byte_e
 * 	\param[in] val: 0x00000000 ~ 0xffffffff, refer to chapter2 Pin Configruation in datasheet for AF assignment
 *  \return none
 */  
void gpio_init2(csp_gpio_t *ptGpioBase,gpio_byte_e eByte,U32_T wValue);

/** \brief Set a specific pin to either input or output
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 * 	\param[in] eIoMux: GPIO input/output/AFs \ref io_mux_e
 *  \return none
 */ 
void gpio_init(csp_gpio_t *ptGpioBase,uint8_t byPinNum,io_mux_e eIoMux);

/** \brief Set a specific pin to GPD(GPIO Disable) mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 * 	\param[in] Dir: 0  output
 * 					1  input
 *  \return none
 */ 
void gpio_inputoutput_disable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief port mode configuration
 * 	The operation changes all the 8 ports simutaneously
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eMode:   PUDR(IO PULL UP/DOWN Configuration)
						DSCR(IO DRIVE STRENGHT Configuration)
						OMCR(OUTPUT MODE Configuration)
						IECR(IO INT ENABLE/DISABLE)
 * 	\param[in] wValue: 0x00000000 ~ 0xffffffff, refer to Chapter GPIO in user maunal for Mode definition
 *  \return none
 */ 
void gpio_mode_init(csp_gpio_t *ptGpioBase,gpio_mode_e eMode,U32_T wValue);

/** \brief Enable pull-up Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_pul_lhigh_init(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Disable pull-down Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_pull_low_init(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Disable pull-down/up Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */
void gpio_pull_disable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Set/Unset a specific pin to open-drain
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 

void gpio_opendrain_enable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Enable open-drain of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_opendrain_enable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Disable open-drain of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_opendrain_disable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Config a specific input pin to TTL or CMOS mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eInputMode: \ref gpio_input_mode_e
 *  \return none
 */ 
void gpio_ttl_gpioos_select(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_input_mode_e eInputMode);

/** \brief Set a specific output pin to strong driving ability
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_drive_strength_enable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Set a specific output pin to normal driving ability
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_drive_strength_disable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief IO Group configuration
 *  There are 20 possible groups seperately connecting to EXI0~19 in SYSCON 
 *  This function assigns a specific input pin to one of EXI0~19 where:
 * 	- EXI0 could be PA0.0/PB0.0
 *  - ...
 *  - EXI15 could be PA0.15/PB0.15
 *  - EXI16/17 could be PA0.0~ PA0.7
 *  - EXI18/19 could be PB0.0~PB0.3
 *  \param[in] eGroup: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] exi_group_e: SELECT_EXI_GROUP0 ~19 \ref exi_group_e
 *  \return err_status_e
 */ 
err_status_e gpio_igroup_set(gpio_group_e eGroup , uint8_t byPinNum , exi_group_e eExiGroup);

/** \brief Enable gpio group signal output to SYSCON module
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eExiPin: EXI0~EXI15 \ref exi_e
 *  \return none
 */ 
void gpio_exi_enable(csp_gpio_t *ptGpioBase,exi_e eExiPin);

/** \brief Set/Clear a specific output pin
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_write_high(csp_gpio_t *ptGpioBase,uint8_t byPinNum);
void gpio_write_low(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Set a specific output pin to a specific level
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] bValue: 0 or 1
 *  \return none
 */ 
void gpio_set_value(csp_gpio_t *ptGpioBase,uint8_t byPinNum, bool bValue);

/** \brief Toggle a specific output pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_reverse(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Read port status info from a specific pin
 *  this pin does not have to be an output pin
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return byValue: 
 */ 
uint8_t gpio_read_status(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Read output status info from a specific pin
 *  The real level measured on this pin does not have to be the same as output status
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
uint8_t gpio_read_output(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief iomap configuration
 *   \param[in] ptGpioBase: GPIOA/GPIOB...
 *   \param[in] byPinNum: 0~15
 *  \param[in] eCfgVal: remap config value \ref ioremap_e
 *  \return none
 */ 
void gpio_remap(csp_gpio_t * ptGpioBase,U8_T byPinNum, ioremap_e eCfgVal);
/*************************************************************/

#endif   /**_GPIO_H */

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/