/***********************************************************************//** 
 * \file  syscon.c
 * \brief  syscon driver including clock, IWDT, EXI, LVD,etc.,
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



/*************************************************************/
//Deinitializes the syscon registers to their default reset
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/    
void SYSCON_RST_VALUE(void)									//reset value
{

	SYSCON->RAMCHK=SYSCON_RAMCHK_RST;
	SYSCON->EFLCHK=SYSCON_EFLCHK_RST;
	SYSCON->SCLKCR=SYSCON_SCLKCR_RST;

	SYSCON->OSTR=SYSCON_OSTR_RST;
	SYSCON->LVDCR=SYSCON_LVDCR_RST;

	SYSCON->EXIRT=SYSCON_EXIRT_RST;
	SYSCON->EXIFT=SYSCON_EXIFT_RST;

	SYSCON->IWDCR=SYSCON_IWDCR_RST;
	SYSCON->IWDCNT=SYSCON_IWDCNT_RST;

	SYSCON->EVTRG=SYSCON_EVTRG_RST;
	SYSCON->EVPS=SYSCON_EVPS_RST;
	SYSCON->EVSWF=SYSCON_EVSWF_RST;

}
/*************************************************************/
//EMOSC OSTR Config
//EM_CNT:0~0X3FF
//EM_GM:0~0X1F
//EM_FLEN;EM_FLEN_DIS,EM_FLEN_EN
//EM_FLSEL:EM_FLSEL_5ns,EM_FLSEL_10ns,EM_FLSEL_15ns,EM_FLSEL_20ns
/*************************************************************/  
void EMOSC_OSTR_Config(U16_T EM_CNT, U8_T EM_GM,EM_LFSEL_TypeDef EM_LFSEL_X, EM_Filter_CMD_TypeDef EM_FLEN_X, EM_Filter_TypeDef EM_FLSEL_X)
{
	SYSCON->OSTR=EM_CNT|(EM_GM<<11)|EM_LFSEL_X|EM_FLEN_X|EM_FLSEL_X;
}
/*************************************************************/
//SYSCON General Control
//EntryParameter:NewState:,ENDIS_X
//NewState:ENABLE,DISABLE
//ENDIS_X:ENDIS_ISOSC,ENDIS_IMOSC,ENDIS_EMOSC,ENDIS_HFOSC
//ReturnValue:NONE
/*************************************************************/  
void SYSCON_General_CMD(FunctionalStatus NewState, SYSCON_General_CMD_TypeDef ENDIS_X )
{
	if (NewState != DISABLE)
	{
		if(ENDIS_X==ENDIS_EMOSC) 
		GPIOA0->CONLR=(GPIOA0->CONLR & 0XFFF00FFF)|0x00044000;					//enable EMOSC PIN
		SYSCON->GCER|=ENDIS_X;													//enable SYSCON General Control
		while(!(SYSCON->GCSR&ENDIS_X));											//check  Enable?	
		switch(ENDIS_X)
		{
			case ENDIS_IMOSC:
				while (!(SYSCON->CKST & ENDIS_IMOSC)); 	
				break;
			case ENDIS_EMOSC:
				while (!(SYSCON->CKST & ENDIS_EMOSC)); 
				break;	
			case ENDIS_ISOSC:
				while (!(SYSCON->CKST & ENDIS_ISOSC)); 
				break;
			case ENDIS_HFOSC:
				while (!(SYSCON->CKST & ENDIS_HFOSC)); 
				break;	
			case ENDIS_IDLE_PCLK:
				break;	
			case ENDIS_SYSTICK:
				break;	
		}
	}
	else
	{
		SYSCON->GCDR|=ENDIS_X;													//disable SYSCON General Control
		while(SYSCON->GCSR&ENDIS_X);											//check Disable?
		SYSCON->ICR|=ENDIS_X;													//Clear ENDIS_X stable bit
	}
}

