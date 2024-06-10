/* 
 * File:   timer0.h
 * Author: Amir Osama Amir
 * Created on March 3, 2024, 8:31 PM
 * @module TIMER-0
 * @describtion The Timer0 module incorporates the following features:
 *              ? Software selectable operation as a timer or counter in both 8-bit or 16-bit modes
 *              ? Readable and writable registers
 *              ? Dedicated 8-bit, software programmable pre-scaler
 *              ? Selectable clock source (internal or external)
 *              ? Edge select for external clock
 *              ? Interrupt-on-overflow
 */

#ifndef TIMER0_H
#define	TIMER0_H

/*================================ section : includes ================================*/
#include "pic18f4620.h"
#include "../../MCAL_layer/compiler.h"
#include "../../MCAL_layer/device_config.h"
#include "../../MCAL_layer/std_libraries.h"
#include "../../MCAL_layer/mcal_std_types.h"

#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "timer0_cfg.h"

/*================================ section : Macro definitions ================================*/
#define TIMER0_PRESCALER_CFG_ENABLE                 1
#define TIMER0_PRESCALER_CFG_DISABLE                 0
/*================================ section : Macro functions definitions ================================*/
/**
 * @breif   T0CON: TIMER0 CONTROL REGISTER
 * @note    controls all aspects of the module?s operation, including the 
 *          pre-scale selection. It is both readable and writable
 */

/**
 * TMR0ON: Timer0 On/Off Control bit  
 * 1 = Enables Timer0 
 * 0 = Stops Timer0
 */
#define TIMER0_ENABLE()             (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()            (T0CONbits.TMR0ON = 0)
/**
 *  T08BIT: Timer0 8-Bit/16-Bit Control bit
 *  1 = Timer0 is configured as an 8-bit timer/counter 
 *  0 = Timer0 is configured as a 16-bit timer/counter
 */
#define TIMER0_8BitConfig()         (T0CONbits.T08BIT = 1)
#define TIMER0_16BitConfig()        (T0CONbits.T08BIT = 0)
/**
 * T0CS: Timer0 Clock Source Select bit 
 * 1 = Transition on T0CKI pin  == "Counter Mode"
 * 0 = Internal instruction cycle clock (CLKO) == "Timer Mode"
 */
#define TIMER0_ExternalClockSelect()        (T0CONbits.T0CS = 1)
#define TIMER0_InternalClockSelect()        (T0CONbits.T0CS = 0)
/**
 * T0SE: Timer0 Source Edge Select bit
 * 1 = Increment on high-to-low transition on T0CKI pin 
 * 0 = Increment on low-to-high transition on T0CKI pin 
 */
#define TIMER0_FallingEdgeSelect()           (T0CONbits.T0SE = 1)
#define TIMER0_RaisingEdgeSelect()           (T0CONbits.T0SE = 0)
/**
 * PSA: Timer0 Pre-scaler Assignment bit 
 * 1 = TImer0 pre-scaler is not assigned. Timer0 clock input bypasses pre-scaler. 
 * 0 = Timer0 pre-scaler is assigned. Timer0 clock input comes from pre-scaler output.
 */
#define TIMER0_PrescalerDisable()           (T0CONbits.PSA = 1)
#define TIMER0_PrescalerEnable()            (T0CONbits.PSA = 0)
/**
 * T0PS2:T0PS0: Timer0 Pre-scaler Select bits
 * @ref timer_prescaler_select_t
 */
#define TIMER0_PrescalerValueSelect(_CONFIG)            (T0CONbits.T0PS = _CONFIG)
/*================================ section : Data type declaration ================================*/
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 =0 ,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
} timer_prescaler_value_select_t ;

typedef enum{
    TIMER0_16BIT_RESOLUTION = 0 ,
    TIMER0_8BIT_RESOLUTION
}timer0_resolution_select_t;

typedef enum{
    TIMER0_TIMER_MODE =0 , 
    TIMER0_COUNTER_MODE
}timer0_mode_select_t;

typedef enum{
    TIMER0_COUNTER_RAISING_EDGE = 0 ,
    TIMER0_COUNTER_FALLING_EDGE        
}timer0_source_edge_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*Timer0Interrupt)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg timer0_priority ; 
#endif
#endif
    timer0_mode_select_t timer0_mode ;                                      /* @ref timer0_mode_select_t */
    timer0_source_edge_select_t timer0_source_edge ;                   /* @ref timer0_source_edge_select_t */
    timer0_resolution_select_t timer0_resolution ;                      /* @ref timer0_resolution_select_t */
    uint8 timer0_prescaler_cfg ;                                               /* "TIMER0_PRESCALER_CFG_ENABLE" or "TIMER0_PRESCALER_CFG_ENABLE" */
    timer_prescaler_value_select_t timer0_prescaler_value ;          /* @ref timer_prescaler_value_select_t */
    uint16 timer0_preload_value ; 
} timer0_config_t;
/*================================ section : functions declarations ================================*/
/**
 * @breif function to initialize Timer0 Module 
 * @preconditions None
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Init(const timer0_config_t *timer0_obj);
/**
 * @breif function to De-Initialize Timer0
 * @preconditions None
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_DeInit(const timer0_config_t *timer0_obj);
/**
 * @breif function to read the value of Timer0 register 
 * @preconditions Timer0_Init() must called before 
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Read_Value(const timer0_config_t *timer0_obj, uint16 *read_value);
/**
 * @breif function to read the value of Timer0 register 
 * @preconditions Timer0_Init() must called before 
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Write_Value(const timer0_config_t *timer0_obj, uint16  _value);

#endif	/* TIMER0_H */

