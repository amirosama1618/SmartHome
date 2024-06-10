/* 
 * File:   mcal_layer_init.h
 * Author: Ameer
 *
 * Created on May 22, 2024, 6:01 PM
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H

#include "EUSART/mcal_eusart.h"
#include "ADC/mcal_adc.h"
#include "TIMER0/timer0.h"
void EUSART_RXDefaultInterruptHandler(void);
void TIMER0_InterruptHandler(void) ;


usart_async_t master_uart = {
    .baudrate = 9600,
    .baudrate_gen_mode = BAUDRATE_ASYNC_8BIT_LOW_SPEED ,
    
    .tx_cfg.eusart_tx_enable = EUSART_ASYNCRONOUS_TX_ENABLE,
    .tx_cfg.eusart_tx_interrupt_enable = EUSART_ASYNCRONOUS_INTERRUPT_TX_ENABLE,
    .tx_cfg.eusart_tx_9bit_enable = EUSART_ASYNCRONOUS_9BIT_TX_DISABLE , 
    
    .rx_cfg.eusart_rx_enable = EUSART_ASYNCRONOUS_RX_ENABLE,
    .rx_cfg.eusart_rx_interrupt_enable = EUSART_ASYNCRONOUS_INTERRUPT_RX_ENABLE,
    .rx_cfg.eusart_rx_9bit_enable = EUSART_ASYNCRONOUS_9BIT_RX_DISABLE ,
    
    .EUSART_TXDefaultInterruptHandler = NULL,
    .EUSART_RXDefaultInterruptHandler = EUSART_RXDefaultInterruptHandler ,
    .EUSART_OverRunErrorHandler = NULL , 
    .EUSART_FramingErrorHandler = NULL 
}; 

timer0_config_t timer0_obj = {
.Timer0Interrupt = TIMER0_InterruptHandler , 
.timer0_mode = TIMER0_TIMER_MODE , 
.timer0_prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
.timer0_preload_value = 3036 , 
.timer0_resolution = TIMER0_16BIT_RESOLUTION ,
.timer0_prescaler_cfg = TIMER0_PRESCALER_CFG_ENABLE
};


void mcal_layer_initialize(void) ;

#endif	/* MCAL_LAYER_INIT_H */

