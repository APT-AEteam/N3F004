/***********************************************************************//** 
 * \file  n3f004_top.h
 * \brief  ETCB description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _N3F004_TOP_H
#define _N3F004_TOP_H

/******************************************************************************
* Embedded Mempry Information
******************************************************************************/	
#define PFLASH_BASE 		0x00000000
#define PFLASH_SIZE 		0x00008000
#define PFLASH_PAGESIZE		256	    //Bytes
//#define PFLASH_PAGESIZE		128	    //Bytes
#define PFLASH_PAGENUM		256

#define PFLASH_LIMIT 		(PFLASH_BASE + PFLASH_SIZE) 
#define PFLASH_PAGE_MSK		~(PFLASH_PAGESIZE-1)

#define DFLASH_BASE 		0x10000000
#define DFLASH_SIZE 		0x10000C00

//#define DFLASH_PAGESIZE		128		//Bytes
#define DFLASH_PAGESIZE		64		//Bytes
#define DFLASH_PAGE_MSK	 	~(DFLASH_PAGESIZE-1)

#define DLASH_PAGENUM		24
#define DFLASH_LIMIT 		(DFLASH_BASE + DFLASH_SIZE) 

#define SRAM_BASE 			0x20000000
#define SRAM_SIZE 			0x00001000
#define SRAM_LIMIT 			(SRAM_BASE + SRAM_SIZE) 

#define USEROPTION_ADDR		0x000800C0
#define PROTECTION_ADDR		0x00080104
#define SWDREMAP_ADDR			0x000801C0

/******************************************************************************
* Peripheral Address Information
******************************************************************************/
#define APB_PERIBASE     0x40000000 

//--Each Peripheral Address Setting
//#define APB_SFMBASE     (APB_PERIBASE + 0x10000)
#define APB_IFCBASE    	(APB_PERIBASE + 0x10000)
#define APB_SYSCONBASE  (APB_PERIBASE + 0x11000)
#define APB_ETCBBASE    (APB_PERIBASE + 0x12000)
#define APB_ADC0BASE    (APB_PERIBASE + 0x30000)
#define APB_BT1BASE     (APB_PERIBASE + 0x52000)
#define APB_BT0BASE     (APB_PERIBASE + 0x51000)
#define APB_TC3BASE    (APB_PERIBASE + 0x50000)
#define APB_GPT0BASE    (APB_PERIBASE + 0x55000)
#define APB_EPT0BASE    (APB_PERIBASE + 0x59000)
#define APB_UART0BASE   (APB_PERIBASE + 0x80000)
#define APB_UART1BASE   (APB_PERIBASE + 0x81000)
#define APB_SPI0BASE    (APB_PERIBASE + 0x90000)
#define APB_I2C0BASE    (APB_PERIBASE + 0xA0000)
#define AHB_CRCBASE     0x50000000
#define AHB_GPIOBASE 	0x60000000
#define APB_GPIOA0BASE  (AHB_GPIOBASE + 0x0000) //A0  
#define APB_GPIOB0BASE  (AHB_GPIOBASE + 0x2000) //B0 
#define APB_IGRPBASE	(AHB_GPIOBASE + 0xF000)

/******************************************************************************
* Interrupt Information
******************************************************************************/
//--Interrupt Bit Position
#define CORET_INT   (0)       //IRQ0
#define SYSCON_INT  (1)       //IRQ1
#define IFC_INT     (2)       //IRQ2
#define ADC_INT     (3)       //IRQ3
#define EPT0_INT    (4)       //IRQ4
//DUMMY       //IRQ5
//DUMMY       //IRQ6
#define EXI0_INT    (7)       //IRQ7
#define EXI1_INT    (8)       //IRQ8
#define GPT0_INT    (9)       //IRQ9 
//DUMMY      //IRQ10
//DUMMY      //IRQ11
//DUMMY      //IRQ12
#define UART0_INT   (13)      //IRQ13
#define UART1_INT   (14)      //IRQ14
//DUMMY      //IRQ15
//DUMMY      //IRQ16
#define I2C_INT     (17)      //IRQ17
//DUMMY      //IRQ18
#define SPI_INT     (19)      //IRQ19
//DUMMY      //IRQ20
#define EXI2_INT    (21)      //IRQ21
#define EXI3_INT    (22)      //IRQ22
#define EXI4_INT    (23)      //IRQ23
#define TC3_INT     (24)      //IRQ24
#define CMP0_INT    (25)      //IRQ25
#define CMP1_INT    (26)      //IRQ26
//DUMMY      //IRQ27
#define BT0_INT     (28)      //IRQ28
#define BT1_INT     (29)      //IRQ29
//DUMMY      //IRQ30
//DUMMY      //IRQ31



