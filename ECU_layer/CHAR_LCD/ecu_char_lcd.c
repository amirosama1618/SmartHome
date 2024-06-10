/* 
 * File:   ecu_char_lcd.c
 * Author: Ameer
 *
 * Created on February 8, 2024, 1:44 PM
 */

#include "ecu_char_lcd.h"
/*************************** static helper functions ***************************/
/* 4-bits */
static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd , uint8 _data_command);
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static STD_ReturnType lcd_4bit_set_cursor_position(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column);
/* 8-bits */
static STD_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *lcd , uint8 _data_command) ; 
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static STD_ReturnType lcd_8bit_set_cursor_position(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column);
/*************************** character lcd 4bits software interface ***************************/
/**
 * @breif function to initialize character lcd 4 bit mode
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_initialize(const chr_lcd_4bit_t *chr_lcd){
    STD_ReturnType error_state = E_OK ;
    uint8 l_data_pin_counter = ZERO_INIT ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
       // Initialize EN and RS pins 
        error_state &= gpio_pin_init(&(chr_lcd->lcd_en));
        error_state &= gpio_pin_init(&(chr_lcd->lcd_rs));

        // Initialize data pins (D4-D7)
        for (l_data_pin_counter = 0; l_data_pin_counter < 4; l_data_pin_counter++) {
            error_state &= gpio_pin_init(&(chr_lcd->lcd_data[l_data_pin_counter]));
        }
        // LCD initialization sequence
        __delay_ms(20);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_8BIT_MODE_2LINE);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_CLEAR);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_RETURN_HOME);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_ENTRY_MODE_SET);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_DISPLAY_ON_CURSOR_OFF);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_4BIT_MODE_2LINE);
        error_state &= chr_lcd_4bit_send_command(chr_lcd, 0x80);
    }
    return error_state ;
}
/**
 * @breif function to send command to 4 bit lcd 
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @param command value of the command need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_command(const chr_lcd_4bit_t *chr_lcd, uint8 command){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        // Set RS to LOW for command mode
        error_state &= gpio_pin_write_logic(&(chr_lcd->lcd_rs), LOW);
        /* send high 4 bits of command */
        error_state &= lcd_send_4bits(chr_lcd , (command >> 4)); 
        /* enable */
        error_state &= lcd_4bit_send_enable_signal(chr_lcd);
        /* send low 4 bits of command */
        error_state &= lcd_send_4bits(chr_lcd , command);
        /* enable */
        error_state &= lcd_4bit_send_enable_signal(chr_lcd);
    }
    return error_state ;
}
/**
 * @breif function to send data to 4 bit lcd 
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @param command value of the data need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_char_data(const chr_lcd_4bit_t *chr_lcd, uint8 data){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        // Set RS to High for command mode
        error_state &= gpio_pin_write_logic(&(chr_lcd->lcd_rs), HIGH);
        /* send high 4 bits of command */
        error_state &= lcd_send_4bits(chr_lcd , (data >> 4)); 
        /* enable */
        error_state &= lcd_4bit_send_enable_signal(chr_lcd);
        /* send low 4 bits of command */
        error_state &= lcd_send_4bits(chr_lcd , data);
        /* enable */
        error_state &= lcd_4bit_send_enable_signal(chr_lcd);
    }
    return error_state ;
}
/**
 * @breif function to send data at position in 4 bit mode 
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @param row     row index
 * @param column  column index
 * @param data    data to be send
 * @return STSD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_char_data_position(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , uint8 data ){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= lcd_4bit_set_cursor_position(chr_lcd , row , column);
        error_state &= chr_lcd_4bit_send_char_data(chr_lcd , data);
    }
    return error_state ;
}
/**
 * @breif function to send string to lcd in 4 bit mode
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @param str pointer to string to be send to lcd
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_string_data(const chr_lcd_4bit_t *chr_lcd, uint8* str){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        while(*str){
            error_state &= chr_lcd_4bit_send_char_data(chr_lcd , *str++);
        }
    }
    return error_state ;
}
/**
 * @breif function to send string data to lcd in 4 bit mode
 * @param chr_lcd pointer to 4 bit char lcd pin configuration @ref chr_lcd_4bit_t
 * @param row row index
 * @param column column index
 * @param str pointer to string need to send to lcd
 * @return STSD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_string_data_position(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , uint8* str ){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= lcd_4bit_set_cursor_position(chr_lcd , row ,column);
        while(*str){
            error_state &= chr_lcd_4bit_send_char_data(chr_lcd , *str++);
        }
    }
    return error_state ;
}
/**
 * @breif function to send a custom character to lcd in 4 bit mode 
 * @param chr_lcd pointer to configuration of the lcd @ref chr_lcd_4bit_t
 * @param row row index
 * @param column column index
 * @param _chr the custom character need to send to lcd
 * @param mem_pos position of the character in CGRAM
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_4bit_send_custom_char(const chr_lcd_4bit_t *chr_lcd , uint8 row , uint8 column , const uint8 _chr[] , uint8 mem_pos){
    STD_ReturnType error_state = E_OK ;
    uint8 l_character_counter = ZERO_INIT ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= chr_lcd_4bit_send_command(chr_lcd, _LCD_CGRAM_START +(8*mem_pos));
        for(l_character_counter = ZERO_INIT ; l_character_counter<=7 ;++l_character_counter){
            error_state &= chr_lcd_4bit_send_char_data(chr_lcd , _chr[l_character_counter] );
        }
        error_state &= chr_lcd_4bit_send_char_data_position(chr_lcd , row , column ,mem_pos);
    }
    return error_state ;
}
/*************************** character lcd 8bits software interface ***************************/
/**
 * @breif function to initialize character lcd 8 bit mode
 * @param chr_lcd pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_initialize(const chr_lcd_8bit_t *chr_lcd){
    STD_ReturnType error_state = E_OK ;
    uint8 l_data_pin_counter = ZERO_INIT ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= gpio_pin_init(&(chr_lcd->lcd_en));
        error_state &= gpio_pin_init(&(chr_lcd->lcd_rs));
        for(l_data_pin_counter = ZERO_INIT ; l_data_pin_counter<8 ; l_data_pin_counter ++){
            error_state &= gpio_pin_init(&(chr_lcd->lcd_data[l_data_pin_counter]));
        }
        __delay_ms(20);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_8BIT_MODE_2LINE);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_CLEAR);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_RETURN_HOME);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_ENTRY_MODE_SET);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_DISPLAY_ON_CURSOR_OFF);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_8BIT_MODE_2LINE);
        error_state &= chr_lcd_8bit_send_command(chr_lcd , _LCD_CGRAM_START);
    }
    return error_state ;
}
/**
 * @breif function to send command to 8 bit lcd 
 * @param chr_lcd pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t
 * @param command value of the command need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_command(const chr_lcd_8bit_t *chr_lcd, uint8 command){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        /* write 0 in RS bit to send command */
        error_state &= gpio_pin_write_logic(&(chr_lcd->lcd_rs),LOW);
        /* send 8 bit command */
        error_state &= lcd_send_8bits(chr_lcd , command);
        /* send 8 bit enable signal */
        error_state &= lcd_8bit_send_enable_signal(chr_lcd);
    }
    return error_state ;
}
/**
 * @breif function to send data to 8 bit lcd 
 * @param chr_lcd pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t
 * @param command value of the data need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_char_data(const chr_lcd_8bit_t *chr_lcd, uint8 data){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        
        /* write 1 in RS bit to send data */
        error_state &= gpio_pin_write_logic(&(chr_lcd->lcd_rs),HIGH);
        /* send 8 bit command */
        error_state &= lcd_send_8bits(chr_lcd , data);
        /* send 8 bit enable signal */
        error_state &= lcd_8bit_send_enable_signal(chr_lcd);
    }
    return error_state ;
}
/**
 * @breif function to send char data at position 8 bit 
 * @param chr_lcd   pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t 
 * @param row       row number 
 * @param column    column number 
 * @param data      data to be send to lcd
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_char_data_position(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , uint8 data ){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= lcd_8bit_set_cursor_position(chr_lcd , row , column);
        error_state &= chr_lcd_8bit_send_char_data(chr_lcd , data);
    }
    return error_state ;
}
/**
 * @breif function to send string to 8 bit lcd 
 * @param chr_lcd pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t 
 * @param str pointer to the string need to be send 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_string_data(const chr_lcd_8bit_t *chr_lcd, uint8* str){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        while(*str){
            error_state &= chr_lcd_8bit_send_char_data(chr_lcd, *str++);
        }
    }
    return error_state ;
}
/**
 * @breif function to send string to 8 bit lcd at position 
 * @param chr_lcd pointer to 8 bit char lcd pin configuration @ref chr_lcd_8bit_t 
 * @param row     row index
 * @param column  column index
 * @param str     pointer to the string need to be send 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_string_data_position(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , uint8* str ){
    STD_ReturnType error_state = E_OK ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= lcd_8bit_set_cursor_position(chr_lcd , row , column);
        error_state &= chr_lcd_8bit_send_string_data(chr_lcd , str);
    }
    return error_state ;
}
/**
 * @breif function to send a custom character to lcd in 8 bit mode 
 * @param chr_lcd pointer to configuration of the lcd @ref chr_lcd_8bit_t
 * @param row row index
 * @param column column index
 * @param _chr the custom character need to send to lcd
 * @param mem_pos position of the character in CGRAM
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType chr_lcd_8bit_send_custom_char(const chr_lcd_8bit_t *chr_lcd , uint8 row , uint8 column , const uint8 _chr[] , uint8 mem_pos){
    STD_ReturnType error_state = E_OK ;
    uint8 l_character_counter = ZERO_INIT ;
    if(chr_lcd == NULL){
        error_state = E_NOT_OK ;
    }
    else{
        error_state &= chr_lcd_8bit_send_command(chr_lcd, _LCD_CGRAM_START +(8*mem_pos));
        for(l_character_counter = ZERO_INIT ; l_character_counter<8 ;l_character_counter++){
            error_state &= chr_lcd_8bit_send_char_data(chr_lcd , _chr[l_character_counter] );
        }
        error_state &= chr_lcd_8bit_send_char_data_position(chr_lcd , row , column ,mem_pos);
    }
    return error_state ;
}
/*************************** convert value to string ***************************/
STD_ReturnType convert_uint8_to_string(uint8 value , uint8 *str){
    STD_ReturnType error_state = E_OK ;
    if(NULL == str){
        error_state = E_NOT_OK ; 
    } 
    else{
        memset(str , '\0' , 4);
        sprintf(str , "%i" , value);
    }
    return error_state ; 
}
STD_ReturnType convert_uint16_to_string(uint16 value , uint8 *str){
    STD_ReturnType error_state = E_OK ;
    if(NULL == str){
        error_state = E_NOT_OK ; 
    } 
    else{
        memset(str , '\0' , 6);
        sprintf(str , "%i" , value);
    }
    return error_state ; 
}
STD_ReturnType convert_uint32_to_string(uint32 value , uint8 *str){
    STD_ReturnType error_state = E_OK ;
    if(NULL == str){
        error_state = E_NOT_OK ; 
    } 
    else{
        memset(str , '\0' , 11);
        sprintf(str , "%u" , value);
    }
    return error_state ; 
}
/*************************** static helper functions ***************************/
/* 4-bits */
static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd , uint8 _data_command){
    STD_ReturnType error_state = E_OK ; 
    error_state = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
    error_state = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
    error_state = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
    error_state = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
    return error_state ; 
}
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    STD_ReturnType error_state = E_OK ;
    error_state &= gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    error_state &= gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    return error_state ; 
}
static STD_ReturnType lcd_4bit_set_cursor_position(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column){
    STD_ReturnType error_state = E_OK ; 
    column -- ;
    switch (row){
        case ROW1: chr_lcd_4bit_send_command(lcd , (0x80 + column)); break ;
        case ROW2: chr_lcd_4bit_send_command(lcd , (0xc0 + column)); break ;
        case ROW3: chr_lcd_4bit_send_command(lcd , (0x94 + column)); break ;
        case ROW4: chr_lcd_4bit_send_command(lcd , (0xd4 + column)); break ;
        default : error_state = E_NOT_OK ;   
    }
    return error_state ;
}
/* 8-bits */
static STD_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *lcd , uint8 _data_command){
    STD_ReturnType error_state = E_OK ; 
    uint8 l_pin_counter  = ZERO_INIT ;
    for(l_pin_counter = ZERO_INIT ; l_pin_counter<8 ; l_pin_counter ++){
        error_state &= gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]) ,
                                             (_data_command >> l_pin_counter) & BIT_MASK);
    }
    return error_state ; 
}
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    STD_ReturnType error_state = E_OK ;
    error_state &= gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    error_state &= gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    return error_state ; 
}
static STD_ReturnType lcd_8bit_set_cursor_position(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column){
    STD_ReturnType error_state = E_OK ; 
    column -- ;
    switch (row){
        case ROW1: chr_lcd_8bit_send_command(lcd , (0x80 + column)); break ;
        case ROW2: chr_lcd_8bit_send_command(lcd , (0xc0 + column)); break ;
        case ROW3: chr_lcd_8bit_send_command(lcd , (0x94 + column)); break ;
        case ROW4: chr_lcd_8bit_send_command(lcd , (0xd4 + column)); break ;
        default : error_state = E_NOT_OK ;   
    }
    return error_state ;
}