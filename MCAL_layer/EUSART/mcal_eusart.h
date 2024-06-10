/* 
 * File:   mcal_eusart.h
 * Author: Ameer
 * @breif The Enhanced Universal Synchronous Asynchronous Receiver Transmitter 
 *        (EUSART) module is one of the two serial I/O modules.
 *        Generically, the USART is also known as a Serial Communications Interface or SCI.
 * @configurations (1) The EUSART can be configured as a full-duplex asynchronous system 
 *                 (2)  It can also be configured as a half-duplex synchronous system 
 * Created on March 16, 2024, 5:03 PM
 */

#ifndef MCAL_EUSART_H
#define	MCAL_EUSART_H

/*========================= section : includes ==================================*/
#include "pic18f4620.h"
#include "../std_libraries.h"
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_eusart_cfg.h"
/*========================= section : Macro definitions =========================*/
/* select EUSART mode */
#define EUSART_ASYNCRONOUS_MODE     0
#define EUSART_SYNCRONOUS_MODE      1
/* High Baud Rate Select */
#define EUSART_ASYNCRONOUS_LOW_SPEED      0
#define EUSART_ASYNCRONOUS_HIGH_SPEED     1
/* Baud Rate Generator Register Size Select */
#define EUSART_8BIT_BAUDRATE_GEN        0
#define EUSART_16BIT_BAUDRATE_GEN        1

/* Transmit Enable */
#define EUSART_ASYNCRONOUS_TX_DISABLE   0
#define EUSART_ASYNCRONOUS_TX_ENABLE     1
/* 9-Bit Transmit mode select */
#define EUSART_ASYNCRONOUS_9BIT_TX_DISABLE   0
#define EUSART_ASYNCRONOUS_9BIT_TX_ENABLE    1
/* Interrupt Transmitter mode select */
#define EUSART_ASYNCRONOUS_INTERRUPT_TX_DISABLE   0
#define EUSART_ASYNCRONOUS_INTERRUPT_TX_ENABLE    1

/* Receiver Enable */
#define EUSART_ASYNCRONOUS_RX_DISABLE   0
#define EUSART_ASYNCRONOUS_RX_ENABLE     1
/* 9-Bit Receiver mode select */
#define EUSART_ASYNCRONOUS_9BIT_RX_DISABLE   0
#define EUSART_ASYNCRONOUS_9BIT_RX_ENABLE    1
/* Interrupt Receiver mode select */
#define EUSART_ASYNCRONOUS_INTERRUPT_RX_DISABLE   0
#define EUSART_ASYNCRONOUS_INTERRUPT_RX_ENABLE    1

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_CLEARED       0
#define EUSART_FRAMING_ERROR_DETECTED       1
/* EUSART Over Run Error */
#define EUSART_OVERRUN_ERROR_CLEARED       0
#define EUSART_OVERRUN_ERROR_DETECTED       1

/*========================= section : Macro functions definitions ===============*/
#define EUSART_ENABLE()       (RCSTAbits.SPEN = 1)
#define EUSART_DISABLE()      (RCSTAbits.SPEN = 0)

#define EUSART_ASYNC_TX_ENABLE()        (TXSTAbits.TXEN = 1)
#define EUSART_ASYNC_TX_DISABLE()       (TXSTAbits.TXEN = 0)

#define EUSART_ASYNC_TX_9BIT_SELECT()     (TXSTAbits.TX9 = 1)
#define EUSART_ASYNC_TX_8BIT_SELECT()     (TXSTAbits.TX9 = 0)

#define EUSART_ASYNC_RX_ENABLE()        (RCSTAbits.CREN = 1)
#define EUSART_ASYNC_RX_DISABLE()       (RCSTAbits.CREN = 0)

#define EUSART_ASYNC_RX_9BIT_SELECT()     (RCSTAbits.RX9 = 1)
#define EUSART_ASYNC_RX_8BIT_SELECT()     (RCSTAbits.RX9 = 0)
/*========================= section : Data type declaration =====================*/
typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED = 0 ,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED ,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED ,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT       
}eusart_baudrate_gen_t ; 

typedef struct{
    uint8 eusart_tx_reserved : 5  ; 
    uint8 eusart_tx_enable :1 ;
    uint8 eusart_tx_interrupt_enable :1 ;
    uint8 eusart_tx_9bit_enable :1 ;
}eusart_tx_cfg_t ; 

typedef struct{
    uint8 eusart_rx_reserved : 5  ; 
    uint8 eusart_rx_enable :1 ;
    uint8 eusart_rx_interrupt_enable :1 ;
    uint8 eusart_rx_9bit_enable :1 ;
}eusart_rx_cfg_t ;

typedef union{
    struct{
        uint8 eusart_rx_reserved : 6  ; 
        uint8 eusart_ferr : 1 ; 
        uint8 eusart_oerr : 1 ; 
    };
    uint8 eusart_error_status ; 
}eusart_error_status_t ; 

typedef struct{
    uint32 baudrate ;                                           
    eusart_baudrate_gen_t baudrate_gen_mode ;          /* @ref eusart_baudrate_gen_t */
    eusart_tx_cfg_t tx_cfg ;                                 /*@ref eusart_tx_cfg_t */
    eusart_rx_cfg_t rx_cfg  ;                                /*@ref eusart_rx_cfg_t */
    eusart_error_status_t error_status;                 /*@ref eusart_error_status_t */
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*EUSART_TXDefaultInterruptHandler)(void) ; 
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg tx_priority ; 
    #endif
#endif
#if EUSART_ASYNC_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*EUSART_RXDefaultInterruptHandler)(void) ;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg rx_priority ; 
    #endif
#endif
    void(*EUSART_FramingErrorHandler)(void) ; 
    void(*EUSART_OverRunErrorHandler)(void) ; 
}usart_async_t ; 
/*========================= section : functions declarations ====================*/
/**
 * @breif function to Initialize the EUSART modeule 
 * @param _eusart pointer to EUSART object configurations 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_Init(const usart_async_t * _eusart);
/**
 * @breif function to De-Initialize the EUSART Module
 * @param _eusart  pointer to EUSART object configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_DeInit(const usart_async_t * _eusart);
/**
 * @breif function to Read byte from the USART Module 
 * @param _eusart pointer to EUSART object configurations
 * @param _data pointer to return the Read data in 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 * _data);
/**
 * 
 * @param _data
 * @return 
 */
STD_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);
STD_ReturnType EUSART_ASYNC_ReadStringBlocking(uint8 *data , uint16 str_len);
/**
 * @breif function to Restart EUSART RX 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_RX_Restart(void);
/**
 * @breif function to Write byte to the USART Module
 * @param _eusart pointer to EUSART object configurations
 * @param data the data need to Write 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_WrireByteBlocking(uint8 data);
/**
 * @breif function to write( transmit ) string 
 * @param _eusartpointer to EUSART object configurations
 * @param data string need to be written 
 * @param str_len string length 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_WrireStringBlocking(uint8 *data , uint16 str_len);
#endif	/* MCAL_EUSART_H */

