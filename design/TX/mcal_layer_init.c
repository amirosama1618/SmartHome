/* 
 * File:   mcal_layer_init.c
 * Author: Ameer
 *
 * Created on May 22, 2024, 6:01 PM
 */

#include "mcal_layer_init.h"

void mcal_layer_initialize(void){
    EUSART_ASYNC_Init(&master_uart); 
}