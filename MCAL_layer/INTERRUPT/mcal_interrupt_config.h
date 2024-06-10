/* 
 * File:   mcal_interrupt_config.h
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:03 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/************************** section : includes **************************/
#include "pic18f4620.h"
#include "../GPIO/mcal_gpio.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_config.h"
/************************** section : Macro definitions **************************/
#define INTERRUPT_ENABLE         1
#define INTERRUPT_DISABLE        0
#define INTERRUPT_OCCUR          1
#define INTERRUPT_NOT_OCCUR      0
#define INTERRUPT_FLAG_ENABLE    1
#define INTERRUPT_FLAG_DISABLE   0

/************************** section : Macro functions definitions **************************/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this macro function will enable the priority interrupt feature */
#define INTERRUPT_PriorityLevelsEnable()             (RCONbits.IPEN = 1)
/* this macro function will disable the priority interrupt feature */
#define INTERRUPT_PriorityLevelsDisable()            (RCONbits.IPEN = 0)

/* this macro function will enable global high priority interrupts */
#define INTERRUPT_GlobalInterruptHighEnable()        (INTCONbits.GIEH = 1)
/* this macro function will disable global high priority interrupts */
#define INTERRUPT_GlobalInterruptHighDisable()       (INTCONbits.GIEH = 0)

/* this macro function will enable global low priority interrupts */
#define INTERRUPT_GlobalInterruptLowEnable()         (INTCONbits.GIEL = 1)
/* this macro function will disable global low priority interrupts */
#define INTERRUPT_GlobalInterruptLowDisable()        (INTCONbits.GIEL = 0)
#else
/* this macro function will enable global  interrupts */
#define INTERRUPT_GlobalInterruptEnable()            (INTCONbits.GIE = 1)
/* this macro function will disable global  interrupts */
#define INTERRUPT_GlobalInterruptDisable()           (INTCONbits.GIE = 0)
/* this macro function will enable prephral interrupts */
#define INTERRUPT_PrephralInterruptEnable()         (INTCONbits.PEIE = 1)
/* this macro function will disable prephral interrupts */
#define INTERRUPT_PrephralInterruptDisable()        (INTCONbits.PEIE = 0)
#endif
/************************** section : Data type declaration **************************/ 
typedef void(*InterruptHandler)(void);
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;
/************************** section : functions declarations **************************/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