/*************************************************************/
//Seleted system clk and seleted clk div
//EntryParameter:SYSCLK_X,HCLK_DIV_X,PCLK_DIV_X
//SYSCLK_X:SYSCLK_IMOSC,SYSCLK_EMOSC,SYSCLK_ISOSC,SYSCLK_HFOSC
//HCLK_DIV_X:HCLK_DIV_1/2/3/4/5/6/7/8/12/16/24/32/64/128/256
//PCLK_DIV_X:PCLK_DIV_1,PCLK_DIV_2,PCLK_DIV_4,PCLK_DIV_8,PCLK_DIV_16
//SystemClk_data_x:EMOSC_24M,EMOSC_16M,EMOSC_12M,EMOSC_8M,EMOSC_4M,EMOSC_36K,
//ISOSC,IMOSC,HFOSC_48M,HFOSC_24M,HFOSC_12M,HFOSC_6M
//ReturnValue:NONE
/*************************************************************/ 
void SystemCLK_HCLKDIV_PCLKDIV_Config(SystemCLK_TypeDef SYSCLK_X , SystemCLK_Div_TypeDef HCLK_DIV_X , PCLK_Div_TypeDef PCLK_DIV_X , SystemClk_data_TypeDef SystemClk_data_x )
{
	if(SystemClk_data_x==HFOSC_48M)
	{
		IFC->CEDR=0X01;						//CLKEN
		IFC->MR=0X04|(0X00<<16);			//High speed mode
	}
	if((SystemClk_data_x==EMOSC_24M)||(SystemClk_data_x==HFOSC_24M))
	{
		IFC->CEDR=0X01;						//CLKEN
		IFC->MR=0X02|(0X00<<16);			//Medium speed mode
	}
	if((SystemClk_data_x==EMOSC_12M)||(SystemClk_data_x==HFOSC_12M)||(SystemClk_data_x==EMOSC_16M))
	{
		IFC->CEDR=0X01;						//CLKEN
		IFC->MR=0X01|(0X00<<16);			//Low speed mode
	}
	if((SystemClk_data_x==EMOSC_8M)||(SystemClk_data_x==EMOSC_4M)||(SystemClk_data_x==EMOSC_36K)
		||(SystemClk_data_x==IMOSC)||(SystemClk_data_x==ISOSC)||(SystemClk_data_x==HFOSC_6M))
	{
		IFC->CEDR=0X01;						//CLKEN
		IFC->MR=0X00|(0X00<<16);			//Low speed mode
	}
	SYSCON->SCLKCR=SYSCLK_KEY | HCLK_DIV_X| SYSCLK_X;
	while (!(SYSCON->CKST & (1<<8))); 											// waiting for sysclk stable
	SYSCON->PCLKCR=PCLK_KEY|PCLK_DIV_X;											//PCLK DIV 1 2 4 6 8 16		
	while(SYSCON->PCLKCR!=PCLK_DIV_X);											//Wait PCLK DIV
}
/*************************************************************/
//clear system clk register
//ReturnValue:NONE
/*************************************************************/ 
void SystemCLK_Clear(void)
{
	SYSCON->SCLKCR=0xd22d0000;
	while(SYSCON->SCLKCR!=0);
}
/*************************************************************/
//SYSCON IMOSC SELECTE
//EntryParameter:IMOSC_SELECTE_X
//IMOSC_SELECTE_X:IMOSC_SELECTE_5556K,IMOSC_SELECTE_4194K;IMOSC_SELECTE_2097K;IMOSC_SELECTE_131K
//ReturnValue:NONE
/*************************************************************/  
void SYSCON_IMOSC_SELECTE(IMOSC_SELECTE_TypeDef IMOSC_SELECTE_X)
{		
	//SYSCON_General_CMD(DISABLE,ENDIS_IMOSC);					//disalbe IMOSC
	SYSCON->OPT1 = (SYSCON->OPT1 & 0XFFFFFFFC)|IMOSC_SELECTE_X;	//IMOSC CLK selected
	//SYSCON_General_CMD(ENABLE,ENDIS_IMOSC);						//enable IMOSC
}
/*************************************************************/
//SYSCON HFOSC SELECTE
//EntryParameter:HFOSC_SELECTE_X
//HFOSC_SELECTE_X:HFOSC_SELECTE_48M,HFOSC_SELECTE_24M;HFOSC_SELECTE_12M;HFOSC_SELECTE_6M
//ReturnValue:NONE
/*************************************************************/  
void SYSCON_HFOSC_SELECTE(HFOSC_SELECTE_TypeDef HFOSC_SELECTE_X)
{		
	SYSCON_General_CMD(DISABLE,ENDIS_HFOSC);					//disable HFOSC
	SYSCON->OPT1 = (SYSCON->OPT1 & 0XFFFFFFCF)|HFOSC_SELECTE_X;
	SYSCON_General_CMD(ENABLE,ENDIS_HFOSC);						//enable HFOSC
}
/*************************************************************/
//WDT enable and disable 
//EntryParameter:,NewState
//NewState:ENABLE,DISABLE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_WDT_CMD(FunctionalStatus NewState)
{
	if(NewState != DISABLE)
	{
		SYSCON->IWDEDR=IWDTEDR_KEY|Enable_IWDT;
		while(!(SYSCON->IWDCR&Check_IWDT_BUSY));
	}
	else
	{
		SYSCON->IWDEDR=IWDTEDR_KEY|Disable_IWDT;
		while(SYSCON->IWDCR&Check_IWDT_BUSY);
	}
}
/*************************************************************/
//reload WDT CN
//EntryParameter:NONE
//ReturnValue: NONE
/*************************************************************/
void SYSCON_IWDCNT_Reload(void)
{
	SYSCON->IWDCNT=CLR_IWDT;
}
/*************************************************************/
//IWDCNT Config
//EntryParameter:NewStateE_IWDT_SHORT,IWDT_TIME_X,IWDT_INTW_DIV_X
//NewStateE_IWDT_SHORT:ENABLE_IWDT_SHORT,DISABLE_IWDT_SHORT
//IWDT_TIME_X:IWDT_TIME_128MS,IWDT_TIME_256MS,IWDT_TIME_500MS,IWDT_TIME_1S,IWDT_TIME_2S,IWDT_TIME_3S,IWDT_TIME_4S,IWDT_TIME_8S
//IWDT_INTW_DIV_X:IWDT_INTW_DIV_1/2/3/4/4/5/6
//ReturnValue: NONE
/*************************************************************/
void SYSCON_IWDCNT_Config(IWDT_TIME_TypeDef IWDT_TIME_X , IWDT_TIMEDIV_TypeDef IWDT_INTW_DIV_X )
{
	SYSCON->IWDCR=IWDT_KEY|IWDT_TIME_X|IWDT_INTW_DIV_X;
}
/*************************************************************/
//LVD Config  and set LVD INT
//EntryParameter:X_LVDEN,INTDET_LVL_X,RSTDET_LVL_X,X_LVD_INT
//X_LVDEN:ENABLE_LVDEN,DISABLE_LVDEN
//INTDET_LVL_X:INTDET_LVL_1_8V,INTDET_LVL_2_1V,INTDET_LVL_2_5V,INTDET_LVL_2_9V,INTDET_LVL_3_3V,INTDET_LVL_3_7V,INTDET_LVL_4_1V,INTDET_LVL_4_5V
//RSTDET_LVL_X:RSTDET_LVL_1_6V,RSTDET_LVL_2_0V,RSTDET_LVL_2_4V,RSTDET_LVL_2_8V,RSTDET_LVL_3_2V,RSTDET_LVL_3_6V,RSTDET_LVL_4_0V,RSTDET_LVL_4_4V
//X_LVD_INT:ENABLE_LVD_INT,DISABLE_LVD_INT
//INTDET_POL_X:INTDET_POL_fall,INTDET_POL_X_rise,INTDET_POL_X_riseORfall
//ReturnValue: NONE
/*************************************************************/
void SYSCON_LVD_Config(X_LVDEN_TypeDef X_LVDEN , INTDET_LVL_X_TypeDef INTDET_LVL_X , RSTDET_LVL_X_TypeDef RSTDET_LVL_X , X_LVD_INT_TypeDef X_LVD_INT , INTDET_POL_X_TypeDef INTDET_POL_X)
{
	//SYSCON->LVDCR=LVD_KEY;
	SYSCON->LVDCR=LVD_KEY|X_LVDEN|INTDET_LVL_X|RSTDET_LVL_X|X_LVD_INT|INTDET_POL_X;
}
/*************************************************************/
//LVD INT ENABLE.
//EntryParameter:NONE
//ReturnValue: NONE
/*************************************************************/
void LVD_Int_Enable(void)
{
	SYSCON->ICR = LVD_INT_ST;				//clear LVD INT status
	SYSCON->IMER  |= LVD_INT_ST;
}
/*************************************************************/
//LVD INT DISABLE.
//EntryParameter:NONE
//ReturnValue: NONE
/*************************************************************/
void LVD_Int_Disable(void)
{
	SYSCON->IMDR  |= LVD_INT_ST;
}
/*************************************************************/
//WDT INT ENABLE.
//EntryParameter:NONE
//ReturnValue: NONE
/*************************************************************/
void IWDT_Int_Enable(void)
{
	SYSCON->ICR = IWDT_INT_ST;				//clear LVD INT status
	SYSCON->IMER  |= IWDT_INT_ST;
}
/*************************************************************/
//WDT INT DISABLE.
//EntryParameter:NONE
//ReturnValue: NONE
/*************************************************************/
void IWDT_Int_Disable(void)
{
	SYSCON->IMDR  |= IWDT_INT_ST;
}
/*************************************************************/
//Reset status.
//EntryParameter:NONE
//ReturnValue: rsr_dat
//rsr_dat=0x01 power on reset
//rsr_dat=0x02 low voltage reset
//rsr_dat=0x04 ex-pin reset
//rsr_dat=0x10 wdt reset
//rsr_dat=0x40 ex clock invalid reset
//rsr_dat=0x80 cpu request reset
//rsr_dat=0x100 software reset
/*************************************************************/
U32_T Read_Reset_Status(void)
{
	return (SYSCON->RSR & 0x1ff);
}
/*************************************************************/
//external trigger  Mode Selection Functions
//EntryParameter:NewState,EXIPIN,EXI_tringer_mode
//NewState:ENABLE,DISABLE
//EXIPIN:EXI_PIN0/1/2/3/4/5/6/7/8/9/10/11/12/13
//EXI_tringer_mode:_EXIRT,_EXIFT
//ReturnValue: LVD detection flag
/*************************************************************/
void EXTI_trigger_CMD(FunctionalStatus NewState , SYSCON_EXIPIN_TypeDef  EXIPIN , EXI_tringer_mode_TypeDef EXI_tringer_mode)
{
	switch(EXI_tringer_mode)
	{
		case _EXIRT:
		if(NewState != DISABLE)
		{
			SYSCON->EXIRT |=EXIPIN;
		}
		else
		{
			SYSCON->EXIRT &=~EXIPIN;	
		}
		break;
		case _EXIFT:
		if(NewState != DISABLE)
		{
			SYSCON->EXIFT |=EXIPIN;
		}
		else
		{
			SYSCON->EXIFT &=~EXIPIN;	
		}
		break;
	}	
}
/*************************************************************/
//external interrupt enable and disable 
//EntryParameter:NewState,EXIPIN,* GPIOX
//* GPIOX:GPIOA,GPIOB
//EXIPIN:EXI_PIN0/1/2/3/4/5/6/7/8/9/10/11/12/13
//NewState:ENABLE,DISABLE
//ReturnValue:NONE
/*************************************************************/
void EXTI_interrupt_CMD(FunctionalStatus NewState , SYSCON_EXIPIN_TypeDef  EXIPIN)
{
	SYSCON->EXICR = 0X3FFF;									//Claer EXI INT status
	if(NewState != DISABLE)
	{
		SYSCON->EXIER|=EXIPIN;								//EXI4 interrupt enable
		while(!(SYSCON->EXIMR&EXIPIN));						//Check EXI is enabled or not
		SYSCON->EXICR |=EXIPIN;								// Clear EXI status bit
	}
	else
	{
		SYSCON->EXIDR|=EXIPIN;
	}
}
/*************************************************************/
//GPIO EXTI interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void GPIO_EXTI_interrupt(CSP_GPIO_T * GPIOX,U32_T GPIO_IECR_VALUE)
{
	GPIOX->IECR=GPIO_IECR_VALUE;
}
/*************************************************************/
//PLCK goto SLEEP mode
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void PCLK_goto_idle_mode(void)
{
	asm ("doze");											// Enter sleep mode
}  
/*************************************************************/
//PLCK goto SLEEP mode
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void PCLK_goto_deepsleep_mode(void)
{
	SYSCON->WKCR=0X3F<<8;
	asm ("stop");
}  
/*************************************************************/
//EXI0 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI0_Int_Enable(void)
{   
	csi_vic_enable_irq(EXI0_INT);  
}

