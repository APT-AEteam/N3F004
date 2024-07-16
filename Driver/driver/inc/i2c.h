/***********************************************************************//** 
 * \file  i2c.h
 * \brief i2c description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7-15 <td>V1_0_0  <td>GQQ  <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _I2C_H
#define _I2C_H

/* Includes ------------------------------------------------------------------*/
#include "types_local.h"

/// \struct csp_i2c_t
/// \brief i2c reg description      
 typedef struct
 {
   __IM U32_T	_RSVD0[20];				//0x0000~0x004C
   __OM U32_T	ECR;							//0x0050	clock enable register
   __OM U32_T	DCR;							//0x0054	clock disable register
   __IM U32_T	PMSR; 						//0x0058	power management status register
   __IM U32_T	_RSVD1;						//0x005C 
   __IOM U32_T	CR;								//0x0060	control register
   __IOM U32_T	MR;								//0x0064	mode register
   __IM U32_T	_RSVD2[2];				//0x0068~0x006c
   __IM U32_T  	SR;							   		 //0x0070   status register
   __OM U32_T	IER;  		   				    //0x0074	interrupt enable register
   __OM U32_T  IDR;     	   				    //0x0078    interrupt disable register
   __IM  U32_T	IMR;   							//0x007C   interrupt mask status register
   __IOM U32_T	SDR;     						//0x0080   data register
   __IOM  U32_T ADR;  		      			//0x0084	slave address register
   __OM  U32_T	THOLD;    				    //0x0088	hold/setup delay control register
   
}csp_i2c_t;

/******************************************************************************
**************************      Global Definition	     ***************************
******************************************************************************/
typedef enum{
	I2C_IDLE= 0,
	I2C_STARTED,
	I2C_RESTARTED,
	I2C_REPEATED_START,
	DATA_ACK,
	DATA_NACK,
	I2C_WR_STARTED,
	I2C_RD_STARTED
} i2c_state_e;

#define BUFSIZE             255

/******************************************************************************
************************** I2C Registers Definition ***************************
******************************************************************************/
#define I2C_RESET_VALUE  	(0x00000000)
#define I2C_MR_RESET          	 (0x000001F4ul)     /**< MR reset value          */
#define I2C_THOLD_RESET        (0x00000001ul)     /**< THOLD reset value       */        
#define I2C_ADDRESS      (0x56) //7 bit

/******************************************************************************
* ECR, DCR, PMSR : I2C Power Management Registers
******************************************************************************/
 #define  I2C_CLKEN         	(0x01ul << 1)    /**< I2C Clock                 */
 #define I2C_IPIDCODE       (0x01ul << 4)    /**< I2C version number        */
 #define I2C_DBGEN           (0x01ul << 31)   /**< Debug Mode Enable         */
/******************************************************************************
* CR : I2C Control Register 
******************************************************************************/
 #define I2C_SWRST          (0x01ul << 0)   /**< I2C Software Reset          */
 #define I2C_AA_POS        (1)
 #define I2C_AA_MSK	      (0x01ul << I2C_AA_POS)   /**< I2C Acknowledge Mask        */ 
 typedef enum{
	I2C_ANSWER_DIS =0,
	I2C_ANSWER_EN
 }i2c_answer_e;

 #define I2C_STO_POS	(2)  
 #define I2C_STO_MSK  (0x01ul << I2C_STO_POS)   /**< I2C Stop                    */
 typedef enum{
	I2C_STOPBIT_DIS =0,
	I2C_STOPBIT_EN
 }i2c_stopbit_e;
 
 #define I2C_STA_POS	(3)  
 #define I2C_STA_MSK   (0x01ul << 3)   /**< I2C Start Mask              */       
 typedef enum{
	I2C_SLAVE =0,
	I2C_MASTER
 }i2c_workmode_e;

 #define I2C_SI            		 (0x01ul << 4)   /**< I2C Interrupt Mask          */
 #define I2C_SI_SET         (0x01ul << 4)   /**< I2C Interrupt Mask          */
 #define I2C_SI_CLR         (0x00ul << 4)   /**< I2C Interrupt Mask          */
 
 #define I2C_ENA_MSK           (0x01ul << 8)   /**< I2C Enable Mask             */
 #define I2C_ENABLE         (0x01ul << 8)   /**< I2C Enable                  */
 #define I2C_DISABLE        (0x00ul << 8)   /**< I2C Disable                 */  

/******************************************************************************
* MR : I2C Mode Register
******************************************************************************/
/** PRV : Prescaler Value                                                    */
 #define I2C_PRV_MASK  (0xFFFul << 0)           /**< Prescaler Value Mask    **/     

