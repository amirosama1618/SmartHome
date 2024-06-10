/* 
 * File:   ecu_led.h
 * Author: Ameer
 *
 * Created on January 30, 2024, 3:46 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/* section : includes */
#include "../../MCAL_layer/GPIO/mcal_gpio.h"
#include "ecu_led_cfg.h"
/* section : Macro definitions */

/* section : Macro functions definitions */

/* section : Data type declaration */
typedef enum{
    LED_OFF , 
    LED_ON
}led_status_t;

typedef struct{
    port_index_t port;
    pin_index_t pin ;
    led_status_t status ;
} led_t ; 
/* section : functions declarations */
/**
 * @breif function to initialize a led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_initialize(const led_t *led);
/**
 * @breif function to turn off the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_on(const led_t *led);
/**
 * @breif function to turn off the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_off(const led_t *led);
/**
 * @breif function to toggle the led 
 * @param led : pointer to led configurations @ref led_t 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