/*************************************************************/
//EXI0 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI0_Int_Disable(void)
{ 
	csi_vic_disable_irq(EXI0_INT);    
}

/*************************************************************/
//EXI1 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1_Int_Enable(void)
{
	csi_vic_enable_irq(EXI1_INT);     
}

/*************************************************************/
//EXI1 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1_Int_Disable(void)
{  
	 csi_vic_disable_irq(EXI1_INT);    
}

/*************************************************************/
//EXI2 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2_Int_Enable(void)
{
	csi_vic_enable_irq(EXI2_INT);      
}

/*************************************************************/
//EXI2 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2_Int_Disable(void)
{
	csi_vic_disable_irq(EXI2_INT);    
}

/*************************************************************/
//EXI3 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI3_Int_Enable(void)
{
	csi_vic_enable_irq(EXI3_INT);   
}

/*************************************************************/
//EXI3 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI3_Int_Disable(void)
{ 
	 csi_vic_disable_irq(EXI3_INT);    
}

/*************************************************************/
//EXI4 Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4_Int_Enable(void)
{
	csi_vic_enable_irq(EXI4_INT);  
}

/*************************************************************/
//EXI4 Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4_Int_Disable(void)
{
	 csi_vic_disable_irq(EXI4_INT);    
}
/*************************************************************/
//EXI0 Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI0_WakeUp_Enable(void)
{
    csi_vic_set_wakeup_irq(EXI0_INT);    
}

