/* 
 * File:   timer2.c
 * Author: Ameer
 *
 * Created on March 7, 2024, 2:48 AM
 */
#include "timer2.h"
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
InterruptHandler TIMER2_InterruptHandler = NULL ; 
#endif
static uint8 timer2_preload = ZERO_INIT ; 
/**
 * @breif function to initialize Timer2 Module 
 * @preconditions None
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Init(const timer2_config_t *timer2){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer2){
        error_state = E_NOT_OK  ;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_PRESCALER_SELECT(timer2->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(timer2->timer2_postscaler_value);
        TMR2 = timer2->timer2_preload_value ; 
        timer2_preload = timer2->timer2_preload_value ; 
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptHandler = timer2->Timer2Interrupt ; 
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer2->timer2_priority == INTERRUPT_HIGH_PRIORITY){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(timer2->timer2_priority == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        }
        else{
            error_state = E_NOT_OK  ;
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PrephralInterruptEnable();
#endif
#endif
        TIMER2_ENABLE();
        error_state = E_OK  ;
    }
    return error_state  ;
}
/**
 * @breif function to De-Initialize Timer2
 * @preconditions None
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_DeInit(const timer2_config_t *timer2){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer2){
        error_state = E_NOT_OK  ;
    }
    else{
        TIMER2_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif
        error_state = E_OK  ;
    }
    return error_state  ;
}
/**
 * @breif function to read the value of Timer2 register 
 * @preconditions Timer2_Init() must called before 
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Read_Value(const timer2_config_t *timer2, uint8 *read_value){
    STD_ReturnType error_state = E_NOT_OK ; 
    if((NULL == timer2) || (NULL == read_value)){
        error_state = E_NOT_OK  ;
    }
    else{
        *read_value = TMR2 ; 
        error_state = E_OK  ;
    }
    return error_state  ;
}
/**
 * @breif function to read the value of Timer2 register 
 * @preconditions Timer2_Init() must called before 
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Write_Value(const timer2_config_t *timer2, uint8  _value){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer2){
        error_state = E_NOT_OK  ;
    }
    else{
        TMR2 = _value ; 
        error_state = E_OK  ;
    }
    return error_state  ;
}

void TIMER2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload  ;
    if(TIMER2_InterruptHandler){
        TIMER2_InterruptHandler();
    }
}