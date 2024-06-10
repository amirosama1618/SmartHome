/* 
 * File:   timer0.c
 * Author: Ameer
 *
 * Created on March 3, 2024, 8:31 PM
 */

/*================================ section : includes ================================*/
#include "timer0.h"

uint16 g_timer0_preload_value = ZERO_INIT ; 
/*================================ section : Timer0 Interrupt Handler ==========================*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static InterruptHandler Timer0_InterruptHandler = NULL ; 
#endif
/*================================ section : Static Helper Function declarations ==========================*/
static STD_ReturnType timer0_ResolutionConfigure(const timer0_config_t *timer0_obj);
static STD_ReturnType timer0_ModeConfigure(const timer0_config_t *timer0_obj);
static STD_ReturnType timer0_PreScalerConfigure(const timer0_config_t *timer0_obj);
static STD_ReturnType timer0_PreScalerValueConfigure(const timer0_config_t *timer0_obj);
static STD_ReturnType timer0_PreLoadConfigure(const timer0_config_t *timer0_obj);
#if TIMER0_INTERRUPT_OVERFLOW_FEATURE == TIMER0_FEATURE_ENABLE
static STD_ReturnType timer0_InterruptConfigure(const timer0_config_t *timer0_obj);
#endif
/*================================ section : functions implementation ================================*/
/**
 * @breif function to initialize Timer0 Module 
 * @preconditions None
 * @param timer0_obj
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Init(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer0_obj){
        error_state  = E_NOT_OK  ;
    }
    else{
        /* Disable Timer0 */
        TIMER0_DISABLE();
        /* Select Timer Resolution : 8Bit or 16Bit */
        error_state = timer0_ResolutionConfigure(timer0_obj);
        /* Select Timer mode : Timer or Counter */
        error_state = timer0_ModeConfigure(timer0_obj);
        /* Enable pre-scaler if needed */
        error_state = timer0_PreScalerConfigure(timer0_obj);
        /* Enable Interrupt on overflow if needed */
#if TIMER0_INTERRUPT_OVERFLOW_FEATURE == TIMER0_FEATURE_ENABLE
        error_state = timer0_InterruptConfigure(timer0_obj);
#else
        /* tmier0 pooling on overflow */
        
#endif
        /* initialize the pre-load value to timer register */
        error_state = timer0_PreLoadConfigure(timer0_obj);
        /* Enable Timer0 */
        TIMER0_ENABLE();
    }
    return error_state  ;
}
/**
 * @breif function to De-Initialize Timer0
 * @preconditions None
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_DeInit(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer0_obj){
        error_state = E_NOT_OK  ;
    }
    else{
    
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif function to read the value of Timer0 register 
 * @preconditions Timer0_Init() must called before 
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Read_Value(const timer0_config_t *timer0_obj, uint16 *read_value){
    STD_ReturnType error_state = E_NOT_OK ; 
    uint8 l_tmr0l = ZERO_INIT , l_tmr0h = ZERO_INIT ; 
    if(NULL == timer0_obj){
        error_state = E_NOT_OK  ;
    }
    else{
        if(TIMER0_8BIT_RESOLUTION == timer0_obj->timer0_resolution){
            *read_value = (uint8)(TMR0L);
            error_state = E_OK  ;
        }
        else if(TIMER0_16BIT_RESOLUTION == timer0_obj->timer0_resolution){
            l_tmr0l = TMR0L ; 
            l_tmr0h = TMR0H ; 
            *read_value = (uint16)((l_tmr0h << 8 )+l_tmr0l);
            error_state = E_OK  ;
        }
        else{
            error_state = E_NOT_OK  ;
        }
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif function to read the value of Timer0 register 
 * @preconditions Timer0_Init() must called before 
 * @param timer0_obj pointer to Timer0 configuration data type @ref timer0_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer0_Write_Value(const timer0_config_t *timer0_obj, uint16 _value){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == timer0_obj){
        error_state = E_NOT_OK  ;
    }
    else{
        if(TIMER0_8BIT_RESOLUTION == timer0_obj->timer0_resolution){
            TMR0L = (uint8)(_value);
            error_state = E_OK  ;
        }
        else if(TIMER0_16BIT_RESOLUTION == timer0_obj->timer0_resolution){
            TMR0H = (_value )>> 8;
            TMR0L = (uint8)(_value);
            error_state = E_OK  ;
        }
        else{
            error_state = E_NOT_OK  ;
        }
        error_state = E_OK ; 
    }
    return error_state ; 
}
/*================================ section : Helper Function implementation ==========================*/
static STD_ReturnType timer0_ResolutionConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(TIMER0_8BIT_RESOLUTION == timer0_obj->timer0_resolution){
        TIMER0_8BitConfig();
        error_state = E_OK  ;
    }
    else if(TIMER0_16BIT_RESOLUTION == timer0_obj->timer0_resolution){
        TIMER0_16BitConfig();
        error_state = E_OK  ;
    }
    else{
        error_state = E_NOT_OK  ;
    }
    return error_state  ;
}

