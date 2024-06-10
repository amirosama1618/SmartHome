/* 
 * File:   ecu_key_pad.h
 * Author: Ameer
 *
 * Created on February 5, 2024, 2:25 PM
 */

#ifndef ECU_KEY_PAD_H
#define	ECU_KEY_PAD_H

/* section : includes */
#include "../../MCAL_layer/GPIO/mcal_gpio.h"
#include "ecu_key_pad_cfg.h"
/* section : Macro definitions */

/* section : Macro functions definitions */

/* section : Data type declaration */
typedef struct{
    pin_config_t ROWS_PINS[ECU_KEYPAD_ROWS];
    pin_config_t COLS_PINS[ECU_KEYPAD_COLS];
}key_pad_t;
/* section : functions declarations */
STD_ReturnType key_pad_initialization(const key_pad_t *KeyPad);
STD_ReturnType key_pad_get_value(const key_pad_t *KeyPad , uint8 *value);
#endif	/* ECU_KEY_PAD_H */

