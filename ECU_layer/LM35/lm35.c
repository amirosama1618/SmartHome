/* 
 * File:   lm35.c
 * Author: Ameer
 *
 * Created on March 1, 2024, 11:04 PM
 */

#include "lm35.h"

STD_ReturnType LM35_Init(const adc_conf_t *adc_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == adc_obj){
        error_state = E_NOT_OK  ;
    }
    else{
        error_state = ADC_Init(adc_obj);
    }
    return error_state  ;
}
STD_ReturnType LM35_GetTempCelsius(const adc_conf_t *adc_obj, adc_result_t *Temp_celsius_res){
    STD_ReturnType error_state = E_NOT_OK ; 
    adc_result_t l_conversion_res = 0 ; 
    if((NULL == adc_obj) || (NULL == Temp_celsius_res)){
        error_state = E_NOT_OK  ;
    }   
    else{
           error_state = ADC_GetConversion_Blocking(adc_obj , adc_obj->channel_select , &l_conversion_res);
           *Temp_celsius_res = l_conversion_res * (4.88);
           *Temp_celsius_res /= 10 ; 
    }
    return error_state  ;
}