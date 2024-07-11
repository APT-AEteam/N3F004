/***********************************************************************//** 
 * \file  uart.c
 * \brief UART function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td>  2024-7-10 <td>V1_5_0  <td>GQQ   <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"

/* externs--------------------------------------------------------------------*/
/* private function-----------------------------------------------------------*/
/* global variablesr----------------------------------------------------------*/
volatile U8_T byRxDataFlag=0;
volatile U8_T byTxDataFlag=0;
volatile U8_T bySendCompleteFlag;
volatile U16_T hwSendLengthTemp;
volatile U16_T hwSendLength;
volatile U8_T byUartBuffer[UART_BUFSIZE];
/* Private variablesr---------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/


/** \brief UART0/1 deinit
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_deinit(csp_uart_t *ptUartBase)
{
    ptUartBase->DATA = UART_RESET_VALUE;
    ptUartBase->SR   	= UART_RESET_VALUE;
    ptUartBase->CTRL 	= UART_RESET_VALUE;
    ptUartBase->ISR 		= UART_RESET_VALUE;
    ptUartBase->BRDIV = UART_RESET_VALUE;
}

/** \brief UART0/1 wake up enable
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_wakeup_enable(csp_uart_t *ptUartBase)
{
	if((csp_uart_t *)ptUartBase == UART0)
	{
		csi_vic_set_wakeup_irq(UART0_INT);   
	}
	else if((csp_uart_t *)ptUartBase == UART1)
	{
		csi_vic_set_wakeup_irq(UART1_INT); 
	}
}

/** \brief UART0/1 wake up disable
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_wakeup_disable(csp_uart_t *ptUartBase)
{
	if((csp_uart_t *)ptUartBase == UART0)
	{
		csi_vic_clear_wakeup_irq(UART0_INT);   
	}
	else if((csp_uart_t *)ptUartBase == UART1)
	{
		csi_vic_clear_wakeup_irq(UART1_INT); 
	}
}

/** \brief UART0/1 initial 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] hwBaudDiv: the division of baudrate ,range: 1~0xfffff
 * 										BaudRate = PCLK/ hwBaudDiv
 *  \param[in] eDataBit:  transmit data bit select \ref uart_databit_e
 *  \param[in] eParity:  Parity select   \ref uart_parity_e
 * 			   
 *  \return none
 */ 
void uart_init(csp_uart_t *ptUartBase,U16_T hwBaudDiv, uart_databit_e eDataBit, uart_parity_e eParity)
{
   ptUartBase->CTRL = (UART_ENABLE<<UART_TX_POS)|(UART_ENABLE<<UART_RX_POS)|(eDataBit<<UART_DATA_POS)|(eParity<<UART_PARITY_POS);
   ptUartBase->BRDIV = hwBaudDiv;
}

/** \brief UART0/1 initial & enable rx,tx interrupt
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] hwBaudDiv: the division of baudrate ,range: 1~0xfffff
 * 										BaudRate = PCLK/ hwBaudDiv
 *  \param[in] eDataBit:  transmit data bit select \ref uart_databit_e
 *  \param[in] eParity:  Parity select   \ref uart_parity_e
 * 			   
 *  \return none
 */ 
void uart_init_rxtx_inten(csp_uart_t *ptUartBase,U16_T hwBaudDiv, uart_databit_e eDataBit, uart_parity_e eParity)
{
	ptUartBase->ISR = UART_INT_RX|UART_INT_TX;
	
	if((csp_uart_t *)ptUartBase == UART0)
	{
		csi_vic_enable_irq(UART0_INT);
	}
	else 
	{
		csi_vic_enable_irq(UART1_INT);
	}
	ptUartBase->CTRL = (UART_ENABLE<<UART_TX_POS)|(UART_ENABLE<<UART_RX_POS)|(eDataBit<<UART_DATA_POS)|(eParity<<UART_PARITY_POS)
										|UART_INT_TX|UART_INT_RX;
   ptUartBase->BRDIV = hwBaudDiv;
}

/** \brief UART0/1 initial & enable rx interrupt
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] hwBaudDiv: the division of baudrate ,range: 1~0xfffff
 * 										BaudRate = PCLK/ hwBaudDiv
 *  \param[in] eDataBit:  transmit data bit select \ref uart_databit_e
 *  \param[in] eParity:  Parity select   \ref uart_parity_e
 * 			   
 *  \return none
 */ 
