/* 
 * File:   buzzer.h
 * Author: Ameer
 *
 * Created on May 25, 2024, 11:53 AM
 */
#include "buzzer.h"

STD_ReturnType Buzzer_init(const buzzer_config_t* buzzer_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(buzzer_obj == NULL){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state = E_OK ; 
        CCP_Init(buzzer_obj);
    }
    return error_state ; 
}
STD_ReturnType Buzzer_on(const buzzer_config_t* buzzer_obj , const uint8 _duty){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(buzzer_obj == NULL){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state = CCP_PWMSetDuty(buzzer_obj , _duty);
        error_state = CCP_PWMStart(buzzer_obj);
    }
    return error_state ; 
}
STD_ReturnType Buzzer_off(const buzzer_config_t* buzzer_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(buzzer_obj == NULL){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state = CCP_PWMEnd(buzzer_obj);
    }
    return error_state ; 
}
