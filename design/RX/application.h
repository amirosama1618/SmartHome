/* 
 * File:   application.h
 * Author: Ameer
 *
 * Created on May 17, 2024, 1:32 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include "ECU_layer/ecu_layer_init.h"

#define OFF     0
#define ON      1
#define AUTO    2
/*========================== Data Type Deceleration =============================*/
void application_init(void);
void AirConditioner_TempHandler(void);
#endif	/* APPLICATION_H */

