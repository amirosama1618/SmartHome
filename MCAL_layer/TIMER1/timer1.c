/* 
 * File:   timer1.h
 * Author: Ameer
 *
 * Created on March 5, 2024, 3:57 PM
 */
/*================================ section : includes ================================*/
#include "timer1.h"
static InterruptHandler TIMER1_InterruptHandler = NULL ;
static uint16 timer1_preload_value = ZERO_INIT ; 
/*================================ section : static Helper functions declarations ====================*/
static STD_ReturnType timer1_oscillator_configure(const timer1_config_t *timer1);
static STD_ReturnType timer1_mode_configure(const timer1_config_t *timer1);
static STD_ReturnType timer1_prescaler_configure(const timer1_config_t *timer1);
static STD_ReturnType timer1_operation_mode_configure(const timer1_config_t *timer1);
static STD_ReturnType timer1_preload_value_configure(const timer1_config_t *timer1);
static STD_ReturnType timer1_interrupt_configure(const timer1_config_t *timer1);
/*================================ section : functions Implementation ================================*/
/**
 * @breif function to initialize Timer1 Module 
 * @preconditions None
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Init(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer1){
        error_state = E_NOT_OK ; 
    }
    else{
        /* disable Timer1*/
        TIMER1_DISABLE();
        /* Timer1 oscillator configure*/
        error_state =timer1_oscillator_configure(timer1);
        /* select Timer1 mode counter or Timer */
        error_state =timer1_mode_configure(timer1);
        /* configure pre-scaler value */
        error_state =timer1_prescaler_configure(timer1);
        /* configure read and write mode 8 or 16 bit */
        error_state =timer1_operation_mode_configure(timer1);
        /* configure the pre-load value */
        error_state =timer1_preload_value_configure(timer1);
        /* enable Timer1 interrupt on overflow if needed */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        error_state =timer1_interrupt_configure(timer1);
