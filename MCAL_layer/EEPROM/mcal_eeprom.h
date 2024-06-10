/* 
 * File:   mcal_eeprom.h
 * Author: Ameer
 *
 * Created on February 24, 2024, 11:49 PM
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/*=========================== section : includes ===========================*/
#include "pic18f4620.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "../../MCAL_layer/mcal_std_types.h"
/*=========================== section : Macro definitions ===========================*/

/*=========================== section : Macro functions definitions ===========================*/

/*=========================== section : Data type declaration ===========================*/

/*=========================== section : functions declarations ===========================*/
/**
 * @breif function to write data into EEPROM
 * @param bAdd the address to write the data in 
 * @param bData the data need to write in EEPROM
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EEPROM_Data_WriteByte(uint16 bAdd, uint8 bData);

STD_ReturnType EEPROM_Data_Write(uint16 bAdd,uint8 *bData);
/**
 * @breif function to read data from EEPROM 
 * @param bAdd the address to read the data from
 * @param bData pointer to return the data in 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EEPROM_Data_ReadByte(uint16 bAdd, uint8 *bData);
STD_ReturnType EEPROM_Data_Read(uint16 bAdd, uint8 *bData , uint16 length);
#endif	/* MCAL_EEPROM_H */

