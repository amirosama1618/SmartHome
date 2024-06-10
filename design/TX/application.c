/* 
 * File:   application.c
 * Author: Ameer
 *
 * Created on May 17, 2024, 1:32 PM
 */
/*========================== Macros Deceleration =============================*/
#include "application.h"
/*========================== Global variable Initialization =============================*/
uint8 keypad_value = 0; 
uint8 password [5] = {'\0' ,'\0' , '\0' ,'\0' , '\0'} ;
uint8 password_temp [4] ;
uint8 counter = 0 ; 
uint8 pass_try_counter = 0 ;
uint8 password_check = PASSWORD_WRONG ; 
uint8 arr[10] = {'0','1','2','3','4','5','6','7','8','9'};
uint8 reception_AC_temp_val[3] = {'\0', '\0', '\0'}  ; 
uint8 room_1_AC_temp_val[3]     = {'\0', '\0', '\0'}  ;
uint8 room_2_AC_temp_val[3]     = {'\0', '\0', '\0'}  ;

uint8 re_AC_temp = 0  ; 
uint8 r_1_AC_temp = 0   ;
uint8 r_2_AC_temp =  0 ;

uint8 re_AC_flag = 0 ;
uint8 re_AC_auto_flag = 0 ;
uint8 re_light_flag = 0   ;
uint8 re_tv_flag =  0 ;

uint8 r1_AC_flag = 0 ;
uint8 r1_AC_auto_flag = 0 ;
uint8 r1_light_flag = 0   ;

uint8 r2_AC_flag = 0 ;
uint8 r2_AC_auto_flag = 0 ;
uint8 r2_light_flag = 0   ;

uint8 re_light_state = 0 ;
uint8 re_tv_state = 0 ;
uint8 re_ac_state = 0 ;

uint8 r1_light_state = 0 ;
uint8 r1_ac_state = 0 ;

uint8 r2_light_state = 0 ;
uint8 r2_ac_state = 0 ;

volatile uint8 uart_val = 0 ;
volatile uint8 uart_reseption_temp =0 ; 
volatile uint8 uart_room1_temp =0 ; 
volatile uint8 uart_room2_temp =0 ; 
volatile uint8 uart_reseption_temp_string [3]; 
volatile uint8 uart_room1_temp_string [3]; 
volatile uint8 uart_room2_temp_string [3];

