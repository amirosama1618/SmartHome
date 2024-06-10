/* 
 * File:   ecu_layer_init.c
 * Author: Ameer
 *
 * Created on February 13, 2024, 2:57 PM
 */

#include "ecu_layer_init.h"
void ecu_layer_initialize(void){
    
    led_initialize(&reseption_light);
    led_initialize(&reseption_AC);
    led_initialize(&reseption_TV);
    
    led_initialize(&room_1_light);
    led_initialize(&room_1_AC);
    
    led_initialize(&room_2_light);
    led_initialize(&room_2_AC);
    
    LM35_Init(&lm35_reseption);
    LM35_Init(&lm35_room1);
    LM35_Init(&lm35_room2);
    

}