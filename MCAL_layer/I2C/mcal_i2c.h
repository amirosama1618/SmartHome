/* 
 * File:   mcal_i2c.h
 * Author: Ameer
 *
 * Created on March 30, 2024, 2:36 PM
 */

#ifndef MCAL_I2C_H
#define	MCAL_I2C_H

/*================================ section : includes ================================*/
#include "pic18f4620.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"
/*================================ section : Macro definitions ================================*/
#define I2C_MASTER_MODE         1
#define I2C_SLAVE_MODE           0
/*---------------------------------------*/
/**
 * SSPSTAT: MSSP STATUS REGISTERSSPSTAT: MSSP STATUS REGISTER
 */
/*---------------------------------------*/
/*SMP: Slew Rate Control bit*/
#define I2C_SLEW_RATE_DISABLE                       0
#define I2C_SLEW_RATE_ENABLE                        1
/* CKE: SMBus Select bit */
#define I2C_SM_BUS_DISABLE                           0
#define I2C_SM_BUS_ENABLE                             1
/* D/A: Data/Address bit */
#define I2C_LAST_BYTE_ADDRESS                        0
#define I2C_LAST_BYTE_DATA                            1
/* D/A: Data/Address bit */
#define I2C_STOP_BIT_NOT_DETECTED                   0
#define I2C_STOP_BIT_DETECTED                        1
#define I2C_START_BIT_NOT_DETECTED                 0
#define I2C_START_BIT_DETECTED                       1
/* R/W: Read/Write Information bit 
 *  In Slave mode:
 *   1 = Read
 *   0 = Write
 *  In Master mode:
 *   1 = Transmit is in progress
 *   0 = Transmit is not in progress
 */
#define I2C_SLAVE_WRITE                                 0
#define I2C_SLAVE_READ                                  1
#define I2C_MASTER_TRANSMIT_IN_PROGRESS                                 0
#define I2C_MASTER_TRANSMIT_NOT_IN_PROGRESS                           1
/**
 * BF: Buffer Full Status bit
 * @In_Transmit_mode:
 *    1 = SSPBUF is full 
 *    0 = SSPBUF is empty
 * @In_Receive_mode:
 *    1 = SSPBUF is full (does not include the ACK and Stop bits)
 *    0 = SSPBUF is empty (does not include the ACK and Stop bits)
 */
#define I2C_BUFFER_EMPTY            0
#define I2C_BUFFER_FULL             1

/*---------------------------------------*/
/**
 *  SSPCON1: MSSP CONTROL REGISTER 1
 */
/*---------------------------------------*/
/* SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits */
#define I2C_SLAVE_MODE_10BIT_ADD_INTERRUPT_ENABLE     15
#define I2C_SLAVE_MODE_7BIT_ADD_INTERRUPT_ENABLE      14
#define I2C_SLAVE_MODE_10BIT_ADD                           7
#define I2C_SLAVE_MODE_7BIT_ADD                             6
#define I2C_MASTER_MODE_DEFINED_CLK                       8
#define I2C_MASTER_MODE_FRIMWARE_CONTROLLED            11

/*---------------------------------------*/
/**
 *  SSPCON2: MSSP CONTROL REGISTER 2
 */
/*---------------------------------------*/
/**
 * GCEN: General Call Enable bit (Slave mode only)
 * 1 = Enables interrupt when a general call address (0000h) is received in the SSPSR 
 * 0 = General call address disabled.
 */
#define I2C_GENERAL_CALL_DISABLE                            0
#define I2C_GENERAL_CALL_ENABLE                             1
/**
 * RCEN: Receive Enable bit (Master mode only)
 * 1 = Enables Receive mode for I2C 
 * 0 = Receive Idle
 */
#define I2C_MASTER_RECEIVER_MODE_DISABLE                   0
#define I2C_MASTER_RECEIVER_MODE_ENABLE                   1
/**
 * SEN: Start Condition Enable/Stretch Enable bit
 * 1 = Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. 
 * 0 = Start condition Idle
 */
