/* 
 * File:   mcal_external_interrupt.c
 * Author: Ameer
 *
 * Created on February 18, 2024, 11:05 AM
 */

/*========================== section : includes ==========================*/
#include "mcal_external_interrupt.h"
/*========================== section : Interrupt handler ==========================*/
/* INTx interrupt handler : pointer to function to callback INTx ISR*/
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;
/* RBx interrupt handler : pointer to function to callback RBx ISR*/
static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB4_InterruptHandler_Low  = NULL;
static InterruptHandler RB5_InterruptHandler_High = NULL;
static InterruptHandler RB5_InterruptHandler_Low  = NULL;
static InterruptHandler RB6_InterruptHandler_High = NULL;
static InterruptHandler RB6_InterruptHandler_Low  = NULL;
static InterruptHandler RB7_InterruptHandler_High = NULL;
static InterruptHandler RB7_InterruptHandler_Low  = NULL;
/*========================== section : helper functions declarations ==========================*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static STD_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static STD_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static STD_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static STD_ReturnType Interrupt_INTx_Flag_Clear(const interrupt_INTx_t *int_obj);

static STD_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
#endif
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static STD_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static STD_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static STD_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);
#endif
/*========================== section : software interface ==========================*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif function to initialize an external interrupt for of INTx type 
 * @param int_obj external interrupt object to initialize @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* disable external interrupt */
        error_state = Interrupt_INTx_Disable(int_obj);
        /* clear interrupt flag */
        error_state |= Interrupt_INTx_Flag_Clear(int_obj);
        /* configure interrupt edge */
        error_state |= Interrupt_INTx_Edge_Init(int_obj);
       /* configure interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        error_state &= Interrupt_INTx_Priority_Init(int_obj);
#endif
        /* configure interrupt i/o pins */
        error_state |= Interrupt_INTx_Pin_Init(int_obj);
        /* configure default call back */
        error_state |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* enable the interrupt */
        error_state |= Interrupt_INTx_Enable(int_obj); 
    }
    return error_state ;
}
void INT0_ISR(void){
    /* clear the flag */
    EXT_INT0_InterruptFlagClear();
    /* code */
        
    /* call back ISR function */
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
}
void INT1_ISR(void){
    /* clear the flag */
    EXT_INT1_InterruptFlagClear();
    /* code */
        
    /* call back ISR function */
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void){
    /* clear the flag */
    EXT_INT2_InterruptFlagClear();
    /* code */
        
    /* call back ISR function */
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}
/**
 * @breif function to de-initialize an external interrupt of INTx type 
 * @param int_obj external interrupt object to initialize @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state |= Interrupt_INTx_Disable(int_obj);
    }
    
    return error_state ;
}
#endif
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/** 
 * @breif function to initialize an external interrupt of RBx type "On Change"
 * @param int_obj external interrupt object to initialize @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* disable RBx interrupt */
        EXT_RBx_InterruptDisable();
        /* clear interrupt flag */
        EXT_RBx_InterruptFlagClear();
        /* interrupt pin initialize */
        error_state |= Interrupt_RBx_Pin_Init(int_obj);
        /* set interrupt handler */
        error_state |= Interrupt_RBx_SetInterruptHandler(int_obj);
        /* priority set */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        error_state |= Interrupt_RBx_Priority_Init(int_obj);
