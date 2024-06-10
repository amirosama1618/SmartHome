#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ECU_layer/buzzer/buzzer.c ECU_layer/CHAR_LCD/ecu_char_lcd.c ECU_layer/KEY_PAD/ecu_key_pad.c ECU_layer/LED/ecu_led.c ECU_layer/LM35/lm35.c ECU_layer/ecu_layer_init.c MCAL_layer/ADC/mcal_adc.c MCAL_layer/CCP1/mcal_ccp1.c MCAL_layer/EEPROM/mcal_eeprom.c MCAL_layer/EUSART/mcal_eusart.c MCAL_layer/GPIO/mcal_gpio.c MCAL_layer/I2C/mcal_i2c.c MCAL_layer/INTERRUPT/mcall_interrupt_manager.c MCAL_layer/INTERRUPT/mcal_external_interrupt.c MCAL_layer/INTERRUPT/mcal_internal_interrupt.c MCAL_layer/TIMER0/timer0.c MCAL_layer/TIMER1/timer1.c MCAL_layer/TIMER2/timer2.c MCAL_layer/TIMER3/timer3.c MCAL_layer/device_config.c MCAL_layer/lm35.c MCAL_layer/mcal_layer_init.c application.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 ${OBJECTDIR}/MCAL_layer/device_config.p1 ${OBJECTDIR}/MCAL_layer/lm35.p1 ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 ${OBJECTDIR}/application.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d ${OBJECTDIR}/MCAL_layer/device_config.p1.d ${OBJECTDIR}/MCAL_layer/lm35.p1.d ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d ${OBJECTDIR}/application.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 ${OBJECTDIR}/MCAL_layer/device_config.p1 ${OBJECTDIR}/MCAL_layer/lm35.p1 ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 ${OBJECTDIR}/application.p1

