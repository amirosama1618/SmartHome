/* 
 * File:   ecu_layer_init.h
 * Author: Ameer
 *
 * Created on February 13, 2024, 2:57 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* section : includes */

#include "LED/ecu_led.h"
#include "CHAR_LCD/ecu_char_lcd.h"
#include "KEY_PAD/ecu_key_pad.h"

/* section : modules declaration */
/**
 * LCD 4Bit Pin Configurations
 * lcd_D4 -> D0
 * lcd_D5 -> D1
 * lcd_D6 -> D2
 * lcd_D7 -> D3
 * lcd_EN -> D4
 * lcd_RS -> D5
 */
chr_lcd_4bit_t _master_lcd ={
.lcd_data[0].port = PORTD_INDEX,
.lcd_data[0].pin = PIN0,
.lcd_data[0].direction = OUTPUT,
.lcd_data[0].logic = LOW,

.lcd_data[1].port = PORTD_INDEX,
.lcd_data[1].pin = PIN1,
.lcd_data[1].direction = OUTPUT,
.lcd_data[1].logic = LOW,

.lcd_data[2].port = PORTD_INDEX,
.lcd_data[2].pin = PIN2,
.lcd_data[2].direction = OUTPUT,
.lcd_data[2].logic = LOW,

.lcd_data[3].port = PORTD_INDEX,
.lcd_data[3].pin = PIN3,
.lcd_data[3].direction = OUTPUT,
.lcd_data[3].logic = LOW,

.lcd_en.port = PORTD_INDEX,
.lcd_en.pin = PIN4,
.lcd_en.direction = OUTPUT,
.lcd_en.logic = LOW,

.lcd_rs.port = PORTD_INDEX,
.lcd_rs.pin = PIN5,
.lcd_rs.direction = OUTPUT,
.lcd_rs.logic = LOW,
};
/**
 * Keypad Pin Configurations
 * keypad_RA -> B0
 * keypad_RB -> B1
 * keypad_RC -> B2
 * keypad_RD -> B3
 * keypad_C1 -> B4
 * keypad_C2 -> B5
 * keypad_C3 -> B6      
 */
key_pad_t _master_keypad ={
.ROWS_PINS[0].port = PORTB_INDEX,
.ROWS_PINS[0].pin = PIN0,
.ROWS_PINS[0].direction = OUTPUT,
.ROWS_PINS[0].logic = LOW,

.ROWS_PINS[1].port = PORTB_INDEX,
.ROWS_PINS[1].pin = PIN1,
.ROWS_PINS[1].direction = OUTPUT,
.ROWS_PINS[1].logic = LOW,

.ROWS_PINS[2].port = PORTB_INDEX,
.ROWS_PINS[2].pin = PIN2,
.ROWS_PINS[2].direction = OUTPUT,
.ROWS_PINS[2].logic = LOW,

.ROWS_PINS[3].port = PORTB_INDEX,
.ROWS_PINS[3].pin = PIN3,
.ROWS_PINS[3].direction = OUTPUT,
.ROWS_PINS[3].logic = LOW,

.COLS_PINS[0].port = PORTB_INDEX,
.COLS_PINS[0].pin = PIN4,
.COLS_PINS[0].direction = INPUT,
.COLS_PINS[0].logic = LOW,

.COLS_PINS[1].port = PORTB_INDEX,
.COLS_PINS[1].pin = PIN5,
.COLS_PINS[1].direction = INPUT,
.COLS_PINS[1].logic = LOW,

.COLS_PINS[2].port = PORTB_INDEX,
.COLS_PINS[2].pin = PIN6,
.COLS_PINS[2].direction = INPUT,
.COLS_PINS[2].logic = LOW,

} ;


/* section : functions declarations */
void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