#define I2C_FAST_POS	(12)  
#define I2C_FAST_MSK  (0x01ul  << I2C_FAST_POS)          /**< Enable/Disable Fast Mode*/
typedef enum{
	I2C_MODE_STANDARD =0,
	I2C_MODE_FAST
}i2c_mode_e;

/*****************************************************************************
* SR : I2C Status Register
******************************************************************************/      
 #define I2C_SC_POS  	 (3)              /* Status Code Mask        */               
 #define I2C_SC_MASK   (0x1Ful << I2C_SC_POS)              /* Status Code Mask        */

/******************************************************************************
* SR :Master Transmitter mode status codes
******************************************************************************/
#define I2C_MTX_START                			0x08u  /**< START condition has been transmitted                */
#define I2C_MTX_RSTART             		  0x10u  /**< REPEAT START condition has   been transmitted           */
#define I2C_MTX_SADDR_ACK           	 0x18u  /**< Slave address and WRITE has  been sent, ACK received    */
#define I2C_MTX_SADDR_NACK           0x20u  /**< Slave address and WRITE has  been sent, No ACK received */
#define I2C_MTX_DATATX_ACK           0x28u  /**< Data byte transmitted,  ACK received               */
#define I2C_MTX_DATATX_NACK          0x30u  /**< Data byte transmitted,  No ACK received            */
#define I2C_MTX_AL                  			 0x38u  /**< Arbitration lost           */
/******************************************************************************
* SR: Master Receiver mode status codes
******************************************************************************/
 #define I2C_MRX_START              	 	  0x08u  /**< START condition has been transmitted                */
#define I2C_MRX_RSTART            	 	  0x10u  /**< REPEAT START condition has   been transmitted           */
#define I2C_MRX_AL                		  		  0x38u  /**< Arbitration lost           */
#define I2C_MRX_SADDR_ACK           	  0x40u  /**< Slave address and Read has  been sent, ACK received    */
#define I2C_MRX_SADDR_NACK           0x48u  /**< Slave address and Read has been sent, No ACK received */ 
#define I2C_MRX_DATARX_ACK           0x50u  /**< Data byte received,  ACK returned               */
#define I2C_MRX_DATARX_NACK        0x58u  /**< Data byte received,   No ACK returned            */

/******************************************************************************
*SR: Slave Receiver mode status codes
*****************************************************************************/
 #define I2C_SRX_OADDR_WRI_ACK        0x60u  /**< Own Slave address + WRITE   received, ACK returned     */
 #define I2C_SRX_AL_OADDR_ACK         	0x68u  /**< Arbitration lost, own slave  address received,  ACK returned               */                                               
 #define I2C_SRX_GCA_ACK             			 0x70u  /**< General Call Address has  been received, ACK returned*/
 #define I2C_SRX_AL_GCADDR_ACK        0x78u  /**< Arbitration lost, general  call address received, ACK returned               */
 #define I2C_SRX_OADDR_DATARX_ACK     0x80u  /**< Addressed with own address and W, data byte received,  ACK returned               */
 #define I2C_SRX_OADDR_DATARX_NACK    0x88u  /**< Addressed with own address,  data byte received,  no ACK returned            */
 #define I2C_SRX_GCADDR_DATARX_ACK    0x90u  /**< Addressed by general call address, data byte received, ACK returned               */
 #define I2C_SRX_GCADDR_DATARX_NACK   0x98u  /**< Addressed by general call   address, data byte received,no ACK returned            */
 #define I2C_SRX_STOP_START           0xA0u  /**< A stop or repeated start has been received while still addressed as slave   */

/*****************************************************************************
* SR:Slave Transmitter mode status codes
******************************************************************************/
 #define I2C_STX_OADDR_READ_ACK      0xA8u  /**< Own Slave address + R received, ACK returned   */ 
 #define I2C_STX_AL_OADDR_ACK        	 0xB0u  /**< Arbitration lost, own slave address has been received,  ACK returned    */
#define I2C_STX_DATATX_ACK         	 	 0xB8u  /**< Data has been transmitted, ACK has been received  */
#define I2C_STX_DATATX_NACK         	 0xC0u  /**< Data has been transmitted, No ACK has been received   */
#define I2C_STX_LDATATX_ACK         		 0xC8u  /**< Last data has been  transmitted, ACK received  */

/*****************************************************************************
* Miscellaneous status codes
******************************************************************************/
 #define I2C_NO_INFORMATION           0xF8u  /**< No revelant state   information                */
 #define I2C_BUS_ERROR              			  0x00u  /**< Bus error due to an illegal START or STOP condition    */

/******************************************************************************
*  IER, IDR, IMR : I2C Interrupt Registers
******************************************************************************/
/* I2C_SI  : I2C Interrupt - Same as CR Register                             */
#define I2C_SI_MSK		(0x1ul << 4)

