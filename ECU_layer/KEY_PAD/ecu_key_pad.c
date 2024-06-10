/* 
 * File:   ecu_key_pad.c
 * Author: Ameer
 *
 * Created on February 5, 2024, 2:25 PM
 */

#include "ecu_key_pad.h"
/**
 * @breif function to initialize the keypad
 * @param KeyPad pointer to the keypad configurations @ref key_pad_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType key_pad_initialization(const key_pad_t *KeyPad){
    STD_ReturnType error_state = E_NOT_OK ;
    uint8 l_rows_counter = ZERO_INIT ;    uint8 l_cols_counter = ZERO_INIT ;
    if(NULL == KeyPad){
        error_state = E_NOT_OK ;
    }
    else{
        for(l_rows_counter = ZERO_INIT ; l_rows_counter<ECU_KEYPAD_ROWS ; l_rows_counter++){
            error_state = gpio_pin_init(&(KeyPad->ROWS_PINS[l_rows_counter]));
        }
        for(l_cols_counter = ZERO_INIT ; l_cols_counter<ECU_KEYPAD_COLS ; l_cols_counter++){
            error_state = gpio_pin_direction_init(&(KeyPad->COLS_PINS[l_cols_counter]));
        }
    }
    return error_state ; 
}
/**
 * @breif function to get the value from the keypad
 * @param KeyPad pointer to the keypad configurations @ref key_pad_t
 * @param value pointer to store the value from the keypad 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType key_pad_get_value(const key_pad_t *KeyPad , uint8 *value){
    STD_ReturnType error_state = E_NOT_OK ;
    logic_t l_cols_logic = LOW ; 
    uint8 l_rows_counter = ZERO_INIT ;    uint8 l_cols_counter = ZERO_INIT ;    uint8 l_counter = ZERO_INIT ;
    if(NULL == KeyPad  || NULL == value){
        error_state = E_NOT_OK ;
    }
    else{
        for(l_rows_counter = ZERO_INIT ; l_rows_counter<ECU_KEYPAD_ROWS ; l_rows_counter++){
            for(l_counter = ZERO_INIT ; l_counter<ECU_KEYPAD_ROWS ; l_counter++){
                error_state = gpio_pin_write_logic(&(KeyPad->ROWS_PINS[l_counter]) , LOW);
            }
            error_state = gpio_pin_write_logic(&(KeyPad->ROWS_PINS[l_rows_counter]) , HIGH);
            for(l_cols_counter = ZERO_INIT ; l_cols_counter<ECU_KEYPAD_COLS ; l_cols_counter++){
                error_state = gpio_pin_read_logic(&(KeyPad->COLS_PINS[l_cols_counter]) , &l_cols_logic);
                if(HIGH == l_cols_logic){
                    *value = KEY_PAD_BTN_VALUES[l_rows_counter][l_cols_counter];
                }
            }
        }
    }
    return error_state ; 
}