/******************************************************************************
* ETCB Event Information
******************************************************************************/
//ETCB Source IP Event
typedef enum{
	ET_EXI_TRGOUT0 = 4,
	ET_EXI_TRGOUT1,
	ET_EXI_TRGOUT2,
	ET_EXI_TRGOUT3,
	ET_EXI_TRGOUT4,
	ET_EXI_TRGOUT5,
	ET_BT0_TRGOUT0 = 0xc,
	ET_BT1_TRGOUT0,
	ET_BT0_TRGOUT1,
	ET_BT1_TRGOUT1,
	ET_EPT0_TRGOUT0,
	ET_EPT0_TRGOUT1,
	ET_EPT0_TRGOUT2,
	ET_EPT0_TRGOUT3,
	ET_GPT0_TRGOUT0 = 0x20,
	ET_GPT0_TRGOUT1,
	ET_ADC_TRGOUT0 = 0x30,
	ET_ADC_TRGOUT1,
	ET_CMP0_TRGOUT0 = 0x36,
	ET_CMP0_TRGOUT1,
	ET_CMP1_TRGOUT0,
	ET_CMP1_TRGOUT1,
}etcb_trgsrc_e;


//ETCB Destination IP Event
typedef enum{
	ET_BT0_SYNCIN0 = 0x2,
	ET_BT0_SYNCIN1,
	ET_BT0_SYNCIN2,
	ET_BT1_SYNCIN0,
	ET_ADC_SYNCIN0 = 0x6,
	ET_ADC_SYNCIN1,
	ET_ADC_SYNCIN2,
	ET_ADC_SYNCIN3,
	ET_ADC_SYNCIN4,
	ET_ADC_SYNCIN5,
	ET_BT1_SYNCIN1,
	ET_BT1_SYNCIN2,
	ET_EPT0_SYNCIN0 = 0x10,
	ET_EPT0_SYNCIN1,
	ET_EPT0_SYNCIN2,
	ET_EPT0_SYNCIN3,
	ET_EPT0_SYNCIN4,
	ET_EPT0_SYNCIN5,
	ET_CMP0_SYNCIN0,
	ET_CMP1_SYNCIN0,
	ET_GPT0_SYNCIN0 = 0x24,
	ET_GPT0_SYNCIN1,
	ET_GPT0_SYNCIN2,
	ET_GPT0_SYNCIN3,
	ET_GPT0_SYNCIN4,
	ET_GPT0_SYNCIN5,
	ET_GPT0_SYNCIN6	
}etcb_trgdes_e;

