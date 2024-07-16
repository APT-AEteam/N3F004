/***********************************************************************//** 
 * \file  i2c.c
 * \brief i2c function interface
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-15 <td>V1_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "n3f004.h"

/* externs--------------------------------------------------------------------*/
/* private function-----------------------------------------------------------*/
/* global variablesr----------------------------------------------------------*/

/* Private variablesr---------------------------------------------------------*/
volatile U8_T byI2cIntFlag ;					//I2C interrupt flag
volatile U8_T byRestart;
//volatile U8_T byI2cMode;
volatile U8_T byI2cSlaveState = I2C_IDLE;
volatile U8_T byI2cTxBuffer[BUFSIZE];		//I2C  Write buffer（slave mode）
volatile U8_T byI2cRxBuffer[BUFSIZE];		//I2C  Read buffer（slave mode）
volatile U8_T byRxIndex = 0;
volatile U8_T byTxIndex = 0;
volatile U8_T byI2cDataAddress;	
volatile U8_T byI2cStartAddress;	
/* defines -------------------------------------------------------------------*/


/** \brief i2c deinit 
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_deinit(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->ECR   = I2C_RESET_VALUE;
    ptI2cBase->DCR   = I2C_RESET_VALUE;
    ptI2cBase->CR    = I2C_RESET_VALUE;
    ptI2cBase->MR    = I2C_MR_RESET;
    ptI2cBase->IER   = I2C_RESET_VALUE;
    ptI2cBase->IDR   = I2C_RESET_VALUE;
    ptI2cBase->SDR   = I2C_RESET_VALUE;
    ptI2cBase->ADR   = I2C_RESET_VALUE;
    ptI2cBase->THOLD = I2C_THOLD_RESET;
}  

/** \brief i2c master init
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] eMode: I2C speed mode select: fast or standard  \ref i2c_mode_e
 *  \param[in] hwPreDiv: pre scaler value ,range :0~0xfff
 * 					fscl = pclk/(hwPreDiv+4)
 *  \param[in] byThold: hold/setup time, range : 1~0xff
 * 					hold/setup time = byThold *pclk
 * 			   
 *  \return none
 */ 
void i2c_master_init(csp_i2c_t *ptI2cBase, i2c_mode_e eMode,U16_T hwPreDiv, U8_T byThold)
{
    ptI2cBase->ECR = I2C_CLKEN;                                              //Enable I2C clock
	ptI2cBase->CR = I2C_SWRST;                                               //I2C Generate a software reset
    if (eMode==I2C_MODE_FAST)
    {    
		ptI2cBase->MR = hwPreDiv|(I2C_MODE_FAST<<I2C_FAST_POS);            //76KHz @PCLK 24MHz  e.g:24000000/(0x138+4)=76000   hwPreDiv=0x138            
    }                                                                 								  //I2C pre-scalar，and ，mode select
    else ptI2cBase->MR = hwPreDiv;
    ptI2cBase->THOLD = byThold;                                          //I2C Hold/Setup delays
    ptI2cBase->IER = I2C_SI_MSK;                                           //Enable Si interrupt
	ptI2cBase->CR = I2C_ENABLE;                                                 //Enable I2C
//	byI2cMode=1;
}

/** \brief i2c slave init
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] eMode: I2C speed mode select: fast or standard  \ref i2c_mode_e
 *  \param[in] hwPreDiv: pre scaler value ,range :0~0xfff
 * 					fscl = pclk/(hwPreDiv+4)
 *  \param[in] byThold: hold/setup time, range : 1~0xff
 * 					hold/setup time = byThold *pclk
 * \param[in] bySlaveAdd: set slave address, range : 0~0xff
 * 			   
 *  \return none
 */ 
void i2c_slave_init(csp_i2c_t *ptI2cBase, i2c_mode_e eMode,U16_T hwPreDiv, U8_T byThold,U8_T bySlaveAdd)
{
    ptI2cBase->ECR = I2C_CLKEN;                                //Enable I2C clock
	ptI2cBase->CR = I2C_SWRST;                               //I2C Generate a software reset
	if (eMode==I2C_MODE_FAST)
    {    
		ptI2cBase->MR = hwPreDiv|(I2C_MODE_FAST<<I2C_FAST_POS);                        //76KHz @PCLK 20MHz  e.g:20000000/(MR_u32+4)=76000   MR_u32=0x103         
    }                                                   //I2C pre-scalar，and ，mode select
	else
	{ 
		ptI2cBase->MR = hwPreDiv;
	}
    ptI2cBase->THOLD = byThold;                            //I2C Hold/Setup delays
    ptI2cBase->SDR = bySlaveAdd;
    ptI2cBase->IER = I2C_SI_MSK;                           //Enable Si interrupt
    ptI2cBase->CR = (ptI2cBase->CR&(~I2C_STA_MSK))| (I2C_SLAVE<<I2C_STA_POS);                //I2C as Slave
	ptI2cBase->CR |= I2C_ENABLE;                      //Enable I2C
    ptI2cBase->CR  |= (I2C_ANSWER_EN<<I2C_AA_POS);
//	byI2cMode=0;
}

