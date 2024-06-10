/* 
 * File:   buzzer.h
 * Author: Ameer
 *
 * Created on May 25, 2024, 11:53 AM
 */

#ifndef BUZZER_H
#define	BUZZER_H


#include "../../MCAL_layer/CCP1/mcal_ccp1.h"

typedef ccp_config_t    buzzer_config_t ; 

STD_ReturnType Buzzer_init(const buzzer_config_t* buzzer_obj);
STD_ReturnType Buzzer_on(const buzzer_config_t* buzzer_obj , const uint8 _duty);
STD_ReturnType Buzzer_off(const buzzer_config_t* buzzer_obj); 

#endif	/* BUZZER_H */