typedef enum {
	PIN_GPD				    =  0U,
	PIN_INPUT				=  1U,		//input
	PIN_OUTPUT				=  2U,		//output
	PIN_OUTPUT_MONI			=  3U,		//output with monitor
	
	PA06_GPTA_CHA	=	4,
	PA06_SPI_NSS	=	5,
	PA06_I2C_SCL	=	6,
	PA06_UART0_TX	=	7,
	PA06_SWCLK	=	8,
	PA06_CMP0_OUT	=	9,
	PA06_G1	=	10,
	
	
	PA07_I2C_SDA	=	4,
	PA07_EBI0	=	5,
	PA07_EPT_CHAX	=	6,
	PA07_UART0_RX	=	7,
	PA07_SWDIO	=	8,
	PA07_CMP1_OUT	=	9,
	PA07_G1	=	10,
	
	
	PB02_I2C_SCL	=	4,
	PB02_UART0_TX	=	5,
	PB02_EPT_CHBX	=	6,
	PB02_EBI3	=	7,
	PB02_SPI_SCK	=	8,
	PB02_CMPIN4P	=	9,
	PB02_AIN5	=	11,
	
	PB03_EPT_CHCX	=	4,
	PB03_EPT_CHAY	=	5,
	PB03_EPT_CHD	=	6,
	PB03_EBI2	=	7,
	PB03_SPI_MOSI	=	8,
	PB03_CMPIN4N	=	9,	
	PB03_AIN6	=	11,
	
	PA08_EPT_CHD	=	4,
	PA08_EPT_CHBY	=	5,
	PA08_CLO	=	7,
	PA08_SPI_MISO	=	8,
	PA08_CMPIN1P	=	9,
	PA08_AIN7	=	11,
	
	PA09_SPI_SCK	=	4,
	PA09_GPTA_CHA	=	5,
	PA09_CLO	=	6,
	PA09_EPT_CHCY	=	7,
	PA09_I2C_SDA	=	8,
	PA09_CMPIN1N	=	9,
	PA09_AIN8	=	11,
	
	PA010_SPI_MOSI	=	4,
	PA010_EPT_CHAX	=	5,
	PA010_GPTA_CHA	=	6,
	PA010_TC3_BUZZ	=	7,
	PA010_I2C_SCL	=	8,
	PA010_AIN9	=	11,
	
	PA011_SPI_MISO	=	4,
	PA011_EPT_CHBX	=	5,
	PA011_UART1_RX	=	6,
	PA011_EPT_CHAX	=	7,
	PA011_GPTA_CHA	=	8,
	
	PA05_SWCLK	=	4,
	PA05_RSVD	=	5,
	PA05_SPI_MISO	=	6,
	PA05_UART0_RX	=	7,
	PA05_EPT_CHBY	=	8,
	PA05_G1	=	10,
	PA05_AIN4	=	11,
	
	PA012_SWDIO	=	4,
	PA012_EPT_CHAY	=	5,
	PA012_SPI_MOSI	=	6,
	PA012_UART0_TX	=	7,
	PA012_TC3_BUZZ	=	8,
	PA012_CMP1_OUT	=	9,
	
	PA013_EBI1	=	4,
	PA013_EPT_CHCY	=	5,
	PA013_I2C_SDA	=	6,
	PA013_UART1_RX	=	7,
	PA013_CMPIN2P	=	9,
	PA013_AIN10	=	11,
	
	PB00_TC3_BUZZ	=	4,
	PB00_EPT_CHCX	=	5,
	PB00_I2C_SCL	=	6,
	PB00_UART1_TX	=	7,
	PB00_RSVD	=	8,
	PB00_CMPIN2N	=	9,
	PB00_AIN11	=	11,
	
	PB01_EPT_CHD	=	4,
	PB01_GPTA_CHA	=	5,
	PB01_UART1_RX	=	6,
	PB01_EPT_CHAY	=	7,
	PB01_TC3_BUZZ	=	8,
	PB01_CMPIN3P	=	9,
	PB01_RSVD	=	10,
	PB01_AIN0	=	11,
	
	PA00_UART0_TX	=	4,
	PA00_I2C_SDA	=	5,
	PA00_UART1_TX	=	6,
	PA00_EPT_CHBX	=	7,
	PA00_CMPIN3N	=	9,
	PA00_G1	=	10,
	PA00_AIN1	=	11,
	
	PA01_UART0_RX	=	4,
	PA01_I2C_SCL	=	5,
	PA01_TC3_BUZZ	=	6,
	PA01_I2C_SDA	=	7,
	PA01_GPTA_CHA	=	8,
	PA01_G1	=	10,
	PA01_AIN2	=	11,
	
	PA03_OSC_XI	=	4,
	PA03_EPT_CHCX	=	5,
	PA03_I2C_SDA	=	6,
	PA03_UART1_TX	=	7,
	PA03_GPTA_CHA	=	8,
	PA03_CMP0_OUT	=	9,
	PA03_G1	=	10,
	PA03_AIN3_VREFN	=	11,
	
	PA04_OSC_XO	=	4,
	PA04_EPT_CHCY	=	5,
	PA04_I2C_SCL	=	6,
	PA04_UART1_RX	=	7,
	PA04_LVDIN	=	8,
	PA04_G1	=	10,
	
	PA02_UART1_TX	=	4,
	PA02_SPI_SCK	=	5,
	PA02_I2C_SCL	=	6,
	PA02_CLO	=	7,
	PA02_VREFP_BUF	=	8,
	PA02_RSVD	=	9,
	PA02_G1	=	10,
	
}io_mux_e;

typedef enum
{
	CLO_PA02		=	0,						//PA0.0 as clo
	CLO_PA08		=	1,						//PA0.8 as clo	
	CLO_PA09		=	2,						//PA0.8 as clo	
}clo_io_e;	


