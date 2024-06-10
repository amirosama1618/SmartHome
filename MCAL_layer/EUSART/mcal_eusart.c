/* 
 * File:   mcal_eusart.c
 * Author: Ameer
 *
 * Created on March 16, 2024, 5:03 PM
 */

/*========================= section : includes ==================================*/
#include "mcal_eusart.h"
/*========================= section : Global Variables ==========================*/
#if (EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) 
InterruptHandler EUSART_ASYNC_TX_InterruptHandler = NULL ;
#endif
#if (EUSART_ASYNC_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
InterruptHandler EUSART_ASYNC_RX_InterruptHandler = NULL ;
static void(* EUSART_ASYNC_FramingErrorHandler)(void) = NULL  ;
static void(* EUSART_ASYNC_OverRunErrorHandler)(void) = NULL  ;
#endif
/*========================= section : Static Helper Functions declaration =======*/
static inline void eusart_async_baudrate_calculation(const usart_async_t * _eusart);
static inline void eusart_async_tx_configure(const usart_async_t * _eusart);
static inline void eusart_async_rx_configure(const usart_async_t * _eusart);
/*========================= section : Macro functions definitions ===============*/

/*========================= section : Data type declaration =====================*/

/*========================= section : functions Implementation ==================*/
/**
 * @breif function to Initialize the EUSART modeule 
 * @param _eusart pointer to EUSART object configurations 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_Init(const usart_async_t * _eusart){
    STD_ReturnType error_state  = E_NOT_OK  ;
    if(NULL == _eusart){
        error_state  = E_NOT_OK  ;
    }
    else{
        /* Disable EUSART Module */
        EUSART_DISABLE();
        TRISCbits.RC7 = 1 ; 
        TRISCbits.RC6 = 1 ; 
        /* Baud Rate calculations */
        eusart_async_baudrate_calculation (_eusart) ;
        /* TX Configurations */
        eusart_async_tx_configure(_eusart);
        /* RX Configurations */
        eusart_async_rx_configure(_eusart);
        /* Enable EUSART Module */
        EUSART_ENABLE();
        error_state  = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to De-Initialize the EUSART Module
 * @param _eusart  pointer to EUSART object configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_DeInit(const usart_async_t * _eusart){
    STD_ReturnType error_state  = E_NOT_OK  ;
    if(NULL == _eusart){
        error_state  = E_NOT_OK  ;
    }
    else{
        EUSART_DISABLE();
        EUSART_ASYNC_TX_InterruptDisable();
        EUSART_ASYNC_RX_InterruptDisable();
        error_state  = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to Read byte from the USART Module @note this function uses Blocking Technique
 * @param _eusart pointer to EUSART object configurations
 * @param _data pointer to return the Read data in 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 * _data){
    STD_ReturnType error_state  = E_NOT_OK  ;
    while(!PIR1bits.RCIF);
    *_data = RCREG ; 
    error_state  = E_OK  ;
    return error_state ; 
}

STD_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data){
    STD_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 * @breif function to Restart EUSART RX 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_RX_Restart(void){
    STD_ReturnType error_state  = E_NOT_OK  ;
    EUSART_ASYNC_RX_DISABLE();
    EUSART_ASYNC_RX_ENABLE();
    return error_state ; 
}
/**
 * @breif function to Write byte to the USART Module @note this function uses Blocking Technique
 * @param _eusart pointer to EUSART object configurations
 * @param data the data need to Write 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_WrireByteBlocking(uint8 data){
    STD_ReturnType error_state  = E_NOT_OK  ;
    while(!TXSTAbits.TRMT);
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_ASYNC_TX_InterruptEnable();
#endif
    TXREG = data ; 
    error_state  = E_OK  ;
    return error_state ; 
}
/**
 * @breif function to write( transmit ) string 
 * @param _eusartpointer to EUSART object configurations
 * @param data string need to be written 
 * @param str_len string length 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EUSART_ASYNC_WrireStringBlocking(uint8 *data , uint16 str_len){
    STD_ReturnType error_state  = E_NOT_OK  ;
    uint16 char_counter = ZERO_INIT ; 
    for(char_counter = ZERO_INIT ; char_counter < str_len ; char_counter++){
        EUSART_ASYNC_WrireByteBlocking(data[char_counter]);
    }
    error_state  = E_OK  ;
    return error_state ; 
}
/*========================= section : Static Helper Functions Implementation ======*/
static inline void eusart_async_baudrate_calculation(const usart_async_t * _eusart){
    float BRG_value = 0 ; 
    switch (_eusart->baudrate_gen_mode){
            case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
                TXSTAbits.   BRGH   = EUSART_ASYNCRONOUS_LOW_SPEED ; 
                BAUDCONbits.BRG16  = EUSART_8BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_ASYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/64)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                break ;
            case BAUDRATE_ASYNC_8BIT_HIGH_SPEED :
                TXSTAbits.   BRGH   = EUSART_ASYNCRONOUS_HIGH_SPEED ; 
                BAUDCONbits.BRG16  = EUSART_8BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_ASYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/16)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                break ;
            case BAUDRATE_ASYNC_16BIT_LOW_SPEED :
                TXSTAbits.   BRGH   = EUSART_ASYNCRONOUS_LOW_SPEED ; 
                BAUDCONbits.BRG16  = EUSART_16BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_ASYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/16)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                SPBRGH = (uint8)(((uint32)BRG_value)>>8) ; 
                break ;
            case BAUDRATE_ASYNC_16BIT_HIGH_SPEED :
                TXSTAbits.   BRGH   = EUSART_ASYNCRONOUS_HIGH_SPEED ; 
                BAUDCONbits.BRG16  = EUSART_16BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_ASYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/4)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                SPBRGH = (uint8)(((uint32)BRG_value)>>8) ;
                break ;
            case BAUDRATE_SYNC_8BIT :
                BAUDCONbits.BRG16  = EUSART_8BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_SYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/4)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                SPBRGH = (uint8)(((uint32)BRG_value)>>8) ;
                break ;
            case BAUDRATE_SYNC_16BIT :
                BAUDCONbits.BRG16  = EUSART_16BIT_BAUDRATE_GEN ; 
                TXSTAbits.   SYNC   = EUSART_SYNCRONOUS_MODE ; 
                BRG_value = ((_XTAL_FREQ/(float)(_eusart->baudrate))/4)-1 ; 
                SPBRG = (uint8)((uint32)BRG_value) ; 
                SPBRGH = (uint8)(((uint32)BRG_value)>>8) ;
                break ;
        default : /*nothing */ ; 
    }
}
static inline void eusart_async_tx_configure(const usart_async_t * _eusart){
    if(_eusart->tx_cfg.eusart_tx_enable == EUSART_ASYNCRONOUS_TX_DISABLE){
        EUSART_ASYNC_TX_DISABLE();
    }
    else if(_eusart->tx_cfg.eusart_tx_enable == EUSART_ASYNCRONOUS_TX_ENABLE){
        EUSART_ASYNC_TX_ENABLE();
        /* TX Interrupt configure */
        if(_eusart->tx_cfg.eusart_tx_interrupt_enable == EUSART_ASYNCRONOUS_INTERRUPT_TX_DISABLE){
            EUSART_ASYNC_TX_InterruptDisable();
        }
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        else if(_eusart->tx_cfg.eusart_tx_interrupt_enable == EUSART_ASYNCRONOUS_INTERRUPT_TX_ENABLE){
            /* Initialize the TX Interrupt Handler CallBack Function */
            EUSART_ASYNC_TX_InterruptHandler = _eusart->EUSART_TXDefaultInterruptHandler ; 
            /* TX Interrupt Priority Configure */
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            if(_eusart->tx_priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_ASYNC_TX_HighPrioritySet();
            }
            else if(_eusart->tx_priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_ASYNC_TX_LowPrioritySet();
            }
            else{/* NOTHING */}
            #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PrephralInterruptEnable();
            #endif
            EUSART_ASYNC_TX_InterruptEnable();
        }
#endif
        else{/* NOTHING */}
        /* TX 9-bit transmission configure  */
        if(_eusart->tx_cfg.eusart_tx_9bit_enable == EUSART_ASYNCRONOUS_9BIT_TX_DISABLE){
            EUSART_ASYNC_TX_8BIT_SELECT();
        }
        else if(_eusart->tx_cfg.eusart_tx_9bit_enable == EUSART_ASYNCRONOUS_9BIT_TX_ENABLE){
            EUSART_ASYNC_TX_9BIT_SELECT();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}
static inline void eusart_async_rx_configure(const usart_async_t * _eusart){
    if(_eusart->rx_cfg.eusart_rx_enable == EUSART_ASYNCRONOUS_RX_DISABLE){
        EUSART_ASYNC_RX_DISABLE();
    }
    else if(_eusart->rx_cfg.eusart_rx_enable == EUSART_ASYNCRONOUS_RX_ENABLE){
        EUSART_ASYNC_RX_ENABLE();
        /* RX Interrupt configure */
        if(_eusart->rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNCRONOUS_INTERRUPT_RX_DISABLE){
            EUSART_ASYNC_RX_InterruptDisable();
        }
#if EUSART_ASYNC_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        else if(_eusart->rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNCRONOUS_INTERRUPT_RX_ENABLE){
            /* Initialize the RX Interrupt Handler CallBack Functions */
            EUSART_ASYNC_RX_InterruptHandler = _eusart->EUSART_RXDefaultInterruptHandler ; 
            EUSART_ASYNC_OverRunErrorHandler = _eusart->EUSART_OverRunErrorHandler ; 
            EUSART_ASYNC_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler ; 
            /* RX Interrupt Priority Configure */
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            if(_eusart->rx_priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_ASYNC_RX_HighPrioritySet();
            }
            else if(_eusart->rx_priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_ASYNC_RX_LowPrioritySet();
            }
            else{/* NOTHING */}
            #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PrephralInterruptEnable();
            #endif
            EUSART_ASYNC_RX_InterruptEnable();
        }
#endif
        else{/* NOTHING */}
        /* RX 9-bit transmission configure  */
        if(_eusart->rx_cfg.eusart_rx_9bit_enable == EUSART_ASYNCRONOUS_9BIT_RX_DISABLE){
            EUSART_ASYNC_RX_8BIT_SELECT();
        }
        else if(_eusart->rx_cfg.eusart_rx_9bit_enable == EUSART_ASYNCRONOUS_9BIT_RX_ENABLE){
            EUSART_ASYNC_RX_9BIT_SELECT();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}
/*========================= section : EUSART ISR Functions Implementation ====================*/
void EUSART_ASYNC_TX_ISR(void){
    EUSART_ASYNC_TX_InterruptDisable();
    if(EUSART_ASYNC_TX_InterruptHandler){
        EUSART_ASYNC_TX_InterruptHandler();
    }
    else{/* NOTHING */}
}
void EUSART_ASYNC_RX_ISR(void){
    if(EUSART_ASYNC_RX_InterruptHandler){
        EUSART_ASYNC_RX_InterruptHandler();
    }
    else if(EUSART_ASYNC_OverRunErrorHandler){
        EUSART_ASYNC_OverRunErrorHandler();
    }
    else if(EUSART_ASYNC_FramingErrorHandler){
        EUSART_ASYNC_FramingErrorHandler();
    }
    else{/* NOTHING */}
}