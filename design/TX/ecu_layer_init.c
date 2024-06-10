/* 
 * File:   ecu_layer_init.c
 * Author: Ameer
 *
 * Created on February 13, 2024, 2:57 PM
 */

#include "ecu_layer_init.h"

void ecu_layer_initialize(void){
    /**
     * lcd Initialization
     */
    chr_lcd_4bit_initialize(&_master_lcd);
    /**
     * keypad Initialization 
     */
    key_pad_initialization(&_master_keypad);
}