#define I2C_START_CONDITION_INITIATE        1
#define I2C_START_CONDITION_IDLE              0
/**
 * ACKSTAT: Acknowledge Status bit (Master Transmit mode only)
 * 1 = Acknowledge was not received from slave 
 * 0 = Acknowledge was received from slave
 */
#define I2C_ACK_RECEIVED_FROM_SLAVE              0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE         1
/**
 * ACKDT: Acknowledge Data bit (Master Receive mode only)(2)
 *  1 = Not Acknowledge
 *  0 = Acknowledge 
 */
#define I2C_MASTER_SEND_ACK             0
#define I2C_MASTER_SEND_NACK            1

/*================================ section : Macro Functions ================================*/
/*---------------------------------------*/
/**
 * SSPSTAT: MSSP STATUS REGISTERSSPSTAT: MSSP STATUS REGISTER
 */
/*---------------------------------------*/
/*SMP: Slew Rate Control bit*/
#define I2C_SLEW_RATE_DISABLE_CFG()       (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_ENABLE_CFG()         (SSPSTATbits.SMP = 1)
/* CKE: SMBus Select bit */
#define I2C_SM_BUS_DISABLE_CFG()          (SSPSTATbits.CKE = 0)
#define I2C_SM_BUS_ENABLE_CFG()          (SSPSTATbits.CKE = 0)
/**
 * S: Start bit 
 * 1 = Indicates that a Start bit has been detected last
 * 0 = Start bit was not detected last
 */
#define I2C_START_BIT_INDICATE_CFG()        (SSPSTATbits.S)
/** 
 * P: Stop bit
 * 1 = Indicates that a Stop bit has been detected last
 * 0 = Stop bit was not detected last
 */
#define I2C_STOP_BIT_INDICATE_CFG()        (SSPSTATbits.P)
/**
 * BF: Buffer Full Status bit
 */
#define I2C_BUFFER_STATUS_CFG()              (SSPSTATbits.BF)


/*---------------------------------------*/
/**
 *  SSPCON1: MSSP CONTROL REGISTER 1
 */
/*---------------------------------------*/
/* SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits */
#define I2C_Master_Synchronous_Serial_Port_Mode_Select_CFG(_CONFIG)        (SSPCON1bits.SSPM = _CONFIG)
/* SSPEN: Master Synchronous Serial Port Enable bit */
#define I2C_MSSP_MODULE_DISABLE_CFG()                       (SSPCON1bits.SSPEN = 0)
#define I2C_MSSP_MODULE_ENABLE_CFG()                        (SSPCON1bits.SSPEN = 1)
/**
 * WCOL: Write Collision Detect bit
 * In Master Transmit mode:
 *   1 = A write to the SSPBUF register was attempted while the I2C conditions were not valid for a
 *       transmission to be started (must be cleared in software)
 *   0 = No collision
 * In Slave Transmit mode:
 *   1 = The SSPBUF register is written while it is still transmitting the previous word (must be cleared in
 *       software)
 *   0 = No collision 
 * In Receive mode (Master or Slave modes): This is a ?don?t care? bit. 
 */
#define I2C_SLAVE_NO_COLLISION_DETECTED()           (SSPCON1bits.WCOL = 0 )
/**
 * SSPOV: Receive Overflow Indicator bit 
 * In Receive mode:
 *   1 = A byte is received while the SSPBUF register is still holding the previous byte (must be cleared in
 *       software)
 *   0 = No overflow
 * In Transmit mode: This is a ?don?t care? bit in Transmit mode
 */
#define I2C_SLAVE_NO_OVERFLOW_DETECTED()            (SSPCON1bits.SSPOV = 0)
/**
 * CKP: SCK Release Control bit 
 * In Slave mode:
 *   1 = Releases clock 
 *   0 = Holds clock low (clock stretch), used to ensure data setup time
 * In Master mode: Unused in this mode.
 */
#define I2C_SLAVE_RELEASE_CLK()                         (SSPCON1bits.CKP = 1)
#define I2C_SLAVE_HOLD_CLK()                             (SSPCON1bits.CKP = 0)
/*---------------------------------------*/
/**
 *  SSPCON2: MSSP CONTROL REGISTER 2
 */
