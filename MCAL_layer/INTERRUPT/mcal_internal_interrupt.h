/* 
 * File:   mcal_internal_interrupt.h
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:04 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* section : includes */
#include "mcal_interrupt_config.h"
/* section : Macro definitions */

/* section : Macro functions definitions */

/*-------------- TIMER0 Interrupt Configuration Start --------------*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable Timer0 interrupt */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE= 1)
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* macro function to clear Timer0 interrupt flag */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF =0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for Timer0 */
#define TIMER0_HighPrioritySet()          (INTCON2bits.TMR0IP = 1)
#define TIMER0_LowPrioritySet()           (INTCON2bits.TMR0IP = 0)
#endif
#endif
/*-------------- TIMER0 Interrupt Configuration end --------------*/

/*-------------- TIMER1 Interrupt Configuration Start --------------*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable Timer1 interrupt */
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE =  1)
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE =  0)
/* macro function to clear Timer1 interrupt flag */
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for Timer1 */
#define TIMER1_HighPrioritySet()          (IPR1bits.TMR1IP = 1)
#define TIMER1_LowPrioritySet()           (IPR1bits.TMR1IP = 0)
#endif
#endif
/*-------------- TIMER1 Interrupt Configuration end --------------*/

/*-------------- TIMER2 Interrupt Configuration Start --------------*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable Timer2 interrupt */
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE =  1)
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE =  0)
/* macro function to clear Timer2 interrupt flag */
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for Timer2 */
#define TIMER2_HighPrioritySet()          (IPR1bits.TMR2IP = 1)
#define TIMER2_LowPrioritySet()           (IPR1bits.TMR2IP = 0)
#endif
#endif
/*-------------- TIMER2 Interrupt Configuration end --------------*/

/*-------------- TIMER3 Interrupt Configuration Start --------------*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable Timer3 interrupt */
#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE =  1)
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE =  0)
/* macro function to clear Timer3 interrupt flag */
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for Timer2 */
#define TIMER3_HighPrioritySet()          (IPR2bits.TMR3IP = 1)
#define TIMER3_LowPrioritySet()           (IPR2bits.TMR3IP = 0)
#endif
#endif
/*-------------- TIMER2 Interrupt Configuration end --------------*/

/*-------------- ADC Interrupt Configuration Start --------------*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable ADC interrupt */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* macro function to clear ADC interrupt flag */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF =0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for ADC */
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)
#endif
#endif
/*-------------- ADC Interrupt Configuration End --------------*/

/*-------------- CCP1 Interrupt Configuration Start --------------*/
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable CCP1 interrupt */
#define CCP1_InterruptEnable()          (PIE1bits.CCP1IE = 1)
#define CCP1_InterruptDisable()         (PIE1bits.CCP1IE = 0)
/* macro function to clear CCP1 interrupt flag */
#define CCP1_InterruptFlagClear()       (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for CCP1 */
#define CCP1_HighPrioritySet()          (IPR1bits.CCP1IP = 1)
#define CCP1_LowPrioritySet()           (IPR1bits.CCP1IP = 0)
#endif
#endif
/*-------------- CCP1 Interrupt Configuration End --------------*/

/*-------------- CCP2 Interrupt Configuration Start ------------*/
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable CCP2 interrupt */
#define CCP2_InterruptEnable()          (PIE2bits.CCP2IE = 1)
#define CCP2_InterruptDisable()         (PIE2bits.CCP2IE = 0)
/* macro function to clear CCP2 interrupt flag */
#define CCP2_InterruptFlagClear()       (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for CCP2 */
#define CCP2_HighPrioritySet()          (IPR2bits.CCP2IP = 1)
#define CCP2_LowPrioritySet()           (IPR2bits.CCP2IP = 0)
#endif
#endif
/*-------------- CCP2 Interrupt Configuration End --------------*/

/*-------------- EUSART ASYNC (TX) Interrupt Configuration Start ------------*/
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable EUSART(TX) interrupt */
#define EUSART_ASYNC_TX_InterruptEnable()          (PIE1bits.TXIE = 1)
#define EUSART_ASYNC_TX_InterruptDisable()         (PIE1bits.TXIE = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for EUSART(TX) */
#define EUSART_ASYNC_TX_HighPrioritySet()          (IPR1bits.TXIP = 1)
#define EUSART_ASYNC_TX_LowPrioritySet()           (IPR1bits.TXIP = 0)
#endif
#endif
/*-------------- EUSART ASYNC (TX) Interrupt Configuration End --------------*/
/*-------------- EUSART ASYNC (RX) Interrupt Configuration Start ------------*/
#if EUSART_ASYNC_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable EUSART(RX) interrupt */
#define EUSART_ASYNC_RX_InterruptEnable()          (PIE1bits.RCIE = 1)
#define EUSART_ASYNC_RX_InterruptDisable()         (PIE1bits.RCIE = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for EUSART(RX) */
#define EUSART_ASYNC_RX_HighPrioritySet()          (IPR1bits.RCIP = 1)
#define EUSART_ASYNC_RX_LowPrioritySet()           (IPR1bits.RCIP = 0)
#endif
#endif
/*-------------- EUSART ASYNC (RX) Interrupt Configuration End --------------*/

/*-------------- MSSP I2C Interrupt Configuration Start ------------*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro functions to enable and disable MSSP I2C interrupt */
#define MSSP_I2C_InterruptEnable()                     (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()          (PIE2bits.BCLIE = 1)
#define MSSP_I2C_InterruptDisable()                    (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable()         (PIE2bits.BCLIE = 0)
/* macro function to clear MSSP I2C interrupt flag */
#define MSSP_I2C_InterruptFlagClear()                    (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear()         (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* macro function  to set the priority level for MSSP I2C */
#define MSSP_I2C_HighPrioritySet()                     (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()          (IPR2bits.BCLIP = 1)
#define MSSP_I2C_LowPrioritySet()                      (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()           (IPR2bits.BCLIP = 0)
#endif
#endif
/*-------------- MSSP I2C Interrupt Configuration End --------------*/

/* section : Data type declaration */

/* section : functions declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

