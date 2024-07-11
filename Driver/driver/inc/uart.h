/***********************************************************************//** 
 * \file  uart.h
 * \brief  UART description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-10 <td>V1_5_0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _UART_H
#define _UART_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"


/*****************************************************************************
********************** UART Structure Description ***********************
******************************************************************************/
typedef struct
{
    __IOM		U32_T 	DATA;		//0x0000	Write and Read Data Register  
    __IOM  	U32_T 	SR;        		//0x0004 	Status Register               
    __IOM  	U32_T 	CTRL;      	//0x0008 	Control Register              
    __IOM  	U32_T  	ISR;       		//0x000C 	Interrupt Status Register     
    __IOM  	U32_T  	BRDIV;     	//0x0010 	Baud Rate Generator Register  
} csp_uart_t; 

/*****************************************************************************
************************** UART Para Macro defined ***************************
******************************************************************************/
#define UART_RESET_VALUE	(0x00000000)
//#define UART_RX_TIMEOUT		(0x1FFF)
//#define UART_TX_TIMEOUT		(0x1FFF)
#define UART_BUFSIZE             32
typedef enum{
	UART_DISABLE =0,
	UART_ENABLE
}uart_state_e;

/******************************************************************************
* SR : UART Status Register
******************************************************************************/									
typedef enum{
	UART_TX_FULL			= (0x01ul << 0),		// Transmitter full        
	UART_RX_FULL		= (0x01ul << 1),		// Receiver full           
	UART_TX_OVER     	= (0x01ul << 2),		// Transmitter buff over   
	UART_RX_OVER     	= (0x01ul << 3), 		// Receiver buff over      
	UART_PAR_ERR     	= (0x01ul << 4), 
}uart_sr_e;

/******************************************************************************
* CTRL : UART Control Register	
******************************************************************************/	
#define	UART_TX_POS			(0)			// Transmitter Enable/disable 	 
#define	UART_TX_MSK			(0x01ul << UART_TX_POS)								
//typedef enum{
//	UART_TX_DIS			= 0,
//	UART_TX_EN	
//}tx_ctrl_e;

#define	UART_RX_POS			(1)			// Receiver Enable/disable         
#define	UART_RX_MSK			(0x01ul << UART_RX_POS)		
//typedef enum{
//	UART_RX_DIS			= 0,
//	UART_RX_EN
//}rx_ctrl_e;

#define	UART_PARITY_POS		(8)			// Uart Parity select			       
#define	UART_PARITY_MSK		(0x07ul << UART_PARITY_POS)
typedef enum{
	UART_PAR_NONE		= 0x00,
	UART_PAR_EVEN			= 0x04,
	UART_PAR_ODD    		= 0x05,
	UART_PAR_SPACE 	 	= 0x06,
	UART_PAR_MARK   	= 0x07
}uart_parity_e;

#define	UART_DATA_POS		(11)		// Receiver FIFO level            
#define	UART_DATA_MSK		(0x03ul << UART_FIFO_POS)		
typedef enum{
	UART_DATA_7BIT		= 0,
	UART_DATA_8BIT,
}uart_databit_e;

#define	UART_DBUG_POS		(31)		// Receiver FIFO level            
#define	UART_DBUG_MSK		(0x01ul << UART_DBUG_POS)		
typedef enum{
	UART_DBUG_DIS		= 0,
	UART_DBUG_EN
}uart_dbug_e;

typedef enum{
	UART_INT_TX     			= (0x01ul << 2),
	UART_INT_RX     			= (0x01ul << 3),
	UART_INT_TX_OV    	= (0x01ul << 4),
	UART_INT_RX_OV    	= (0x01ul << 5),
	UART_INT_PARERR 	= (0x01ul << 7),
	UART_INT_TXDONE 	= (0x01ul << 19),
}uart_int_e;

/******************************************************************************
* ISR : UART Interrupt Status Register	
******************************************************************************/						
typedef enum{
	UART_INT_TX_S   				= (0x01ul << 0),	//Transmitter INT Status      
	UART_INT_RX_S					= (0x01ul << 1),	//Receiver INT Status          
	UART_INT_TX_OV_S    		= (0x01ul << 2),	//Transmitter Over INT Status  
	UART_INT_RX_OV_S   	 		= (0x01ul << 3),	//Receiver Over INT Status   
	UART_INT_PARERR_S     	= (0x01ul << 4),	//Parity Error INT Status  
	UART_INT_TXDONE_S     	= (0x01ul << 19),	//Transmitter Complete INT Status
	UART_INT_ALL_S     			= (0x8001Ful << 0)	//All INT Status 
}uart_isr_e;

/******************************************************************************
* BRDIV : BRDIV register 
******************************************************************************/
#define UART_BRDIV_POS			(0) 
#define	UART_BRDIV_MSK		(0x000FFFFF << UART_BRDIV_POS)	

/******************************************************************************
********************* UARTx inline Functions Declaration **********************
******************************************************************************/

	
	
#endif