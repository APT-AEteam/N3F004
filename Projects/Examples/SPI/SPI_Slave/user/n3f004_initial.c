/***********************************************************************//** 
 * \file  n3f004_initial.c
 * \brief initialization for all IPs
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
#include "n3f004_top.h"

#if 0
/* define --------------------------------------------------------------------*/
	
/* externs--------------------------------------------------------------------*/
/*************************************************************/
//software delay
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void delay_nms(unsigned int t)
{
    volatile unsigned int i,j ,k=0;
    j = 50* t;
    for ( i = 0; i < j; i++ )
    {
        k++;
		SYSCON_IWDCNT_Reload(); 
    }
}

void delay_nus(unsigned int t)
{
    volatile unsigned int i,j ,k=0;
    j = 1* t;
    for ( i = 0; i < j; i++ )
    {
        k++;
    }
}
/*************************************************************/
//GPIO Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void GPIO_CONFIG(void)
{
//	gpio_init(GPIOA0,13,0);
}
/*************************************************************/
//CORET Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void CORET_CONFIG(void)
{
	CORET_DeInit();
	SYSCON_General_CMD(ENABLE,ENDIS_SYSTICK);
	CORET->LOAD=59999;						
	//CORETCLK=sysclock/8=48M/8=6Mhz  e.g:10ms=(CORET_RVR+1)*(8/48M);CORET_RVR=60000-1=59999
	CORET_reload();																
	CORET_CLKSOURCE_EX();						      //use ex clock
	CORET_TICKINT_Enable();								//clear CORET counter
	CORET_start();	
	
	CORET_Int_Enable();
	//CORET_WakeUp_Enable();									
}
/*************************************************************/
//ETP0 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void EPT0_CONFIG(void)
{

}
/*************************************************************/
//GPT0 Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void GPT0_CONFIG(void)
{
	
}
/*************************************************************/
//LPT Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void LPT_CONFIG(void)
{
	
}
/*************************************************************/
//BT Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void BT_CONFIG(void)
{
}
/*************************************************************/
//COUNTA Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void COUNTA_CONFIG(void)
{
                                                                   //countA INT enable
}
/*************************************************************/
//RTC Initial
//EntryParameter:NONE
//ReturnValue:NONE
//RTC CLK=(CLKSRC_EMOSC)/(DIVS+1)/(DIVA+1)/4
//		  (ISCLK)/(DIVS+1)/(DIVA+1)/4
//		  (IMCLK)/(DIVS+1)/(DIVA+1)/4
/*************************************************************/	
void RTC_CONFIG(void)
{
	
}
/*************************************************************/
//ET Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void ET_CONFIG(void)
{

}
/*************************************************************/
//SIO Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/ 
void SIO_CONFIG(void)
{
	
}
/*************************************************************/
//SPI MASTER Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void SPI_MASTER_CONFIG(void)
{
	
}
/*************************************************************/
//SPI SLAVE Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void SPI_SLAVE_CONFIG(void)
{
//	spi_pin_config(SPI_NSS_PA06);
	spi_pin_config(SPI_SCK_PB02);
	spi_pin_config(SPI_MOSI_PB03);
	spi_pin_config(SPI_MISO_PA08);
		
	spi_deinit(SPI0);
	// 发送数据大小为8BIT;SCK第一个时钟沿捕捉;接收1个数据中断触发断点 ;FSSPCLKOUT=20M/12=1.6M
	spi_slave_init(SPI0,SPI_LEN_8,SPI_CPOL_0_CPHA_0,SPI_RXFIFO_1_DATA,0,12);			
	spi_int_enable(SPI0,SPI_INT_RXFIFO);				//使能FIFO接收中断
}
/*************************************************************/
//IIC MASTER Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void I2C_MASTER_CONFIG(void)
{
	
}
/*************************************************************/
//IIC SLAVER Initial
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void I2C_SLAVE_CONFIG(void)
{
	
	
}
/*************************************************************/
//UART0  CONFIG
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void UART0_CONFIG(void)
{
	
}	
/*************************************************************/
//UART1  CONFIG
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void UART1_CONFIG(void)
{
	
}	
/*************************************************************/
//UART2  CONFIG
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void UART2_CONFIG(void)
{
	
}	
/*************************************************************/
//adc config
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void ADC12_CONFIG(void)
{
						
} 
/*************************************************************/
//TK config
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/	
void TK_CONFIG(void)
{
	
}  
/*************************************************************/
//syscon Functions
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void SYSCON_CONFIG(void)
{
		
//------SYSTEM CLK AND PCLK FUNTION---------------------------/
	SYSCON_deinit();                                                         //SYSCON all register clr
	SYSCON_General_CMD(ENABLE,ENDIS_ISOSC);										//SYSCON enable/disable clock source
						//0X0a //0X07
	//EMOSC_OSTR_Config(0XAD,0X1f,EM_LFSEL_EN,EM_FLEN_EN,EM_FLSEL_10ns);		//EM_CNT=0X3FF,0xAD(36K),EM_GM=0,Low F modedisable,EM filter disable,if enable,cont set 5ns
	//SYSCON_General_CMD(ENABLE,ENDIS_EMOSC);
	SYSCON_HFOSC_SELECTE(HFOSC_SELECTE_48M);									//HFOSC selected 48MHz
	SystemCLK_HCLKDIV_PCLKDIV_Config(SYSCLK_HFOSC,HCLK_DIV_1,PCLK_DIV_1,HFOSC_48M);//system clock set, Hclk div ,Pclk div  set system clock=SystemCLK/Hclk div/Pclk div
//------------  WDT FUNTION  --------------------------------/
    SYSCON_IWDCNT_Config(IWDT_TIME_4S,IWDT_INTW_DIV_7);      					//WDT TIME 1s,WDT alarm interrupt time=1s-1s*1/8=0.875S
    SYSCON_WDT_CMD(DISABLE);                                                  	//enable/disable WDT		
    SYSCON_IWDCNT_Reload();                                                   	//reload WDT
	IWDT_Int_Enable();
													//enable wwdt
//------------  CLO Output --------------------------------/	
	//SYSCON_CLO_CONFIG(CLO_PA08);												//CLO output setting
	//SYSCON_CLO_SRC_SET(CLO_HFCLK,CLO_DIV16);									//CLO output clock and div
//------------  LVD FUNTION  --------------------------------/ 
    SYSCON_LVD_Config(DISABLE_LVDEN,INTDET_LVL_3_9V,RSTDET_LVL_1_9V,DISABLE_LVD_INT,INTDET_POL_fall);   //LVD LVR Enable/Disable
    LVD_Int_Enable();	
//------------  SYSCON Vector  --------------------------------/ 	
	SYSCON_Int_Enable();    														//SYSCON VECTOR
	//SYSCON_WakeUp_Enable();    													//Enable WDT wakeup INT

	
}
/*********************************************************************************/  
/*********************************************************************************/
//APT32S003_init                                                                  /
//EntryParameter:NONE                                                             /
//ReturnValue:NONE                                                                /
/*********************************************************************************/
/*********************************************************************************/  
/*********************************************************************************/
void APT32F102_init(void) 
{
	VIC->ISER[0U] = (0xffffffff);									// 使能VIC层所有的中断，如果要响应IP的中断处理函数，还有另外两个使能开关
																	// 1) 使能IP层中断：如 xx_IMER
																	// 2) 使能总中断： CK_CPU_ENALLNORMALIRQ
//------------------------------------------------------------/
//Peripheral clock enable and disable
//EntryParameter:NONE
//ReturnValue:NONE
//------------------------------------------------------------/
    SYSCON->PCER0=0xFFFFFFF;                                        //PCLK Enable  0x00410071
    SYSCON->PCER1=0xFFFFFFF;                                        //PCLK Enable
    while(!(SYSCON->PCSR0&0x1));                                    //Wait PCLK enabled	
//------------------------------------------------------------/
//ISOSC/IMOSC/EMOSC/SYSCLK/IWDT/LVD/EM_CMFAIL/EM_CMRCV/CMD_ERR OSC stable interrupt
//EntryParameter:NONE
//ReturnValue:NONE
//------------------------------------------------------------/
    SYSCON_CONFIG();                                                 //syscon  initial
	CK_CPU_ENALLNORMALIRQ;                                         //enable all IRQ
//------------------------------------------------------------/
//Other IP config
//------------------------------------------------------------/
	//GPIO_CONFIG();                                                //GPIO initial    
	//CORET_CONFIG();												//CORET initial 
	//EPT0_CONFIG();                                                //EPT0 initial 
	//GPT0_CONFIG();												//GPT0 initial
	//LPT_CONFIG();													//LPT initial	
	//	BT_CONFIG();													//BT initial
	//COUNTA_CONFIG();                                              //CountA initial	
	//RTC_CONFIG();													//RCT initial		              
	//ET_CONFIG();													//ETCB initial
    //I2C_MASTER_CONFIG();                                          //I2C harware master initial 
	//I2C_SLAVE_CONFIG();                                           //I2C harware slave initial 
	//SPI_MASTER_CONFIG();											//SPI Master initial 	
	spi_slave_cofigure();											//SPI Slaver initial 
  //SIO_CONFIG();													//SIO initial
    //UART0_CONFIG();                                               //UART0 initial 
	//UART1_CONFIG();                                               //UART1 initial 
	//UART2_CONFIG();                                               //UART2 initial 
	//ADC12_CONFIG();                                               //ADC initial 
	//TK_CONFIG();													//Touch Key initial
}

#endif
/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/