/*
  ******************************************************************************
  * @file    apt32f102_ifc.c
  * @author  APT AE Team
  * @version V1.17
  * @date    2023/08/30
  ******************************************************************************
  *THIS SOFTWARE WHICH IS FOR ILLUSTRATIVE PURPOSES ONLY WHICH PROVIDES 
  *CUSTOMER WITH CODING INFORMATION REGARDING THEIR PRODUCTS.
  *APT CHIP SHALL NOT BE HELD RESPONSIBILITY ADN LIABILITY FOR ANY DIRECT, 
  *INDIRECT DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF 
  *SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION 
  *CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.AND APT CHIP RESERVES 
  *THE RIGHT TO MAKE CHANGES IN THE SOFTWARE WITHOUT NOTIFICATION
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"
volatile unsigned int R_INT_FlashAdd;
volatile unsigned char f_Drom_writing=0;
/* define --------------------------------------------------------------------*/
extern void delay_nms(unsigned int t); 
/* externs--------------------------------------------------------------------*/
/*************************************************************
//ChipErase fuction
//EntryParameter:NONE
//ReturnValue:NONE
*************************************************************/
void ChipErase(void)
{
	SetUserKey;
	EnChipErase;
	StartErase;
	while(IFC->CR!=0x0);			//Wait for the operation to complete
}
/*************************************************************
//PageErase fuction
//EntryParameter:XROM_PageAdd
//XROM_PageAdd:PROM_PageAdd0~PROM_PageAdd255
//DROM_PageAdd0~DROM_PageAdd31
//ReturnValue:NONE
*************************************************************/
void PageErase(IFC_ROMSELETED_TypeDef XROM_PageAdd)
{
	SetUserKey;
	EnPageErase;
	IFC->FM_ADDR=XROM_PageAdd;
	StartErase;
	while(IFC->CR!=0x0);
}
/*************************************************************
//Enable or Disable IFC Interrupt when Operate FlashData 
//EntryParameter:FlashAdd、DataSize、*BufArry
//ReturnValue:NONE
*************************************************************/
//PROM:Write at most 256 bytes once time
//DROM:Write at most 64 bytes at once time
//Interrupt mode requires multiple loop queries to complete
//Not Support across page writing!!!
void Page_ProgramData_int(unsigned int FlashAdd,unsigned int DataSize,volatile unsigned char *BufArry)
{
	int i,DataBuffer;
	if(!f_Drom_writing)
	{
		f_Drom_writing=1;
		R_INT_FlashAdd=FlashAdd;
		ifc_step=0;
		//Page cache wipe 1
		SetUserKey;
		IFC->CMR=0x07;					//Page cache wipe
		IFC->FM_ADDR=FlashAdd;
		IFC->CR=0X01;					//Start Program
		while(IFC->CR!=0x0);			//Wait for the operation to complete
		//Write data to the cache 2
		for(i=0;i<((DataSize+3)/4);i++)   //sizeof structure
		{
			DataBuffer=*BufArry+(*(BufArry+1)<<8)+(*(BufArry+2)<<16)+(*(BufArry+3)<<24);
			*(volatile unsigned int *)(FlashAdd+4*i)=DataBuffer;
			BufArry  +=4;
		}
		//Pre-programmed operation settings 3
		SetUserKey;
		IFC->CMR=0x06;					
		IFC->FM_ADDR=FlashAdd;
		IFC->CR=0X01;					//Start Program
		while(IFC->CR!=0x0);			//Wait for the operation to complete
		//Perform pre-programming 4
		SetUserKey;
		IFC->CMR=0x01;					
		IFC->FM_ADDR=FlashAdd;			//
		IFC->CR=0X01;					//Start Program
	}
}
//Normal mode, when the call is completed once, it will delay 4.2ms in the program
//Not Support across page writing!!!
void Page_ProgramData(unsigned int FlashAdd,unsigned int DataSize,volatile unsigned char *BufArry)
{
	int i,DataBuffer;

	//Page cache wipe 1
	SetUserKey;
	IFC->CMR=0x07;					
	IFC->FM_ADDR=FlashAdd;
	IFC->CR=0X01;					//Start Program
	while(IFC->CR!=0x0);			//Wait for the operation to complete
	//Write data to the cache 2
	for(i=0;i<((DataSize+3)/4);i++)   //sizeof structure
	{
		DataBuffer=*BufArry+(*(BufArry+1)<<8)+(*(BufArry+2)<<16)+(*(BufArry+3)<<24);
		*(volatile unsigned int *)(FlashAdd+4*i)=DataBuffer;
		BufArry  +=4;
	}
	//Pre-programmed operation settings 3
	SetUserKey;
	IFC->CMR=0x06;					
	IFC->FM_ADDR=FlashAdd;
	IFC->CR=0X01;					//Start Program
	while(IFC->CR!=0x0);			//Wait for the operation to complete
	//Perform pre-programming 4
	SetUserKey;
	IFC->CMR=0x01;					
	IFC->FM_ADDR=FlashAdd;			//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=PEP_END_INT);			//Wait for the operation to complete
	//Page erase 5
	SetUserKey;
	IFC->CMR=0x02;					
	IFC->FM_ADDR=FlashAdd;			//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=ERS_END_INT);			//Wait for the operation to complete
	//Write page cache data to flash memory 6
	SetUserKey;
	IFC->CMR=0x01;					
	IFC->FM_ADDR=FlashAdd;		//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=RGM_END_INT);			//Wait for the operation to complete
}

