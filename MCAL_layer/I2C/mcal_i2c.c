/* 
 * File:   mcal_i2c.c
 * Author: Ameer
 *
 * Created on March 30, 2024, 2:36 PM
 */


/*================================ section : includes ================================*/
#include "mcal_i2c.h"
/*================================ section : Data type declaration ================================*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
InterruptHandler I2C_InterruptHandler      = NULL ;
InterruptHandler I2C_BC_InterruptHandler  = NULL ;
InterruptHandler I2C_Read_OverFlow_InterruptHandler  = NULL ;
#endif
/*================================ section : Helper Functions declaration  ================================*/
static inline void mssp_i2c_mode_select(const mssp_i2c_t* i2c_obj);
static inline void mssp_i2c_mode_master_clock_configurations(const mssp_i2c_t* i2c_obj);
static inline void mssp_i2c_mode_slave_configurations(const mssp_i2c_t* i2c_obj);
static inline void mssp_i2c_mode_gpio_cfg(void);
static inline void mssp_i2c_mode_slew_rate_cfg(const mssp_i2c_t* i2c_obj);
static inline void mssp_i2c_mode_SMBus_rate_cfg(const mssp_i2c_t* i2c_obj);
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void mssp_i2c_mode_interrupt_cfg(const mssp_i2c_t* i2c_obj);
#endif
/*================================ section : functions Impelemntation  ================================*/
/**
 * @breif function to Initialize MSSP I2C mode
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Init(const mssp_i2c_t* i2c_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == i2c_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Disable MSSP module */
        I2C_MSSP_MODULE_DISABLE_CFG();
        /* configure I2C mode selected */
        mssp_i2c_mode_select(i2c_obj);
        /* MSSP I2C GPIO Configurations */
        mssp_i2c_mode_gpio_cfg();
        /* MSSP Interrupt Configurations */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        mssp_i2c_mode_interrupt_cfg(i2c_obj);
#endif
        /* MSSP I2C SLEW rate Control */
        mssp_i2c_mode_slew_rate_cfg(i2c_obj);
        /* MSSP I2C SMBus Control */
        mssp_i2c_mode_SMBus_rate_cfg(i2c_obj);
        /* Interrupt Configurations */
        /* Enable MSSP module */
        I2C_MSSP_MODULE_ENABLE_CFG();
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif function to De-Initialize MSSP I2C Mode
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t* i2c_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == i2c_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Disable MSSP module */
        I2C_MSSP_MODULE_DISABLE_CFG();
        /* Disable Interrupt If it was Enabled */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptDisable();