#endif
        /* enable Timer1 */
        TIMER1_ENABLE();
    }
    return error_state  ;
}
/**
 * @breif function to De-Initialize Timer1
 * @preconditions None
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_DeInit(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer1){
        error_state = E_NOT_OK ; 
    }
    else{
        TIMER1_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
        TIMER1_InterruptHandler = NULL ;
#endif
        error_state = E_OK ; 
    }
    return error_state  ;
}
/**
 * @breif function to read the value of Timer1 register 
 * @preconditions Timer1_Init() must called before 
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Read_value(const timer1_config_t *timer1 , uint16 *value){
    STD_ReturnType error_state = E_NOT_OK ; 
    uint8 l_tmr1l = ZERO_INIT , l_tmr1h = ZERO_INIT ;
    if((NULL == timer1)||(NULL == value)){
        error_state = E_NOT_OK ; 
    }
    else{
        l_tmr1l = TMR1L ; 
        l_tmr1h = TMR1H ; 
        *value = (uint16)((l_tmr1h << 8 )+l_tmr1l);
        error_state = E_OK ; 
    }
    
    return error_state  ;
}
/**
 * @breif function to read the value of Timer1 register 
 * @preconditions Timer1_Init() must called before 
 * @param timer1_obj pointer to Timer1 configuration data type @ref timer1_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer1_Write_value(const timer1_config_t *timer1 , uint16 value){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer1){
        error_state = E_NOT_OK ; 
    }
    else{
        TMR1H = (value ) >> 8 ;
        TMR1L= (uint8)(value ) ;
        error_state = E_OK ; 
    }
    
    return error_state  ;
}
/*================================ section : static helper functions Implementation ================================*/
static STD_ReturnType timer1_oscillator_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(TIMER1_OSC_ENABLE ==  timer1->timer1_oscillator_cfg){
        TIMER1_OSCILLATOR_ENABLE();
    }
    else if(TIMER1_OSC_DISABLE ==  timer1->timer1_oscillator_cfg){
        TIMER1_OSCILLATOR_DISABLE();
    }
    else{
        /* nothing */
        error_state = E_NOT_OK ;  
    }
    return error_state  ;
}
static STD_ReturnType timer1_mode_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(TIMER1_TIMER_MODE == timer1->timer1_mode){
        TIMER1_INTERNAL_CLOCK_SOURCE();
    }
    else if(TIMER1_COUNTER_MODE){
        TIMER1_EXTERNAL_CLOCK_SOURCE();
        if(TIMER1_COUNTER_SYNC == timer1->timer1_counter_mode){
            TIMER1_SYNCHRONOUS_EXTERNAL_CLOCK_INPUT();
        }
        else if(TIMER1_COUNTER_ASYNC == timer1->timer1_counter_mode){
            TIMER1_ASYNCHRONOUS_EXTERNAL_CLOCK_INPUT();
        }
        else{
            /* nothing */
            error_state = E_NOT_OK ;  
        }
    }
    else{
        /* nothing */
        error_state = E_NOT_OK ;  
    }
    return error_state  ;
}
static STD_ReturnType timer1_prescaler_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    switch(timer1->timer1_prescaler_value){
        case TIMER1_PRESCALER_DIV_1 : 
            TIMER1_PRESCALER_SELECT(TIMER1_PRESCALER_DIV_1);
            error_state = E_OK ; 
            break ; 
        case TIMER1_PRESCALER_DIV_2 : 
            TIMER1_PRESCALER_SELECT(TIMER1_PRESCALER_DIV_2);
            error_state = E_OK ; 
            break ; 
        case TIMER1_PRESCALER_DIV_4 : 
            TIMER1_PRESCALER_SELECT(TIMER1_PRESCALER_DIV_4);
            error_state = E_OK ; 
            break ; 
        case TIMER1_PRESCALER_DIV_8 : 
            TIMER1_PRESCALER_SELECT(TIMER1_PRESCALER_DIV_8);
            error_state = E_OK ; 
            break ; 
        default : error_state = E_NOT_OK ; 
    }
    return error_state  ;
}
static STD_ReturnType timer1_operation_mode_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(TIMER1_8BIT_OPERATION == timer1->timer1_operation_mode){
        TIMER1_READ_WRITE_8BIT_MODE();
    }
    else if(TIMER1_16BIT_OPERATION == timer1->timer1_operation_mode){
        TIMER1_READ_WRITE_16BIT_MODE();
    }
    else{ 
        /* nothing */
        error_state = E_NOT_OK ;
    }
    return error_state  ;
}
static STD_ReturnType timer1_preload_value_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
        TMR1H = (timer1->preload_value) >> 8 ;
        TMR1L= (uint8)(timer1->preload_value) ;
        timer1_preload_value = timer1->preload_value ; 
        error_state = E_OK ;
    return error_state  ;
}
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType timer1_interrupt_configure(const timer1_config_t *timer1){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer1->Timer1_Interrupt){
        error_state = E_NOT_OK ; 
    }
    else{
        TIMER1_InterruptDisable();
        TIMER1_InterruptFlagClear();
        TIMER1_InterruptHandler = timer1->Timer1_Interrupt ; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == timer1->timer1_interrupt_priority){
            TIMER1_HighPrioritySet();
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptHighEnable();
            error_state = E_OK  ;
        }
        else if(INTERRUPT_LOW_PRIORITY == timer1->timer1_interrupt_priority){
            TIMER1_LowPrioritySet();
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            error_state = E_OK  ;
        }
        else{ 
            error_state = E_NOT_OK  ;
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PrephralInterruptEnable();
        error_state = E_OK  ;
#endif
        TIMER1_InterruptEnable();
    }
    return error_state  ;
}
void TIMER1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H = (timer1_preload_value ) >> 8 ;
    TMR1L= (uint8)(timer1_preload_value ) ;
    if(TIMER1_InterruptHandler){
        TIMER1_InterruptHandler();
    }
}
#endif