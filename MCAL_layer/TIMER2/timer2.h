/* 
 * File:   timer2.h
 * Author: Ameer
 *
 * Created on March 7, 2024, 2:48 AM
 */

#ifndef TIMER2_H
#define	TIMER2_H
/*================================ section : includes ================================*/
#include "pic18f4620.h"
#include "../../MCAL_layer/compiler.h"
#include "../../MCAL_layer/device_config.h"
#include "../../MCAL_layer/std_libraries.h"
#include "../../MCAL_layer/mcal_std_types.h"

#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/*================================ section : Macro definitions ================================*/

/*================================ section : Macro functions definitions ================================*/
/**
 * @breif   T2CON: TIMER2 CONTROL REGISTER
 * @note    controls all aspects of the modules operation, including the 
 *          pre-scale selection. It is both readable and writable
 */

/**
 * TMR2ON: Timer2 On/Off Control bit  
 * 1 = Enables Timer2 
 * 0 = Stops Timer2
 */
#define TIMER2_ENABLE()             (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()            (T2CONbits.TMR2ON = 0)
/**
 * T2OUTPS3:T2OUTPS0: Timer2 Output Postscale Select bits
 */
#define TIMER2_POSTSCALER_SELECT(_CONFIG)       (T2CONbits.TOUTPS = _CONFIG)
/**
 * T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
 */
#define TIMER2_PRESCALER_SELECT(_CONFIG)       (T2CONbits.T2CKPS = _CONFIG)
/*================================ section : Data type declaration ================================*/
typedef enum{
    TIMER2_PRESCALER_DIV_1 = 0 , 
    TIMER2_PRESCALER_DIV_4,
    TIMER2_PRESCALER_DIV_16
}timer2_prescaler_select_t;

typedef enum{
    TIMER2_POSTSCALER_DIV_1 = 0 , 
    TIMER2_POSTSCALER_DIV_2,
    TIMER2_POSTSCALER_DIV_3,
    TIMER2_POSTSCALER_DIV_4,
    TIMER2_POSTSCALER_DIV_5,       
    TIMER2_POSTSCALER_DIV_6,
    TIMER2_POSTSCALER_DIV_7,
    TIMER2_POSTSCALER_DIV_8,
    TIMER2_POSTSCALER_DIV_9,
    TIMER2_POSTSCALER_DIV_10,
    TIMER2_POSTSCALER_DIV_11,
    TIMER2_POSTSCALER_DIV_12,
    TIMER2_POSTSCALER_DIV_13,
    TIMER2_POSTSCALER_DIV_14,       
    TIMER2_POSTSCALER_DIV_15,
    TIMER2_POSTSCALER_DIV_16
}timer2_postscaler_select_t;

typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*Timer2Interrupt)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg timer2_priority ; 
#endif
#endif
    uint8 timer2_preload_value  ;
    uint8 timer2_postscaler_value   :4 ; 
    uint8 timer2_prescaler_value    : 2;
    uint8 timer2_reserved              :2 ; 
} timer2_config_t;
/*================================ section : functions declarations ================================*/
/**
 * @breif function to initialize Timer2 Module 
 * @preconditions None
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Init(const timer2_config_t *timer2);
/**
 * @breif function to De-Initialize Timer2
 * @preconditions None
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_DeInit(const timer2_config_t *timer2);
/**
 * @breif function to read the value of Timer2 register 
 * @preconditions Timer2_Init() must called before 
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @param read_value pointer to the value need to be read 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Read_Value(const timer2_config_t *timer2, uint8 *read_value);
/**
 * @breif function to read the value of Timer2 register 
 * @preconditions Timer2_Init() must called before 
 * @param timer2 pointer to Timer2 configuration data type @ref timer2_config_t
 * @param _value pointer to the value need to be Written 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Timer2_Write_Value(const timer2_config_t *timer2, uint8  _value);

#endif	/* TIMER2_H */

