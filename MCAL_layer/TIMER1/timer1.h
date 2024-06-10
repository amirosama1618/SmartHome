/* 
 * @File:   timer1.h
 * @Author: Ameer
 * @module TIMER-1
 * @describtion The Timer1 module incorporates the following features:
 *              - Software selectable operation as a timer or counter in 16-bit Resolution 
 *              - counter mode has two configurations "synchronous" and "Asynchronous"
 *              - Dedicated 8-bit, software programmable pre-scaler
 *              - Selectable clock source (internal or external or Timer1 Oscillator )
 *                  @note Timer1 Oscillator provide lower clock source 
 *                        to get the micro-controller into low-power mode  
 *              - Edge select for external clock is only Rising edge
 *              - Interrupt-on-overflow
 * @Created on March 5, 2024, 3:57 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

/*================================ section : includes ================================*/
#include "pic18f4620.h"
#include "../../MCAL_layer/compiler.h"
#include "../../MCAL_layer/device_config.h"
#include "../../MCAL_layer/std_libraries.h"
#include "../../MCAL_layer/mcal_std_types.h"

#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/*================================ section : Macro definitions ================================*/

/*================================ section : Macro functions definitions ================================*/
/* T1CON: TIMER1 CONTROL REGISTER
 *@note Default value  = 0x00
 */

/**
 * TMR1ON: Timer1 On bit
 * 1 = Enables Timer1 
 * 0 = Stops Timer1
 */
#define TIMER1_ENABLE()         (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()         (T1CONbits.TMR1ON = 0)
/**
 * TMR1CS: Timer1 Clock Source Select bit
 * 1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge) 
 * 0 = Internal clock (FOSC/4)
 */
#define TIMER1_EXTERNAL_CLOCK_SOURCE()      (T1CONbits.TMR1CS = 1)
#define TIMER1_INTERNAL_CLOCK_SOURCE()      (T1CONbits.TMR1CS = 0)
/**
 * T1SYNC: Timer1 External Clock Input Synchronization Select bit
 * When TMR1CS = 1: 1 = Do not synchronize external clock input 
 *                  0 = Synchronize external clock input
 * When TMR1CS = 0: This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
 */
#define TIMER1_SYNCHRONOUS_EXTERNAL_CLOCK_INPUT()       (T1CONbits.T1SYNC  = 0)
#define TIMER1_ASYNCHRONOUS_EXTERNAL_CLOCK_INPUT()       (T1CONbits.T1SYNC  = 1)
/**
 * T1OSCEN: Timer1 Oscillator Enable bit
 * 1 = Timer1 oscillator is enabled 
 * 0 = Timer1 oscillator is shut off 
 * The oscillator inverter and feedback resistor are turned off to eliminate power drain.
 */
#define TIMER1_OSCILLATOR_ENABLE()          (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE()          (T1CONbits.T1OSCEN = 0)
/**
 * (T1CKPS1:T1CKPS0) : Timer1 Input Clock Pre-scaler Select bits
 */
#define TIMER1_PRESCALER_SELECT(_CONFIG)        (T1CONbits.T1CKPS = _CONFIG)
/**
 * T1RUN: Timer1 System Clock Status bit
 * @note Read only bit
 * 1 = Device clock is derived from Timer1 oscillator
 * 0 = Device clock is derived from another source
 */
#define TIMER1_SYSTEM_CLOCK_STATUS()        (T1CONbits.T1RUN)
/**
 * RD16: 16-Bit Read/Write Mode Enable bit
 * 1 = Enables register read/write of TImer1 in one 16-bit operation
 * 0 = Enables register read/write of Timer1 in two 8-bit operations
 */
#define TIMER1_READ_WRITE_16BIT_MODE()     (T1CONbits.RD16 = 1)
#define TIMER1_READ_WRITE_8BIT_MODE()     (T1CONbits.RD16 = 0)
/*================================ section : Data type declaration ================================*/
typedef enum {
    TIMER1_PRESCALER_DIV_1 = 0 ,
    TIMER1_PRESCALER_DIV_2,
    TIMER1_PRESCALER_DIV_4,
    TIMER1_PRESCALER_DIV_8
} timer1_prescaler_value_t;

typedef enum{
    TIMER1_TIMER_MODE =0 , 
    TIMER1_COUNTER_MODE
}timer1_mode_select_t;

typedef enum{
    TIMER1_COUNTER_SYNC = 0 ,
    TIMER1_COUNTER_ASYNC
}timer1_counter_mode_select_t;

typedef enum{
    TIMER1_OSC_ENABLE = 0 ,
    TIMER1_OSC_DISABLE
}timer1_oscillator_cfg_t;

typedef enum{
    TIMER1_8BIT_OPERATION = 0 ,
    TIMER1_16BIT_OPERATION       
}timer1_read_write_mode_select_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*Timer1_Interrupt)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg timer1_interrupt_priority ; 
#endif
#endif
    timer1_mode_select_t timer1_mode ; 
    timer1_counter_mode_select_t timer1_counter_mode ;
    timer1_oscillator_cfg_t timer1_oscillator_cfg;
    timer1_prescaler_value_t timer1_prescaler_value ; 
    timer1_read_write_mode_select_t timer1_operation_mode ; 
    uint16 preload_value ; 
}timer1_config_t ; 
/*================================ section : functions declarations ================================*/
/**
 * @breif function to initialize Timer1 Module 
 * @preconditions None
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Init(const timer1_config_t *timer1);
/**
 * @breif function to De-Initialize Timer1
 * @preconditions None
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_DeInit(const timer1_config_t *timer1);
/**
 * @breif function to read the value of Timer1 register 
 * @preconditions Timer1_Init() must called before 
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Read_value(const timer1_config_t *timer1 , uint16 *value);
/**
 * @breif function to read the value of Timer1 register 
 * @preconditions Timer1_Init() must called before 
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Write_value(const timer1_config_t *timer1 , uint16 value);
#endif	/* TIMER1_H */

