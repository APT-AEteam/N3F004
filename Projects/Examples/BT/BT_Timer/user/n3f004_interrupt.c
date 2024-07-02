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
	__NOP();
	if((SYSCON->MISR&ISOSC_ST)==ISOSC_ST)				//ISOSC stable interrupt
	{
		SYSCON->ICR = ISOSC_ST;
	} 
	else if((SYSCON->MISR&IMOSC_ST)==IMOSC_ST)			//IMOSC stable interrupt
	{
		SYSCON->ICR = IMOSC_ST;
	} 
	else if((SYSCON->MISR&EMOSC_ST)==EMOSC_ST)			//EMOSC stable interrupt
	{
		SYSCON->ICR = EMOSC_ST;
	} 
	else if((SYSCON->MISR&HFOSC_ST)==HFOSC_ST)			//HFOSC stable interrupt
	{
		SYSCON->ICR = HFOSC_ST;
	} 
	else if((SYSCON->MISR&SYSCLK_ST)==SYSCLK_ST)		//SYSCLK change end & stable interrupt
	{
		SYSCON->ICR = SYSCLK_ST;
	}
	else if((SYSCON->MISR&IWDT_INT_ST)==IWDT_INT_ST)	//IWDT alarm window interrupt
	{
		SYSCON->ICR = IWDT_INT_ST;
		SYSCON->IWDCNT=0x5aul<<24;
	}
	else if((SYSCON->MISR&WKI_INT_ST)==WKI_INT_ST)
	{
		SYSCON->ICR = WKI_INT_ST;
	}
	else if((SYSCON->MISR&RAMERRINT_ST)==RAMERRINT_ST)	//SRAM check fail interrupt
	{
		SYSCON->ICR = RAMERRINT_ST;
	}
	else if((SYSCON->MISR&LVD_INT_ST)==LVD_INT_ST)		//LVD threshold interrupt
	{
		__NOP();
		SYSCON->ICR = LVD_INT_ST;
	}
	else if((SYSCON->MISR&HWD_ERR_ST)==HWD_ERR_ST)		//Hardware Divider divisor = 0 interrupt
	{
		SYSCON->ICR = HWD_ERR_ST;
	}
	else if((SYSCON->MISR&EFL_ERR_ST)==EFL_ERR_ST)		//Flash check fail interrupt
	{
		SYSCON->ICR = EFL_ERR_ST;
	}
	else if((SYSCON->MISR&OPTERR_INT)==OPTERR_INT)		//Option load fail interrupt
	{
		SYSCON->ICR = OPTERR_INT;
	}
	else if((SYSCON->MISR&EM_CMLST_ST)==EM_CMLST_ST)	//EMOSC clock monitor fail interrupt
	{
		SYSCON->ICR = EM_CMLST_ST;
	}
	else if((SYSCON->MISR&EM_EVTRG0_ST)==EM_EVTRG0_ST)	//Event Trigger Channel 0 Interrupt
	{
		SYSCON->ICR = EM_EVTRG0_ST;
	}
	else if((SYSCON->MISR&EM_EVTRG1_ST)==EM_EVTRG1_ST)	//Event Trigger Channel 1 Interrupt
	{
		SYSCON->ICR = EM_EVTRG1_ST;
	}
	else if((SYSCON->MISR&EM_EVTRG2_ST)==EM_EVTRG2_ST)	//Event Trigger Channel 2 Interrupt
	{
		SYSCON->ICR = EM_EVTRG2_ST;
	}
	else if((SYSCON->MISR&EM_EVTRG3_ST)==EM_EVTRG3_ST)	//Event Trigger Channel 3 Interrupt
	{
		SYSCON->ICR = EM_EVTRG3_ST;
	}
	else if((SYSCON->MISR&CMD_ERR_ST)==CMD_ERR_ST)		//Command error interrupt
	{
		SYSCON->ICR = CMD_ERR_ST;
	}
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
	if ((SYSCON->EXIRS&EXI_PIN0)==EXI_PIN0) 			//EXT0 Interrupt
	{
		SYSCON->EXICR = EXI_PIN0;
	}
	else if ((SYSCON->EXIRS&EXI_PIN16)==EXI_PIN16) 		//EXT16 Interrupt
	{
		SYSCON->EXICR = EXI_PIN16;
	}
}
/*************************************************************/
//EXT1/17 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1IntHandler(void) 
{
    // ISR content ...
	if ((SYSCON->EXIRS&EXI_PIN1)==EXI_PIN1) 			//EXT1 Interrupt
	{
		SYSCON->EXICR = EXI_PIN1;
	}
	else if ((SYSCON->EXIRS&EXI_PIN17)==EXI_PIN17) 		//EXT17 Interrupt
	{
		SYSCON->EXICR = EXI_PIN17;
	}
}
/*************************************************************/
//EXI2~3 18~19Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2to3IntHandler(void) 
{
    // ISR content ...
	if ((SYSCON->EXIRS&EXI_PIN2)==EXI_PIN2) 			//EXT2 Interrupt
	{
		SYSCON->EXICR = EXI_PIN2;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN3)==EXI_PIN3) 		//EXT3 Interrupt
	{
		SYSCON->EXICR = EXI_PIN3;
	}
	else if ((SYSCON->EXIRS&EXI_PIN18)==EXI_PIN18) 		//EXT18 Interrupt
	{
		SYSCON->EXICR = EXI_PIN18;
	}
	else if ((SYSCON->EXIRS&EXI_PIN19)==EXI_PIN19) 		//EXT19 Interrupt
	{
		SYSCON->EXICR = EXI_PIN19;
	}
}
/*************************************************************/
//EXI4~9 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4to9IntHandler(void) 
{
    // ISR content ...
	if ((SYSCON->EXIRS&EXI_PIN4)==EXI_PIN4) 			//EXT4 Interrupt
	{
		SYSCON->EXICR = EXI_PIN4;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN5)==EXI_PIN5) 		//EXT5 Interrupt
	{
		SYSCON->EXICR = EXI_PIN5;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN6)==EXI_PIN6) 		//EXT6 Interrupt
	{
		SYSCON->EXICR = EXI_PIN6;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN7)==EXI_PIN7) 		//EXT7 Interrupt
	{
		SYSCON->EXICR = EXI_PIN7;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN8)==EXI_PIN8) 		//EXT8 Interrupt
	{
		SYSCON->EXICR = EXI_PIN8;
	}
	else if ((SYSCON->EXIRS&EXI_PIN9)==EXI_PIN9) 		//EXT9 Interrupt
	{
		SYSCON->EXICR = EXI_PIN9;
	} 

}
/*************************************************************/
//EXI4 Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI10to15IntHandler(void) 
{
    // ISR content ...
	if ((SYSCON->EXIRS&EXI_PIN10)==EXI_PIN10) 			//EXT10 Interrupt
	{
		SYSCON->EXICR = EXI_PIN10;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN11)==EXI_PIN11) 		//EXT11 Interrupt
	{
		SYSCON->EXICR = EXI_PIN11;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN12)==EXI_PIN12) 		//EXT12 Interrupt
	{
		SYSCON->EXICR = EXI_PIN12;
	} 
	else if ((SYSCON->EXIRS&EXI_PIN13)==EXI_PIN13) 		//EXT13 Interrupt
	{
		SYSCON->EXICR = EXI_PIN13;
	}
	else if ((SYSCON->EXIRS&EXI_PIN14)==EXI_PIN14) 		//EXT14 Interrupt
	{
		SYSCON->EXICR = EXI_PIN14;
	}
	else if ((SYSCON->EXIRS&EXI_PIN15)==EXI_PIN15) 		//EXT15 Interrupt
	{
		SYSCON->EXICR = EXI_PIN15;
	}
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