#endif
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif function master send start condition to start communication 
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendStart(const mssp_i2c_t* i2c_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == i2c_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Initiates Start Condition on SDA and SCL Pins */
        I2C_START_CONDITION_INITIATE_CFG();
        /* Wait for Completion of Start Condition */
        while(I2C_START_CONDITION_STATE_CFG());
        /* Clear The MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0 ;
        /* Report The Start Condition Detection */
        if(I2C_START_BIT_INDICATE_CFG()){
           error_state = E_OK ; 
        }
        else{error_state = E_NOT_OK ; }
    }
    return error_state ; 
}
/**
 * @breif function master send repeated start condition
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendRepeatedStart(const mssp_i2c_t* i2c_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == i2c_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Initiates Start Condition on SDA and SCL Pins */
        I2C_REPEATED_START_CONDITION_INITIATE_CFG();
        /* Wait for Completion of Start Condition */
        while(I2C_REPEATED_START_CONDITION_STATE_CFG());
        /* Clear The MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0 ;
        error_state = E_OK ; 
    }
    return error_state ; 
}
/**
 * @breif function master send repeated stop condition to stop communication 
 *        @note only used in master mode 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_MasterSendStop(const mssp_i2c_t* i2c_obj){
    STD_ReturnType error_state = E_NOT_OK ; 
    if(NULL == i2c_obj){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Initiates Stop Condition on SDA and SCL Pins */
        I2C_STOP_CONDITION_INITIATE_CFG();
        /* Wait for Completion of STOP Condition */
        while(I2C_STOP_CONDITION_STATE_CFG());
        /* Clear The MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0 ;
        /* Report The Start Condition Detection */
        if(I2C_STOP_BIT_INDICATE_CFG()){
           error_state = E_OK ; 
        }
        else{error_state = E_NOT_OK ; } 
    }
    return error_state ; 
}
/**
 * @breif function to write byte on the I2C Bus 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @param i2c_data the data need to be send
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t* i2c_obj , uint8 i2c_data , uint8 *i2c_ack){
    STD_ReturnType error_state = E_NOT_OK ; 
    if((NULL == i2c_obj) || (NULL == i2c_ack)){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Write Data to the Data Register */
        SSPBUF = i2c_data ; 
        /* Wait for Completion of the Transmission */
        while(I2C_BUFFER_STATUS_CFG());
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report The ACK Received From The Slave */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == I2C_ACK_STATUS_CFG()){
            *i2c_ack = I2C_ACK_RECEIVED_FROM_SLAVE ; 
            error_state = E_OK ;
        }
        else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == I2C_ACK_STATUS_CFG()){
            *i2c_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE ; 
            error_state = E_OK ;
        }
        else{error_state = E_NOT_OK ;}
         
    }
    return error_state ; 
}
/**
 * @breif function to write byte on the I2C Bus 
 * @preconditions MSSP_I2C_Init(); function must be called first
 * @param i2c_obj pointer to I2C configurations
 * @param ack
 * @param i2c_data pointer to store the read data 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t* i2c_obj , uint8 ack , uint8* i2c_data){
    STD_ReturnType error_state = E_NOT_OK ; 
    if((NULL == i2c_obj)|| (NULL == i2c_data)){
        error_state = E_NOT_OK ; 
    }
    else{
        /* Enable Master Receiver Mode */
        I2C_MASTER_RECEIVER_CONTROL_ENABLE_CFG() ; 
        /* Wait For Complete Byte Received */
        while(!I2C_BUFFER_STATUS_CFG());
        /* Copy the Data Register To Buffer Variable */
        *i2c_data = SSPBUF ; 
        /* Send The ACK After Read */
        if(I2C_MASTER_SEND_ACK == ack){
            I2C_MASTER_SEND_ACK_CFG();
            I2C_MASTER_INITIATE_ACK_SEQUENCE_CFG();
            error_state = E_OK ;
        }
        else if(I2C_MASTER_SEND_NACK == ack){
            I2C_MASTER_SEND_NACK_CFG();
            I2C_MASTER_INITIATE_ACK_SEQUENCE_CFG();
            error_state = E_OK ;
        }
        else{ error_state = E_NOT_OK ;  }
        *i2c_data = SSPBUF ; 
        PIR1bits.SSPIF = 0 ; 
         
    }
    return error_state ; 
}
/*================================ section : ISR Functions Impelemntation  ================================*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void MSSP_I2C_ISR(void){
    MSSP_I2C_InterruptFlagClear();
    if(I2C_InterruptHandler){
        I2C_InterruptHandler();
    }
}
void MSSP_I2C_BC_ISR(void){
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(I2C_BC_InterruptHandler){
        I2C_BC_InterruptHandler();
    }
}
#endif
/*================================ section : Helper Functions Impelemntation  ================================*/
static inline void mssp_i2c_mode_select(const mssp_i2c_t* i2c_obj){
    if(I2C_MASTER_MODE ==i2c_obj->i2c_cfg.i2c_mode){ 
        /* I2C Master Mode Clock Configurations */
        mssp_i2c_mode_master_clock_configurations(i2c_obj);
    }
    else if(I2C_SLAVE_MODE ==i2c_obj->i2c_cfg.i2c_mode){
        /* I2C Slave Mode Clock Configurations */
        /* I2C General Call Configure */
        if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call){
            I2C_GENERAL_CALL_ENABLE_CFG(); 
        }
        else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
            I2C_GENERAL_CALL_DISABLE_CFG();
        }
        else{/* nothing */}
        /* clear the Write Collision Detect */
        I2C_SLAVE_NO_COLLISION_DETECTED();
        /* clear the Receive OverFlow Detect */
        I2C_SLAVE_NO_OVERFLOW_DETECTED();
        /* Release The Clock */
        I2C_SLAVE_RELEASE_CLK();
        /* Assign the I2C Slave Address */
        SSPADD = i2c_obj->i2c_cfg.i2c_slave_address ; 
        /* i2C slave Mode Configurations */
        mssp_i2c_mode_slave_configurations(i2c_obj);
    }
    else{/* nothing */}
}
static inline void mssp_i2c_mode_master_clock_configurations(const mssp_i2c_t* i2c_obj){
    I2C_Master_Synchronous_Serial_Port_Mode_Select_CFG(i2c_obj->i2c_cfg.i2c_mode_cfg);
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_master_clock_freq) - 1);
}
static inline void mssp_i2c_mode_slave_configurations(const mssp_i2c_t* i2c_obj){
    I2C_Master_Synchronous_Serial_Port_Mode_Select_CFG(i2c_obj->i2c_cfg.i2c_mode_cfg);
}
static inline void mssp_i2c_mode_gpio_cfg(void){
    TRISCbits.TRISC3 = 1; /* Serial clock (SCL) is Input */
    TRISCbits.TRISC4 = 1; /* Serial data (SDA) is Input */
}
static inline void mssp_i2c_mode_slew_rate_cfg(const mssp_i2c_t* i2c_obj){
    if(I2C_SLEW_RATE_ENABLE ==i2c_obj->i2c_cfg.i2c_slew_rate){
        I2C_SLEW_RATE_ENABLE_CFG();
    }
    else if(I2C_SLEW_RATE_DISABLE ==i2c_obj->i2c_cfg.i2c_slew_rate){
        I2C_SLEW_RATE_DISABLE_CFG();
    }
    else{/* nothing */}
}
static inline void mssp_i2c_mode_SMBus_rate_cfg(const mssp_i2c_t* i2c_obj){
    if(I2C_SM_BUS_ENABLE ==i2c_obj->i2c_cfg.i2c_SM_bus_control){
        I2C_SM_BUS_ENABLE_CFG();
    }
    else if(I2C_SM_BUS_DISABLE ==i2c_obj->i2c_cfg.i2c_SM_bus_control){
        I2C_SM_BUS_DISABLE_CFG();
    }
    else{/* nothing */}
}
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void mssp_i2c_mode_interrupt_cfg(const mssp_i2c_t* i2c_obj){
    MSSP_I2C_InterruptDisable();
    MSSP_I2C_InterruptFlagClear();
    MSSP_I2C_BUS_COL_InterruptDisable();
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    /* set Interrupt Handlers */
    I2C_InterruptHandler                    = i2c_obj->I2C_Report_InterruptHandler ; 
    I2C_BC_InterruptHandler                = i2c_obj->I2C_Report_Write_Collision ; 
    I2C_Read_OverFlow_InterruptHandler = i2c_obj->I2C_Report_Read_OverFlow ; 
    /* set priority configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority){
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_I2C_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority){
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_I2C_LowPrioritySet();
    }
    else{ /* nothing */ }
    /* set Interrupt configurations for Bus Collission */
    if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority){
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_I2C_BUS_COL_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority){
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_I2C_BUS_COL_LowPrioritySet();
    }
    else{ /* nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PrephralInterruptEnable();
#endif
    MSSP_I2C_InterruptEnable();
    MSSP_I2C_BUS_COL_InterruptEnable();
}
#endif