/** \brief i2c enable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_enable(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR |=I2C_ENABLE;
}

/** \brief i2c disable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_disable(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR = (ptI2cBase->CR&(~I2C_ENA_MSK))| I2C_DISABLE;
}

/** \brief i2c interrupt enable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_int_enable(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);					//clear I2C INT status
	csi_vic_enable_irq(I2C_INT);
	ptI2cBase->IER = I2C_SI_MSK;
}

/** \brief i2c interrupt disable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_int_disable(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->IDR = I2C_SI_MSK;
	ptI2cBase->CR &= (~I2C_SI);					//clear I2C INT status
}

/** \brief i2c wakeup enable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void i2c_wakeup_enable(void)
{
	csi_vic_set_wakeup_irq(I2C_INT);            //Enable I2C wake up
}
/** \brief i2c wakeup disable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void i2c_wakeup_disable(void)
{
	csi_vic_clear_wakeup_irq(I2C_INT);            //Enable I2C wake up
}

/** \brief i2c generate start signal
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_generate_start(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR |= I2C_MASTER<<I2C_STA_POS;
}

/** \brief i2c generate stop signal
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_generate_stop(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR |= I2C_STOPBIT_EN<<I2C_STO_POS;
}

/** \brief i2c software reset
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_software_reset(csp_i2c_t *ptI2cBase)
{
    ptI2cBase->CR |= I2C_SWRST;
}

/** \brief i2c ACK generate
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_ack_configure(csp_i2c_t *ptI2cBase,i2c_answer_e eAck)
{
  if (eAck == I2C_ANSWER_DIS)
  {
    /* Disable the acknowledgement */
    ptI2cBase->CR = (ptI2cBase->CR &(~I2C_AA_MSK))| (I2C_ANSWER_DIS<<I2C_AA_POS);
  }
  else
  {
    /* Enable the acknowledgement */
    ptI2cBase->CR |= I2C_ANSWER_EN<<I2C_AA_POS;
  }
}

/** \brief i2c read data
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return receive data
 */ 
U8_T i2c_receive_data(csp_i2c_t *ptI2cBase)
{
  /* Return the data present in the DR register */
  return ptI2cBase->SDR;
}
/** \brief i2c send data
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] bySend: data to be sent
 * 			   
 *  \return none
 */ 
void i2c_send_data(csp_i2c_t *ptI2cBase,uint8_t bySend)
{
  /* Write in the DR register the data to be sent */
  ptI2cBase->SDR = bySend;
}

/** \brief i2c send slave address(7bit ) 
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] bySlaveAdd: slave address 
 *  \param[in] eDataDir: slave address  \ref i2c_data_dir_e
 * 			   
 *  \return none
 */ 
void i2c_send_slave_addr(csp_i2c_t *ptI2cBase, uint8_t bySlaveAdd, i2c_data_dir_e eDataDir)
{
  /* Clear bit0 (direction) just in case */
  bySlaveAdd &= 0xfe;
  /* Send the Address + Direction */
  ptI2cBase->SDR= bySlaveAdd | eDataDir;
}

/** \brief i2c write byte
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] byData: data
 * 			   
 *  \return none
 */ 
