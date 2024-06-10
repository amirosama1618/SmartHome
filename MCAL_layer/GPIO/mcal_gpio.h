/* 
 * File:   mcal_gpio.h
 * Author: Ameer
 *
 * Created on January 30, 2024, 3:20 PM
 */

#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H

/* section : includes */
#include <pic18f4620.h>
#include <xc.h>
#include "../mcal_std_types.h"
#include "../../MCAL_layer/device_config.h"

/* section : Macro definitions */
#define BIT_MASK            (uint8)1
#define PORT_PIN_MAX_NUMBER     7
#define PORT_MAX_NUMBER         4
#define PORT_MASK               0xff
/* section : Macro functions definitions */
#define HWREG(_x)       (*((volatile uint8*)(_x)))

#define SET_BIT(REG,BIT_POSN)         (REG |= (BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)       (REG &=~(BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)      (REG ^= (BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)        ((REG >> BIT_POSN) & BIT_MASK)  

/* section : Data type declaration */
typedef enum{
    LOW,
    HIGH
}logic_t;

typedef enum{
    OUTPUT,
    INPUT
}direction_t;

typedef enum{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX    
}  port_index_t;


typedef struct{
    uint8 port      :3;     /*@ref  port_index_t */
    uint8 pin       :3;     /*@ref  pin_index_t */
    uint8 direction :1;     /*@ref  direction_t */
    uint8 logic     :1;     /*@ref  logic_t */
}pin_config_t;

/* section : functions declarations */
STD_ReturnType gpio_pin_direction_init(const pin_config_t *_pin_config);
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
STD_ReturnType gpio_pin_init(const pin_config_t *_pin_config);

STD_ReturnType gpio_port_direction_init(port_index_t port , direction_t direction);
STD_ReturnType gpio_port_get_direction_status(port_index_t port , direction_t *dic_status);
STD_ReturnType gpio_port_write_logic(port_index_t port ,logic_t logic);
STD_ReturnType gpio_port_read_logic(port_index_t port ,logic_t *logic);
STD_ReturnType gpio_port_toggle_logic(port_index_t port );

#endif	/* MCAL_GPIO_H */

