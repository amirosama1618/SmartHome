/* 
 * File:   mcal_ccp1.h
 * Author: Ameer
 * CAPTURE/COMPARE/PWM (CCP) MODULE
 * Created on March 10, 2024, 1:26 AM
 */

#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

/*================================ section : includes ================================*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../std_libraries.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "../GPIO/mcal_gpio.h"
#include "../TIMER1/timer1.h"
#include "../TIMER2/timer2.h"
#include "../TIMER3/timer3.h"
#include "mcal_ccp1_cfg.h"
/*================================ section : Macro definitions ================================*/
/**
 * CCP1M3:CCP1M0: CCP1 Module Mode Select bits
 */
#define CCP_MODULE_DISABLE         0x00

/* CCP Capture sub-Mode */
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
#define CCP_CAPTURE_MODE_1_FALLING_EDGE        ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE         ((uint8) 0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE         ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE        ((uint8)0x07)
/* Capture Mode State */
#define CCP_CAPTURE_NOT_READY          0x00
#define CCP_CAPTURE_READY                0x01
#endif

/* CCP Compare sub-Mode*/
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
#define CCP_COMPARE_MODE_SET_PIN_LOW            ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH           ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH       ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT      ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT                ((uint8)0x0B)
/* Compare Mode State */
#define CCP_COMPARE_NOT_READY          0x00
#define CCP_COMPARE_READY               0x01
#endif

/* CCP PWM Mode */
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
#define CCP_PWM_MODE                                   ((uint8)0x0C)
#endif
/*================================ section : Macro Functions ================================*/
/* macro function to set CCP Sub-mode */
#define CCP1_SET_MODE(_CONFIG)      (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)      (CCP2CONbits.CCP2M = _CONFIG)
/*================================ section : Data type declaration ================================*/
/**
 * @breif define the CCP inst. CCP1 or CCP2
 */
typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;
/**
 * @breif define capture mode timer select : timer1 or timer3
 */
typedef enum{
    CCP1_CCP2_TIMER1_SELECT = 0,
    CCP1_TIMER1_CCP2_TIMER3_SELECT,
    CCP1_CCP2_TIMER3_SELECT
}ccp_capture_timer_select_t;
/**
 * @breif define the value to select the CCP1 Main Mode        
 */
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0,     /* select capture mode */
    CCP_COMPARE_MODE_SELECTED,         /* select compare mode */
    CCP_PWM_MODE_SELECTED                /* select pwm mode */
}ccp_mode_t;
/**
 * @breif   define the values to convert the 16bit to two 8bit and vice versa 
 */
typedef union{
    struct{
        uint8 ccpr_low ;           /* CCPRx Low Register */
        uint8 ccpr_high  ;         /* CCPRx High Register */
    };
    struct{
        uint16 ccpr_16bit  ;       /* Read CCPRx as a 16bit Value  */
    };
}ccp_reg_t;

typedef struct {
    ccp_inst_t ccp_inst ;            /* @ref ccp_inst_t */
    ccp_mode_t ccp_mode   ;          /* @ref ccp1_mode_t */
    uint8 ccp_sub_mode :4  ;
#if ((CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)||(CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE))
    void (*ccp_InterruptHandler)(void) ; 
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg ccp_priority ; 
    #endif
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
    ccp_capture_timer_select_t ccp_capture_timer ;          /* @ref ccp_capture_timer_select_t */
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
    ccp_capture_timer_select_t ccp_capture_timer ;          /* @ref ccp_capture_timer_select_t */
#endif
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
    uint32 pwm_frequency ;                     
    uint8 timer2_postscaler_value   :4 ;    /*@ref timer2_postscaler_select_t*/
    uint8 timer2_prescaler_value    : 2;    /* @ref timer2_prescaler_select_t*/
#endif
}ccp_config_t;
/*================================ section : functions declarations ================================*/
/**
 * @breif function to initialize CCP module
 * @preconditions NONE
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_Init(const ccp_config_t *_ccp );
/**
 * @breif function to De-Initialize the CCP module
 * @preconditions NONE
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_DeInit(const ccp_config_t *_ccp );

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED))
/**
 * @breif function to check capture mode status "CCP_CAPTURE_READY" or "CCP_CAPTURE_READY" 
 * @preconditions CCP_Init() function must called before,
 *                CCP1_CFG_SELECTED_MODE() must select capture mode in mcal_ccp_cfg file 
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _capture_status pointer to return the capture status 
 *        @note 0x01 : CCP_CAPTURE_READY
 *              0x00 : CCP_CAPTURE_READY
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_IsCaptureDataReady(const ccp_config_t *_ccp, uint8 *_capture_status);
/**
 * @breif function to read the captured value 
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select capture mode in mcal_ccp1_cfg file  
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _capture_value pointer to return the captured value 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_CaptureModeReadValue(const ccp_config_t *_ccp,uint16 *_capture_value);
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED))
/**
 * @breif function to check the compare status "CCP_COMPARE_READY" or "CCP_COMPARE_NOT_READY"
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select compare mode in mcal_ccp1_cfg file  
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _compare_status pointer to return the compare status 
 *        @note 0x01 : CCP_COMPARE_READY
 *              0x00 : CCP_COMPARE_NOT_READY
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_IsCompareComplete(const ccp_config_t *_ccp, uint8 *_compare_status);
/**
 * @breif function to set compare value in CCPx register 
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select compare mode in mcal_ccp1_cfg file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _compare_value the compare value need to be set 
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_CompareModeSetValue(const ccp_config_t *_ccp, uint16 _compare_value);
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
/**
 * @breif function to set Duty of the PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @param _duty value of the Duty of the PWM need to be set 
 *        @note (_duty) value : 0 to 100
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMSetDuty(const ccp_config_t *_ccp, const uint8 _duty);
/**
 * @breif function to Start PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMStart(const ccp_config_t *_ccp);
/**
 * @breif function to End PWM
 * @preconditions CCP_Init() function must called before,
 *                CCPx_CFG_SELECTED_MODE() must select PWM mode in 'mcal_ccp1_cfg' file
 * @param _ccp pointer to CCP module configurations @ref ccp_config_t
 * @return STD_Returntype error state
 *         (E_OK) : function done successfully 
 *         (E_NOT_OK) : the function has an issue to perform this action
 */
STD_ReturnType CCP_PWMEnd(const ccp_config_t *_ccp);
#endif

#endif	/* MCAL_CCP1_H */