/*************************************************************/
//EXI0 Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI0_WakeUp_Disable(void)
{
    csi_vic_clear_wakeup_irq(EXI0_INT);     
}

/*************************************************************/
//EXI1 Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1_WakeUp_Enable(void)
{
    csi_vic_set_wakeup_irq(EXI1_INT);  
}

/*************************************************************/
//EXI1 Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI1_WakeUp_Disable(void)
{
    csi_vic_clear_wakeup_irq(EXI1_INT);    
}

/*************************************************************/
//EXI2 Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2_WakeUp_Enable(void)
{
	csi_vic_set_wakeup_irq(EXI2_INT);
}

/*************************************************************/
//EXI2 Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI2_WakeUp_Disable(void)
{
    csi_vic_clear_wakeup_irq(EXI2_INT);   
}

/*************************************************************/
//EXI3 Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI3_WakeUp_Enable(void)
{
    csi_vic_set_wakeup_irq(EXI3_INT);
}

/*************************************************************/
//EXI3 Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI3_WakeUp_Disable(void)
{
	csi_vic_clear_wakeup_irq(EXI3_INT); 
}

/*************************************************************/
//EXI4 Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4_WakeUp_Enable(void)
{ 
	csi_vic_set_wakeup_irq(EXI4_INT);
}

/*************************************************************/
//EXI4 Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void EXI4_WakeUp_Disable(void)
{
	csi_vic_clear_wakeup_irq(EXI4_INT);
}

