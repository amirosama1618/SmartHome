/* 
 * File:   mcal_gpio.c
 * Author: Amir osama amir 
 *
 * Created on January 30, 2024, 3:20 PM
 * last update feb 2, 2024 
 */
#include "mcal_gpio.h"

/* reference to the data of direction control registers */
volatile uint8 *tris_regs[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/* reference to the data of Latch registers */
volatile uint8 *lat_regs[] = {&LATA,&LATB,&LATC,&LATD,&LATE};
/* reference to the port registers status */
volatile uint8 *port_regs[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/**
 * @breif function to initialize pin direction  @ref  direction_t
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config){
    STD_ReturnType error_state = E_OK ;
    if(NULL == _pin_config ){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(_pin_config->direction){
            case    OUTPUT :
                CLEAR_BIT(*tris_regs[_pin_config->port],_pin_config->pin);
                break ;
            case    INPUT :
                SET_BIT(*tris_regs[_pin_config->port],_pin_config->pin);
                break ;
            default: error_state = E_NOT_OK ;
        }
    }
    return error_state ; 
}
/**
 * @breif function to read the direction status for specific pin @ref  direction_t
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @param direction_status pointer to direction of the pin @ref  direction_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status){
    STD_ReturnType error_state = E_OK ;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(READ_BIT(*tris_regs[_pin_config->port],_pin_config->pin)){
            case OUTPUT :
                *direction_status = OUTPUT ; 
                break ;
            case INPUT :
                *direction_status = INPUT ;
                break ;
            default : error_state = E_NOT_OK ;
        }  
    }
    return error_state ;
}
/**
 * @breif function to write a logic in a specific pin @ref logic_t
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @param logic @ref logic_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    STD_ReturnType error_state = E_OK ;
    if(NULL == _pin_config ){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(logic){
            case    LOW :
                CLEAR_BIT(*lat_regs[_pin_config->port],_pin_config->pin) ;
                break ;
            case    HIGH :
                SET_BIT(*lat_regs[_pin_config->port],_pin_config->pin) ;
                break ;
            default : error_state = E_NOT_OK ; 
        }
    }
    return error_state ;
}
/**
 * @breif function to read the logic of specific pin @ref logic_t
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @param logic @ref logic_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    STD_ReturnType error_state = E_OK ;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(READ_BIT(*port_regs[_pin_config->port],_pin_config->pin)){
            case LOW :
                *logic = LOW ; 
                break ;
            case HIGH :
                *logic = HIGH ;
                break ;
            default : error_state = E_NOT_OK ;
        }
        }
    return error_state ;
}
/**
 * @breif function to toggle the logic of specific pin @ref logic_t
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
     STD_ReturnType error_state = E_OK ;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER){
        error_state = E_NOT_OK ; 
    }
    else{
        TOGGLE_BIT(*lat_regs[_pin_config->port],_pin_config->pin);
        }
    return error_state ;
}
/**
 * @breif function to initialize pin direction and logic 
 * @param _pin_config pointer to configurations @ref pin_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_pin_init(const pin_config_t *_pin_config){
    STD_ReturnType error_state = E_OK ; 
    if(NULL == _pin_config ){
        error_state = E_NOT_OK ;
    }
    else{
        error_state = gpio_pin_direction_init(_pin_config) ; 
        error_state = gpio_pin_write_logic(_pin_config,_pin_config->logic) ;
    }
    return error_state ; 
}
/*********************************************************************************/
/**
 * @breif function to initialize the whole port direction 
 * @param port : parameter to select the port @ref port_index_t
 * @param direction : parameter to select the port direction 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_port_direction_init(port_index_t port , direction_t direction){
    STD_ReturnType error_state = E_OK ; 
    if(port > PORT_MAX_NUMBER){
        error_state = E_NOT_OK ;
    }
    else{
        *tris_regs[port] = direction ; 
        }
    return error_state ; 
}
/**
 * @breif function to read the whole port directions 
 * @param port : parameter to select the port @ref port_index_t
 * @param dic_status : pointer to the direction status of the port 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_port_get_direction_status(port_index_t port , direction_t *dic_status){
    STD_ReturnType error_state = E_OK ; 
    if(port > PORT_MAX_NUMBER || NULL == dic_status){
        error_state = E_NOT_OK ; 
    }
    else{
        *dic_status = *tris_regs[port] ; 
    }
    return error_state ; 
}
/**
 * @breif function to write a logic to the whole port 
 * @param port : parameter to select the port @ref port_index_t
 * @param logic : parameter to select the logic to be writen in the port  
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_port_write_logic(port_index_t port,logic_t logic){
    STD_ReturnType error_state = E_OK ; 
    if(port > PORT_MAX_NUMBER ){
        error_state = E_NOT_OK ; 
    }
    else{
        if(logic == HIGH){
            *lat_regs[port] = 0xff ; 
        }
        else{
            *lat_regs[port] = 0x00 ; 
        }
    }
    return error_state ; 
}
/**
 * @breif function to read the logic writen in the port
 * @param port : parameter to select the port @ref port_index_t
 * @param logic : pointer to the logic of the port 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_port_read_logic(port_index_t port,logic_t *logic){
    STD_ReturnType error_state = E_OK ; 
    if( port > PORT_MAX_NUMBER || NULL == logic){
        error_state = E_NOT_OK ; 
    }
    else{
        *logic = *lat_regs[port] ; 
    }
    return error_state ; 
}
/**
 * @breif function to toggle the logic of the port
 * @param port : parameter to select the port @ref port_index_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType gpio_port_toggle_logic(port_index_t port){
    STD_ReturnType error_state = E_OK ; 
    if( port > PORT_MAX_NUMBER){
        error_state = E_NOT_OK ; 
    }
    else{
        *lat_regs[port] ^= PORT_MASK ; 
    }
    return error_state ;
}