/* 
 * File:   mcal_ccp1.c
 * Author: Ameer
 * CAPTURE/COMPARE/PWM (CCP) MODULE
 * Created on March 10, 2024, 1:26 AM
 */

/*================================ section : includes ================================*/
#include "mcal_ccp1.h"
/*================================ section : Global Variables  ================================*/
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
pin_config_t CCP1_PIN_CAPTURE_MODE={
.port = PORTC_INDEX , 
.pin  = PIN2,
.direction = INPUT,
.logic = LOW
};
pin_config_t CCP2_PIN_CAPTURE_MODE={
.port = PORTC_INDEX , 
.pin  = PIN1,
.direction = INPUT,
.logic = LOW
};
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
pin_config_t CCP1_PIN_COMPARE_MODE={
.port = PORTC_INDEX , 
.pin  = PIN2,
.direction = OUTPUT,
.logic = LOW
};
pin_config_t CCP2_PIN_COMPARE_MODE={
.port = PORTC_INDEX , 
.pin  = PIN1,
.direction = OUTPUT,
.logic = LOW
};
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
pin_config_t CCP1_PIN_PWM_MODE={
.port = PORTC_INDEX , 
.pin  = PIN2,
.direction = OUTPUT,
};
pin_config_t CCP2_PIN_PWM_MODE={
.port = PORTC_INDEX , 
.pin  = PIN1,
.direction = OUTPUT,
};
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
InterruptHandler CCP1_InterruptHandler = NULL ; 
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
InterruptHandler CCP2_InterruptHandler = NULL ; 
#endif
/*================================ section : static helper functions declaration ================================*/
static inline void ccp_capture_timer_config(const ccp_config_t *_ccp);
/*================================ section : Data type declaration ================================*/

/*================================ section : functions Implementation ================================*/
/**
 * @breif function to initialize CCP module
 * @preconditions NONE
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_Init(const ccp_config_t *_ccp ){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(NULL == _ccp){
        error_state  = E_NOT_OK ; 
    }
    else{
        if(CCP1_INST == _ccp->ccp_inst){
            /* CCP1 Disable*/
            CCP1_SET_MODE(CCP_MODULE_DISABLE);  
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
            if(CCP_CAPTURE_MODE_SELECTED == _ccp->ccp_mode){
                switch(_ccp->ccp_sub_mode){
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE :
                        CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_1_RISING_EDGE :
                        CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_4_RISING_EDGE :
                        CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_16_RISING_EDGE :
                        CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    default : error_state  = E_NOT_OK ; 
                }
            }
            else{error_state  = E_NOT_OK ;}
            /* Pin Configuration : Input */
            gpio_pin_direction_init(&CCP1_PIN_CAPTURE_MODE);
            /* CCP Capture Timer Configure */
            ccp_capture_timer_config(&_ccp);
 
#endif
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
            if(CCP_COMPARE_MODE_SELECTED == _ccp->ccp_mode){
                switch(_ccp->ccp_sub_mode){
                    case CCP_COMPARE_MODE_SET_PIN_LOW :
                        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH :
                        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH :
                        CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT :
                        CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_GEN_EVENT :
                        CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                        error_state  = E_OK ;
                        break;
                    default : error_state  = E_NOT_OK ; 
                }
            }
            else{error_state  = E_NOT_OK ;}
            /* Pin Configuration : Input */
            gpio_pin_direction_init(&CCP1_PIN_COMPARE_MODE);
            /* CCP Capture Timer Configure */
            ccp_capture_timer_config(&_ccp);
            