/*************************************************************/
//SYSCON Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_Int_Enable(void)
{
  	csi_vic_enable_irq(SYSCON_INT);
}

/*************************************************************/
//SYSCON Interrupt disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_Int_Disable(void)
{
    csi_vic_disable_irq(SYSCON_INT);    
}
/*************************************************************/
//SYSCON Wake up enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_WakeUp_Enable(void)
{
	csi_vic_set_wakeup_irq(SYSCON_INT);
}
/*************************************************************/
//set PA0.0/PA0.8 as CLO output 
//EntryParameter:CLO_PA02/CLO_PA08
//ReturnValue:NONE
/*************************************************************/
void SYSCON_CLO_CONFIG(CLO_IO_TypeDef clo_io)
{
	if (clo_io==CLO_PA02)
	{
		GPIOA0->CONLR = (GPIOA0->CONLR&0XFFFFF0FF) | 0X00000700;
	}
	if (clo_io==CLO_PA08)
	{
		GPIOA0->CONHR = (GPIOA0->CONHR&0XFFFFFFF0) | 0X00000007;
	}
	
}
/*************************************************************/
//set CLO clk and div
//EntryParameter:clomxr/clodivr
//ReturnValue:NONE
/*************************************************************/
void SYSCON_CLO_SRC_SET(SystemClk_CLOMX_TypeDef clomxr,SystemClk_CLODIV_TypeDef clodivr)
{
	SYSCON->OPT1=(SYSCON->OPT1 & 0XFFFF00FF)|(clomxr<<8)|(clodivr<<12);
}
/*************************************************************/
//SYSCON Wake up disable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_WakeUp_Disable(void)
{
    csi_vic_clear_wakeup_irq(SYSCON_INT);  
}
/*************************************************************/
//READ CIF0 data
//EntryParameter:None
//ReturnValue:VALUE
/*************************************************************/
U32_T SYSCON_Read_CINF0(void)
{
    U32_T value = 0;
    value=SYSCON->CINF0;
    return value;
}
/*************************************************************/
//READ CIF1 data
//EntryParameter:None
//ReturnValue:VALUE
/*************************************************************/
U32_T SYSCON_Read_CINF1(void)
{
    U32_T value = 0;
    value=SYSCON->CINF1;
    return value;
}
/*************************************************************/
//Software_Reset
//EntryParameter:None
//ReturnValue:MCU reset
/*************************************************************/
void SYSCON_Software_Reset(void)
{
	SYSCON->IDCCR=IDCCR_KEY|SWRST;
}
/*************************************************************/
//Interrupt Priority initial
//EntryParameter:00/40/80/C0
//----------------------
//CORET_INT   IRQ0
//SYSCON_INT  IRQ1
//IFC_INT     IRQ2
//ADC_INT     IRQ3
//----------------------
//EPT0_INT    IRQ4
//****DUMMY   IRQ5
//WWDT_INT    IRQ6
//EXI0_INT    IRQ7
//----------------------
//EXI1_INT    IRQ8
//GPT0_INT    IRQ9 
//****DUMMY   IRQ10
//****DUMMY   IRQ11
//----------------------
//RTC_INT     IRQ12
//UART0_INT   IRQ13
//UART1_INT   IRQ14
//UART2_INT   IRQ15
//----------------------
//****DUMMY   IRQ16
//I2C_INT     IRQ17
//****DUMMY   IRQ18
//SPI_INT     IRQ19
//----------------------
//SIO_INT     IRQ20
//EXI2_INT    IRQ21
//EXI3_INT    IRQ22
//EXI4_INT    IRQ23
//----------------------
//CA_INT      IRQ24
//TKEY_INT    IRQ25
//LPT_INT     IRQ26
//****DUMMY   IRQ27
//----------------------
//BT0_INT     IRQ28
//BT1_INT     IRQ29
//----------------------
//ReturnValue:None
//00:Priority 0		highest
//40:Priority 1
//80:Priority 2
//C0:Priority 3		lowest
/*************************************************************/
void SYSCON_INT_Priority(void)
{
	uint8_t i;
	uint8_t ePrio = 3;
	for(i = 0; i < 8; i++)
	{
		VIC->IPR[i] = (ePrio << 6) | (ePrio << 14) | (ePrio << 22) | (ePrio << 30);
	}
}
///*************************************************************/
////Set Interrupt Priority
////EntryParameter:
////int_name:CORET_IRQ~BT1_IRQ
////int_level:0~3  0=highest   3=lowest
////ReturnValue:None
///*************************************************************/
//void Set_INT_Priority(U8_T int_name,U8_T int_level)
//{
//	U8_T i_temp,j_temp;
//	U32_T k_temp;
//	i_temp=(int_name%4)*8;
//	j_temp=int_name/4;
//	k_temp=CK801 -> IPR[j_temp]&(~(0xff<<i_temp));
//	CK801 -> IPR[j_temp]=k_temp|((int_level*0x40)<<(i_temp));
//}

