/* 
 * File:   ecu_key_pad_cfg.h
 * Author: Ameer
 *
 * Created on February 5, 2024, 2:26 PM
 */

#ifndef ECU_KEY_PAD_CFG_H
#define	ECU_KEY_PAD_CFG_H

/* section : includes */

/* section : Macro definitions */
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLS    3
/* section : key pad buttons values*/
const uint8 KEY_PAD_BTN_VALUES[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLS] = {
                                                                        {'1','2','3'},
                                                                        {'4','5','6'},
                                                                        {'7','8','9'},
                                                                        {'*','0','#'},
};
/* section : Macro functions definitions */

/* section : Data type declaration */

/* section : functions declarations */

#endif	/* ECU_KEY_PAD_CFG_H */