/*---------------------------------------*/
/* GCEN: General Call Enable bit (Slave mode only) */
#define I2C_GENERAL_CALL_DISABLE_CFG()                                           (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()                                             (SSPCON2bits.GCEN = 1)
/* RCEN: Receive Enable bit (Master mode only) */
#define I2C_MASTER_RECEIVER_CONTROL_DISABLE_CFG()                             (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVER_CONTROL_ENABLE_CFG()                              (SSPCON2bits.RCEN = 1)
/* SEN: Start Condition Enable/Stretch Enable bit */
#define I2C_START_CONDITION_INITIATE_CFG()                                      (SSPCON2bits.SEN = 1)
#define I2C_START_CONDITION_STATE_CFG()                                          (SSPCON2bits.SEN)
/* PEN: Stop Condition Enable/Stretch Enable bit */
#define I2C_STOP_CONDITION_INITIATE_CFG()                                       (SSPCON2bits.PEN = 1)
#define I2C_STOP_CONDITION_STATE_CFG()                                           (SSPCON2bits.PEN)
/* RSEN: Repeated Start Condition Enable bit (Master mode only) */
#define I2C_REPEATED_START_CONDITION_INITIATE_CFG()                         (SSPCON2bits.RSEN = 1)
#define I2C_REPEATED_START_CONDITION_STATE_CFG()                             (SSPCON2bits.RSEN)
/* ACKSTAT: Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_STATUS_CFG()                                                               (SSPCON2bits.ACKSTAT)
/**
 * ACKDT: Acknowledge Data bit (Master Receive mode only)(2)
 */
#define I2C_MASTER_SEND_ACK_CFG()            (SSPCON2bits.ACKDT = 0)
#define I2C_MASTER_SEND_NACK_CFG()           (SSPCON2bits.ACKDT = 1)
/* ACKEN: Acknowledge Sequence Enable bit (Master Receive mode only) */
#define I2C_MASTER_INITIATE_ACK_SEQUENCE_CFG()      (SSPCON2bits.ACKEN  = 1)

/*================================ section : Data type declaration ================================*/
typedef struct{
    uint8 i2c_mode_cfg ;   
    uint8 i2c_mode : 1 ;
    uint8 i2c_slave_address ;
    uint8 i2c_slew_rate : 1 ;
    uint8 i2c_SM_bus_control : 1 ;
    uint8 i2c_general_call : 1 ;
    uint8 i2c_master_reciever_mode : 1 ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priority ; 
    interrupt_priority_cfg mssp_i2c_bc_priority ; 
#endif
    uint8 reserved : 3 ;
}i2c_config_t;
typedef struct{
    i2c_config_t i2c_cfg ; 
    uint32 i2c_master_clock_freq ; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* I2C_Report_InterruptHandler)(void);
    void (* I2C_Report_Write_Collision)(void);
    void (* I2C_Report_Read_OverFlow)(void);
#endif
}mssp_i2c_t;
/*================================ section : functions declarations ================================*/
/**
 * @breif function to Initialize MSSP I2C mode
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Init(const mssp_i2c_t* i2c_obj);
/**
 * @breif function to De-Initialize MSSP I2C Mode
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t* i2c_obj);
/**
 * @breif function master send start condition to start communication 
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendStart(const mssp_i2c_t* i2c_obj);
/**
 * @breif function master send repeated start condition
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendRepeatedStart(const mssp_i2c_t* i2c_obj);
/**
 * @breif function master send repeated stop condition to stop communication 
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendStop(const mssp_i2c_t* i2c_obj);
/**
 * @breif function to Master write byte on the I2C Bus 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @param i2c_data the data need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t* i2c_obj , uint8 i2c_data, uint8 *i2c_ack);
/**
 * @breif function to write byte on the I2C Bus 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @param ack
 * @param i2c_data pointer to store the read data 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t* i2c_obj , uint8 ack , uint8* i2c_data);
#endif	/* MCAL_I2C_H */