void uart_init_rx_inten(csp_uart_t *ptUartBase,U16_T hwBaudDiv, uart_databit_e eDataBit, uart_parity_e eParity)
{
	ptUartBase->ISR = UART_INT_RX;
	
	if((csp_uart_t *)ptUartBase == UART0)
	{
		csi_vic_enable_irq(UART0_INT);
	}
	else 
	{
		csi_vic_enable_irq(UART1_INT);
	}
	ptUartBase->CTRL = (UART_ENABLE<<UART_TX_POS)|(UART_ENABLE<<UART_RX_POS)|(eDataBit<<UART_DATA_POS)|(eParity<<UART_PARITY_POS)
										|UART_INT_RX;
    ptUartBase->BRDIV = hwBaudDiv;
}

/** \brief UART0/1 disable
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_disable(csp_uart_t *ptUartBase)
{
	ptUartBase->CTRL = UART_DISABLE;
}

/** \brief  get uart status 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
U8_T uart_get_status(csp_uart_t *ptUartBase)
{
	return ptUartBase->SR;
}

/** \brief UART0/1  one byte data without interrupt
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] byData: datab to be sent
 * 			   
 *  \return none
 */ 
void uart_send_byte(csp_uart_t *ptUartBase,U8_T byData)
{
	ptUartBase->DATA = byData;
	while((uart_get_status(ptUartBase)&UART_TX_FULL) == UART_TX_FULL);    //Loop  when tx is full
}

/** \brief UART0/1  send data without interrupt
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] ptData: pointer of data to be sent
 *  \param[in] hwLen: data length
 * 			   
 *  \return none
 */ 
void uart_send(csp_uart_t *ptUartBase,U8_T *ptData ,U16_T hwLen)
{
	U16_T cnt;
	for(cnt = 0;cnt < hwLen ;cnt ++)
	{
		ptUartBase->DATA = *ptData++;
		while((uart_get_status(ptUartBase)&UART_TX_FULL) == UART_TX_FULL);    //Loop  when tx is full
	}
}

/** \brief UART0/1  interrupt send byte  
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_int_send_byte(csp_uart_t *ptUartBase )
{
	if(!bySendCompleteFlag)
	{
		bySendCompleteFlag=1;
		hwSendLengthTemp++;
		ptUartBase->DATA = byUartBuffer[0];
	}
}

/** \brief UART0/1  interrupt send data  
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return none
 */ 
void uart_int_send(csp_uart_t *ptUartBase )
{
	if(bySendCompleteFlag)
	{
		if(hwSendLengthTemp>=hwSendLength)
		{
			bySendCompleteFlag=0;
			hwSendLengthTemp=0;
		}
		else
		{
			ptUartBase->DATA = byUartBuffer[hwSendLengthTemp++];
		}
	}	
}

/** \brief UART0/1 receive one byte 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[out] ptData: pointer of  received data 
 * 			   
 *  \return TRUE or FLASE
 */ 
U8_T uart_receive_byte(csp_uart_t *ptUartBase,U8_T *ptData)
{
	if((uart_get_status(ptUartBase)&UART_RX_FULL) != UART_RX_FULL)   //Loop  when rx is not full
		return FALSE;
	else
	{
		*ptData = ptUartBase->DATA;
	    return TRUE;
	}
}

/** \brief UART0/1 interrupt receive one byte
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 * 			   
 *  \return recieved data
 */ 
U8_T uart_int_receive_byte(csp_uart_t *ptUartBase)
{
//	byRxDataFlag = FALSE;
//	while(byRxDataFlag != TRUE);
	return ptUartBase->DATA;
}

/** \brief UART0/1  receive data
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] ptData: pointer of received data
 *  \param[in] hwLen:  receive data length
 * 			   
 *  \return TRUE OR FLASE
 */ 
U16_T UARTReceive(csp_uart_t *ptUartBase,U8_T *ptData,U16_T hwLen)
{
	U16_T hwCnt = 0;
	U32_T wTime = 0;
	
	do{
		if((uart_get_status(ptUartBase)&UART_RX_FULL) != UART_RX_FULL) //Loop  when rx is full
		{
			*ptData++ = ptUartBase->DATA;
			hwCnt++;
			wTime = 0;
		}
		if(wTime ++ >= 0xfff0)
			return FALSE;
	}while(hwCnt < hwLen);
	return TRUE;
}