#define Set_INT_Priority csi_vic_set_prio

/*************************************************************/
//IO REMAP
//EntryParameter:GPIOA0(0,1,2,3,4,5,6,7) GPIOB0(2,3),GPIOA0(8,9,10,11,12,13)
//0x00=I2C_SCL 0X01=I2C_SDA 0X02=GPT_CHA 0X03=GPT_CHB
//0X04=SPI_MOSI 0X05=SPI_MISO 0X06=SPI_SCK 0X07=SPI_NSS
//0x00=UART0_RX 0X01=UART0_TX 0X02=EPT_CHAX 0X03=PT_CHBX
//0X04=PT_CHCX 0X05=PT_CHAY 0X06=PT_CHBY 0X07=PT_CHCY
//ReturnValue:NONE
/*************************************************************/
void GPIO_Remap(CSP_GPIO_T *GPIOx,uint8_t bit,IOMAP_DIR_TypeDef iomap_data)
{
	U8_T i;
	if(iomap_data&0x10)
	{
		iomap_data=iomap_data&0X0F;
		if(iomap_data==0)
		{
			for(i=0;i<28;i+=4)
			{
				if((SYSCON->IOMAP1&(0xf<<i))==0)
				{
					SYSCON->IOMAP1=SYSCON->IOMAP1|(0xf<<i);
				}
			}
		}
		if(bit==2){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xfffffff0)|iomap_data;(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFFF0FF) | 0x00000A00;}
		if(bit==3){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xffffff0f)|(iomap_data<<4);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFF0FFF) | 0x0000A000;}
		if(bit==8){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xfffff0ff)|(iomap_data<<8);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFFFFFFF0) | 0x0000000A;}
		if(bit==9){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xffff0fff)|(iomap_data<<12);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFFFFFF0F) | 0x000000A0;}
		if(bit==10){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xfff0ffff)|(iomap_data<<16);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFFFFF0FF) | 0x00000A00;}
		if(bit==11){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xff0fffff)|(iomap_data<<20);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFFFF0FFF) | 0x0000A000;}
		if(bit==12){SYSCON->IOMAP1=(SYSCON->IOMAP1&0xf0ffffff)|(iomap_data<<24);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFFF0FFFF) | 0x000A0000;}
		if(bit==13){SYSCON->IOMAP1=(SYSCON->IOMAP1&0x0fffffff)|(iomap_data<<28);(GPIOx)->CONHR =((GPIOx)->CONHR&0XFF0FFFFF) | 0x00A00000;}
	}
	else
	{
		if(iomap_data==0)
		{
			for(i=0;i<28;i+=4)
			{
			if((SYSCON->IOMAP0&(0xf<<i))==0)
				{
					SYSCON->IOMAP0=SYSCON->IOMAP0|(0xf<<i);
				}
			}
		}
		if(bit==0){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xfffffff0)|iomap_data;(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFFFFF0) | 0x0000000A;}
		if(bit==1){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xffffff0f)|(iomap_data<<4);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFFFF0F) | 0x000000A0;}
		if(bit==2){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xfffff0ff)|(iomap_data<<8);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFFF0FF) | 0x00000A00;}
		if(bit==3){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xffff0fff)|(iomap_data<<12);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFFF0FFF) | 0x0000A000;}
		if(bit==4){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xfff0ffff)|(iomap_data<<16);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFFF0FFFF) | 0x000A0000;}
		if(bit==5){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xff0fffff)|(iomap_data<<20);(GPIOx)->CONLR =((GPIOx)->CONLR&0XFF0FFFFF) | 0x00A00000;}
		if(bit==6){SYSCON->IOMAP0=(SYSCON->IOMAP0&0xf0ffffff)|(iomap_data<<24);(GPIOx)->CONLR =((GPIOx)->CONLR&0XF0FFFFFF) | 0x0A000000;}
		if(bit==7){SYSCON->IOMAP0=(SYSCON->IOMAP0&0x0fffffff)|(iomap_data<<28);(GPIOx)->CONLR =((GPIOx)->CONLR&0X0FFFFFFF) | 0x0A0000000;}
	}
}
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/