#endif
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
            if(CCP_PWM_MODE_SELECTED == _ccp->ccp_mode){
                CCP1_SET_MODE(CCP_PWM_MODE);
                /* Pin Configuration */
                gpio_pin_init(&CCP1_PIN_PWM_MODE);
                /* PWM frequency initialize */
                PR2 = (uint8)((_XTAL_FREQ/(_ccp->pwm_frequency * 4.0 * (_ccp->timer2_postscaler_value +1) 
                                    * (_ccp->timer2_prescaler_value +1)))-1);
                /* Set the TMR2 prescale value, then enable Timer2 by writing to T2CON*/
                timer2_config_t timer2={
                .Timer2Interrupt = NULL ,
                .timer2_postscaler_value = _ccp->timer2_postscaler_value , 
                .timer2_prescaler_value = _ccp->timer2_prescaler_value,
                .timer2_preload_value = 0
                };
                error_state  = Timer2_Init(&timer2);
                error_state  = E_OK ;
            }
            else{error_state  = E_NOT_OK ;}
            
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
            /* CCP1 Interrupt Configuration */
            if(NULL == _ccp->ccp_InterruptHandler){
                /* nothing */
                error_state =  E_NOT_OK  ;
            }
            else{
                CCP1_InterruptDisable();
                CCP1_InterruptFlagClear();
                CCP1_InterruptHandler = _ccp->ccp_InterruptHandler ; 
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _ccp->ccp_priority){
                    CCP1_HighPrioritySet();
                    INTERRUPT_GlobalInterruptHighEnable();
                    error_state  = E_OK ;
                }
                else if(INTERRUPT_LOW_PRIORITY == _ccp->ccp_priority){
                    CCP1_LowPrioritySet();
                    INTERRUPT_GlobalInterruptLowEnable();
                    error_state  = E_OK ;
                }
                else{error_state  = E_NOT_OK ;}
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PrephralInterruptEnable();
                error_state  = E_OK ;
            #endif
                CCP1_InterruptEnable();
#endif
           }
        }
        else if(CCP2_INST == _ccp->ccp_inst){
            /* CCP2 Disable*/
            CCP2_SET_MODE(CCP_MODULE_DISABLE);  
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
            if(CCP_CAPTURE_MODE_SELECTED == _ccp->ccp_mode){
                switch(_ccp->ccp_sub_mode){
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE :
                        CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_1_RISING_EDGE :
                        CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_4_RISING_EDGE :
                        CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    case CCP_CAPTURE_MODE_16_RISING_EDGE :
                        CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                        error_state  = E_OK ;
                        break;
                    default : error_state  = E_NOT_OK ; 
                }
            }
            else{error_state  = E_NOT_OK ;}
            /* Pin Configuration : Input */
            gpio_pin_direction_init(&CCP2_PIN_CAPTURE_MODE);
            /* CCP Capture Timer Configure */
            ccp_capture_timer_config(&_ccp);
#endif
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
            if(CCP_COMPARE_MODE_SELECTED == _ccp->ccp_mode){
                switch(_ccp->ccp_sub_mode){
                    case CCP_COMPARE_MODE_SET_PIN_LOW :
                        CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH :
                        CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH :
                        CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT :
                        CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                        error_state  = E_OK ;
                        break;
                    case CCP_COMPARE_MODE_GEN_EVENT :
                        CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                        error_state  = E_OK ;
                        break;
                    default : error_state  = E_NOT_OK ; 
                }
            }
            else{error_state  = E_NOT_OK ;}
            /* Pin Configuration : Input */
            gpio_pin_direction_init(&CCP2_PIN_COMPARE_MODE);
            /* CCP Capture Timer Configure */
            ccp_capture_timer_config(&_ccp);
#endif
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
            if(CCP_PWM_MODE_SELECTED == _ccp->ccp_mode){
                CCP2_SET_MODE(CCP_PWM_MODE);
                error_state  = E_OK ;
            }
            else{error_state  = E_NOT_OK ;}
            /* Pin Configuration */
            gpio_pin_direction_init(&CCP2_PIN_PWM_MODE);
            /* PWM frequency initialize */
            PR2 = (uint8)((_XTAL_FREQ/(_ccp->pwm_frequency * 4.0 * (_ccp->timer2_postscaler_value+ 1) 
                                * (_ccp->timer2_prescaler_value + 1)))-1);
            /* Set the TMR2 prescale value, then enable Timer2 by writing to T2CON*/
            timer2_config_t timer2={
            .Timer2Interrupt = NULL ,
            .timer2_postscaler_value = _ccp->timer2_postscaler_value , 
            .timer2_prescaler_value = _ccp->timer2_prescaler_value,
            .timer2_preload_value = 0
            };
            error_state  = Timer2_Init(&timer2);
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
            /* CCP2 Interrupt Configuration */
            if(NULL == _ccp->ccp_InterruptHandler){
                /* nothing */
                error_state =  E_NOT_OK  ;
            }
            else{
                CCP2_InterruptDisable();
                CCP2_InterruptFlagClear();
                CCP1_InterruptHandler = _ccp->ccp_InterruptHandler ; 
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _ccp->ccp_priority){
                    CCP2_HighPrioritySet();
                    INTERRUPT_GlobalInterruptHighEnable();
                    error_state  = E_OK ;
                }
                else if(INTERRUPT_LOW_PRIORITY == _ccp->ccp_priority){
                    CCP2_LowPrioritySet();
                    INTERRUPT_GlobalInterruptLowEnable();
                    error_state  = E_OK ;
                }
                else{error_state  = E_NOT_OK ;}
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PrephralInterruptEnable();
                error_state  = E_OK ;
            #endif
                CCP2_InterruptEnable();
#endif
           } 
        }
        else{
            error_state  = E_NOT_OK ; 
        }
    }
    return error_state ; 
}
/**
 * @breif function to De-Initialize the CCP module
 * @preconditions NONE
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_DeInit(const ccp_config_t *_ccp ){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(NULL == _ccp){
        error_state  = E_NOT_OK ; 
    }
    else{
        if(CCP1_INST == _ccp->ccp_inst){
           /* CCP1 Disable*/
           CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
           CCP1_InterruptDisable();
