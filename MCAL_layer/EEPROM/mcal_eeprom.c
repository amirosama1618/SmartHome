/* 
 * File:   mcal_eeprom.c
 * Author: Ameer
 *
 * Created on February 24, 2024, 11:49 PM
 */

#include "mcal_eeprom.h"

/**
 * @breif function to write data into EEPROM
 * @param bAdd the address to write the data in 
 * @param bData the data need to write in EEPROM
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EEPROM_Data_WriteByte(uint16 bAdd, uint8 bData){
    STD_ReturnType error_state = E_NOT_OK ;
        /* Read the Interrupt Status "Enabled or Disabled"*/
        uint8 Interrupt_status = INTCONbits.GIE ;
        /* write the address in EEADR and EEADRH registers */
        EEADRH = (uint8)((bAdd >> 8)& 0x03);
        EEADR  = (uint8)(bAdd & 0xFF);
        /* write the data in EEDATA register */
        EEDATA = bData ; 
        /* clear EEPGD bit in EECON1 register to select EEPROM */
        EECON1bits.EEPGD = 0 ; 
        /* clear CFGS bit in EECON1 register to select Flash/EEPROM */
        EECON1bits.CFGS = 0 ;
        /* set WREN bit in EECON1 to enable data write */
        EECON1bits.WREN = 1 ; 
        /* disable Global Interrupt : clear GIE/GIEH bit in INTCON register */
        INTERRUPT_GlobalInterruptDisable();
        /*  write 55h to EECON2, write 0AAh to EECON2
        * !! The write will not begin if this sequence is not exactly */
        EECON2 = 0x55 ;
        EECON2 = 0xAA ;
        /* set WR bit in EECON1 register to start writing the data 
        * (can only be set (not cleared) in software)*/
        EECON1bits.WR = 1 ;
        /* wait for WR bit cleared : Write cycle to the EEPROM is complete */
        while(EECON1bits.WR);
        /* clear WREN bit in EECON1 register to Inhibits write cycles to data EEPROM*/
        EECON1bits.WREN = 0 ;
        /* Restore the Interrupt status before writing cycle */
        INTCONbits.GIE = Interrupt_status ;
        error_state = E_OK ;
    
    return error_state ; 
}
STD_ReturnType EEPROM_Data_Write(uint16 bAdd,uint8 *bData){
    STD_ReturnType error_state = E_NOT_OK ; 
    uint16 i = 0 ; 
    if(NULL == bData){
        error_state = E_NOT_OK ;
    }
    else{
        for (uint16_t i = 0; bData[i] != NULL ; i++) {
            error_state = EEPROM_Data_WriteByte(bAdd + i, bData[i]);
        }
    }
    return error_state ;
}
/**
 * @breif function to  one byte read data from EEPROM 
 * @param bAdd the address to read the data from
 * @param bData pointer to return the data in 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType EEPROM_Data_ReadByte(uint16 bAdd, uint8 *bData){
    STD_ReturnType error_state = E_NOT_OK ;
    if(NULL == bData){
        error_state = E_NOT_OK;
    }
    else{
        /* Write the address in EEADR and EEADRH */
        EEADRH = (uint8)((bAdd >> 8)& 0x03);
        EEADR  = (uint8)(bAdd & 0xFF);
        /* clear EEPGD bit in EECON1 register to select EEPROM */
        EECON1bits.EEPGD = 0 ; 
        /* clear CFGS bit in EECON1 register to select Flash/EEPROM */
        EECON1bits.CFGS = 0 ;
        /* Set RD bit in EECON1 register to start reading process */
        EECON1bits.RD = 1 ; 
        /* wait at least 2 operations in high frequancy */
        NOP(); NOP();
        /* Return the data from EEDATA register */
        *bData = EEDATA ; 
        
        error_state = E_OK ;
    }
    return error_state ; 
}
STD_ReturnType EEPROM_Data_Read(uint16 bAdd, uint8 *bData , uint16 length){
    STD_ReturnType error_state = E_NOT_OK ;
    uint16 i = 0 ; 
    if(NULL == bData){
        error_state = E_NOT_OK ;
    }
    else{
        for (i = 0; i<length ; i++) {
            error_state = EEPROM_Data_ReadByte(bAdd + i, bData+i);
        }
    }
    return error_state ;
}