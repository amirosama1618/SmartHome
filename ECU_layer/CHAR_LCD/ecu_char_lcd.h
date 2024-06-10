/* 
 * File:   ecu_char_lcd.h
 * Author: Ameer
 *
 * Created on February 8, 2024, 1:44 PM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

/******************************* section : includes *******************************/
#include "../../MCAL_layer/GPIO/mcal_gpio.h"
#include "ecu_char_lcd_cfg.h"
/******************************* section : Macro definitions *******************************/
#define _LCD_CLEAR                      0x01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_SET             0x06
/* display ON/OFF control */
#define _LCD_DISPLAY_OFF                0x08
#define _LCD_DISPLAY_ON_CURSOR_OFF      0x0C
#define _LCD_DISPLAY_ON_CURSOR_ON       0x0E
#define _LCD_CURSOR_ON_BLINK_OFF        0x0E
#define _LCD_CURSOR_ON_BLINK_ON         0x0F
/* cursor and display shift */
#define _LCD_CURSOR_SHIFT_LEFT          0x10
#define _LCD_CURSOR_SHIFT_RIGHT         0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
/* function set */
#define _LCD_8BIT_MODE_2LINE            0x38
#define _LCD_4BIT_MODE_2LINE            0x28
/* start addresses*/
#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_SATRT                0x80

#define ROW1        1
#define ROW2        2
#define ROW3        3
#define ROW4        4
/******************************* section : Macro functions definitions *******************************/

/******************************* section : Data type declaration *******************************/
typedef struct{
    pin_config_t lcd_rs ; 
    pin_config_t lcd_en ; 
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs ; 
    pin_config_t lcd_en ; 
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;
/******************************* section : functions declarations *******************************/
/* character lcd 4bits software interface */
STD_ReturnType chr_lcd_4bit_initialize(const chr_lcd_4bit_t *chr_lcd);
STD_ReturnType chr_lcd_4bit_send_command(const chr_lcd_4bit_t *chr_lcd, uint8 command);
STD_ReturnType chr_lcd_4bit_send_char_data(const chr_lcd_4bit_t *chr_lcd, uint8 data);
STD_ReturnType chr_lcd_4bit_send_char_data_position(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , uint8 data );
STD_ReturnType chr_lcd_4bit_send_string_data(const chr_lcd_4bit_t *chr_lcd, uint8* str);
STD_ReturnType chr_lcd_4bit_send_string_data_position(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , uint8* str );
STD_ReturnType chr_lcd_4bit_send_custom_char(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , const uint8 _chr[] , uint8 mem_pos);
/* character lcd 8bits software interface */
STD_ReturnType chr_lcd_8bit_initialize(const chr_lcd_8bit_t *chr_lcd);
STD_ReturnType chr_lcd_8bit_send_command(const chr_lcd_8bit_t *chr_lcd, uint8 command);
STD_ReturnType chr_lcd_8bit_send_char_data(const chr_lcd_8bit_t *chr_lcd, uint8 data);
STD_ReturnType chr_lcd_8bit_send_char_data_position(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , uint8 data );
STD_ReturnType chr_lcd_8bit_send_string_data(const chr_lcd_8bit_t *chr_lcd, uint8* str);
STD_ReturnType chr_lcd_8bit_send_string_data_position(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , uint8* str );
STD_ReturnType chr_lcd_8bit_send_custom_char(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , const uint8 _chr[] , uint8 mem_pos);
/* convert value to string */
STD_ReturnType convert_uint8_to_string(uint8 value , uint8 *str);
STD_ReturnType convert_uint16_to_string(uint16 value , uint8 *str);
STD_ReturnType convert_uint32_to_string(uint32 value , uint8 *str);
#endif	/* ECU_CHAR_LCD_H */

