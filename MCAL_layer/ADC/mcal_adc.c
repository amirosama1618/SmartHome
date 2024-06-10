/* 
 * File:   mcal_adc.c
 * Author: Ameer
 *
 * Created on February 29, 2024, 11:59 AM
 */

/*========================== section : includes ==========================*/
#include "mcal_adc.h"
/*========================== section : ADC Interrupt Handler ==========================*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* ADC interrupt handler : pointer to function to callback ADC ISR*/
    static InterruptHandler ADC_InterruptHandler = NULL;
    static STD_ReturnType Interrupt_ADC_Init(const adc_conf_t *adc_obj);
#endif
/*========================== section : Helper Functions Declarations ==========================*/
static inline void adc_input_cahnnel_port_configure(adc_channel_select_t channel );
static inline void adc_configure_result_format(const adc_conf_t *adc_obj);
static inline void adc_configure_voltage_refrence(const adc_conf_t *adc_obj);
/*========================== section : functions implementation ==========================*/
/**
 * @breif function to initialize the ADC
 * @note  must be called before any other ADC routine is called
 *        must called only once during the system initialization  
 * @precondition  None
 * @param adc_obj pointer to ADC configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_Init(const adc_conf_t *adc_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(NULL == adc_obj){
         error_state = E_NOT_OK  ;
    }
    else{
        /*Disable ADC */
        ADC_Converter_Disable();
        /* configure the Acquisition time */
        ADC_ACQUISITION_TIME_SELECT(adc_obj->aquisition_time);
        /* configure the conversion clock */
        ADC_CONVERSION_CLOCK_SELECT(adc_obj->conversion_clock);
        /* configure the default channel */
        ADC_CHANNEL_BIT_SELECT(adc_obj->channel_select);
        adc_input_cahnnel_port_configure(adc_obj->channel_select);
        /* configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        error_state = Interrupt_ADC_Init(adc_obj);
#endif
        /* configure the result format */
        adc_configure_result_format(adc_obj);
        /* configure the voltage reference */
        adc_configure_voltage_refrence(adc_obj);
        /*Enable the ADC */
        ADC_Converter_Enable();
        error_state = E_OK ;
    }
    return error_state ; 
}
/**
 * @breif function to De-initialize the ADC
 * @param adc_obj pointer to ADC configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_DeInit(const adc_conf_t *adc_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(NULL == adc_obj){
         error_state = E_NOT_OK  ;
    }
    else{
        /* Disable ADC */
        ADC_Converter_Disable();
        /* Disable ADC interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
#endif
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to select ADC analog Channel
 * @preconditions ADC_Init() function should be called before calling this function  
 * @param adc_obj pointer to ADC configurations
 * @param channel define the channel index for conversion
 *        @ref adc_channel_select_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_SelectChannel(const adc_conf_t *adc_obj, adc_channel_select_t channel ){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(NULL == adc_obj){
        error_state = E_NOT_OK  ;
    }
    else{
        /* configure the channel */
        ADC_CHANNEL_BIT_SELECT(channel);
        adc_input_cahnnel_port_configure(channel);
        
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to start conversion 
 * @preconditions ADC_Init() and ADC_SelectChannel() must be called first to initialize ADC and
 *                select the channel to start conversion
 * @param adc_obj pointer to ADC configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_StartConversion(const adc_conf_t *adc_obj){
    STD_ReturnType error_state = E_NOT_OK  ;
    if(NULL == adc_obj){
         error_state = E_NOT_OK  ;
    }
    else{
        ADC_Conversion_Start();
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to check if the conversion process is done or not 
 * @param adc_obj pointer to ADC configurations
 * @preconditions ADC_StartConversion() must called before to start the conversion process 
 * @param conversion_status pointer to return the conversion progress status
 *        @note: 1 -> ADC_CONVERSION_DONE
 *               2 -> ADC_CONVERSION_NOT_DONE 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_IsConversionDone(const adc_conf_t *adc_obj, uint8 *conversion_status){
    STD_ReturnType error_state = E_NOT_OK  ;
    if((NULL == adc_obj) || (NULL == conversion_status)){
        error_state = E_NOT_OK  ;
    }
    else{
        *conversion_status = (uint8)!(ADC_Conversion_Status());
        error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to get the result of ADC conversion process 
 * @note the result DataType depend on the ADC Type in the microcontroller 
 *       @ref adc_result_t
 *       @ex: ADC 10-bit -> the result of conversion will be 10-bit length so..
 *           adc_result_t = uint16
 * @precondition ADC_IsConversionDone()must be called before 
 *               and the (conversion_status) pointer return ADC_CONVERSION_DONE
 * @param adc_obj pointer to ADC configurations
 * @param conversion_result pointer to return the conversion result
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_GetConversionResult(const adc_conf_t *adc_obj, adc_result_t *conversion_result){
    STD_ReturnType error_state = E_NOT_OK  ;
    if((NULL == adc_obj) || (NULL == conversion_result)){
        error_state = E_NOT_OK  ;
    }
    else{
        if(ADC_RESULT_FORMAT_RIGHT == adc_obj->Result_format){
            *conversion_result = (adc_result_t)((ADRESH<<8)+ADRESL);
        }
        else if(ADC_RESULT_FORMAT_LEFT == adc_obj->Result_format){
            *conversion_result = (adc_result_t)(((ADRESH<<8)+ADRESL) >> 6);
        }
        else{
            *conversion_result = (adc_result_t)(((ADRESH<<8)+ADRESL) >> 6);
        }
         error_state = E_OK  ;
    }
    return error_state ; 
}
/**
 * @breif function to return the conversion result
 *        also allows selection of the analog channel(AN0,AN1,....AN12)
 * @note  this function uses blocking technique !!
 * @preconditions ADC_Init() must be called before to call this function
 * @param adc_obj pointer to ADC configurations
 * @param channel define the channel index for conversion (AN0,AN1,....AN12)
 * @param conversion_result pointer to return the conversion result
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *adc_obj, adc_channel_select_t channel ,
                                             adc_result_t *conversion_result){
    STD_ReturnType error_state = E_NOT_OK  ;
    uint8 l_conversion_status = ZERO_INIT ; 
    if((NULL == adc_obj) || (NULL == conversion_result)){
         error_state = E_NOT_OK  ;
    }
    else{
        /* select ADC channel */
        error_state = ADC_SelectChannel(adc_obj, channel);
        /* Start conversion */
        error_state = ADC_StartConversion(adc_obj); 
        /* check if the conversion is done */
        while(ADCON0bits.GO_nDONE);
        error_state = ADC_GetConversionResult(adc_obj , conversion_result);

    }
    return error_state ; 
}
STD_ReturnType ADC_GetConversion_Interrrupt(const adc_conf_t *adc_obj, adc_channel_select_t channel ,
                                             adc_result_t *conversion_result){
    STD_ReturnType error_state = E_NOT_OK  ;
    uint8 l_conversion_status = ZERO_INIT ; 
    if((NULL == adc_obj) || (NULL == conversion_result)){
         error_state = E_NOT_OK  ;
    }
    else{
        /* select ADC channel */
        error_state = ADC_SelectChannel(adc_obj, channel);
        /* Start conversion */
        error_state = ADC_StartConversion(adc_obj); 
        /* check if the conversion is done */
        error_state = ADC_IsConversionDone(adc_obj, &l_conversion_status);
        while(l_conversion_status == ADC_CONVERSION_NOT_DONE);
        error_state = ADC_GetConversionResult(adc_obj , conversion_result);

    }
    return error_state ; 
}
/**
 * @breif function make interrupt when conversion done 
 *        also allows selection of the analog channel(AN0,AN1,....AN12)
 * @note  this function uses Interrupt !!
 * @preconditions ADC_Init() must be called before to call this function
 * @param adc_obj pointer to ADC configurations
 * @param channel define the channel index for conversion (AN0,AN1,....AN12)
 * @param conversion_result pointer to return the conversion result
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc_obj, adc_channel_select_t channel){
    STD_ReturnType error_state = E_NOT_OK  ;
    uint8 l_conversion_status = ZERO_INIT ; 
    if((NULL == adc_obj)){
         error_state = E_NOT_OK  ;
    }
    else{
        /* select ADC channel */
        error_state = ADC_SelectChannel(adc_obj, channel);
        /* Start conversion */
        error_state = ADC_StartConversion(adc_obj); 
    }
    return error_state ; 
}
/*========================== section : Helper Functions implementation  ==========================*/
static inline void adc_input_cahnnel_port_configure(adc_channel_select_t channel ){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA,_TRISA_RA0_POSITION); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA,_TRISA_RA1_POSITION); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA,_TRISA_RA2_POSITION); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA,_TRISA_RA3_POSITION); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA,_TRISA_RA5_POSITION); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE,_TRISE_RE0_POSITION); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE,_TRISE_RE1_POSITION); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE,_TRISE_RE2_POSITION); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB,_TRISB_RB2_POSITION); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB,_TRISB_RB3_POSITION); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB,_TRISB_RB1_POSITION); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB,_TRISB_RB4_POSITION); break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB,_TRISB_RB0_POSITION); break; 
    }
}
static inline void adc_configure_result_format(const adc_conf_t *adc_obj){
    if(ADC_RESULT_FORMAT_RIGHT == adc_obj->Result_format){
            ADC_ResultFormat_RightJustified();
        }
        else if(ADC_RESULT_FORMAT_LEFT == adc_obj->Result_format){
            ADC_ResultFormat_LeftJustified();
        }
        else{
            ADC_ResultFormat_RightJustified();
        }
}
static inline void adc_configure_voltage_refrence(const adc_conf_t *adc_obj){
    if(ADC_VOLTAGE_REFRENCE_ENABLE == adc_obj->voltage_reference){
            ADC_VoltageReference_Enable();
        }
        else if(ADC_VOLTAGE_REFRENCE_DISABLE == adc_obj->voltage_reference){
            ADC_VoltageReference_Disable();
        }
        else{
            ADC_VoltageReference_Disable();
        }
}
/*========================== section : ADC Interrupt Handler ==========================*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType Interrupt_ADC_Init(const adc_conf_t *adc_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if((NULL == adc_obj) || (NULL == adc_obj->ADC_InterruptHandler)){
        error_state = E_NOT_OK ; 
    }
    else{
        /* disable ADC interrupt */
        ADC_InterruptDisable();
        /* clear interrupt flag */
        ADC_InterruptFlagClear();
       /* configure interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == adc_obj->ADC_priority){
            ADC_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_PriorityLevelsEnable();
            error_state =E_OK ;
        }
        else if(INTERRUPT_LOW_PRIORITY == adc_obj->ADC_priority){
            ADC_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
            INTERRUPT_PriorityLevelsEnable();
            error_state =E_OK ;
        }
        else{
            error_state = E_NOT_OK ; 
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PrephralInterruptEnable();
#endif
        /* configure default call back */
        ADC_InterruptHandler = adc_obj->ADC_InterruptHandler ; 
        /* enable the interrupt */
        ADC_InterruptEnable();
        error_state= E_OK  ;
    }
    return error_state ;
}
void ADC_ISR(void){
    /* clear the flag */
    ADC_InterruptFlagClear();
    /* code */
        
    /* call back ISR function */
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}
#endif