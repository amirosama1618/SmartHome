/* 
 * File:   timer3.h
 * Author: Ameer
 *
 * Created on March 7, 2024, 3:18 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H
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
/**
 *  T3CON: TIMER3 CONTROL REGISTER
 *@note Default value  = 0x00
 */

/**
 * TMR3ON: Timer3 On bit
 * 1 = Enables Timer3 
 * 0 = Stops Timer3
 */
#define TIMER3_ENABLE()         (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()         (T3CONbits.TMR3ON = 0)
/**
 * TMR3CS: Timer1 Clock Source Select bit
 * 1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge after the first falling edge) 
 * 0 = Internal clock (FOSC/4)
 */
#define TIMER3_COUNTER_MODE_CONFIG()      (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_CONFIG()         (T3CONbits.TMR3CS = 0)
/**
 * T1SYNC: Timer3 External Clock Input Synchronization Select bit
 * When TMR3CS = 1: 1 = Do not synchronize external clock input 
 *                  0 = Synchronize external clock input
 * When TMR3CS = 0: This bit is ignored. Timer3 uses the internal clock when TMR3CS = 0.
 */
#define TIMER3_SYNCHRONOUS_EXTERNAL_CLOCK_INPUT()       (T3CONbits.T3SYNC  = 0)
#define TIMER3_ASYNCHRONOUS_EXTERNAL_CLOCK_INPUT()       (T3CONbits.T3SYNC  = 1)
/**
 * T3CKPS1:T3CKPS0: Timer3 Input Clock Prescale Select bits
 */
#define TIMER3_PRESCALER_SELECT(_CONFIG)        (T3CONbits.T3CKPS = _CONFIG)
/**
 * RD16: 16-Bit Read/Write Mode Enable bit
 * 1 = Enables register read/write of TImer3 in one 16-bit operation
 * 0 = Enables register read/write of Timer3 in two 8-bit operations
 */
#define TIMER3_READ_WRITE_16BIT_MODE()     (T3CONbits.RD16 = 1)
#define TIMER3_READ_WRITE_8BIT_MODE()       (T3CONbits.RD16 = 0)
/*================================ section : Data type declaration ================================*/
typedef enum {
    TIMER3_PRESCALER_DIV_1 = 0 ,
    TIMER3_PRESCALER_DIV_2,
    TIMER3_PRESCALER_DIV_4,
    TIMER3_PRESCALER_DIV_8
} timer3_prescaler_value_t;

typedef enum{
    TIMER3_TIMER_MODE =0 , 
    TIMER3_COUNTER_MODE
}timer3_mode_select_t;

typedef enum{
    TIMER3_COUNTER_SYNC = 0 ,
    TIMER3_COUNTER_ASYNC
}timer3_counter_mode_select_t;

typedef enum{
    TIMER3_8BIT_OPERATION = 0 ,
    TIMER3_16BIT_OPERATION       
}timer3_read_write_mode_select_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*Timer3_Interrupt)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg timer3_interrupt_priority ; 
#endif
#endif
    timer3_mode_select_t timer3_mode ; 
    timer3_counter_mode_select_t timer3_counter_mode ;
    timer3_prescaler_value_t timer3_prescaler_value ; 
    timer3_read_write_mode_select_t timer3_operation_mode ; 
    uint16 preload_value ; 
}timer3_config_t ; 
/*================================ section : functions declarations ================================*/
/**
 * @breif function to initialize Timer3 Module 
 * @preconditions None
 * @param timer3 pointer to Timer3 configuration data type @ref timer3_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Init(const timer3_config_t *timer3);
/**
 * @breif function to De-Initialize Timer3
 * @preconditions None
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_DeInit(const timer3_config_t *timer3);
/**
 * @breif function to read the value of timer3 register 
 * @preconditions Timer3_Init() must called before 
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Read_value(const timer3_config_t *timer3 , uint16 *value);
/**
 * @breif function to read the value of timer3 register 
 * @preconditions Timer3_Init() must called before 
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Write_value(const timer3_config_t *timer3 , uint16 value);
#endif	/* TIMER3_H */

