/* 
 * File:   ecu_layer_init.h
 * Author: Ameer
 *
 * Created on February 13, 2024, 2:57 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* section : includes */
#include "../MCAL_layer/mcal_layer_init.h"
#include "LED/ecu_led.h"
#include "CHAR_LCD/ecu_char_lcd.h"
#include "KEY_PAD/ecu_key_pad.h"
#include "LM35/lm35.h"

/* section : modules declaration */
/*Reception light*/
led_t reseption_light ={
.port = PORTD_INDEX , 
.pin = PIN0 , 
.status = LED_OFF
};
/*Reception AC*/
led_t reseption_AC ={
.port = PORTD_INDEX , 
.pin = PIN1 , 
.status = LED_OFF
};
/*Reception TV*/
led_t reseption_TV ={
.port = PORTD_INDEX , 
.pin = PIN2 , 
.status = LED_OFF
};

/*Room 1 light*/
led_t room_1_light ={
.port = PORTD_INDEX , 
.pin = PIN3 , 
.status = LED_OFF
};
/*Room 1 AC*/
led_t room_1_AC ={
.port = PORTD_INDEX , 
.pin = PIN4 , 
.status = LED_OFF
};

/*Room 2 light*/
led_t room_2_light ={
.port = PORTD_INDEX , 
.pin = PIN5 , 
.status = LED_OFF
};
/*Room 2 AC*/
led_t room_2_AC ={
.port = PORTD_INDEX , 
.pin = PIN6 , 
.status = LED_OFF
};
/* temperature sensors */
adc_conf_t lm35_reseption ={
.ADC_InterruptHandler = NULL ,
.aquisition_time = ADC_12_TAD,
.channel_select = ADC_CHANNEL_AN0,
.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
.voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE,
.Result_format = ADC_RESULT_FORMAT_RIGHT
};
adc_conf_t lm35_room1 ={
.ADC_InterruptHandler = NULL ,
.aquisition_time = ADC_12_TAD,
.channel_select = ADC_CHANNEL_AN1,
.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
.voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE,
.Result_format = ADC_RESULT_FORMAT_RIGHT
};
adc_conf_t lm35_room2 ={
.ADC_InterruptHandler = NULL ,
.aquisition_time = ADC_12_TAD,
.channel_select = ADC_CHANNEL_AN2,
.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
.voltage_reference = ADC_VOLTAGE_REFRENCE_DISABLE,
.Result_format = ADC_RESULT_FORMAT_RIGHT
};

/* section : functions declarations */
void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