#endif
    }
    /* enable RBx interrupt */
        error_state |= Interrupt_RBx_Enable(int_obj);
    return error_state ;
}
/**
 * @breif function to de-initialize an external interrupt of RBx type "On Change"
 * @param int_obj external interrupt object to initialize @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state &= Interrupt_RBx_Disable(int_obj);
    }
    
    return error_state ;
}
void RB4_ISR(uint8 source){
    /* clear RB flag */
    EXT_RBx_InterruptFlagClear();
    /* code */
    /* call back function */
    if(0 == source){
        if(RB4_InterruptHandler_High){
            RB4_InterruptHandler_High();
        }
    }
    else{/* nothing */}
    if(1 == source){
        if(RB4_InterruptHandler_Low){
            RB4_InterruptHandler_Low();
        }
    }
    else{/* nothing */}
}
void RB5_ISR(uint8 source){
    /* clear RB flag */
    EXT_RBx_InterruptFlagClear();
    /* code */
    /* call back function */
    if(0 == source){
        if(RB5_InterruptHandler_High){
            RB5_InterruptHandler_High();
        }
    }
    else{/* nothing */}
    if(1 == source){
        if(RB5_InterruptHandler_Low){
            RB5_InterruptHandler_Low();
        }
    }
    else{/* nothing */}
}
void RB6_ISR(uint8 source){
    /* clear RB flag */
    EXT_RBx_InterruptFlagClear();
    /* code */
    /* call back function */
    if(0 == source){
        if(RB6_InterruptHandler_High){
            RB6_InterruptHandler_High();
        }
    }
    else{/* nothing */}
    if(1 == source){
        if(RB6_InterruptHandler_Low){
            RB6_InterruptHandler_Low();
        }
    }
    else{/* nothing */}
}
void RB7_ISR(uint8 source){
    /* clear RB flag */
    EXT_RBx_InterruptFlagClear();
    /* code */
    /* call back function */
    if(LOW == source){
        if(RB7_InterruptHandler_High){
            RB7_InterruptHandler_High();
        }
    }
    else{/* nothing */}
    if(HIGH == source){
        if(RB7_InterruptHandler_Low){
            RB7_InterruptHandler_Low();
        }
    }
    else{/* nothing */}
}
#endif
/*========================== section : helper functions implementation ==========================*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif helper function to enable External interrupt of INTx type
 * @param int_obj external interrupt object to enable @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* enable priority levels feature */
                INTERRUPT_PriorityLevelsEnable();
                /* enable global interrupt High priority enable */
                INTERRUPT_GlobalInterruptHighEnable(); 
#else 
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PrephralInterruptEnable();
#endif
                /* enable INTx interrupt */
                EXT_INT0_InterruptEnable();
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* enable priority levels feature */
                INTERRUPT_PriorityLevelsEnable();
                /* check HIGH or LOW priority */
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                     /* enable global interrupt LOW priority enable */
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                     /* enable global interrupt High priority enable */
                    INTERRUPT_GlobalInterruptHighEnable(); 
                }
                else{/* nothing */}