/******************************************************************************
*  SDR : I2C Serial Data Registers
******************************************************************************/
 #define I2C_DATA_MASK    (0xFFul << 0)            /**< Data Mask            */
 
#define I2C_DATA_DIR_POS	(0)
 typedef enum{
	I2C_TX = 0,
	I2C_RX
 }i2c_data_dir_e;

/******************************************************************************
*  ADR : I2C Serial Slave Address Registers
******************************************************************************/
 #define I2C_GC_EN         (0x01ul << 0)            /**< General call           */  
 #define I2C_ADDR_POS  	  (1)
 #define I2C_ADDR_MASK   (0x7Ful << I2C_ADDR_POS)           /**< Address Mask           */

/******************************************************************************
*  ADR : I2C Hold/Setup Delay Registers
******************************************************************************/
 #define I2C_DL_MASK    (0xFFul << 0)             /**< Hold/Setup Delay Mask */

/******************************************************************************
*************************** I2C Frame Macros Definition **********************
******************************************************************************/

#define I2C_TIMEOUT_CNT 48000000ul 

/******************************************************************************
********************* I2C Functions Declaration **********************
******************************************************************************/
/** \brief i2c deinit 
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_deinit(csp_i2c_t *ptI2cBase);

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
void i2c_master_init(csp_i2c_t *ptI2cBase, i2c_mode_e eMode,U16_T hwPreDiv, U8_T byThold);

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
void i2c_slave_init(csp_i2c_t *ptI2cBase, i2c_mode_e eMode,U16_T hwPreDiv, U8_T byThold,U8_T bySlaveAdd);

/** \brief i2c enable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_enable(csp_i2c_t *ptI2cBase);

/** \brief i2c disable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_disable(csp_i2c_t *ptI2cBase);

/** \brief i2c interrupt enable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_int_enable(csp_i2c_t *ptI2cBase);

/** \brief i2c interrupt disable
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_int_disable(csp_i2c_t *ptI2cBase);

/** \brief i2c wakeup enable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void i2c_wakeup_enable(void);

/** \brief i2c wakeup disable
 * 
 *  \param[in] none
 * 			   
 *  \return none
 */ 
void i2c_wakeup_disable(void);

/** \brief i2c generate start signal
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_generate_start(csp_i2c_t *ptI2cBase);

/** \brief i2c generate stop signal
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_generate_stop(csp_i2c_t *ptI2cBase);

/** \brief i2c software reset
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_software_reset(csp_i2c_t *ptI2cBase);

/** \brief i2c ACK generate
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return none
 */ 
void i2c_ack_configure(csp_i2c_t *ptI2cBase,i2c_answer_e eAck);

/** \brief i2c read data
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 * 			   
 *  \return receive data
 */ 
U8_T i2c_receive_data(csp_i2c_t *ptI2cBase);

/** \brief i2c send data
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] bySend: data to be sent
 * 			   
 *  \return none
 */ 
void i2c_send_data(csp_i2c_t *ptI2cBase,uint8_t bySend);

/** \brief i2c send slave address(7bit ) 
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] bySlaveAdd: slave address 
 *  \param[in] eDataDir: slave address  \ref i2c_data_dir_e
 * 			   
 *  \return none
 */ 
void i2c_send_slave_addr(csp_i2c_t *ptI2cBase, uint8_t bySlaveAdd, i2c_data_dir_e eDataDir);

/** \brief i2c write byte
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] byData: data
 * 			   
 *  \return none
 */ 
void i2c_write_byte(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T byData);

/** \brief i2c write numbers of byte(defined by slave )
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] ptData: pointer of data
 *  \param[in] byNum: number of data
 * 			   
 *  \return none
 */ 
void i2c_write_bytes(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T *ptData,U8_T byNum);

/** \brief i2c write byte with interrupt
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 *  \param[in] byData:  data
 * 			   
 *  \return none
 */ 
void i2c_int_write_byte(csp_i2c_t *ptI2cBase, U8_T byAddr, U8_T byData);

/** \brief i2c read byte with interrupt
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 * 			   
 *  \return receive data
 */ 
U8_T i2c_int_read_byte(csp_i2c_t *ptI2cBase, U8_T byAddr);

/** \brief i2c slave receive
 * 
 *  \param[in] ptI2cBase: pointer of i2c register structure
 *  \param[in] byAddr: slave address 
 * 			   
 *  \return receive data
 */
void i2c_slave_receive(csp_i2c_t *ptI2cBase);



#endif   

/******************* (C) COPYRIGHT 2018 APT Chip *****END OF FILE****/