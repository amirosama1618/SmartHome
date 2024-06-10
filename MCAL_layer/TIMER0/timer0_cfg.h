/* 
 * File:   timer0_cfg.h
 * Author: Ameer
 *
 * Created on March 4, 2024, 12:38 AM
 */

#ifndef TIMER0_CFG_H
#define	TIMER0_CFG_H

/*================================ section : includes ================================*/
#include "timer0.h"
/*================================ section : Macro definitions ================================*/
#define TIMER0_FEATURE_ENABLE       1
#define TIMER0_FEATURE_DISABLE      0
/**
 * macro to select if Timer0 will use Interrupt or pooling technique on overflow
 * TIMER0_FEATURE_ENABLE : Timer0 will fire interrupt on over flow 
 * TIMER0_FEATURE_DISABLE :Timer0 will use pooling pooling technique on over flow
 */
#define TIMER0_INTERRUPT_OVERFLOW_FEATURE       TIMER0_FEATURE_ENABLE


/*================================ section : Data type declaration ================================*/

/*================================ section : functions declarations ================================*/

#endif	/* TIMER0_CFG_H */

