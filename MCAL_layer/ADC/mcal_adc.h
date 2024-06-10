/* 
 * File:   mcal_adc.h
 * Author: Ameer
 *
 * Created on February 29, 2024, 11:59 AM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/*========================== section : includes ==========================*/
#include "pic18f4620.h" 
#include "../../MCAL_layer/mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_adc_cfg.h"
/*========================== section : Macro definitions ==========================*/
/**
 * @breif : Analog_To_Digital_Port_Configuration_Control
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY        0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY        0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY        0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY        0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY        0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY        0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY        0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY        0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY        0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY        0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY       0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY       0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY       0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY        0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY       0x0F

#define ADC_VOLTAGE_REFRENCE_ENABLE         1
#define ADC_VOLTAGE_REFRENCE_DISABLE        0

#define ADC_RESULT_FORMAT_RIGHT               1
#define ADC_RESULT_FORMAT_LEFT                0 

#define ADC_CONVERSION_DONE                     1
#define ADC_CONVERSION_NOT_DONE                0 
/*========================== section : Macro functions definitions ==========================*/
/* ADCON0 register */
/* A/D Converter module is enabled */
#define ADC_Converter_Enable()                        (ADCON0bits.ADON = 1)
/* A/D Converter module is Disable */
#define ADC_Converter_Disable()                       (ADCON0bits.ADON = 0)
/**
 *  A/D Conversion Status bit 
 *  1 =  A/D conversion in progress
 *  0 =  A/D Idle
 */
#define ADC_Conversion_Status()           (ADCON0bits.GODONE)
/* ADC Start conversion */
#define ADC_Conversion_Start()           (ADCON0bits.GODONE = 1)
/**
 * @breif set the analog channel bit
 */
#define ADC_CHANNEL_BIT_SELECT(_CONFIG)     (ADCON0bits.CHS = _CONFIG)

/* ADCON1 register */
/**
 * @breif Voltage Reference Configuration 
 * @note: ADC_VoltageReference_Enable(): Voltage reference is (VREF+ , VREF-)
 *        ADC_VoltageReference_Disable() : Voltage reference is (VSS , VDD)
 */
#define ADC_VoltageReference_Enable()        do{  ADCON1bits.VCFG1 = 1;\
                                                                 ADCON1bits.VCFG0 = 1;\
                                                            }while(0)
#define ADC_VoltageReference_Disable()       do{  ADCON1bits.VCFG1 = 0;\
                                                                 ADCON1bits.VCFG0 = 0;\
                                                            }while(0)
/**
 * @breif : Analog/Digital Pin functionality configuration 
 * @note : for example ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY)
 *         pins(AN4,3,2,1,0) are Analog functionality 
 *         the rest of pins have Digital functionality 
 *         @ref Analog_To_Digital_Port_Configuration_Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)     (ADCON1bits.PCFG = _CONFIG)

/* ADCON2 register */
/**
 * @breif ADC Result Format select
 * @note ADC_ResultFormat_RightJustified(): result format is right justified
 *       ADC_ResultFormat_LeftJustified(): result format is Left justified
 */
#define ADC_ResultFormat_RightJustified()       (ADCON2bits.ADFM = 1)
#define ADC_ResultFormat_LeftJustified()        (ADCON2bits.ADFM = 0)
/**
 * @breif   Acquisituin Time select
 * @ref     adc_aquisition_time_t
 */
#define ADC_ACQUISITION_TIME_SELECT(_CONFIG)    (ADCON2bits.ACQT = _CONFIG)
/**
 * @breif  A/D Conversion Clock Select
 * @ref    adc_conversion_clock_select_t
 */
#define ADC_CONVERSION_CLOCK_SELECT(_CONFIG)    (ADCON2bits.ADCS = _CONFIG)

/*========================== section : Data type declaration ==========================*/
/**
 *@breif: Analog Channel Select (13 Channel)
 *@note:  selection done by 4-bits in REG(ADCON0) bits:5-2 (CHS3:CHS0)
 */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;
/**
 * @breif   A/D Acquisition Time select
 * @note    Acquisition Time is the time required for the ADC to 
 *          capture the input voltage during sampling 
 * @note    Acquisition Time for (SAR) ADCs is the amount of time required to 
 *          charge the holding capacitor 
 */
typedef enum{
    ADC_0_TAD = 0 , 
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_aquisition_time_t;
/**
 * @breif   A/D Conversion Clock Select bits 
 * @note    If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle)
 *          is added before the A/D clock starts
 * @note    This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8 , 
    ADC_CONVERSION_CLOCK_FOSC_DIV_32 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_RC ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4  ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_select_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (* ADC_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
     interrupt_priority_cfg ADC_priority  ;
#endif
#endif
    adc_aquisition_time_t  aquisition_time ;                /* @ref adc_aquisition_time_t */
    adc_conversion_clock_select_t  conversion_clock;    /* @ref adc_conversion_clock_select_t */
    adc_channel_select_t  channel_select ;                  /* @ref adc_channel_select_t */ 
    uint8 voltage_reference  :1;            /* ADC_VOLTAGE_REFRENCE_ENABLE \\ ADC_VOLTAGE_REFRENCE_DISABLE */  
    uint8 Result_format  :1;                 /* ADC_RESULT_FORMAT_RIGHT \\ ADC_RESULT_FORMAT_LEFT */
    uint8 ADC_Reserved  :6;                  /* reserved bits */
}adc_conf_t;

typedef uint16  adc_result_t ; 
/*========================== section : functions declarations ==========================*/
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
STD_ReturnType ADC_Init(const adc_conf_t *adc_obj);
/**
 * @breif function to De-initialize the ADC
 * @param adc_obj pointer to ADC configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_DeInit(const adc_conf_t *adc_obj);
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
STD_ReturnType ADC_SelectChannel(const adc_conf_t *adc_obj, adc_channel_select_t channel );
/**
 * @breif function to start conversion 
 * @preconditions ADC_Init() and ADC_SelectChannel() must be called first to initialize ADC and
 *                select the channel to start conversion
 * @param adc_obj pointer to ADC configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType ADC_StartConversion(const adc_conf_t *adc_obj);
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
STD_ReturnType ADC_IsConversionDone(const adc_conf_t *adc_obj, uint8 *conversion_status);
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
STD_ReturnType ADC_GetConversionResult(const adc_conf_t *adc_obj, adc_result_t *conversion_result);
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
                                             adc_result_t *conversion_result);
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
STD_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc_obj, adc_channel_select_t channel);

#endif	/* MCAL_ADC_H */

