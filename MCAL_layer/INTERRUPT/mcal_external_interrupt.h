/* 
 * File:   mcal_external_interrupt.h
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:05 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*************************** section : includes ***************************/
#include "mcal_interrupt_config.h"
/*************************** section : Macro definitions ***************************/

/*************************** section : Macro functions definitions ***************************/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable INT0 interrupt */
#define EXT_INT0_InterruptEnable()          (INTCONbits.INT0IE = 1)
#define EXT_INT0_InterruptDisable()         (INTCONbits.INT0IE = 0)
/* macro function to clear INT0 interrupt flag */
#define EXT_INT0_InterruptFlagClear()       (INTCONbits.INT0IF = 0)
/* macro function  to select edge for INT0 */
#define EXT_INT0_RisingEdge()               (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdge()              (INTCON2bits.INTEDG0 = 0)
/* macro functions to enable and disable INT1 interrupt */
#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1E = 1)
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1E = 0)
/* macro function to clear INT1 interrupt flag */
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1F = 0)
/* macro function  to select edge for INT1 */
#define EXT_INT1_RisingEdge()               (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdge()              (INTCON2bits.INTEDG1 = 0)
/* macro functions to enable and disable INT2 interrupt */
#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2E = 1)
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2E = 0)
/* macro function to clear INT2 interrupt flag */
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2F = 0)
/* macro function  to select edge for INT2 */
#define EXT_INT2_RisingEdge()               (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdge()              (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* priority set for INTx */
/* INT0 is fixed high priority */
/* macro function  to set the priority level for INT1 */
#define EXT_INT1_HighPrioritySet()          (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPrioritySet()           (INTCON3bits.INT1IP = 0)
/* macro function  to set the priority level for INT2 */
#define EXT_INT2_HighPrioritySet()          (INTCON3bits.INT2IP = 1)
#define EXT_INT2_LowPrioritySet()           (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function to enable or disable port change interrupt */
#define EXT_RBx_InterruptEnable()           (INTCONbits.RBIE = 1)
#define EXT_RBx_InterruptDisable()          (INTCONbits.RBIE = 0)
/* macro function to clear port change interrupt flag */
#define EXT_RBx_InterruptFlagClear()        (INTCONbits.RBIF = 0)
/* macro functions to select port change interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define EXT_RBx_HighPrioritySet()           (INTCON2bits.RBIP = 1)
#define EXT_RBx_LowPrioritySet()            (INTCON2bits.RBIP = 0)
#endif

#endif
/*************************** section : Data type declaration ***************************/
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXT_INT0 = 0,
    INTERRUPT_EXT_INT1,
    INTERRUPT_EXT_INT2
}interrupt_INTx_src;

typedef struct{
    void (*EXT_InterruptHandler)(void);
    pin_config_t intx_pin ;
    interrupt_INTx_src source;
    interrupt_INTx_edge edge ; 
    interrupt_priority_cfg priority ;
}interrupt_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_High)(void);
    void (*EXT_InterruptHandler_Low)(void);
    pin_config_t rbx_pin ;
    interrupt_priority_cfg priority ;
}interrupt_RBx_t;
        
/*************************** section : functions declarations ***************************/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif function to initialize an external interrupt for of INTx type 
 * @param int_obj external interrupt object to initialize @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
/**
 * @breif function to de-initialize an external interrupt of INTx type 
 * @param int_obj external interrupt object to initialize @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
#endif
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif function to initialize an external interrupt of RBx type "On Change"
 * @param int_obj external interrupt object to initialize @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
/**
 * @breif function to de-initialize an external interrupt of RBx type "On Change"
 * @param int_obj external interrupt object to initialize @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);
#endif
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