#endif
           error_state  = E_OK ; 
        }
        else if(CCP2_INST == _ccp->ccp_inst){
           CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
           CCP2_InterruptDisable();
#endif
           error_state  = E_OK ; 
        }
        else{
           error_state  = E_NOT_OK ;
        }
    }
    return error_state ; 
}

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
/**
 * @breif function to check capture mode status "CCP_CAPTURE_READY" or "CCP_CAPTURE_READY" 
 * @preconditions CCP_Init() function must called before,
 *                CCP1_CFG_SELECTED_MODE() must select capture mode in mcal_ccp_cfg file 
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _capture_status pointer to return the capture status 
 *        @note 0x01 : CCP_CAPTURE_READY
 *              0x00 : CCP_CAPTURE_READY
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_IsCaptureDataReady(const ccp_config_t *_ccp, uint8 *_capture_status){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(NULL == _capture_status){
        error_state  = E_NOT_OK ; 
    }
    else{
        if(CCP1_INST == _ccp -> ccp_inst){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            CCP1_InterruptFlagClear();
            *_capture_status = CCP_CAPTURE_READY ; 
            }
            else{
             *_capture_status = CCP_CAPTURE_NOT_READY ; 
            }
            error_state  = E_OK ;
        }
        else if(CCP2_INST == _ccp -> ccp_inst){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
            CCP2_InterruptFlagClear();
            *_capture_status = CCP_CAPTURE_READY ; 
            }
            else{
             *_capture_status = CCP_CAPTURE_NOT_READY ; 
            }
            error_state  = E_OK ;
        }
        else{
            error_state  = E_NOT_OK ; 
        }
    }
    return error_state ; 
}
/**
 * @breif function to read the captured value 
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select capture mode in mcal_ccp1_cfg file  
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _capture_value pointer to return the captured value 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_CaptureModeReadValue(const ccp_config_t *_ccp,uint16 *_capture_value){
    STD_ReturnType error_state  =E_NOT_OK ; 
    ccp_reg_t capture_TempValue = {   .ccpr_low = ZERO_INIT ,
                                                .ccpr_high = ZERO_INIT,
                                                .ccpr_16bit = ZERO_INIT} ; 
    if( (NULL == _capture_value)||(NULL == _ccp)){
        error_state  =E_NOT_OK ;
    }
    else{
        if(CCP1_INST == _ccp-> ccp_inst){
            capture_TempValue.ccpr_low = CCPR1L ; 
            capture_TempValue.ccpr_high = CCPR1H ; 
            *_capture_value = capture_TempValue.ccpr_16bit ; 
            error_state  =E_OK;
        }
        else if(CCP2_INST == _ccp-> ccp_inst){
            capture_TempValue.ccpr_low = CCPR2L ; 
            capture_TempValue.ccpr_high = CCPR2H ; 
            *_capture_value = capture_TempValue.ccpr_16bit ; 
            error_state  =E_OK;
        }
        else{
            error_state  =E_NOT_OK ;
        }
    }
    return error_state ; 
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
/**
 * @breif function to check the compare status "CCP_COMPARE_READY" or "CCP_COMPARE_NOT_READY"
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select compare mode in mcal_ccp1_cfg file  
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _compare_status pointer to return the compare status 
 *        @note 0x01 : CCP_COMPARE_READY
 *              0x00 : CCP_COMPARE_NOT_READY
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_IsCompareComplete(const ccp_config_t *_ccp, uint8 *_compare_status){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(NULL == _compare_status){
        error_state  = E_NOT_OK ; 
    }
    else{
        if(CCP1_INST == _ccp->ccp_inst){
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            CCP1_InterruptFlagClear();
            *_compare_status = CCP_COMPARE_READY ; 
            }
            else{
                 *_compare_status = CCP_COMPARE_NOT_READY ; 
            }
            error_state  = E_OK ;
        }
        else if(CCP2_INST == _ccp->ccp_inst){
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            CCP2_InterruptFlagClear();
            *_compare_status = CCP_COMPARE_READY ; 
            }
            else{
                 *_compare_status = CCP_COMPARE_NOT_READY ; 
            }
            error_state  = E_OK ;
        }
        else{
            error_state  = E_NOT_OK ; 
        }
    }
    return error_state ; 
}
/**
 * @breif function to set compare value in CCPx register 
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select compare mode in mcal_ccp1_cfg file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _compare_value the compare value need to be set 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_CompareModeSetValue(const ccp_config_t *_ccp, uint16 _compare_value){
    STD_ReturnType error_state  =E_NOT_OK ; 
    ccp_reg_t capture_TempValue = {   .ccpr_low = ZERO_INIT ,
                                                .ccpr_high = ZERO_INIT,
                                                .ccpr_16bit = ZERO_INIT} ;
    if(CCP1_INST == _ccp->ccp_inst){
        capture_TempValue.ccpr_16bit =  _compare_value ; 
        CCPR1L = capture_TempValue.ccpr_low ; 
        CCPR1H = capture_TempValue.ccpr_high ; 
        error_state  =E_OK;
    }
    else if(CCP2_INST == _ccp->ccp_inst){
        capture_TempValue.ccpr_16bit =  _compare_value ; 
        CCPR2L = capture_TempValue.ccpr_low ; 
        CCPR2H = capture_TempValue.ccpr_high ; 
        error_state  =E_OK;
    }
    else{
        error_state  =E_NOT_OK ; 
    }
    return error_state ; 
}
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
/**
 * @breif function to set Duty of the PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _duty value of the Duty of the PWM need to be set 
 *        @note (_duty) value : 0 to 100
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMSetDuty(const ccp_config_t *_ccp, const uint8 _duty){
    STD_ReturnType error_state  =E_NOT_OK ; 
    uint16 l_temp_duty = ZERO_INIT ; 
    l_temp_duty = (uint16)(((float)PR2+1.0)*((float)_duty/100.0)*(float)4);
    if(CCP1_INST == _ccp->ccp_inst){
        CCP1CONbits.DC1B = (uint8)(l_temp_duty & 0x0003);
        CCPR1L = (uint8)(l_temp_duty >> 2);
        error_state  =E_OK;
    }
    else if(CCP2_INST == _ccp->ccp_inst){
        CCP2CONbits.DC2B = (uint8)(l_temp_duty & 0x0003);
        CCPR2L = (uint8)(l_temp_duty >> 2);
        error_state  =E_OK;
    }
    else{
        error_state  =E_NOT_OK ;
    }
    return error_state ; 
}
/**
 * @breif function to Start PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMStart(const ccp_config_t *_ccp){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(CCP1_INST == _ccp->ccp_inst){
        CCP1_SET_MODE(CCP_PWM_MODE);
        error_state  =E_OK;
    }
    else if(CCP2_INST == _ccp->ccp_inst){
        CCP2_SET_MODE(CCP_PWM_MODE);
        error_state  =E_OK;
    }
    else{
        error_state  =E_NOT_OK ;
    }
    return error_state ; 
}
/**
 * @breif function to End PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMEnd(const ccp_config_t *_ccp){
    STD_ReturnType error_state  =E_NOT_OK ; 
    if(CCP1_INST == _ccp->ccp_inst){
        CCP1_SET_MODE(CCP_MODULE_DISABLE);
        error_state  =E_OK;
    }
    else if(CCP2_INST == _ccp->ccp_inst){
        CCP2_SET_MODE(CCP_MODULE_DISABLE);
        error_state  =E_OK;
    }
    else{
        error_state  =E_NOT_OK ;
    }
    return error_state ; 
}
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}
#endif
/*================================ section : static helper functions Implementation ================================*/
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
static inline void ccp_capture_timer_config(const ccp_config_t *_ccp){
    if(CCP1_CCP2_TIMER1_SELECT == _ccp->ccp_capture_timer){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 1 ;

    }
    else if(CCP1_TIMER1_CCP2_TIMER3_SELECT == _ccp->ccp_capture_timer){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 0 ;

    }
    else if(CCP1_CCP2_TIMER3_SELECT == _ccp->ccp_capture_timer){
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 0 ;

    }
    else{ /* nothing */ }

}
#endif