/*========================== MAIN  =============================*/
void main (void){
    application_init();
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 8 , "Hello");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2 , 5 , "Smart Home");
    __delay_ms(500);
    System_Initialize();
    do{
        password_check = PasswordCheck_Handler();
    }while(password_check == PASSWORD_WRONG);
    while(1){
        master_lcd_home_page();
        __delay_ms(200);
        keypad_value = 0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value); 
        }while(keypad_value == 0);
        switch (keypad_value){
            case '1' :
                /* reception */
                Reception_Handler();
                break ;
            case '2' :
                /* Room 1*/
                Room1_Handler();
                break ;
            case '3' :
                /* Room 2*/
                Room2_Handler();
                break ;
            case '4' :
                /* Temperature display */
                    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
                    keypad_value = 0 ;
                    do{
                        master_lcd_temperature_page();
                        __delay_ms(200);
                        key_pad_get_value(&_master_keypad , &keypad_value);
                    }while(keypad_value == 0); 
                    if(keypad_value == '#'){
                        /* Exit */
                    }
                    else{
                        master_lcd_temperature_page();
                    }
                keypad_value = 0 ;
                break ;
            case '5' :
                /* log out */
                master_lcd_log_out_page() ;
                __delay_ms(200);
                keypad_value = 0 ;
                do{
                    key_pad_get_value(&_master_keypad , &keypad_value);
                }while(keypad_value == 0); 
                switch(keypad_value){
                    case '1' : 
                        /* confirm log out */
                        master_lcd_log_out_confirm_page();
                        do{
                            password_check = PasswordCheck_Handler();
                        }while(password_check == PASSWORD_WRONG);
                        break;
                    case '2' :
                        /* change password */
                        master_lcd_password_change_page(); 
                        __delay_ms(200);
                        keypad_value = 0 ;
                        do{
                            key_pad_get_value(&_master_keypad , &keypad_value);
                        }while(keypad_value == 0); 
                        switch(keypad_value){
                            case '1':
                                /* set new password */
                                master_lcd_password_set_page();
                                __delay_ms(200);
                                Get_new_password(password);
                                  
                                break ;
                            case '2':
                                /* cancel*/
                                break ;
                        }
                        break; 
                    case '3' :
                        /* cancel */
                        /* back to home page */
                        break;
                    default:
                        keypad_value = 0 ;
                        break;
                }
                keypad_value = 0 ;
                break ;
       }
     }
}
/*========================== Application Initializations ======================*/
void application_init(void){
    mcal_layer_initialize();    
    ecu_layer_initialize();
}
void System_Initialize(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2 ,1 , "System Initialize"); 
    for(counter = 0 ; counter< 3 ; counter ++){
        chr_lcd_4bit_send_char_data(&_master_lcd , '.');
        __delay_ms(300);
    }
    EEPROM_Data_ReadByte(RECEPTION_LIGHT_ADD , &re_light_state); 
    EEPROM_Data_ReadByte(RECEPTION_TV_ADD , &re_tv_state); 
    EEPROM_Data_ReadByte(RECEPTION_AC_ADD , &re_ac_state); 
    
    EEPROM_Data_ReadByte(ROOM1_LIGHT_ADD , &r1_light_state); 
    EEPROM_Data_ReadByte(ROOM1_AC_ADD , &r1_ac_state); 

    EEPROM_Data_ReadByte(ROOM2_LIGHT_ADD , &r2_light_state);
    EEPROM_Data_ReadByte(ROOM2_AC_ADD , &r2_ac_state); 
    /**
     * Reception system initialize 
     */
    /* lights */
    if(re_light_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('b');
        re_light_flag = 0 ;
    }
    else if(re_light_state == ON){
        EUSART_ASYNC_WrireByteBlocking('a');
        re_light_flag = 1 ;
    }else{/* nothing */}
    /* Tv */
    if(re_tv_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('d');
        re_tv_flag = 0 ;
    }
    else if(re_tv_state == ON){
        EUSART_ASYNC_WrireByteBlocking('c');
        re_tv_flag = 1 ;
    }else{/* nothing */}
    /* AC */
    if(re_ac_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('f');
        re_AC_flag = 0 ;
        re_AC_auto_flag = 0 ;
    }
    else if(re_ac_state == ON){
        EUSART_ASYNC_WrireByteBlocking('e');
        re_AC_flag = 1 ; 
        re_AC_auto_flag = 0;
    }
    else if(re_ac_state == AUTO){
        EUSART_ASYNC_WrireByteBlocking('g');
        re_AC_flag = 0 ;
        re_AC_auto_flag = 1 ;
        EUSART_ASYNC_WrireByteBlocking('G');
        EEPROM_Data_Read(RECEPTION_AC_CHAR_AUTO_TEMP_ADD , reception_AC_temp_val , 2);
        for (int i = 0; reception_AC_temp_val[i] != '\0'; i++) {
            re_AC_temp = re_AC_temp * 10 + (reception_AC_temp_val[i] - '0');
        }
        EUSART_ASYNC_WrireByteBlocking(re_AC_temp);
    }else{/* nothing */}
    /**
     * ROOM1 system initialize 
     */
    /* lights */
    if(r1_light_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('i');
        r1_light_flag == 0 ; 
    }
    else if(r1_light_state == ON){
        EUSART_ASYNC_WrireByteBlocking('h');
        r1_light_flag == 1 ; 
    }else{/* nothing */}
    /* AC */
    if(r1_ac_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('k');
        r1_AC_flag = 0 ;
        r1_AC_auto_flag = 0 ;
    }
    else if(r1_ac_state == ON){
        EUSART_ASYNC_WrireByteBlocking('j');
        r1_AC_flag = 1 ;
        r1_AC_auto_flag = 0 ;
    }
    else if(r1_ac_state == AUTO){
        EUSART_ASYNC_WrireByteBlocking('l');
        r1_AC_flag = 0 ;
        r1_AC_auto_flag = 1 ;
        EUSART_ASYNC_WrireByteBlocking('L');
        EEPROM_Data_Read(ROOM1_AC_CHAR_AUTO_TEMP_ADD , room_1_AC_temp_val , 2);
        for (int i = 0; room_1_AC_temp_val[i] != '\0'; i++) {
            r_1_AC_temp = r_1_AC_temp * 10 + (room_1_AC_temp_val[i] - '0');
        }
        EUSART_ASYNC_WrireByteBlocking(r_1_AC_temp);
    }else{/* nothing */}
    /**
     * ROOM2 system initialize 
     */
    /* lights */
    if(r2_light_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('n');
        r2_light_flag == 0 ; 
    }
    else if(r2_light_state == ON){
        EUSART_ASYNC_WrireByteBlocking('m');
        r2_light_flag == 1 ; 
    }else{/* nothing */}
    /* AC */
    if(r2_ac_state == OFF){
        EUSART_ASYNC_WrireByteBlocking('p');
        r2_AC_flag = 0 ;
        r2_AC_auto_flag = 0 ;
    }
    else if(r2_ac_state == ON){
        EUSART_ASYNC_WrireByteBlocking('o');
        r2_AC_flag = 1 ;
        r2_AC_auto_flag = 0 ;
    }
    else if(r2_ac_state == AUTO){
        EUSART_ASYNC_WrireByteBlocking('q');
        r2_AC_flag = 0 ;
        r2_AC_auto_flag = 1 ;
        EUSART_ASYNC_WrireByteBlocking('Q');
        EEPROM_Data_Read(ROOM1_AC_CHAR_AUTO_TEMP_ADD , room_2_AC_temp_val , 2);
        for (int i = 0; room_2_AC_temp_val[i] != '\0'; i++) {
            r_2_AC_temp = r_2_AC_temp * 10 + (room_2_AC_temp_val[i] - '0');
        }
        EUSART_ASYNC_WrireByteBlocking(r_2_AC_temp);
    }else{/* nothing */}
}
/*========================== User Interface Functions implementations ==========================*/
void master_lcd_home_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Home Page");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:Reception");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:Room 1");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "3:Room 2");    
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 11,"4:Temp");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 11,"5:Log Out");
}
void master_lcd_reception_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Reception");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:lights");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 10, "2:TV");   
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "3:A/C");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "4:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"5:Home page");
}
void master_lcd_room1_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Room 1");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:lights");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:A/C");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "3:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"4:Home page");
}
void master_lcd_room2_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Room 2");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:lights");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:A/C");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "3:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"4:Home page");
}
void master_lcd_temperature_page(void){
    uart_reseption_temp_string[0]= '\0';
    uart_reseption_temp_string[1]= '\0';
    uart_reseption_temp_string[2]= '\0';
    convert_uint8_to_string(uart_reseption_temp , uart_reseption_temp_string);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Home Temperature");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "Reception:");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 11, "   ");
        chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 11, uart_reseption_temp_string);
    chr_lcd_4bit_send_char_data_position(&_master_lcd , 2, 14, 'C');
    
    uart_room1_temp_string[0]= '\0';
    uart_room1_temp_string[1]= '\0';
    uart_room1_temp_string[2]= '\0';
    convert_uint8_to_string(uart_room1_temp , uart_room1_temp_string);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "Room1:");
        chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 7, "   ");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 7, uart_room1_temp_string);
    chr_lcd_4bit_send_char_data_position(&_master_lcd , 3, 10, 'C');

    uart_room2_temp_string[0]= '\0';
    uart_room2_temp_string[1]= '\0';
    uart_room2_temp_string[2]= '\0';
    convert_uint8_to_string(uart_room2_temp , uart_room2_temp_string);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "Room2:");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 7, "   ");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 7, uart_room2_temp_string);
    chr_lcd_4bit_send_char_data_position(&_master_lcd , 4, 10, 'C');
    
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 15, "#:Exit");
}
void master_lcd_light_control_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Lights Control");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:ON");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"3:Home page");
}
void master_lcd_air_conditioner_control_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "A/C Control");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:ON");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "3:Auto");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"4:Home page");
}
void master_lcd_AC_Temperature_control_page(uint8 *AC_temp_val){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Temperature Control");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "Temp value = ");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 14, AC_temp_val);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "1:Set Temp Value");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"2:Back");
}
void master_lcd_Set_Temperature_control_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "Set Temp Control");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "Temp value = ");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "#:Save");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 1, "*:ReEnter");
}
void master_lcd_TV_control_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 1, "TV Control");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "1:ON");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3, 1, "2:OFF");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4, 10,"3:Home page");
}
void master_lcd_password_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 5, "welcome back");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "Enter Password:");
}
void master_lcd_password_check_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "password check");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4,13 , "wait...");
    __delay_ms(1000);
}
void master_lcd_password_correct_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "password is correct");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 3,5, "welcome back");
    __delay_ms(1000);
}
void master_lcd_password_wrong_try_again_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 1, 2, "password is wrong");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2,6, "Try again:");
}
void master_lcd_password_wrong_no_try_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 2, 1, "password is wrong");
    chr_lcd_4bit_send_string_data_position(&_master_lcd , 4,6, "wait 10 sec");
    __delay_ms(1000);
    for(counter = 0 ; counter <= 10 ; counter ++ ){
        chr_lcd_4bit_send_string_data_position(&_master_lcd , 4,11, "  ");
       chr_lcd_4bit_send_char_data_position(&_master_lcd , 4,11, arr[10-counter]);
       __delay_ms(1000);
    }
}
void master_lcd_log_out_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,1,1,"Log Out");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,1,"1:Confirm");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,3,1,"2:Change Password");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,4,1,"3:Cancel");
}
void master_lcd_log_out_confirm_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,3,"Logging out....");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,3,8,"See you");
    __delay_ms(1000);
}
void master_lcd_password_change_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
     EEPROM_Data_Read(PASSWORD_EEPROM_ADD , password_temp , 4);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,1,1,"Change Password");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,1,"your Password:");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,15,password_temp);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,3,1,"1:Set New Password");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,4,1,"2:Cancel");
}
void master_lcd_password_set_page(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,1,1,"Enter New Password");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,1,"Password:");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,3,1,"*:Rewrite");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,4,1,"#:Cancel");
}
/*========================== Helper Functions implementations ==========================*/
uint8 PasswordCheck_Handler(void){
    uint8 pass = PASSWORD_WRONG ; 
    EEPROM_Data_Read(PASSWORD_EEPROM_ADD , password, 4); 
    if(password[0] == 0xFF){
        /* password not set yet */
        master_lcd_password_page();
        Get_password(password); 
        EEPROM_Data_Write(PASSWORD_EEPROM_ADD , password);
        pass = PASSWORD_CORRECT ;
    }
    else{
        /* password has been set before */
        master_lcd_password_page();
        for(pass_try_counter = 0; pass_try_counter <4 ; pass_try_counter++){
            if(pass_try_counter == 3){
                master_lcd_password_wrong_no_try_page() ; 
                pass = PASSWORD_WRONG ; 
            }else{
                Get_password(password); 
                EEPROM_Data_Read(PASSWORD_EEPROM_ADD , password_temp , 4);
                master_lcd_password_check_page() ; 
                if((password_temp[0]==password[0])&(password_temp[1]==password[1])
                    &(password_temp[2]==password[2])&(password_temp[3]==password[3])){
                    /* password is correct */
                    master_lcd_password_correct_page(); 
                    pass = PASSWORD_CORRECT ; 
                    break ;
                }
                else{
                    /* pass word is wrong */
                    master_lcd_password_wrong_try_again_page();
                    pass = PASSWORD_WRONG ; 
                }
            }
        }     
    }
    return pass ; 
}
void Get_password(uint8 *pass){
    for(counter = 0 ; counter<4 ; counter++ ){
        keypad_value = 0;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value); 
        }while(keypad_value == 0);
        chr_lcd_4bit_send_char_data_position(&_master_lcd ,2 , 16+counter  ,keypad_value);
        __delay_ms(100);
        chr_lcd_4bit_send_char_data_position(&_master_lcd,2 ,16+ counter  , '*');
        pass[counter] = keypad_value ; 
        __delay_ms(200);
    }
}
void Get_new_password(uint8 *pass){
    for(counter = 0 ; counter<4 ; counter++ ){
        __delay_ms(200);
        keypad_value = 0;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value); 
        }while(keypad_value == 0);
        if(keypad_value == '*'){
            /* rewrite the password */
            counter = 0 ; 
            pass[4] = 0;
            chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
            master_lcd_password_set_page();
            __delay_ms(200);
            keypad_value = 0;
            do{
                key_pad_get_value(&_master_keypad , &keypad_value); 
            }while(keypad_value == 0);
            chr_lcd_4bit_send_char_data_position(&_master_lcd ,2 , 10+counter  ,keypad_value);
            pass[counter] = keypad_value ;
        }
        else if(keypad_value == '#'){
            /* cancel */
            break ;
        }
        else if((keypad_value != 0) &&(keypad_value != '*')&&(keypad_value != '#')){
            chr_lcd_4bit_send_char_data_position(&_master_lcd ,2 , 10+counter  ,keypad_value);
            pass[counter] = keypad_value ; 
            __delay_ms(200);
        } 
    }
    if((keypad_value != '#')&&(keypad_value != '*')){
        new_password_confirm();
    }  
}
void new_password_confirm(void){
    chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
    __delay_ms(20);
    chr_lcd_4bit_send_string_data_position(&_master_lcd,1,1," To Confirm Press *");
    chr_lcd_4bit_send_string_data_position(&_master_lcd,2,1," To Cancel Press #");
    __delay_ms(200);
    keypad_value = 0;
    do{
        key_pad_get_value(&_master_keypad , &keypad_value); 
    }while(keypad_value == 0);
    switch(keypad_value){
        case '*':
            EEPROM_Data_Write(PASSWORD_EEPROM_ADD , password) ;
            chr_lcd_4bit_send_command(&_master_lcd , _LCD_CLEAR);
            __delay_ms(20);
            chr_lcd_4bit_send_string_data_position(&_master_lcd,1,1,"password Reset");
            for(counter = 0 ; counter< 3 ; counter ++){
                chr_lcd_4bit_send_char_data(&_master_lcd , '.');
                __delay_ms(300);
            }
            break ;
        case '#' :
            /* cancel*/
            break ;
    }
}
void Reception_LightControlHandler(void){
    do{
        master_lcd_light_control_page();
        if(re_light_flag == 0){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if(re_light_flag == 1){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else{/* nothing */}
        __delay_ms(500);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' :
                /* light on */
                EUSART_ASYNC_WrireByteBlocking('a');
                re_light_flag = 1 ;
                EEPROM_Data_WriteByte(RECEPTION_LIGHT_ADD , ON);
                break ; 
            case '2' :
                /* light off */
                EUSART_ASYNC_WrireByteBlocking('b');
                re_light_flag = 0 ;
                EEPROM_Data_WriteByte(RECEPTION_LIGHT_ADD , OFF);
                break ;
            case '3' :
                /* home page */
                master_lcd_home_page();
                __delay_ms(500);
                break ;
            default: 
                keypad_value = 0 ;break ; 
        }
    }while(keypad_value != '3');
    keypad_value = 0 ;
}
void Reception_TvControlHandler(void){
     do{
        master_lcd_TV_control_page();
        if(re_tv_flag == 0){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if(re_tv_flag == 1){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else{ /* nothing */}
        __delay_ms(500);
        keypad_value = 0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' :
                /* TV ON */
                EUSART_ASYNC_WrireByteBlocking('c');
                re_tv_flag = 1 ;
                EEPROM_Data_WriteByte(RECEPTION_TV_ADD , ON);
                break ;
            case '2' :
                /* TV OFF */
                EUSART_ASYNC_WrireByteBlocking('d');
                re_tv_flag = 0 ;
                EEPROM_Data_WriteByte(RECEPTION_TV_ADD , OFF);
                break ;
            case '3' :
                /* home page */
                master_lcd_home_page() ;
                break ;
            default: 
                keypad_value = 0 ;
            break ; 
        }
    }while(keypad_value != '3');
    keypad_value = 0 ;
}
void Reception_AcSetTempHandler(void){
    re_AC_temp = 0 ;
    counter = 0 ; 
    EUSART_ASYNC_WrireByteBlocking('G');
    master_lcd_Set_Temperature_control_page();
    do{
       keypad_value = 0 ;
       __delay_ms(200);
       do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        if(keypad_value == '#'){
            /* save */
        }
        else if(keypad_value == '*'){
            /*re enter*/
            reception_AC_temp_val[0] = '\0' ;
            reception_AC_temp_val[1] = '\0' ;
            chr_lcd_4bit_send_string_data_position(&_master_lcd ,2, 14,"  ");
            counter = 0 ;
            re_AC_temp = 0 ;
        }
        else{
            if(counter == 2){
                counter = 0 ;
            }
            else{
                reception_AC_temp_val[counter] = keypad_value ;
                chr_lcd_4bit_send_char_data_position(&_master_lcd ,2, 14+counter , keypad_value);
                counter++;
            }
        }
    }while(keypad_value != '#');
    EEPROM_Data_Write(RECEPTION_AC_CHAR_AUTO_TEMP_ADD , reception_AC_temp_val);
    for (int i = 0; reception_AC_temp_val[i] != '\0'; i++) {
        re_AC_temp = re_AC_temp * 10 + (reception_AC_temp_val[i] - '0');
    }
    EUSART_ASYNC_WrireByteBlocking(re_AC_temp);
    re_AC_temp = 0 ;
}
void Reception_AcControlHandler(void){
    do{
        master_lcd_air_conditioner_control_page();
        if((re_AC_flag == 0) && (re_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if((re_AC_flag == 1) && (re_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else if((re_AC_flag == 0) && (re_AC_auto_flag == 1)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 20 ,"A");
        }
        else{ /* nothing */}
        __delay_ms(500);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' : 
                /* AC ON */
                EUSART_ASYNC_WrireByteBlocking('e');
                re_AC_flag = 1 ; 
                re_AC_auto_flag = 0;
                EEPROM_Data_WriteByte(RECEPTION_AC_ADD , ON);
                break ;
            case '2' : 
                /* AC OFF */
                EUSART_ASYNC_WrireByteBlocking('f');
                re_AC_flag = 0 ;
                re_AC_auto_flag = 0 ;
                EEPROM_Data_WriteByte(RECEPTION_AC_ADD , OFF);
                break ;
            case '3' : 
                /* AC AUTO */
                re_AC_flag = 0 ;
                re_AC_auto_flag = 1 ;
                re_AC_temp =0;
                EUSART_ASYNC_WrireByteBlocking('g');
                EUSART_ASYNC_WrireByteBlocking('G');
                EEPROM_Data_WriteByte(RECEPTION_AC_ADD , AUTO);
                EEPROM_Data_Read(RECEPTION_AC_CHAR_AUTO_TEMP_ADD , reception_AC_temp_val , 2);
                master_lcd_AC_Temperature_control_page(reception_AC_temp_val);
                for (int i = 0; reception_AC_temp_val[i] != '\0'; i++) {
                    re_AC_temp = re_AC_temp * 10 + (reception_AC_temp_val[i] - '0');
                }
                EUSART_ASYNC_WrireByteBlocking(re_AC_temp);
                __delay_ms(200);
                keypad_value = 0;
                do{
                    key_pad_get_value(&_master_keypad , &keypad_value);
                }while(keypad_value == 0);
                switch(keypad_value){
                    case '1' :
                        /* set Temp */
                       Reception_AcSetTempHandler();
                        break ;
                    case '2' :
                        /* home page */
                        master_lcd_home_page() ;
                        break ;
                    default :
                        keypad_value = 0 ;
                        break ;
                }
                break ;
            case '4' : 
                /* Home Page */
                master_lcd_home_page();
                break ;
            default :
                keypad_value = 0 ; 
                break;
        }
        }while(keypad_value != '4');
        keypad_value = 0 ;
}
void Reception_OFF(void){
    EUSART_ASYNC_WrireByteBlocking('x');
    re_AC_flag = 0 ;
    re_AC_auto_flag = 0 ;
    re_light_flag = 0   ;
    re_tv_flag =  0 ;
    keypad_value = 0 ;
    EEPROM_Data_WriteByte(RECEPTION_LIGHT_ADD , OFF);
    EEPROM_Data_WriteByte(RECEPTION_AC_ADD , OFF);
    EEPROM_Data_WriteByte(RECEPTION_TV_ADD , OFF);
}
void Reception_Handler(void){
    master_lcd_reception_page();
    __delay_ms(200);
    keypad_value = 0;
    do{
        key_pad_get_value(&_master_keypad , &keypad_value); 
    }while(keypad_value == 0);
    switch(keypad_value){
        case '1' :
            /* light control */
            Reception_LightControlHandler();
            break ;
        case '2' :
            /* TV Control*/
           Reception_TvControlHandler();
            break; 
        case '3' :
            /* AC Control*/
            Reception_AcControlHandler();
            break; 
        case '4' :
            /* reception OFF */
            Reception_OFF();
            break; 
         case '5' :
            /* home page */
            master_lcd_home_page();
            __delay_ms(200);
            keypad_value = 0 ;
            break; 
    }
}
void Room1_Handler(void){
    master_lcd_room1_page();
    __delay_ms(200);
    keypad_value = 0;
    do{
        key_pad_get_value(&_master_keypad , &keypad_value); 
    }while(keypad_value == 0);
    switch(keypad_value){
        case '1' :
            /* light control */
            Room1_LightControlHandler();
            break ;
        case '2' :
            /* AC Control*/
           Room1_AcControlHandler();
            break; 
        case '3' :
            /* room 1 OFF */
            Room1_OFF();
            break; 
         case '4' :
            /* home page */
            master_lcd_home_page();
            __delay_ms(200);
            keypad_value = 0 ;
            break; 
    }
}
void Room1_LightControlHandler(void){
    do{
        master_lcd_light_control_page();
        if(r1_light_flag == 0){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if(r1_light_flag == 1){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else{ /* nothing */}
        __delay_ms(200);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' :
                /* light on */
                EUSART_ASYNC_WrireByteBlocking('h');
                EEPROM_Data_WriteByte(ROOM1_LIGHT_ADD , ON);
                r1_light_flag = 1 ; 
                break ; 
            case '2' :
                /* light off */
                EUSART_ASYNC_WrireByteBlocking('i');
                EEPROM_Data_WriteByte(ROOM1_LIGHT_ADD , OFF);
                r1_light_flag = 0 ; 
                break ;
            case '3' :
                /* home page */
                master_lcd_home_page();
                __delay_ms(200);
                break ;
        }
    }while(keypad_value != '3');
    keypad_value = 0 ;
}
void Room1_AcControlHandler(void){
    do{
         master_lcd_air_conditioner_control_page();
        if((r1_AC_flag == 0) && (r1_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if((r1_AC_flag == 1) && (r1_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else if((r1_AC_flag == 0) && (r1_AC_auto_flag == 1)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 20 ,"A");
        }
        else{ /* nothing */}
        __delay_ms(200);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' : 
                /* AC ON */
                EUSART_ASYNC_WrireByteBlocking('j');
                r1_AC_flag = 1 ;
                r1_AC_auto_flag = 0 ;
                EEPROM_Data_WriteByte(ROOM1_AC_ADD , ON);
                break ;
            case '2' : 
                /* AC OFF */
                EUSART_ASYNC_WrireByteBlocking('k');
                r1_AC_flag = 0 ;
                r1_AC_auto_flag = 0 ;
                EEPROM_Data_WriteByte(ROOM1_AC_ADD , OFF);
                break ;
            case '3' : 
                /* AC AUTO */
                r1_AC_flag = 0 ;
                r1_AC_auto_flag = 1 ;
                r_1_AC_temp =0;
                EUSART_ASYNC_WrireByteBlocking('l');
                EUSART_ASYNC_WrireByteBlocking('L');
                EEPROM_Data_WriteByte(ROOM1_AC_ADD , AUTO);
                EEPROM_Data_Read(ROOM1_AC_CHAR_AUTO_TEMP_ADD , room_1_AC_temp_val , 2);
                master_lcd_AC_Temperature_control_page(room_1_AC_temp_val);
                for (int i = 0; room_1_AC_temp_val[i] != '\0'; i++) {
                    r_1_AC_temp = r_1_AC_temp * 10 + (room_1_AC_temp_val[i] - '0');
                }
                EUSART_ASYNC_WrireByteBlocking(r_1_AC_temp);
                __delay_ms(200);
                keypad_value = 0;
                do{
                    key_pad_get_value(&_master_keypad , &keypad_value);
                }while(keypad_value == 0);
                switch(keypad_value){
                    case '1' :
                        /* set Temp */
                        Room1_AcSetTempHandler();
                        break ;
                    case '2' :
                        /* home page */
                        master_lcd_home_page() ;
                        break ;
                    default :
                        keypad_value = 0 ;
                        break ;
                }
                break ;
            case '4' : 
                /* Home Page */
                master_lcd_home_page();
                break ;
            default :
                keypad_value = 0 ; 
                break;
        }
    }while(keypad_value != '4');
    keypad_value = 0 ;
}
void Room1_AcSetTempHandler(void){
    r_1_AC_temp =0;
    counter = 0 ; 
    EUSART_ASYNC_WrireByteBlocking('L');
    master_lcd_Set_Temperature_control_page();
    do{
       keypad_value = 0 ;
       __delay_ms(200);
       do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        if(keypad_value == '#'){
            /* save */
        }
        else if(keypad_value == '*'){
            /*re enter*/
            room_1_AC_temp_val[0] = '\0' ;
            room_1_AC_temp_val[1] = '\0' ;
            chr_lcd_4bit_send_string_data_position(&_master_lcd ,2, 14,"  ");
            counter = 0 ;
            r_1_AC_temp = 0 ;
        }
        else{
            if(counter == 2){
                counter = 0 ;
            }
            else{
                room_1_AC_temp_val[counter] = keypad_value ;
                chr_lcd_4bit_send_char_data_position(&_master_lcd ,2, 14+counter , keypad_value);
                counter++;
            }
        }
    }while(keypad_value != '#');
    EEPROM_Data_Write(ROOM1_AC_CHAR_AUTO_TEMP_ADD , room_1_AC_temp_val);
    for (int i = 0; room_1_AC_temp_val[i] != '\0'; i++) {
        r_1_AC_temp = r_1_AC_temp * 10 + (room_1_AC_temp_val[i] - '0');
    }
    EUSART_ASYNC_WrireByteBlocking(r_1_AC_temp);
    r_1_AC_temp = 0 ;
}
void Room1_OFF(void){
    EUSART_ASYNC_WrireByteBlocking('y');
    r1_AC_flag = 0 ;
    r1_AC_auto_flag = 0 ;
    r1_light_flag = 0   ;
    keypad_value = 0 ;
    EEPROM_Data_WriteByte(ROOM1_LIGHT_ADD , OFF);
    EEPROM_Data_WriteByte(ROOM1_AC_ADD , OFF);
}
void Room2_Handler(void){
    master_lcd_room2_page();
    __delay_ms(200);
    keypad_value = 0;
    do{
        key_pad_get_value(&_master_keypad , &keypad_value); 
    }while(keypad_value == 0);
    switch(keypad_value){
        case '1' :
            /* light control */
            Room2_LightControlHandler();
            break ;
        case '2' :
            /* AC Control*/
            Room2_AcControlHandler();
            break; 
        case '3' :
            /* room 2 OFF */
            Room2_OFF();
            break; 
         case '4' :
            /* home page */
            master_lcd_home_page();
            __delay_ms(200);
            keypad_value = 0 ;
            break; 
    }
}
void Room2_LightControlHandler(void){
    do{
        master_lcd_light_control_page();
        if(r2_light_flag == 0){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if(r2_light_flag == 1){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else{ /* nothing */}
        __delay_ms(500);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' :
                /* light on */
                EUSART_ASYNC_WrireByteBlocking('m');
                EEPROM_Data_WriteByte(ROOM2_LIGHT_ADD , ON);
                r2_light_flag = 1 ; 
                break ; 
            case '2' :
                /* light off */
                EUSART_ASYNC_WrireByteBlocking('n');
                EEPROM_Data_WriteByte(ROOM2_LIGHT_ADD , OFF);
                r2_light_flag = 0 ; 
                break ;
            case '3' :
                /* home page */
                master_lcd_home_page();
                __delay_ms(500);
                break ;
            default: 
                keypad_value = 0 ;
            break ; 
        }
    }while(keypad_value != '3');
    keypad_value = 0 ;
}
void Room2_AcControlHandler(void){
    do{
        master_lcd_air_conditioner_control_page();
        if((r2_AC_flag == 0) && (r2_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 18 ,"OFF");
        }
        else if((r2_AC_flag == 1) && (r2_AC_auto_flag == 0)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 19 ,"ON");
        }
        else if((r2_AC_flag == 0) && (r2_AC_auto_flag == 1)){
            chr_lcd_4bit_send_string_data_position(&_master_lcd , 1 , 20 ,"A");
        }
        else{ /* nothing */}
        __delay_ms(200);
        keypad_value =0 ;
        do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        switch(keypad_value){
            case '1' : 
                /* AC ON */
                EUSART_ASYNC_WrireByteBlocking('o');
                r2_AC_flag = 1 ;
                r2_AC_auto_flag = 0 ;
                EEPROM_Data_WriteByte(ROOM2_AC_ADD , ON);
                break ;
            case '2' : 
                /* AC OFF */
                EUSART_ASYNC_WrireByteBlocking('p');
                r2_AC_flag = 0 ;
                r2_AC_auto_flag = 0 ;
                EEPROM_Data_WriteByte(ROOM2_AC_ADD , OFF);
                break ;
            case '3' : 
                /* AC AUTO */
                r2_AC_flag = 0 ;
                r2_AC_auto_flag = 1 ;
                r_2_AC_temp =0 ;
                EUSART_ASYNC_WrireByteBlocking('q');
                EUSART_ASYNC_WrireByteBlocking('Q');
                EEPROM_Data_WriteByte(ROOM2_AC_ADD , AUTO);
                EEPROM_Data_Read(ROOM2_AC_CHAR_AUTO_TEMP_ADD , room_2_AC_temp_val , 2);
                master_lcd_AC_Temperature_control_page(room_2_AC_temp_val);
                for (int i = 0; room_2_AC_temp_val[i] != '\0'; i++) {
                    r_2_AC_temp = r_2_AC_temp * 10 + (room_2_AC_temp_val[i] - '0');
                }
                EUSART_ASYNC_WrireByteBlocking(r_2_AC_temp);
                __delay_ms(200);
                keypad_value = 0;
                do{
                    key_pad_get_value(&_master_keypad , &keypad_value);
                }while(keypad_value == 0);
                switch(keypad_value){
                    case '1' :
                        /* set Temp */
                        Room2_AcSetTempHandler();
                        break ;
                    case '2' :
                        /* home page */
                        master_lcd_home_page() ;
                        keypad_value = 0 ;
                        break ;
                }
                break ;
            case '4' : 
                /* Home Page */
                master_lcd_home_page();
                break ;
        }
    }while(keypad_value != '4');
    keypad_value = 0 ;
}
void Room2_AcSetTempHandler(void){
    r_2_AC_temp =0 ;
    counter = 0 ; 
    EUSART_ASYNC_WrireByteBlocking('Q');
    master_lcd_Set_Temperature_control_page();
    do{
       keypad_value = 0 ;
       __delay_ms(200);
       do{
            key_pad_get_value(&_master_keypad , &keypad_value);
        }while(keypad_value == 0);
        if(keypad_value == '#'){
            /* save */
        }
        else if(keypad_value == '*'){
            /*re enter*/
            room_2_AC_temp_val[0] = '\0' ;
            room_2_AC_temp_val[1] = '\0' ;
            chr_lcd_4bit_send_string_data_position(&_master_lcd ,2, 14,"  ");
            counter = 0 ;
            r_2_AC_temp = 0 ;
        }
        else{
            if(counter == 2){
                counter = 0 ;
            }
            else{
                room_2_AC_temp_val[counter] = keypad_value ;
                chr_lcd_4bit_send_char_data_position(&_master_lcd ,2, 14+counter , keypad_value);
                counter++;
            }
        }
    }while(keypad_value != '#');
    EEPROM_Data_Write(ROOM2_AC_CHAR_AUTO_TEMP_ADD , room_2_AC_temp_val);
    for (int i = 0; room_2_AC_temp_val[i] != '\0'; i++) {
        r_2_AC_temp = r_2_AC_temp * 10 + (room_2_AC_temp_val[i] - '0');
    }
    EUSART_ASYNC_WrireByteBlocking(r_2_AC_temp);
    r_2_AC_temp = 0 ;
}
void Room2_OFF(void){
    EUSART_ASYNC_WrireByteBlocking('z');
    r2_AC_flag = 0 ;
    r2_AC_auto_flag = 0 ;
    r2_light_flag = 0   ;
    keypad_value = 0 ;
    EEPROM_Data_WriteByte(ROOM2_LIGHT_ADD , OFF);
    EEPROM_Data_WriteByte(ROOM2_AC_ADD , OFF);
}
/*========================== Interrupt Handler ISR ==========================*/
void EUSART_RXDefaultInterruptHandler(void){
    EUSART_ASYNC_ReadByteNonBlocking(&uart_val);
    if(uart_val == 'a'){
        uart_reseption_temp = 0 ;
        EUSART_ASYNC_ReadByteBlocking(&uart_reseption_temp);
        
    }
    else if(uart_val == 'b'){
        uart_room1_temp = 0 ;
        EUSART_ASYNC_ReadByteBlocking(&uart_room1_temp);
        
    }
    else if(uart_val == 'c'){
        uart_room2_temp = 0 ;
        EUSART_ASYNC_ReadByteBlocking(&uart_room2_temp);
        
    }else{/* nothing */}
    
}
