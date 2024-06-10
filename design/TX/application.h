/* 
 * File:   application.h
 * Author: Ameer
 *
 * Created on May 17, 2024, 1:32 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include "MCAL_layer/mcal_layer_init.h"
#include "ECU_layer/ecu_layer_init.h"
/*========================== Macros Deceleration =============================*/
#define PASSWORD_WRONG          0
#define PASSWORD_CORRECT        1

#define PASSWORD_EEPROM_ADD             0x00

#define OFF     0
#define ON       1
#define AUTO    2

#define RECEPTION_LIGHT_ADD                         0x14
#define RECEPTION_AC_ADD                             0x28
#define RECEPTION_AC_CHAR_AUTO_TEMP_ADD         0x50
#define RECEPTION_TV_ADD                             0x64

#define ROOM1_LIGHT_ADD             0x78
#define ROOM1_AC_ADD                 0x8C
#define ROOM1_AC_CHAR_AUTO_TEMP_ADD   0xB4

#define ROOM2_LIGHT_ADD             0xC8
#define ROOM2_AC_ADD                 0xDC
#define ROOM2_AC_CHAR_AUTO_TEMP_ADD   0x104
/*========================== Application Initializations =============================*/
void application_init(void);
void System_Initialize(void) ; 
/*========================== User Interface Functions Deceleration =============================*/
void master_lcd_home_page(void);
void master_lcd_room1_page(void);
void master_lcd_room2_page(void);
void master_lcd_reception_page(void);
void master_lcd_temperature_page(void);
void master_lcd_light_control_page(void);
void master_lcd_air_conditioner_control_page(void);
void master_lcd_TV_control_page(void);
void master_lcd_AC_Temperature_control_page(uint8 *AC_temp_val);
void master_lcd_Set_Temperature_control_page(void);
void master_lcd_password_page(void); 
void master_lcd_password_check_page(void) ;
void master_lcd_password_correct_page(void);
void master_lcd_password_wrong_try_again_page(void);
void master_lcd_password_wrong_no_try_page(void);
void master_lcd_log_out_page(void);
void master_lcd_log_out_confirm_page(void);
void master_lcd_password_change_page(void);
void master_lcd_password_set_page(void);
/*========================== Helper Functions Deceleration ==========================*/
uint8 PasswordCheck_Handler(void) ; 
void Get_password(uint8 *pass) ; 
void Get_new_password(uint8 *pass); 
void new_password_confirm(void); 

void Reception_Handler(void);
void Reception_LightControlHandler(void);
void Reception_TvControlHandler(void);
void Reception_AcControlHandler(void);
void Reception_AcSetTempHandler(void);
void Reception_OFF(void);

void Room1_Handler(void);
void Room1_LightControlHandler(void);
void Room1_AcControlHandler(void);
void Room1_AcSetTempHandler(void);
void Room1_OFF(void);

void Room2_Handler(void);
void Room2_LightControlHandler(void);
void Room2_AcControlHandler(void);
void Room2_AcSetTempHandler(void);
void Room2_OFF(void);
#endif	/* APPLICATION_H */