//Not Support across page writing!!!
void Page_ProgramData_U32(unsigned int FlashAdd,unsigned int DataSize,volatile U32_T *BufArry)
{
	int i,DataBuffer;

	//Page cache wipe 1
	SetUserKey;
	IFC->CMR=0x07;					
	IFC->FM_ADDR=FlashAdd;
	IFC->CR=0X01;					//Start Program
	while(IFC->CR!=0x0);			//Wait for the operation to complete
	//Write data to the cache 2
	for(i=0;i<DataSize;i++)   //sizeof structure
	{
		DataBuffer=*BufArry;
		*(volatile unsigned int *)(FlashAdd+4*i)=DataBuffer;
		BufArry  +=1;
	}
	//Pre-programmed operation settings 3
	SetUserKey;
	IFC->CMR=0x06;					
	IFC->FM_ADDR=FlashAdd;
	IFC->CR=0X01;					//Start Program
	while(IFC->CR!=0x0);			//Wait for the operation to complete
	//Perform pre-programming 4
	SetUserKey;
	IFC->CMR=0x01;					
	IFC->FM_ADDR=FlashAdd;			//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=PEP_END_INT);			//Wait for the operation to complete
	//Page erase 5
	SetUserKey;
	IFC->CMR=0x02;					
	IFC->FM_ADDR=FlashAdd;			//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=ERS_END_INT);			//Wait for the operation to complete
	//Write page cache data to flash memory 6
	SetUserKey;
	IFC->CMR=0x01;					
	IFC->FM_ADDR=FlashAdd;		//
	IFC->CR=0X01;					//Start Program
	while(IFC->RISR!=RGM_END_INT);			//Wait for the operation to complete
}
/*************************************************************
// ReadFlashData fuction return Data arry save in Flash
// DataLength must be a multiple of 4, DataLength % 4 ==0.
//EntryParameter:RdStartAdd、DataLength、*DataArryPoint
//ReturnValue:NONE
*************************************************************/
void ReadDataArry(unsigned int RdStartAdd,unsigned int DataLength,volatile unsigned char *DataArryPoint)
{
	unsigned int i,Buffer;
	//delay_nms(1);
	for(i=0;i<((DataLength+3)/4);i++)
	{
		Buffer=*(volatile unsigned int *)RdStartAdd;
		*DataArryPoint=Buffer;
		*(DataArryPoint+1)=Buffer>>8;
		*(DataArryPoint+2)=Buffer>>16;
		*(DataArryPoint+3)=Buffer>>24;
		RdStartAdd +=4;
		DataArryPoint +=4;
	}
}
/*************************************************************
//ReadFlashData fuction return Data arry save in Flash
//EntryParameter:RdStartAdd、DataLength、*DataArryPoint
//ReturnValue:NONE
*************************************************************/
void ReadDataArry_U8(unsigned int RdStartAdd,unsigned int DataLength,volatile unsigned char *DataArryPoint)
{
	unsigned int i;
	for (i=0;i<DataLength;i++)
	{
		if((i!=0)&&(i%4==0))
		{
			RdStartAdd +=4;
		}	
		*DataArryPoint=*(U8_T *)(RdStartAdd+ (i%4));
		DataArryPoint++;
	}
}
void ReadDataArry_U32(unsigned int RdStartAdd,unsigned int DataLength,volatile U32_T *DataArryPoint)
{
	unsigned int i;
	for (i=0;i<DataLength;i++)
	{
		*DataArryPoint=*(U32_T *)(RdStartAdd+4*i);
		DataArryPoint++;
	}
}
/*************************************************************
//Enable or Disable IFC Interrupt when Operate FlashData 
//EntryParameter:IFC_INT_x
//IFC_INT_x:ERS_END_INT,RGM_END_INT,PEP_END_INT,PROT_ERR_INT,UDEF_ERR_INT,ADDR_ERR_INT,OVW_ERR_INT
//ReturnValue:NONE
*************************************************************/
void IFC_interrupt_CMD(FunctionalStatus NewState ,IFC_INT_TypeDef IFC_INT_x)
{
	if(NewState != DISABLE)
	{
		IFC->IMCR =IFC->IMCR|IFC_INT_x;
	}
	else 
	{
		IFC->IMCR =IFC->IMCR & (~IFC_INT_x);
	}
}
/*************************************************************/
//IFC Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void IFC_Int_Enable(void)
{
    IFC->ICR=0Xf007;					//CLAER IFC INT status
	INTC_ISER_WRITE(IFC_INT);    
}

/*************************************************************/
//IFC Interrupt enable
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/
void IFC_Int_Disable(void)
{
    INTC_ICER_WRITE(IFC_INT);    
}
/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/