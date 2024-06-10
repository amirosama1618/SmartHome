/* 
 * File:   mcal_ccp1_cfg.h
 * Author: Ameer
 * CAPTURE/COMPARE/PWM (CCP1) MODULE
 * Created on March 10, 2024, 1:33 AM
 */

#ifndef MCAL_CCP1_CFG_H
#define	MCAL_CCP1_CFG_H
/*================================ section : includes ================================*/

/*================================ section : Macro definitions ================================*/
#define CCP_CFG_CAPTURE_MODE_SELECTED  0x00
#define CCP_CFG_COMPARE_MODE_SELECTED  0x01
#define CCP_CFG_PWM_MODE_SELECTED       0x02

#define CCP1_CFG_SELECTED_MODE  (CCP_CFG_PWM_MODE_SELECTED)
#define CCP2_CFG_SELECTED_MODE  (CCP_CFG_PWM_MODE_SELECTED)
/*================================ section : Data type declaration ================================*/

/*================================ section : functions declarations ================================*/

#endif	/* MCAL_CCP1_CFG_H */

