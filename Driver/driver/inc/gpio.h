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
#include "syscon.h"


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
  * @brief  GPIO  exi number
  */
#define EXI_PIN(n) n
typedef enum
{
    EXI_PIN0 = 0,
    EXI_PIN1 = 1,
    EXI_PIN2 = 2,
    EXI_PIN3 = 3,
    EXI_PIN4 = 4,
    EXI_PIN5 = 5,
    EXI_PIN6 = 6,
    EXI_PIN7 = 7,
    EXI_PIN8 = 8,
    EXI_PIN9 = 9,
    EXI_PIN10 = 10,
    EXI_PIN11 = 11,
    EXI_PIN12 = 12,
    EXI_PIN13 = 13,
	EXI_PIN14 = 14,
	EXI_PIN15 = 15,
}exi_e;



/**
  * @brief  GPIO INPUT MODE SETECTED
  */
typedef enum
{
	INPUT_MODE_CMOS			=		0,
	INPUT_MODE_TTL1			=		1,
	INPUT_MODE_TTL2			=		2
}gpio_input_mode_e;

/**
  * @brief  GPIO INPUT MODE SETECTED
  */
typedef enum
{
	OUTPUT_MODE_PUSHPULL_NORMAL		=		0,
	OUTPUT_MODE_PUSHPULL_STRONG,
	OUTPUT_MODE_OPENDRAIN
}gpio_output_mode_e;


#define GPIO_PULL_MODE_MSK	3

typedef enum{
	PULL_MODE_NOPULL = 0,
	PULL_MODE_PULLUP = 0x1 << 0,
	PULL_MODE_PULLDN = 0x1 << 1,
}gpio_pull_mode_e;

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
 *  The operation changes all the 8 ports simutaneously for higher efficiency
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] eByte: either lower 8 pins or higher 8 pins \ref gpio_byte_e
 * 	\param[in] val: 0x00000000 ~ 0xffffffff, refer to chapter2 Pin Configruation in datasheet for AF assignment
 *  \return none
 */  
void gpio_port_init(csp_gpio_t *ptGpioBase,gpio_byte_e eByte,U32_T wValue);

/** \brief Set a specific pin to either input or output
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 * 	\param[in] eIoMux: GPIO input/output/AFs \ref io_mux_e
 *  \return none
 */ 
void gpio_init(csp_gpio_t *ptGpioBase,uint8_t byPinNum,io_mux_e eIoMux);


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
void gpio_port_mode_init(csp_gpio_t *ptGpioBase,gpio_mode_e eMode,U32_T wValue);

/** \brief Config pull-up or pull-down of a specific output pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eOutputMode: \ref gpio_pull_mode_e
 *  \return none
 */ 
void gpio_pull_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum, gpio_pull_mode_e ePullMode);


/** \brief Config a specific input pin to TTL or CMOS mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eInputMode: \ref gpio_input_mode_e
 *  \return none
 */ 
void gpio_input_mode_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_input_mode_e eInputMode);

/** \brief Config a specific output pin to opendrain or push-pull mode
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] eOutputMode: \ref gpio_output_mode_e
 *  \return none
 */ 
void gpio_output_mode_configure(csp_gpio_t *ptGpioBase,uint8_t byPinNum,gpio_output_mode_e eOutputMode);
 
/** \brief Enable pull-up Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_pull_high(csp_gpio_t *ptGpioBase,uint8_t byPinNum);


/** \brief Disable pull-down Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_pull_low(csp_gpio_t *ptGpioBase,uint8_t byPinNum);

/** \brief Disable pull-down/up Resistor of a specific pin
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */
void gpio_pull_disable(csp_gpio_t *ptGpioBase,uint8_t byPinNum);



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
 *  \param[in] eExiGroup: SELECT_EXI_GROUP0 ~19 \ref exi_grp_e
 *  \return err_status_e
 */ 
err_status_e gpio_igroup_set(exi_grp_e eExiGroup,gpio_group_e eGroup , uint8_t byPinNum);

/** \brief Enable a specific gpio group signal output to SYSCON module
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: pin number
 *  \return none
 */ 
void gpio_exi_enable(csp_gpio_t *ptGpioBase,U8_T byPinNum);

/** \brief disable a specific gpio group signal output to SYSCON module
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: pin number
 *  \return none
 */ 
void gpio_exi_disable(csp_gpio_t *ptGpioBase,U8_T byPinNum);

/** \brief simultaneouly external interrupt enable, disable control in GPIO
 *  \param[in] hwExiMsk: EXI pin mask, 0'b  for disable, 1'b for enable
 *  \return none
 */
void gpio_exi_port_cmd(csp_gpio_t * ptGpioBase,U16_T hwExiMsk);

/** \brief Set/Clear a specific output pin
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \return none
 */ 
void gpio_write_high(csp_gpio_t *ptGpioBase,uint8_t byPinNum);
void gpio_write_low(csp_gpio_t *ptGpioBase,uint8_t byPinNum);


/** \brief simultaneouly port write
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] wExiMsk: pin mask, 0'b  for disable, 1'b for enable
 *  \return none
 */ 
void gpio_port_write(csp_gpio_t * ptGpioBase,U16_T hwExiMsk);


/** \brief Set a specific output pin to a specific level
 * 
 *  \param[in] ptGpioBase: GPIOA/GPIOB...
 *  \param[in] byPinNum: 0~15
 *  \param[in] bValue: 0 or 1
 *  \return none
 */ 
void gpio_write(csp_gpio_t *ptGpioBase,uint8_t byPinNum, bool bValue);

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