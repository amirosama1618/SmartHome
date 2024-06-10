/* 
 * File:   mcal_interrupt_manager.h
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:05 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* section : includes */
#include "mcal_interrupt_config.h"
/* section : Macro definitions */

/* section : Macro functions definitions */

/* section : Data type declaration */

/* section : functions declarations */



void ADC_ISR(void);
void TIMER0_ISR(void) ;

void EUSART_ASYNC_TX_ISR(void);
void EUSART_ASYNC_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

