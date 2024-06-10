/* 
 * File:   mcal_interrupt_manager.c
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:05 AM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1,
                      RB5_flag = 1,
                      RB6_flag = 1,
                      RB7_flag = 1; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*================================ interrupt High Priority ================================*/
void __interrupt() InterruptManagerHigh(void){

}
/*================================ interrupt Low Priority ================================*/
void __interrupt(low_priority) InterruptManagerLow(void){

}
#else
void __interrupt() InterruptManager(void){
/*================================ TIMER0 Internal interrupt Start ================================*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TIMER0_ISR();
    }
    else{/* nothing */}
#endif
/*================================ ADC Internal interrupt end ================================*/

/*================================ ADC Internal interrupt Start ================================*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.ADIE ) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/* nothing */}
#endif
/*================================ ADC Internal interrupt end ================================*/
    
/*================================ EUSART ASYNC Internal interrupt Start ================================*/  
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE ==  PIE1bits.TXIE ) && (INTERRUPT_OCCUR ==  PIE1bits.TXIE)){
        EUSART_ASYNC_TX_ISR();
    }
    else{/* nothing */}
#endif
#if EUSART_ASYNC_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE ==  PIE1bits.RCIE ) && (INTERRUPT_OCCUR ==  PIR1bits.RCIF)){
        EUSART_ASYNC_RX_ISR();
    }
    else{/* nothing */}
#endif
/*================================ EUSART ASYNC Internal interrupt End ================================*/ 
    
}
#endif