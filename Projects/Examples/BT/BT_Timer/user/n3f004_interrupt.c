/***********************************************************************//** 
 * \file  n3f004_interrupt.c
 * \brief interrupt handlers implementation declared in startup file
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/

/****************************************************
//include
*****************************************************/
#include "n3f004.h"
#include <stdint.h>
/****************************************************
//define
*****************************************************/
volatile int R_CMPA_BUF,R_CMPB_BUF;
volatile int R_SIOTX_count,R_SIORX_count;
volatile int R_SIORX_buf[10];
/****************************************************
//extern
*****************************************************/
extern void delay_nms(unsigned int t);
/*************************************************************/
//CORET Interrupt
//If you use a touch library file that does not contain coret
//you need to open this interrupt entry
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void CORETHandler(void)
{
	// ISR content ...
}

void TKEYIntHandler(void)
{
	// ISR content ...
}
/*************************************************************/
//SYSCON Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCONIntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//IFC Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void IFCIntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//ADC Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void ADCIntHandler(void) 
{
    // ISR content ...
	
}
/*************************************************************/
//EPT0 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EPT0IntHandler(void) 
{
    // ISR content ...
	
}


/*************************************************************/
//GPT0 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void GPT0IntHandler(void) 
{
    // ISR content ...
	
}

/*************************************************************/
//UART0 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void UART0IntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//UART1 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void UART1IntHandler(void) 
{
    // ISR content ...

}

/*************************************************************/
//I2C Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void I2CIntHandler(void) 
{
    // ISR content ...
	//I2C_Slave_Receive();										//I2C slave receive function in interruption
}
/*************************************************************/
//SPI Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SPI0IntHandler(void) 
{
    // ISR content ...


}

/*************************************************************/
//EXT0/16 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI0IntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//EXT1/17 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1IntHandler(void) 
{
    // ISR content ...
}
/*************************************************************/
//EXI2~3 18~19Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2to3IntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//EXI4~9 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4to9IntHandler(void) 
{
    // ISR content ...


}
/*************************************************************/
//EXI4 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI10to15IntHandler(void) 
{
    // ISR content ...

}
/*************************************************************/
//CONTA Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void CNTAIntHandler(void) 
{
    // ISR content ...
}

/*************************************************************/
//BT0 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT0IntHandler(void) 
{
    static U8_T temp;
	// ISR content ...
	if((BT0->MISR&BT_PEND)==BT_PEND)				//BT0 PEND interrupt
	{
		BT0->ICR = BT_PEND;
		
		if(temp==0)
		{
			temp = 1;
//			GPIO_Write_Low(GPIOA0,13);
		}
		else
		{
			temp = 0;
//			GPIO_Write_High(GPIOA0,13);
		}
	} 
	else if((BT0->MISR&BT_CMP)==BT_CMP)				//BT0 CMP Match interrupt 
	{
		BT0->ICR = BT_CMP;
	}
	else if((BT0->MISR&BT_OVF)==BT_OVF)				//BT0 OVF interrupt
	{
		BT0->ICR = BT_OVF;
	} 
	else if((BT0->MISR&BT_EVTRG)==BT_EVTRG)			//BT0 Event trigger interrupt
	{
		BT0->ICR = BT_EVTRG;
	} 
}
/*************************************************************/
//BT1 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void BT1IntHandler(void) 
{
    // ISR content ...
	if((BT1->MISR&BT_PEND)==BT_PEND)				//BT1 PEND interrupt
	{
		BT1->ICR = BT_PEND;
	} 
	else if((BT0->MISR&BT_CMP)==BT_CMP)				//BT1 CMP Match interrupt 
	{
		BT1->ICR = BT_CMP;
	}
	else if((BT0->MISR&BT_OVF)==BT_OVF)				//BT1 OVF interrupt
	{
		BT1->ICR = BT_OVF;
	} 
	else if((BT0->MISR&BT_EVTRG)==BT_EVTRG)			//BT1 Event trigger interrupt
	{
		BT1->ICR = BT_EVTRG;
	} 
}

/*************************************************************/
//CMP0 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void CMP0IntHandler(void) 
{
    // ISR content ...
	
}

/*************************************************************/
//CMP1 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void CMP1IntHandler(void) 
{
    // ISR content ...
	
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
void PriviledgeVioHandler(void) 
{
    // ISR content ...

}

void SystemDesPtr(void) 
{
    // ISR content ...

}

void MisalignedHandler(void) 
{
    // ISR content ...

}

void IllegalInstrHandler(void) 
{
    // ISR content ...

}

void AccessErrHandler(void) 
{
    // ISR content ...

}

void BreakPointHandler(void) 
{
    // ISR content ...

}

void UnrecExecpHandler(void) 
{
    // ISR content ...

}

void Trap0Handler(void) 
{
    // ISR content ...

}

void Trap1Handler(void) 
{
    // ISR content ...

}

void Trap2Handler(void) 
{
    // ISR content ...

}

void Trap3Handler(void) 
{
    // ISR content ...

}

void PendTrapHandler(void) 
{
    // ISR content ...

}
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/

