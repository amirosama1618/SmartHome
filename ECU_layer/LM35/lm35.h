/* 
 * File:   lm35.h
 * Author: Ameer
 *
 * Created on March 1, 2024, 11:04 PM
 */

#ifndef LM35_H
#define	LM35_H


/* section : includes */
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/std_libraries.h"
#include "../../MCAL_layer/ADC/mcal_adc.h"
/* section : Macro definitions */

/* section : Macro functions definitions */

/* section : Data type declaration */

/* section : functions declarations */

STD_ReturnType LM35_Init(const adc_conf_t *adc_obj);
STD_ReturnType LM35_GetTempCelsius(const adc_conf_t *adc_obj, adc_result_t *Temp_celsius_res);

#endif	/* LM35_H */

