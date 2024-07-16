/***********************************************************************
 * \file  spi.h
 * \brief  SPI description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-12 <td>V2_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_H
#define _SPI_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"

/// \struct csp_spi_t
/// \brief SPI reg description
typedef struct
{
	__IOM  U32_T  CR0;		//0x0000	Control Register 0 			 
	__IOM  U32_T  CR1;		//0x0004	Control Register 1 
	__IOM  U32_T  DR; 		//0x0008	Receive/transmit  data register 
	__IM     U32_T  SR;		//0x000C	Status register 
	__IOM  U32_T  CPSR;		//0x0010	Clock prescale register         
	__IOM  U32_T  IMCR;		//0x0014	Interrupt set/clear register    
	__IM     U32_T  RISR;		//0x0018	Raw interrupt status register   
	__IM     U32_T  MISR;		//0x001C	Mask interrupt status register  
	__OM   U32_T  ICR;		//0x0020	Interrupt clear register 
    __IOM  U32_T  _RSVD;     //0x0024    
	__OM   U32_T  SRR;		//0x0028	Software Reset Register
} csp_spi_t;

/*****************************************************************************
************************** SPI Function defined *****************************
******************************************************************************/

//SPI Registers RST  Value
#define SPI_CR0_RST          	(0x00000000)    	//CR0 reset value     
#define SPI_CR1_RST          	(0x00000010)    	//CR1 reset value     
#define SPI_DR_RST          		(0x00000000)   	 	//DR reset value          
#define SPI_CPSR_RST          	(0x00000000)    	//CPSR reset value    
#define SPI_IMCR_RST          	(0x00000000)   	 	//IMCR reset value   
#define SPI_ICR_RST         	 	(0x00000000)    	//ICR reset value     

/*****************************************************************************
* SPICR0 : Control Register 0
******************************************************************************/
#define	SPI_DATA_LEN_POS	(0)							//Data Size Select    
#define	SPI_DATA_LEN_MSK	(0x0Ful << SPI_DATA_LEN_POS)
typedef enum
{
	SPI_LEN_4		= 3,            
	SPI_LEN_5,            
	SPI_LEN_6,            
	SPI_LEN_7,            
	SPI_LEN_8,  
	SPI_LEN_9,      
	SPI_LEN_10,            
	SPI_LEN_11,            
	SPI_LEN_12,            
	SPI_LEN_13,            
	SPI_LEN_14,  
	SPI_LEN_15,  
	SPI_LEN_16
}spi_data_len_e;

#define	SPI_RFR_POS		(4)							//Frame Format 		
#define	SPI_RFR_MSK		(0x03ul << SPI_RFR_POS)

#define SPI_WORK_MODE_POS	(6)							//SPICLK Polarity & Phase   
#define SPI_WORK_MODE_MSK	(0x03ul << SPI_WORK_MODE_POS)
typedef enum
{
	SPI_CPOL_0_CPHA_0	= (0x00ul),   
	SPI_CPOL_1_CPHA_0	= (0x01ul),          
	SPI_CPOL_0_CPHA_1	= (0x02ul),  
	SPI_CPOL_1_CPHA_1  = (0x03ul)            
}spi_work_mode_e;

#define SPI_SCR_POS		(8)							//Serial Clock Rate   			
#define SPI_SCR_MSK		(0xFFul << SPI_SCR_POS)							

/******************************************************************************
* SPICR1 : Control Register 1
******************************************************************************/ 
#define	SPI_LBM_POS		(0)					//Loopback mode 				 				
#define	SPI_LBM_MSK		(0x01ul << SPI_LBM_POS)
typedef enum
{
	SPI_LBM_DIS		= 0,            
	SPI_LBM_EN   
}spi_lbm_e;

#define	SPI_SSE_POS		(1)	
#define	SPI_SSE_EN		(0x01ul << SPI_SSE_POS)							 				
#define	SPI_SSE_MSK		(0x01ul << SPI_SSE_POS)

#define	SPI_MODE_POS	(2)					//Master / Slave Mode Select  	
#define	SPI_MODE_MSK	(0x01ul << SPI_MODE_POS)
typedef enum
{
	SPI_MASTER	= 0,            
	SPI_SLAVE      
}spi_mode_e;

#define	SPI_SOD_POS		(3)					
#define	SPI_SOD_MSK		(0x01ul << SPI_SOD_POS)
typedef enum
{
	SPI_SOD_TXEN	= 0,            
	SPI_SOD_TXDIS      
}spi_sod_e;

#define	SPI_RXIFL_POS	(4)					//RX INT FIFO Level Select    
#define	SPI_RXIFL_MSK	(0x07ul << SPI_RXIFL_POS)
typedef enum
{
	SPI_RXFIFO_1_DATA	= (0x01ul),            
	SPI_RXFIFO_1_UP9_2_BL8  = (0x02ul),        
}spi_rxifl_e;

#define	SPI_LPMD_POS		(7)				
#define	SPI_LPMD_MSK		(0x01ul << SPI_LPMD_POS)
typedef enum
{
	SPI_LPMD_NORMAL	= 0,            
	SPI_LPMD_SINGLE      
}spi_lpmd_e;

#define	SPI_LPTXOE_POS		(8)					
#define	SPI_LPTXOE_MSK		(0x01ul << SPI_LPTXOE_POS)


/******************************************************************************
* SPIDR : Data Register
******************************************************************************/
#define	SPI_DATA_POS			(0)				//Transmit/Receive FIFO 		 
#define	SPI_DATA_MSK		(0xFFFFul << SPI_RXFIFO_POS)

