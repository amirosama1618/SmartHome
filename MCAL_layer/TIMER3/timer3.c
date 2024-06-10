/* 
 * File:   timer3.c
 * Author: Ameer
 *
 * Created on March 7, 2024, 3:18 PM
 */

/*================================ section : includes ================================*/
#include "timer3.h"
/*================================ section : Global Variables ==========================*/
uint16 g_timer3_preload_value = ZERO_INIT ; 
/*================================ section : Timer0 Interrupt Handler ==========================*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static InterruptHandler Timer3_InterruptHandler = NULL ; 
#endif
/*================================ section : Static Helper Function declarations ==========================*/
static inline void TIMER3_MODE_CONFIGURE(const timer3_config_t *timer3);
static inline void TIMER3_RW_MODE_CONFIGURE(const timer3_config_t *timer3);
/*================================ section : functions Implementation ================================*/
/**
 * @breif function to initialize Timer3 Module 
 * @preconditions None
 * @param timer3 pointer to Timer3 configuration data type @ref timer3_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Init(const timer3_config_t *timer3){
    STD_ReturnType error_state =  E_NOT_OK  ;
    if(NULL == timer3){
        error_state = E_NOT_OK  ;
    }
    else{
        /* Disable Timer3 */
        TIMER3_ENABLE();
        /* Configure Timer3 mode : Timer mode or Counter Mode */
        TIMER3_MODE_CONFIGURE(timer3);
        /* Configure the Pre-scaler */
        TIMER3_PRESCALER_SELECT(timer3->timer3_prescaler_value);
        /* Configure R/W mode 8 or 16 Bit */
        TIMER3_RW_MODE_CONFIGURE(timer3);
        /* configure the PreLoad Value */
        TMR3H = ((timer3->preload_value) >> 8);
        TMR3L = (uint8)(timer3->preload_value);
        g_timer3_preload_value = timer3->preload_value ; 
        /* Check if Interrupt Feature is Enabled */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
        TIMER3_InterruptFlagClear();
        /* Configure The Interrupt Call back Function */
        Timer3_InterruptHandler = timer3->Timer3_Interrupt ; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer3->timer3_interrupt_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer3->timer3_interrupt_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        else{
            error_state = E_NOT_OK ;
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PrephralInterruptEnable();
#endif
        
        TIMER3_InterruptEnable();
#endif
        /* Enable Timer3*/
        TIMER3_ENABLE();
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to De-Initialize Timer3
 * @preconditions None
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_DeInit(const timer3_config_t *timer3){
    STD_ReturnType error_state =  E_NOT_OK  ;
    if(NULL == timer3){
        error_state = E_NOT_OK  ;
    }
    else{
        TIMER3_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif
        error_state = E_OK  ;
    }
    
    return error_state ; 
}
/**
 * @breif function to read the value of timer3 register 
 * @preconditions Timer3_Init() must called before 
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Read_value(const timer3_config_t *timer3 , uint16 *value){
    STD_ReturnType error_state =  E_NOT_OK  ;
    uint8 l_tmr3l = ZERO_INIT , l_tmr3h = ZERO_INIT ; 
    if((NULL == timer3) || (NULL == value)){
        error_state = E_NOT_OK  ;
    }
    else{
        l_tmr3l = TMR3L  ;
        l_tmr3h = TMR3H ; 
        *value = (uint16)((l_tmr3h << 8)+l_tmr3l);
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to read the value of timer3 register 
 * @preconditions Timer3_Init() must called before 
 * @param timer3 pointer to timer3 configuration data type @ref timer3_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer3_Write_value(const timer3_config_t *timer3 , uint16 value){
    STD_ReturnType error_state =  E_NOT_OK  ;
    if(NULL == timer3){
        error_state = E_NOT_OK  ;
    }
    else{
        TMR3H = ((value) >> 8);
        TMR3L = (uint8)(value);
        error_state = E_OK  ;
    }
    
    return error_state ; 
}
/*================================ section : Static Helper Function Implementation ==========================*/
static inline void TIMER3_MODE_CONFIGURE(const timer3_config_t *timer3){
    if(TIMER3_TIMER_MODE == timer3->timer3_mode){
        TIMER3_TIMER_MODE_CONFIG();
    }
    else if(TIMER3_COUNTER_MODE == timer3->timer3_mode){
        TIMER3_COUNTER_MODE_CONFIG();
        if(TIMER3_COUNTER_SYNC == timer3->timer3_counter_mode){
            TIMER3_SYNCHRONOUS_EXTERNAL_CLOCK_INPUT();
        }
        else if(TIMER3_COUNTER_ASYNC == timer3->timer3_counter_mode){
            TIMER3_ASYNCHRONOUS_EXTERNAL_CLOCK_INPUT();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}
static inline void TIMER3_RW_MODE_CONFIGURE(const timer3_config_t *timer3){
    if(TIMER3_8BIT_OPERATION == timer3->timer3_operation_mode){
        TIMER3_READ_WRITE_8BIT_MODE();
    }
    else if(TIMER3_16BIT_OPERATION == timer3->timer3_operation_mode){
        TIMER3_READ_WRITE_16BIT_MODE();
    }
    else{ /* nothing */ }
}
void TIMER3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR1H = (g_timer3_preload_value ) >> 8 ;
    TMR1L= (uint8)(g_timer3_preload_value ) ;
    
    if(Timer3_InterruptHandler){
        Timer3_InterruptHandler();
    }
}