static STD_ReturnType timer0_ModeConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    /**
    * Pin configuration for Timer0 clock input
    * T0CKI : PortA , PIN 4 
    * @note must be declared for Timer0 counter mode
    */
    pin_config_t timer0_External_Clock_Input_Pin = {
        .port = PORTA_INDEX , 
        .pin  = PIN4 , 
        .direction  =INPUT ,
    } ; 
    if(TIMER0_TIMER_MODE == timer0_obj->timer0_mode){
        TIMER0_InternalClockSelect();
        error_state = E_OK  ;
    }
    else if(TIMER0_COUNTER_MODE == timer0_obj->timer0_mode){
        /* enable external clock in pin T0CKI */
        TIMER0_ExternalClockSelect();
        /* select timer0 source edge */
        if(TIMER0_COUNTER_RAISING_EDGE == timer0_obj->timer0_source_edge){
            TIMER0_RaisingEdgeSelect();
            error_state = E_OK  ;
        }
        else if(TIMER0_COUNTER_FALLING_EDGE == timer0_obj->timer0_source_edge){
            TIMER0_FallingEdgeSelect();
            error_state = E_OK  ;
        }
        else{
            /* source edge not declared */
            error_state = E_NOT_OK  ;
        }
        /* pin T0CKI Configure*/
        error_state =  gpio_pin_direction_init(&timer0_External_Clock_Input_Pin);
    }
    else{
        error_state = E_NOT_OK  ;
    }
    return error_state  ;
}

static STD_ReturnType timer0_PreScalerConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(TIMER0_PRESCALER_CFG_ENABLE == timer0_obj->timer0_prescaler_cfg){
        /* Enable PreScaler */
        TIMER0_PrescalerEnable();
        error_state = timer0_PreScalerValueConfigure(timer0_obj);
        error_state = E_OK  ;
    }
    else if(TIMER0_PRESCALER_CFG_DISABLE == timer0_obj->timer0_prescaler_cfg){
        /* Disable PreScaler */
        TIMER0_PrescalerDisable();
        error_state = E_OK  ;
    }
    else{
        error_state = E_NOT_OK  ;
    }
    return error_state  ;
}
static STD_ReturnType timer0_PreScalerValueConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    switch(timer0_obj->timer0_prescaler_value){
            case TIMER0_PRESCALER_DIV_BY_2 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_2);
                break;
           case TIMER0_PRESCALER_DIV_BY_4 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_4);
                break;
           case TIMER0_PRESCALER_DIV_BY_8 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_8);
                break;
           case TIMER0_PRESCALER_DIV_BY_16 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_16);
                break;
            case TIMER0_PRESCALER_DIV_BY_32 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_32);
                break;
           case TIMER0_PRESCALER_DIV_BY_64 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_64);
                break;
           case TIMER0_PRESCALER_DIV_BY_128 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_128);
                break;
           case TIMER0_PRESCALER_DIV_BY_256 :
                TIMER0_PrescalerValueSelect(TIMER0_PRESCALER_DIV_BY_256);
                break;
            default: error_state = E_NOT_OK  ;
        }
    return error_state  ;
}
static STD_ReturnType timer0_PreLoadConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(TIMER0_8BIT_RESOLUTION == timer0_obj->timer0_resolution){
        TMR0L = (uint8)(timer0_obj->timer0_preload_value);
        g_timer0_preload_value = (uint8)(timer0_obj->timer0_preload_value) ; 
        error_state = E_OK  ;
    }
    else if(TIMER0_16BIT_RESOLUTION == timer0_obj->timer0_resolution){
        TMR0H = (timer0_obj->timer0_preload_value )>> 8;
        TMR0L = (uint8)(timer0_obj->timer0_preload_value);
        g_timer0_preload_value = timer0_obj->timer0_preload_value ; 
        error_state = E_OK  ;
    }
    else{
        error_state = E_NOT_OK  ;
    }
    return error_state  ;
}
#if TIMER0_INTERRUPT_OVERFLOW_FEATURE == TIMER0_FEATURE_ENABLE
static STD_ReturnType timer0_InterruptConfigure(const timer0_config_t *timer0_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(NULL == timer0_obj->Timer0Interrupt){
        error_state = E_NOT_OK  ;
    }
    else{
        /* Disable Timer0 Interrupt */
        TIMER0_InterruptDisable();
        /* priority feature configuration */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* priority configuration */
        switch(timer0_obj ->timer0_priority){
            case INTERRUPT_HIGH_PRIORITY :
                TIMER0_HighPrioritySet();
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                error_state = E_OK ;
                break;
            case INTERRUPT_LOW_PRIORITY :
                TIMER0_LowPrioritySet();
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                error_state = E_OK ;
                break;
            default : error_state = E_NOT_OK ; 
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PrephralInterruptEnable();
        error_state = E_OK ;
#endif
       /* set interrupt handler */
        Timer0_InterruptHandler = timer0_obj->Timer0Interrupt ; 
         /* Enable Timer0 Interrupt */
        TIMER0_InterruptEnable();
    }
    return error_state  ;
}
void TIMER0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (g_timer0_preload_value)>> 8;
    TMR0L = (uint8)(g_timer0_preload_value);
    if(Timer0_InterruptHandler){
        Timer0_InterruptHandler();
    }
}
#endif

