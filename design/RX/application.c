/* 
 * File:   application.c
 * Author: Ameer
 *
 * Created on May 17, 2024, 1:32 PM
 */
#include "application.h"
volatile uint8 euart_val = 0 ;
volatile uint8 re_ac = 0  ;   /* flag to indicate reception AC Auto mode */
volatile uint8 r1_ac= 0  ;   /* flag to indicate room 1 AC Auto mode */
volatile uint8 r2_ac = 0  ;   /* flag to indicate room 2 AC Auto mode */

volatile uint8 re_ac_temp ; 
volatile uint8 r1_ac_temp ; 
volatile uint8 r2_ac_temp ; 

volatile adc_result_t re_temp =0 ;
volatile adc_result_t r1_temp =0 ;
volatile adc_result_t r2_temp =0 ;


void main (void){
    application_init();
    
    while(1){
        AirConditioner_TempHandler();
        

     }
}
/*========================== Application Initializations ======================*/
void application_init(void){
    mcal_layer_initialize();    
    ecu_layer_initialize();
}
void AirConditioner_TempHandler(void){
    if(re_ac == AUTO){
        /* reception ac in auto mode */
        if(re_ac_temp >= re_temp){
            led_turn_off(&reseption_AC);
        }
        else{
            led_turn_on(&reseption_AC);
        }
    }
    else if(re_ac == ON){
        led_turn_on(&reseption_AC);
    }
    else if(re_ac == OFF){
        led_turn_off(&reseption_AC);
    }
    if(r1_ac == AUTO){
        /* room 1 ac in auto mode */
        if(r1_ac_temp >= r1_temp){
            led_turn_off(&room_1_AC);
        }
        else{
            led_turn_on(&room_1_AC);
        }
    }
    else if(r1_ac == ON){
        led_turn_on(&room_1_AC);
    }
    else if(r1_ac == OFF){
        led_turn_off(&room_1_AC);
    }
    if(r2_ac == AUTO){
        /* reception ac in auto mode */
        if(r2_ac_temp >= r2_temp){
            led_turn_off(&room_2_AC);
        }
        else{
            led_turn_on(&room_2_AC);
        }
    }
    else if(r2_ac == ON){
        led_turn_on(&room_2_AC);
    }
    else if(r2_ac == OFF){
        led_turn_off(&room_2_AC);
    }
}
/*========================== ISR Initializations ======================*/
void EUSART_RXDefaultInterruptHandler(void){
    EUSART_ASYNC_ReadByteNonBlocking(&euart_val); 
    if(euart_val == 'a'){
        led_turn_on(&reseption_light);
    }
    else if(euart_val == 'b'){
        led_turn_off(&reseption_light);
    }
    else if(euart_val == 'c'){
        led_turn_on(&reseption_TV);
    }
    else if(euart_val == 'd'){
        led_turn_off(&reseption_TV);
    }
    else if(euart_val == 'e'){
        led_turn_on(&reseption_AC);
        re_ac = ON ; 
    }
    else if(euart_val == 'f'){
        led_turn_off(&reseption_AC);
        re_ac = OFF ;
    }
    else if(euart_val == 'g'){
        /* Reception AC Auto mode */
        re_ac = AUTO ;
    }
    else if(euart_val == 'G'){
        re_ac_temp = 0 ;
        EUSART_ASYNC_ReadByteBlocking(&re_ac_temp); 
    }
    else if(euart_val == 'h'){
        led_turn_on(&room_1_light);
    }
    else if(euart_val == 'i'){
        led_turn_off(&room_1_light);
    }
    else if(euart_val == 'j'){
        led_turn_on(&room_1_AC);
        r1_ac = ON ; 
    }
    else if(euart_val == 'k'){
        led_turn_off(&room_1_AC);
        r1_ac = OFF ; 
    }
    else if(euart_val == 'l'){
        /* AC AUTO */
        r1_ac = AUTO ; 
    }
    else if(euart_val == 'L'){
        r1_ac_temp = 0; 
        EUSART_ASYNC_ReadByteBlocking(&r1_ac_temp);
    }
    else if(euart_val == 'm'){
        led_turn_on(&room_2_light);
    }
    else if(euart_val == 'n'){
        led_turn_off(&room_2_light);
    }
    else if(euart_val == 'o'){
        led_turn_on(&room_2_AC);
        r2_ac = ON ; 
    }
    else if(euart_val == 'p'){
        led_turn_off(&room_2_AC);
        r2_ac = OFF ;  
    }
    else if(euart_val == 'q'){
       /* AC AUTO */
        r2_ac = AUTO ; 
    }
    else if(euart_val == 'Q'){
        r2_ac_temp = 0 ;
        EUSART_ASYNC_ReadByteBlocking(&r2_ac_temp);
    }
    else if(euart_val == 'x'){
       /* reception OFF */
        led_turn_off(&reseption_light);
        led_turn_off(&reseption_AC);
        led_turn_off(&reseption_TV);
        re_ac = OFF ; 
    }
    else if(euart_val == 'y'){
       /* room 1 OFF */
        led_turn_off(&room_1_light);
        led_turn_off(&room_1_AC);
        r1_ac = OFF ;
    }
    else if(euart_val == 'z'){
       /* room 2 OFF */
        led_turn_off(&room_2_light);
        led_turn_off(&room_2_AC);
        r2_ac = OFF ;
    }
    else{/*nothing*/}
}
void TIMER0_InterruptHandler(void){
        EUSART_ASYNC_WrireByteBlocking('a');
        LM35_GetTempCelsius(&lm35_reseption  , &re_temp) ; 
        EUSART_ASYNC_WrireByteBlocking((uint8)re_temp);

        EUSART_ASYNC_WrireByteBlocking('b');
        LM35_GetTempCelsius(&lm35_room1  , &r1_temp) ; 
        EUSART_ASYNC_WrireByteBlocking((uint8)r1_temp);
        EUSART_ASYNC_WrireByteBlocking('c');
        LM35_GetTempCelsius(&lm35_room2  , &r2_temp) ; 
        EUSART_ASYNC_WrireByteBlocking((uint8)r2_temp);
}