# Source Files
SOURCEFILES=ECU_layer/buzzer/buzzer.c ECU_layer/CHAR_LCD/ecu_char_lcd.c ECU_layer/KEY_PAD/ecu_key_pad.c ECU_layer/LED/ecu_led.c ECU_layer/LM35/lm35.c ECU_layer/ecu_layer_init.c MCAL_layer/ADC/mcal_adc.c MCAL_layer/CCP1/mcal_ccp1.c MCAL_layer/EEPROM/mcal_eeprom.c MCAL_layer/EUSART/mcal_eusart.c MCAL_layer/GPIO/mcal_gpio.c MCAL_layer/I2C/mcal_i2c.c MCAL_layer/INTERRUPT/mcall_interrupt_manager.c MCAL_layer/INTERRUPT/mcal_external_interrupt.c MCAL_layer/INTERRUPT/mcal_internal_interrupt.c MCAL_layer/TIMER0/timer0.c MCAL_layer/TIMER1/timer1.c MCAL_layer/TIMER2/timer2.c MCAL_layer/TIMER3/timer3.c MCAL_layer/device_config.c MCAL_layer/lm35.c MCAL_layer/mcal_layer_init.c application.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1: ECU_layer/buzzer/buzzer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/buzzer" 
	@${RM} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 ECU_layer/buzzer/buzzer.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.d ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1: ECU_layer/CHAR_LCD/ecu_char_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/CHAR_LCD" 
	@${RM} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 ECU_layer/CHAR_LCD/ecu_char_lcd.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.d ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1: ECU_layer/KEY_PAD/ecu_key_pad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/KEY_PAD" 
	@${RM} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 ECU_layer/KEY_PAD/ecu_key_pad.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.d ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/LED/ecu_led.p1: ECU_layer/LED/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/LED" 
	@${RM} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 ECU_layer/LED/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/LED/ecu_led.d ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/LM35/lm35.p1: ECU_layer/LM35/lm35.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/LM35" 
	@${RM} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 ECU_layer/LM35/lm35.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/LM35/lm35.d ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/ecu_layer_init.p1: ECU_layer/ecu_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer" 
	@${RM} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 ECU_layer/ecu_layer_init.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/ecu_layer_init.d ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1: MCAL_layer/ADC/mcal_adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/ADC" 
	@${RM} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 MCAL_layer/ADC/mcal_adc.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.d ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1: MCAL_layer/CCP1/mcal_ccp1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/CCP1" 
	@${RM} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 MCAL_layer/CCP1/mcal_ccp1.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.d ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1: MCAL_layer/EEPROM/mcal_eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/EEPROM" 
	@${RM} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 MCAL_layer/EEPROM/mcal_eeprom.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.d ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1: MCAL_layer/EUSART/mcal_eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/EUSART" 
	@${RM} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 MCAL_layer/EUSART/mcal_eusart.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.d ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1: MCAL_layer/GPIO/mcal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/GPIO" 
	@${RM} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 MCAL_layer/GPIO/mcal_gpio.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.d ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1: MCAL_layer/I2C/mcal_i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/I2C" 
	@${RM} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 MCAL_layer/I2C/mcal_i2c.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.d ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1: MCAL_layer/INTERRUPT/mcall_interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 MCAL_layer/INTERRUPT/mcall_interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1: MCAL_layer/INTERRUPT/mcal_external_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 MCAL_layer/INTERRUPT/mcal_external_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1: MCAL_layer/INTERRUPT/mcal_internal_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 MCAL_layer/INTERRUPT/mcal_internal_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1: MCAL_layer/TIMER0/timer0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER0" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 MCAL_layer/TIMER0/timer0.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.d ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1: MCAL_layer/TIMER1/timer1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER1" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 MCAL_layer/TIMER1/timer1.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.d ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1: MCAL_layer/TIMER2/timer2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER2" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 MCAL_layer/TIMER2/timer2.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.d ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1: MCAL_layer/TIMER3/timer3.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER3" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 MCAL_layer/TIMER3/timer3.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.d ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/device_config.p1: MCAL_layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/device_config.p1 MCAL_layer/device_config.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/device_config.d ${OBJECTDIR}/MCAL_layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/lm35.p1: MCAL_layer/lm35.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/lm35.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/lm35.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/lm35.p1 MCAL_layer/lm35.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/lm35.d ${OBJECTDIR}/MCAL_layer/lm35.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/lm35.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1: MCAL_layer/mcal_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 MCAL_layer/mcal_layer_init.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.d ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application.p1: application.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/application.p1.d 
	@${RM} ${OBJECTDIR}/application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/application.p1 application.c 
	@-${MV} ${OBJECTDIR}/application.d ${OBJECTDIR}/application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1: ECU_layer/buzzer/buzzer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/buzzer" 
	@${RM} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1 ECU_layer/buzzer/buzzer.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.d ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/buzzer/buzzer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1: ECU_layer/CHAR_LCD/ecu_char_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/CHAR_LCD" 
	@${RM} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1 ECU_layer/CHAR_LCD/ecu_char_lcd.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.d ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/CHAR_LCD/ecu_char_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1: ECU_layer/KEY_PAD/ecu_key_pad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/KEY_PAD" 
	@${RM} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1 ECU_layer/KEY_PAD/ecu_key_pad.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.d ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/KEY_PAD/ecu_key_pad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/LED/ecu_led.p1: ECU_layer/LED/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/LED" 
	@${RM} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1 ECU_layer/LED/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/LED/ecu_led.d ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/LED/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/LM35/lm35.p1: ECU_layer/LM35/lm35.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer/LM35" 
	@${RM} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/LM35/lm35.p1 ECU_layer/LM35/lm35.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/LM35/lm35.d ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/LM35/lm35.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_layer/ecu_layer_init.p1: ECU_layer/ecu_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_layer" 
	@${RM} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1 ECU_layer/ecu_layer_init.c 
	@-${MV} ${OBJECTDIR}/ECU_layer/ecu_layer_init.d ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_layer/ecu_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1: MCAL_layer/ADC/mcal_adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/ADC" 
	@${RM} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1 MCAL_layer/ADC/mcal_adc.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.d ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/ADC/mcal_adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1: MCAL_layer/CCP1/mcal_ccp1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/CCP1" 
	@${RM} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1 MCAL_layer/CCP1/mcal_ccp1.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.d ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/CCP1/mcal_ccp1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1: MCAL_layer/EEPROM/mcal_eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/EEPROM" 
	@${RM} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1 MCAL_layer/EEPROM/mcal_eeprom.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.d ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/EEPROM/mcal_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1: MCAL_layer/EUSART/mcal_eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/EUSART" 
	@${RM} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1 MCAL_layer/EUSART/mcal_eusart.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.d ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/EUSART/mcal_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1: MCAL_layer/GPIO/mcal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/GPIO" 
	@${RM} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1 MCAL_layer/GPIO/mcal_gpio.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.d ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/GPIO/mcal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1: MCAL_layer/I2C/mcal_i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/I2C" 
	@${RM} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1 MCAL_layer/I2C/mcal_i2c.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.d ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/I2C/mcal_i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1: MCAL_layer/INTERRUPT/mcall_interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1 MCAL_layer/INTERRUPT/mcall_interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcall_interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1: MCAL_layer/INTERRUPT/mcal_external_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1 MCAL_layer/INTERRUPT/mcal_external_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_external_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1: MCAL_layer/INTERRUPT/mcal_internal_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/INTERRUPT" 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1 MCAL_layer/INTERRUPT/mcal_internal_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.d ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/INTERRUPT/mcal_internal_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1: MCAL_layer/TIMER0/timer0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER0" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1 MCAL_layer/TIMER0/timer0.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.d ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER0/timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1: MCAL_layer/TIMER1/timer1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER1" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1 MCAL_layer/TIMER1/timer1.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.d ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER1/timer1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1: MCAL_layer/TIMER2/timer2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER2" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1 MCAL_layer/TIMER2/timer2.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.d ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER2/timer2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1: MCAL_layer/TIMER3/timer3.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer/TIMER3" 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1 MCAL_layer/TIMER3/timer3.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.d ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/TIMER3/timer3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/device_config.p1: MCAL_layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/device_config.p1 MCAL_layer/device_config.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/device_config.d ${OBJECTDIR}/MCAL_layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/lm35.p1: MCAL_layer/lm35.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/lm35.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/lm35.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/lm35.p1 MCAL_layer/lm35.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/lm35.d ${OBJECTDIR}/MCAL_layer/lm35.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/lm35.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1: MCAL_layer/mcal_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_layer" 
	@${RM} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1 MCAL_layer/mcal_layer_init.c 
	@-${MV} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.d ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_layer/mcal_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application.p1: application.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/application.p1.d 
	@${RM} ${OBJECTDIR}/application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/application.p1 application.c 
	@-${MV} ${OBJECTDIR}/application.d ${OBJECTDIR}/application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/smart_home.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/smart_home.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/smart_home.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/smart_home.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