/******************************************************************************
* SPISR : Status Register
******************************************************************************/
typedef enum
{
	SPI_TFE		= (0x01ul << 0), 			//Transmit FIFO Empty                    
	SPI_TNF     = (0x01ul << 1), 			//Transmit FIFO is not Full          
	SPI_RNE     = (0x01ul << 2),			//Receive is not Empty             
	SPI_RFF		= (0x01ul << 3),   			//Receive FIFO Full                    
	SPI_BSY     = (0x01ul << 4) 			//PrimeCell SPI Busy Flag            
}spi_sr_e;

/******************************************************************************
* CPSR : Clock prescale register
******************************************************************************/
#define	SPI_CPSDVSR_POS		(0)				//Clock Prescale Devisor		 
#define	SPI_CPSDVSR_MSK		(0xFFul << SPI_CPSDVSR_POS)

/******************************************************************************
* interrupt
******************************************************************************/
typedef enum
{
	SPI_INT_RX_OV	= (0x01ul << 0), 		//Receive Over flow Interrupt              
	SPI_INT_RXTO  	= (0x01ul << 1), 		//Receive Timeout Interrupt          
	SPI_INT_RXFIFO  = (0x01ul << 2),		//Receive FIFO Interrupt           
	SPI_INT_TXFIFO	= (0x01ul << 3),   		//Transmit FIFO interrupt 
	SPI_INT_ALL		= (0x0F),   			//ALL interrupt 
}spi_int_e;

/******************************************************************************
* SRR : Software Reset register 
******************************************************************************/
#define	SPI_PCLK_SWRST_POS			(0)			 
#define	SPI_PCLK_SWRST_MSK			(0x01ul << SPI_PCLK_SWRST_POS)

#define	SPI_SCLK_SWRST_POS			(1)			 
#define	SPI_SCLK_SWRST_MSK			(0x01ul << SPI_SCLK_SWRST_POS)

#define	SPI_RXFIFO_RST_POS		(8)			 
#define SPI_RXFIFO_RST_MSK		(0x01ul << SPI_RXFIFO_RST_POS)

#define	SPI_TXFIFO_RST_POS		(9)			 
#define SPI_TXFIFO_RST_MSK		(0x01ul << SPI_TXFIFO_RST_POS)

/******************************************************************************
* function declaration
******************************************************************************/
/** \brief SPI deinit
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_deinit(csp_spi_t *ptSpiBase);

/** \brief SPI init as master
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eDataLen: data length select \ref spi_data_len_e
 *  \param[in] eWorkMd: work mode config : CPOL & CPHA \ref spi_work_mode_e
 *  \param[in] eLbm: loopback function control  \ref spi_lbm_e
 *  \param[in] eRxFifo: Rx fifo  trigger point of interrupt   \ref spi_rxifl_e
 *  \param[in] bySclkDiv: Serial clk divsion ,range: 0~0xff
 *  \param[in] byPclkDiv: PCLK division , must be even !!!  range : 0x2~0xfe 
 * 					spi bit rate = FPCLK/ (byPclkDiv *(1 + bySclkDiv))
 * 			   
 *  \return none
 */ 
void spi_master_init(csp_spi_t *ptSpiBase,spi_data_len_e eDataLen , spi_work_mode_e eWorkMd , spi_lbm_e eLbm , spi_rxifl_e eRxFifo , U8_T bySclkDiv, U8_T byPclkDiv );

/** \brief SPI init as slave
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eDataLen: data length select \ref spi_data_len_e
 *  \param[in] eWorkMd: work mode config : CPOL & CPHA \ref spi_work_mode_e
 *  \param[in] eRxFifo: Rx fifo  trigger point of interrupt   \ref spi_rxifl_e
 *  \param[in] bySclkDiv: Serial clk divsion ,range: 0~0xff
 *  \param[in] byPclkDiv: PCLK division , must be even !!!  range : 0x2~0xfe 
 * 					spi bit rate = FPCLK/ (byPclkDiv *(1 + bySclkDiv))
 * 			   
 *  \return none
 */ 
void spi_slave_init(csp_spi_t *ptSpiBase,spi_data_len_e eDataLen , spi_work_mode_e eWorkMd ,  spi_rxifl_e eRxFifo , U8_T bySclkDiv, U8_T byPclkDiv);

/** \brief SPI write data
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] hwData: data to be sent
 * 			   
 *  \return none
 */ 
void spi_write_data(csp_spi_t *ptSpiBase, U16_T hwData);

/** \brief SPI read data
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] hwData: data to be sent
 *  \param[out] ptData: pointer of received data
 *  \param[in] byNum: number of receive data
 * 			   
 *  \return none
 */ 
void spi_read_data(csp_spi_t *ptSpiBase, U16_T hwData ,volatile U16_T *ptData , U8_T byNum);

/** \brief SPI interrupt enable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eInt: interrupt select \ref spi_int_e
 * 			   
 *  \return none
 */ 
void spi_int_enable(csp_spi_t *ptSpiBase,  spi_int_e eInt);

/** \brief SPI interrupt disable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 *  \param[in] eInt: interrupt select \ref spi_int_e
 * 			   
 *  \return none
 */ 
void spi_int_disable(csp_spi_t *ptSpiBase,  spi_int_e eInt);

/** \brief SPI wakeup enable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_wakeup_enable(csp_spi_t *ptSpiBase);

/** \brief SPI wakeup disable 
 * 
 *  \param[in] ptSpiBase: pointer of spi register structure
 * 			   
 *  \return none
 */ 
void spi_wakeup_disable(csp_spi_t *ptSpiBase);


#endif