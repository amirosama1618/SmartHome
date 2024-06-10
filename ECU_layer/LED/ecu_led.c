/* 
 * File:   ecu_led.c
 * Author: Ameer
 *
 * Created on January 30, 2024, 3:46 PM
 */
    
#include "ecu_led.h"
/**
 * @breif function to initialize a led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_initialize(const led_t *led){
    STD_ReturnType error_state = E_OK ;
    if(NULL == led){
        error_state = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
            .port       = led->port ,
            .pin        = led->pin ,
            .direction  = OUTPUT ,
            .logic      = led->status
        } ; 
        error_state =gpio_pin_init(&pin_obj);
    }
    return error_state ; 
}
/**
 * @breif function to turn off the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_on(const led_t *led)
{
    STD_ReturnType error_state = E_OK ;
    if(NULL == led){
        error_state = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
            .port       = led->port ,
            .pin        = led->pin ,
            .direction  = OUTPUT ,
            .logic      = led->status
        } ; 
        error_state =gpio_pin_write_logic(&pin_obj,HIGH);
    }
    return error_state ; 
}
/**
 * @breif function to turn off the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_off(const led_t *led){
    STD_ReturnType error_state = E_OK ;
    if(NULL == led){
        error_state = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
            .port       = led->port ,
            .pin        = led->pin ,
            .direction  = OUTPUT ,
            .logic      = led->status
        } ; 
        error_state =gpio_pin_write_logic(&pin_obj,LOW);
    }
    return error_state ; 
}
/**
 * @breif function to toggle the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_toggle(const led_t *led){
    STD_ReturnType error_state = E_OK ;
    if(NULL == led){
        error_state = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {
            .port       = led->port ,
            .pin        = led->pin ,
            .direction  = OUTPUT ,
            .logic      = led->status
        } ; 
        error_state =gpio_pin_toggle_logic(&pin_obj);
    }
    return error_state ; 
}