void i2c_write_byte(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T byData)
{
	// Write Byte
	ptI2cBase->CR |= (I2C_MASTER<<I2C_STA_POS);
	while((ptI2cBase->SR& I2C_MTX_START) != I2C_MTX_START );
	while((ptI2cBase->CR& I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	ptI2cBase->SDR = I2C_ADDRESS<<1;//0xA2;									// Device ID, Write
	while((ptI2cBase->CR& I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	ptI2cBase->SDR = byAddr;									// Address
	while((ptI2cBase->CR& I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	ptI2cBase->SDR = byData;								// Data
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);
	ptI2cBase->CR &= (~I2C_SI);
                
	ptI2cBase->CR  |= (I2C_STOPBIT_EN<<I2C_STO_POS);
}

/** \brief i2c write numbers of byte(defined by slave )
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] ptData: pointer of data
 *  \param[in] byNum: number of data
 * 			   
 *  \return none
 */ 
void i2c_write_bytes(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T *ptData,U8_T byNum)
{
// Write Byte
	ptI2cBase->CR |= (I2C_MASTER<<I2C_STA_POS);
	while((ptI2cBase->SR & I2C_MTX_START) != I2C_MTX_START );   //master tx start bit is sent
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	ptI2cBase->SDR = I2C_ADDRESS<<1;//0xA2;									// Device ID, Write
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	ptI2cBase->SDR = byAddr;									// Address
	while((ptI2cBase->CR  & I2C_SI) != I2C_SI);
	ptI2cBase->CR &= (~I2C_SI);
	while(byNum!=0)
		
	ptI2cBase->SDR = *ptData++;
//	ptData++;// Data
	while((ptI2cBase->CR  & I2C_SI) != I2C_SI);
	ptI2cBase->CR &= (~I2C_SI);
	byNum--;               
	ptI2cBase->CR  |= (I2C_STOPBIT_EN<<I2C_STO_POS);
}

/** \brief i2c write byte with interrupt
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] byData:  data
 * 			   
 *  \return none
 */ 
void i2c_int_write_byte(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T byData)
{
	byI2cIntFlag=0;

// Write Byte
	ptI2cBase->CR |= (I2C_MASTER<<I2C_STA_POS);
//	while((CSP_I2C_GET_SR(ptI2cBase) & I2C_MTX_START) != I2C_MTX_START );
	while(byI2cIntFlag!=1);
	byI2cIntFlag=0;

//	ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);
	ptI2cBase->SDR = I2C_ADDRESS<<1;//0xA2;									// Device ID, Write
	while(!byI2cIntFlag);
	byI2cIntFlag=0;

//	ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);
	ptI2cBase->SDR = byAddr;									// Address
	while(!byI2cIntFlag);
	byI2cIntFlag=0;

//	ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);
	ptI2cBase->SDR = byData;									// Data
	while(!byI2cIntFlag);
	byI2cIntFlag=0;

//	ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);
	ptI2cBase->CR |= (I2C_STOPBIT_EN<<I2C_STO_POS);
}

/** \brief i2c read byte
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 * 			   
 *  \return receive data
 */ 
U8_T i2c_read_byte(csp_i2c_t *ptI2cBase, U8_T byAddr)
{
	// Verify
	ptI2cBase->CR |= (I2C_MASTER<<I2C_STA_POS);
	while((ptI2cBase->SR& I2C_MTX_START) != I2C_MTX_START );
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);
	ptI2cBase->CR &= (~I2C_SI);

	ptI2cBase->SDR= I2C_ADDRESS<<1;//0xA2;									// Device ID, Write
//	ptI2cBase->CR = ptI2cBase->CR & (~I2C_SI);
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->SDR = byAddr;									// Address
	ptI2cBase->CR &= (~I2C_SI);
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->CR = (ptI2cBase->CR & (~I2C_SI)) |  (I2C_MASTER<<I2C_STA_POS);		// re-start
//	while((CSP_I2C_GET_SR(ptI2cBase) & I2C_MTX_START) != I2C_MTX_START );
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->SDR = (I2C_ADDRESS<<1)+1;//0xA3;									// Device ID, Read
	ptI2cBase->CR &= (~I2C_SI);
	while((ptI2cBase->CR & I2C_SI) != I2C_SI);

	ptI2cBase->CR &= (~I2C_SI);
	while((ptI2cBase->CR& I2C_SI) != I2C_SI);

	ptI2cBase->CR = (ptI2cBase->CR & (~I2C_SI)) | (I2C_STOPBIT_EN<<I2C_STO_POS);

	return ptI2cBase->SDR;
}

/** \brief i2c read byte with interrupt
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 * 			   
 *  \return receive data
 */ 
U8_T i2c_int_read_byte(csp_i2c_t *ptI2cBase, U8_T byAddr)
{

	byI2cIntFlag=0;
	U8_T byI2cReceive;

	// Verify
	ptI2cBase->CR |= (I2C_MASTER<<I2C_STA_POS);
//	while((CSP_I2C_GET_SR(ptI2cBase) & I2C_MTX_START) != I2C_MTX_START );
	while(!byI2cIntFlag);

	ptI2cBase->SDR = I2C_ADDRESS<<1;//0xA2;									// Device ID, Write
	byI2cIntFlag=0;
	while(!byI2cIntFlag);

	ptI2cBase->SDR = byAddr;									// Address
	byI2cIntFlag=0;
	byRestart=1;
	while(!byI2cIntFlag);

//	ptI2cBase->CR = ptI2cBase->CR | I2C_STA;						// re-start
	byI2cIntFlag=0;
	while(!byI2cIntFlag);

	ptI2cBase->SDR = (I2C_ADDRESS<<1)+1;//0xA3;									// Device ID, Read
	byI2cIntFlag=0;
	while(!byI2cIntFlag);

	byI2cIntFlag=0;
	while(!byI2cIntFlag);

	byI2cReceive = ptI2cBase->SDR;

	ptI2cBase->CR |=  (I2C_STOPBIT_EN<<I2C_STO_POS);

//	return ptI2cBase->DAT;
	return byI2cReceive;
}

/** \brief i2c slave receive
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 * 			   
 *  \return receive data
 */
void i2c_slave_receive(csp_i2c_t *ptI2cBase)
{
//    uint8_t SR_Value;
//	SR_Value=ptI2cBase->SR;
    switch(ptI2cBase->SR)
    {
        case I2C_SRX_OADDR_WRI_ACK:                                                        
        case I2C_SRX_AL_OADDR_ACK:                              //slave receive address and ACK returned
        byRxIndex=0;
		ptI2cBase->CR |=I2C_ANSWER_EN<<I2C_AA_POS;
		ptI2cBase->CR &= (~I2C_SI);
        byI2cSlaveState = I2C_WR_STARTED;
        break;
		
        case I2C_SRX_OADDR_DATARX_ACK:                          
        case I2C_SRX_GCADDR_DATARX_ACK:                        //Address data received
        if ( byI2cSlaveState == I2C_WR_STARTED )
        {
			/*byI2cRxBuffer[byRxIndex] = ptI2cBase->DAT;
			byRxIndex++;
			ptI2cBase->CR = ptI2cBase->CR | I2C_AA;*/
			if(byRxIndex==0)
			{
				//byI2cRxBuffer[byRxIndex] = ptI2cBase->DAT;
				byI2cDataAddress=ptI2cBase->SDR;
				byI2cStartAddress=byI2cDataAddress;
				byRxIndex++;
				ptI2cBase->CR |= I2C_ANSWER_EN<<I2C_AA_POS;
			}
			else
			{
				//byI2cRxBuffer[byI2cRxBuffer[0]]= ptI2cBase->DAT;
				if(byI2cDataAddress<BUFSIZE)
				{
					byI2cRxBuffer[byI2cDataAddress]= ptI2cBase->SDR;
				}
				byI2cDataAddress++;
				ptI2cBase->CR |= I2C_ANSWER_EN<<I2C_AA_POS;
			}
        }
        else
        {
          ptI2cBase->CR |=(ptI2cBase->CR&(~(I2C_AA_MSK)))|(I2C_ANSWER_DIS<<I2C_AA_POS);
        }
		ptI2cBase->CR&= (~I2C_SI);
		break;
		
		case I2C_STX_OADDR_READ_ACK:
		case I2C_STX_AL_OADDR_ACK:                             //Slave address and read bit received，ACK returned
		byRxIndex=0;
		byI2cSlaveState = I2C_RD_STARTED;
		byTxIndex = byI2cStartAddress;
		if(byTxIndex<BUFSIZE)
		{
			ptI2cBase->SDR= byI2cTxBuffer[byTxIndex];
		}	
		ptI2cBase->CR |=I2C_ANSWER_EN<<I2C_AA_POS;
		ptI2cBase->CR &= (~I2C_SI);
		break;
		
		case I2C_STX_DATATX_ACK:
		case I2C_STX_LDATATX_ACK:
		if ( byI2cSlaveState == I2C_RD_STARTED )
		{
			if(byTxIndex+1<BUFSIZE)
			{
				 ptI2cBase->SDR= byI2cTxBuffer[byTxIndex+1];
			}
            byTxIndex++;
			ptI2cBase->CR |= I2C_ANSWER_EN<<I2C_AA_POS;
		}
		else
		{
             ptI2cBase->CR |=(ptI2cBase->CR&(~(I2C_AA_MSK)))|(I2C_ANSWER_DIS<<I2C_AA_POS);
		}
		ptI2cBase->CR  &= (~I2C_SI);
		break;
		
		case I2C_STX_DATATX_NACK:                             //Data has been transmitted，and no ack
		ptI2cBase->CR |=(ptI2cBase->CR&(~(I2C_AA_MSK)))|(I2C_ANSWER_DIS<<I2C_AA_POS);
		ptI2cBase->CR &= (~I2C_SI);
		byI2cSlaveState = DATA_NACK;
		break;
          
		case I2C_SRX_STOP_START:                              //A stop or repeated start received
		ptI2cBase->CR |= I2C_ANSWER_EN<<I2C_AA_POS;
		ptI2cBase->CR &= (~I2C_SI);
		byI2cSlaveState = I2C_IDLE;
		break;

		default:
		i2c_software_reset(I2C0);
//		I2C_SLAVE_CONFIG();                                     //if error，reset I2C
		ptI2cBase->CR  &= (~I2C_SI);
    }
	return;
}

/******************* (C) COPYRIGHT 2018 APT Chip *****END OF FILE****/