#else 
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PrephralInterruptEnable();
#endif
                /* enable INTx interrupt */
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXT_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* enable priority levels feature */
                INTERRUPT_PriorityLevelsEnable();
                /* check HIGH or LOW priority */
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                     /* enable global interrupt LOW priority enable */
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                     /* enable global interrupt High priority enable */
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{/* nothing */}
#else 
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PrephralInterruptEnable();
#endif
                /* enable INTx interrupt */
                EXT_INT2_InterruptEnable();
                error_state = E_OK;
                break;
            default: error_state= E_NOT_OK;
        }    
    }
    
    return error_state ;
}
/**
 * @breif helper function to disable External interrupt of INTx type
 * @param int_obj external interrupt object to disable @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0: 
                EXT_INT0_InterruptDisable();
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT1: 
                EXT_INT1_InterruptDisable();
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT2: 
                EXT_INT2_InterruptDisable();
                error_state = E_OK;
                break;
            default: error_state= E_NOT_OK;
        } 
    }
    
    return error_state ;
}
/**
 * @breif helper function to initialize pin configuration of the INTx @ref pin_config_t
 * @param int_obj external interrupt object to pin initialized @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        error_state |= gpio_pin_direction_init(&(int_obj->intx_pin));
    }
    
    return error_state ;
}
/**
 * @breif helper function to initialize interrupt of INTx priority @ref interrupt_priority_cfg 
 * @param int_obj external interrupt object to priority initialized @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT1: 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet();}
                else{/* nothing */}
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT2: 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet();}
                else{/* nothing */}
                error_state = E_OK;
                break;
            default: error_state= E_NOT_OK;
        }
    }
    
    return error_state ;
}
#endif
/**
 * @breif helper function to initialize interrupt of INTx Edge @ref interrupt_INTx_edge 
 * @param int_obj external interrupt object to Edge initialized @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdge();}
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge){ EXT_INT0_RisingEdge();}
                else{/* nothing */}
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT1: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdge();}
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdge();}
                else{/* nothing */}
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT2: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT2_FallingEdge();}
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge){EXT_INT2_RisingEdge();}
                else{/* nothing */}
                error_state = E_OK;
                break;
            default: error_state= E_NOT_OK;
        }
    }
    
    return error_state ;
}
/**
 * @breif helper function to clear the external interrupt flag 
 * @param int_obj external interrupt object to flag cleared @ref interrupt_INTx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_INTx_Flag_Clear(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0: 
                EXT_INT0_InterruptFlagClear();
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT1: 
                EXT_INT1_InterruptFlagClear();
                error_state = E_OK;
                break;
            case INTERRUPT_EXT_INT2: 
                EXT_INT2_InterruptFlagClear();
                error_state = E_OK;
                break;
            default: error_state= E_NOT_OK;
        } 
    }
    return error_state ;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_ReturnType error_state = E_NOT_OK ;
    if(NULL == InterruptHandler){
        error_state = E_NOT_OK ;
    }
    else{
        INT0_InterruptHandler = InterruptHandler ;
        error_state = E_OK ; 
    }
    return error_state ;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_ReturnType error_state = E_NOT_OK ;
    if(NULL == InterruptHandler){
        error_state = E_NOT_OK ;
    }
    else{
        INT1_InterruptHandler = InterruptHandler ;
        error_state = E_OK ; 
    }
    return error_state ;
}
/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_ReturnType error_state = E_NOT_OK ;
    if(NULL == InterruptHandler){
        error_state = E_NOT_OK ;
    }
    else{
        INT2_InterruptHandler = InterruptHandler ;
        error_state = E_OK ; 
    }
    return error_state ;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0: 
                error_state = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXT_INT1: 
                error_state = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXT_INT2: 
                error_state = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default: error_state= E_NOT_OK;
        } 
    }
    return error_state ;
}
#endif
/*--------------------------------------------------------------------------------------*/
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif helper function to enable External interrupt of RBx type
 * @param int_obj external interrupt object to enable @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ;
    if(NULL == int_obj){
        error_state = E_NOT_OK ;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* enable priority levels feature */
        INTERRUPT_PriorityLevelsEnable();
        /* set priority level */
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            /* enable global Low priority Interrupt */
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            /* enable global High priority Interrupt */
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else{/* nothing */}
#else
        /* enable Global interrupt */
       INTERRUPT_GlobalInterruptEnable();
       /* enable prephral interrupt */
       INTERRUPT_PrephralInterruptEnable();
#endif
        /* enable RBx interrupt */
        EXT_RBx_InterruptEnable();
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif helper function to disable External interrupt of RBx type
 * @param int_obj external interrupt object to disable @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        EXT_RBx_InterruptDisable();
        error_state = E_OK ; 
    }
    return error_state ;
}
/**
 * @breif helper function to initialize pin configuration of the INTx @ref pin_config_t
 * @param int_obj external interrupt object to pin initialized @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        if((PORTB_INDEX != int_obj->rbx_pin.port) || (PIN3 >= int_obj->rbx_pin.pin)){
            error_state = E_NOT_OK ; 
        }
        else{
            error_state = gpio_pin_direction_init(&(int_obj->rbx_pin));
        }
    }
    return error_state ;
}

static STD_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state  =E_NOT_OK ;
    if(NULL == int_obj){
        error_state = E_NOT_OK ;
    }
    else{
        switch(int_obj->rbx_pin.pin){
            case PIN4 :
                RB4_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                error_state = E_OK ;
                break;
            case PIN5 :
                RB5_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                error_state = E_OK ;
                break;
            case PIN6 :
                RB6_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                error_state = E_OK ;
                break;
            case PIN7 :
                RB7_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                error_state = E_OK ;
                break;
            default : error_state = E_NOT_OK; 
        }
    }
    return error_state ; 
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @breif helper function to initialize interrupt of INTx priority @ref interrupt_priority_cfg 
 * @param int_obj external interrupt object to priority initialized @ref interrupt_RBx_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
static STD_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == int_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        switch(int_obj->priority){
            case INTERRUPT_HIGH_PRIORITY :
                EXT_RBx_HighPrioritySet();
                error_state = E_OK ; 
                break;
            case INTERRUPT_LOW_PRIORITY :
                EXT_RBx_LowPrioritySet();
                error_state = E_OK ; 
                break;
            default : error_state = E_NOT_OK ; 
        }
    }
    return error_state ;
}
#endif
#endif