typedef enum{
	IOREMAP_DIS		= 	0,
	IOREMAP_EPT_CHD,
	IOREMAP_EPT_CHAX,
	IOREMAP_EPT_CHBX,
	IOREMAP_EPT_CHCX,
	IOREMAP_EPT_CHAY,
	IOREMAP_EPT_CHBY,
	IOREMAP_EPT_CHCY
}ioremap_e;


typedef enum
{
	CMPIN1P_PA08 = 0,
	CMPIN1N_PA09,
	CMPIN2P_PA013,
	CMPIN2N_PB00,
	CMPIN3P_PB01,
	CMPIN3N_PA00,
	CMPIN4P_PB02,
	CMPIN4N_PB03,
	CMP0OUT_PA06,
	CMP0OUT_PA03,
	CMP1OUT_PA07,
	CMP1OUT_PA012
}cmp_io_e;




typedef enum{
	EPT_CHAX_PA07		= 0,
	EPT_CHBX_PB02,
	EPT_CHCX_PB03,
	EPT_CHAY_PB03,
	EPT_CHD_PB03,
	EPT_CHD_PA08,
	EPT_CHBY_PA08,
	EPT_CHCY_PA09,
	EPT_CHAX_PA010,
	EPT_CHBX_PA011,
	EPT_CHAX_PA011,
	EPT_CHBY_PA05,
	EPT_CHAY_PA012,
	EPT_CHCY_PA013,
	EPT_CHCX_PB00,
	EPT_CHD_PB01,
	EPT_CHAY_PB01,
	EPT_CHBX_PA00,
	EPT_CHCX_PA03,
	EPT_CHCY_PA04,
	EPT_EBI0_PA07,
	EPT_EBI1_PA013,
	EPT_EBI2_PB03,
	EPT_EBI3_PB02,
	
}ept_io_e;

typedef enum{
	GPTA_CHA_PA06		= 0,
	GPTA_CHA_PA09,
	GPTA_CHA_PA010,
	GPTA_CHA_PA011,
	GPTA_CHA_PB01,
	GPTA_CHA_PA01,
	GPTA_CHA_PA03
}gpta_io_e;

typedef enum{
	UART0_TX_PA06		= 0,
	UART0_RX_PA07,
	UART0_TX_PB02,
	UART0_RX_PA05,
	UART0_TX_PA012,
	UART0_TX_PA00,
	UART0_RX_PA01,
}uart0_io_e;

typedef enum{
	UART1_RX_PA011		= 0,
	UART1_RX_PA013,
	UART1_TX_PB00,
	UART1_RX_PB01,
	UART1_TX_PA00,
	UART1_TX_PA03,
	UART1_RX_PA04,
	UART1_TX_PA02,
}uart1_io_e;

typedef enum{
	SPI_NSS_PA06		= 0,
	SPI_SCK_PB02,
	SPI_MOSI_PB03,
	SPI_MISO_PA08,
	SPI_SCK_PA09,
	SPI_MOSI_PA010,
	SPI_MISO_PA011,
	SPI_MISO_PA05,
	SPI_MOSI_PA012,
	SPI_SCK_PA02
}spi_io_e;

typedef enum{
	I2C_SCL_PA06		= 0,
	I2C_SDA_PA07,
	I2C_SCL_PB02,
	I2C_SDA_PA09,
	I2C_SCL_PA010,
	I2C_SDA_PA013,
	I2C_SCL_PB00,
	I2C_SDA_PA00,
	I2C_SCL_PA01,
	I2C_SDA_PA01,
	I2C_SDA_PA03,
	I2C_SCL_PA04,
	I2C_SCL_PA02
}i2c_io_e;

typedef enum{
	ADC_AIN0_PB01		= 0,
	ADC_AIN1_PA00,
	ADC_AIN2_PA01,
	ADC_AIN3_VREFN_PA03,
	ADC_AIN4_PA05,
	ADC_AIN5_PB02,
	ADC_AIN6_PB03,
	ADC_AIN7_PA08,
	ADC_AIN8_PA09,
	ADC_AIN9_PA010,
	ADC_AIN10_PA013,
	ADC_AIN11_PB00,
	ADC_VREFP_BUF_PA02
}adc_io_e;

typedef enum{
	TC3_BUZZ_PA010		= 0,
	TC3_BUZZ_PA012,
	TC3_BUZZ_PB00,
	TC3_BUZZ_PB01,
	TC3_BUZZ_PA01
}tc3_io_e;


#endif 

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/
