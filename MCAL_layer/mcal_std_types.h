/* 
 * File:   mcal_std_types.h
 * Author: Ameer
 *
 * Created on January 30, 2024, 3:38 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H



/* section : includes */
#include "std_libraries.h"
#include "compiler.h"

/* section : Data type declaration */
typedef unsigned char   uint8   ;
typedef unsigned short  uint16  ;
typedef unsigned int    uint32  ;

typedef signed char   sint8   ;
typedef signed short  sint16  ;
typedef signed int    sint32  ;

typedef uint8 STD_ReturnType    ;

/* section : Macro definitions */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (STD_ReturnType)0x01
#define E_NOT_OK        (STD_ReturnType)0x00

#define PORT_OUTPUT     0x00
#define PORT_INPUT      0xff

#define ZERO_INIT       0


/* section : Macro functions definitions */


/* section : functions declarations */
#endif	/* MCAL_STD_TYPES_H */

