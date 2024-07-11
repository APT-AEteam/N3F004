/***********************************************************************//** 
 * \file  n3f004_interrupt.c
 * \brief interrupt handlers implementation declared in startup file
 * 		  IFC操作不依赖于任何中断处理函数
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
/* global variables----------------------------------------------------------*/
/* Private variables---------------------------------------------------------*/


/*************************************************************/
/* hardware vector interrupt Handler
*************************************************************/

void CORETHandler(void)
{
	// ISR content ...
}

void TKEYIntHandler(void)
{
	// ISR content ...
}

void SYSCONIntHandler(void) 
{
    // ISR content ...

}

void IFCIntHandler(void) 
{
    // ISR content ...

}

void ADCIntHandler(void) 
{
    // ISR content ...
	
}

void EPT0IntHandler(void) 
{
    // ISR content ...
}


void GPT0IntHandler(void) 
{
    // ISR content ...
}


void UART0IntHandler(void) 
{
    // ISR content ...
}

void UART1IntHandler(void) 
{
    // ISR content ...
}


void I2CIntHandler(void) 
{
    // ISR content ...
}

void SPI0IntHandler(void) 
{
    // ISR content ...

}


void EXI0IntHandler(void) 
{
	// ISR content ...
}

void EXI1IntHandler(void) 
{
	// ISR content ...
}

void EXI2to3IntHandler(void) 
{
	// ISR content ...
}

void EXI4to9IntHandler(void) 
{
	// ISR content ...
}

void EXI10to15IntHandler(void) 
{
	// ISR content ...
}

void CNTAIntHandler(void) 
{
    // ISR content ...
}


void BT0IntHandler(void) 
{
	// ISR content ...

}

void BT1IntHandler(void) 
{
    // ISR content ...
}


void CMP0IntHandler(void) 
{
    // ISR content ...
	
}

void CMP1IntHandler(void) 
{
    // ISR content ...
	
}

/*************************************************************/
/* system abnormal Handler
*************************************************************/
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

