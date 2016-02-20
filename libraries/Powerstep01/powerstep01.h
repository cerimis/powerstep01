/******************************************************//**
 * @file    Powerstep01.h
 * @version V1.0
 * @date    March 3, 2014
 * @brief   Header for Powerstep01   library for arduino
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 **********************************************************/ 

#ifndef __POWERSTEP01_H_INCLUDED
#define __POWERSTEP01_H_INCLUDED

#include "Arduino.h"
#include <inttypes.h>

#include "../Powerstep01/Powerstep01_target_config.h"

//To use 3 Powerstep01 shield boards you have to ebable this flag
//but you will no more able to use Arduino functions which
//are based on timer 0 (delay(), millis()...)
//#define _USE_TIMER_0_FOR_Powerstep01

/// Define to print debug logs via the UART 
#ifndef _DEBUG_Powerstep01
//#define _DEBUG_Powerstep01
#endif

#ifdef _DEBUG_Powerstep01
/// Size of the log buffer
#define DEBUG_BUFFER_SIZE    (75)
/// Log buffer
extern char Powerstep01StrOut[DEBUG_BUFFER_SIZE];
#endif

/// Clear bit Macro 
#ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

/// Set bit Macro 
#ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/// Current FW version
#define Powerstep01_FW_VERSION (1)

/// Digital Pins used for the Powerstep01 flag pin
#define Powerstep01_FLAG_Pin   (2)
/// Digital Pins used for the Powerstep01 step clock pin of shield 0
#define Powerstep01_PWM_1_Pin  (9)
/// Digital Pins used for the Powerstep01 step clock pin of shield 1
#define Powerstep01_PWM_2_Pin  (3)
/// Digital Pins used for the Powerstep01 step clock pin of shield 2
#define Powerstep01_PWM_3_Pin  (6)
/// Digital Pins used for the Powerstep01 direction pin of shield 0
#define Powerstep01_DIR_1_Pin  (7)
/// Digital Pins used for the Powerstep01 direction pin of shield 1
#define Powerstep01_DIR_2_Pin  (4)
/// Digital Pins used for the Powerstep01 direction pin of shield 2
#define Powerstep01_DIR_3_Pin  (5)
/// Digital Pins used for the Powerstep01 reset pin
#define Powerstep01_Reset_Pin  (8)

/// Maximum number of steps
#define MAX_STEPS         (0x7FFFFFFF)
/// uint8_t max value
#define UINT8_MAX         (uint8_t)(0XFF)
/// uint16_t max value
#define UINT16_MAX        (uint16_t)(0XFFFF)

/// Pwm prescaler array size for timer 0 & 1
#define PRESCALER_ARRAY_TIMER0_1_SIZE   (6)
/// Pwm prescaler array size for timer 2
#define PRESCALER_ARRAY_TIMER2_SIZE     (8)

/// Maximum frequency of the PWMs
#define Powerstep01_MAX_PWM_FREQ   (10000)
/// Minimum frequency of the PWMs
#define Powerstep01_MIN_PWM_FREQ   (30)
  
/// Powerstep01 max number of bytes of command & arguments to set a parameter
#define Powerstep01_CMD_ARG_MAX_NB_BYTES              (4)

/// Powerstep01 command + argument bytes number for NOP command
#define Powerstep01_CMD_ARG_NB_BYTES_NOP              (1)
/// Powerstep01 command + argument bytes number for ENABLE command
#define Powerstep01_CMD_ARG_NB_BYTES_ENABLE           (1)
/// Powerstep01 command + argument bytes number for DISABLE command
#define Powerstep01_CMD_ARG_NB_BYTES_DISABLE          (1)
/// Powerstep01 command + argument bytes number for GET_STATUS command
#define Powerstep01_CMD_ARG_NB_BYTES_GET_STATUS       (1)

/// Powerstep01 response bytes number
#define Powerstep01_RSP_NB_BYTES_GET_STATUS           (2)

/// Daisy chain command mask
#define DAISY_CHAIN_COMMAND_MASK (0xFA)

/// Powerstep01 value mask for ABS_POS register
#define Powerstep01_ABS_POS_VALUE_MASK    ((uint32_t) 0x003FFFFF)
/// Powerstep01 sign bit mask for ABS_POS register
#define Powerstep01_ABS_POS_SIGN_BIT_MASK ((uint32_t) 0x00200000)

/// Powerstep01 step mask for electrical position (EL_POS) register
#define Powerstep01_ELPOS_STEP_MASK       ((uint8_t)0xC0)
/// Powerstep01 microstep mask for electrical position (EL_POS) register
#define Powerstep01_ELPOS_MICROSTEP_MASK  ((uint8_t)0x3F)

/// Powerstep01 fast decay time option (TOFF_FAST values for T_FAST register )
typedef enum {
  Powerstep01_TOFF_FAST_2us = ((uint8_t) 0x00 << 4),
  Powerstep01_TOFF_FAST_4us = ((uint8_t) 0x01 << 4),
  Powerstep01_TOFF_FAST_6us = ((uint8_t) 0x02 << 4),
  Powerstep01_TOFF_FAST_8us = ((uint8_t) 0x03 << 4),
  Powerstep01_TOFF_FAST_10us = ((uint8_t) 0x04 << 4),
  Powerstep01_TOFF_FAST_12us = ((uint8_t) 0x05 << 4),
  Powerstep01_TOFF_FAST_14us = ((uint8_t) 0x06 << 4),
  Powerstep01_TOFF_FAST_16us = ((uint8_t) 0x07 << 4),
  Powerstep01_TOFF_FAST_18us = ((uint8_t) 0x08 << 4),
  Powerstep01_TOFF_FAST_20us = ((uint8_t) 0x09 << 4),
  Powerstep01_TOFF_FAST_22us = ((uint8_t) 0x0A << 4),
  Powerstep01_TOFF_FAST_24us = ((uint8_t) 0x0B << 4),
  Powerstep01_TOFF_FAST_26us = ((uint8_t) 0x0C << 4),
  Powerstep01_TOFF_FAST_28us = ((uint8_t) 0x0D << 4),
  Powerstep01_TOFF_FAST_30us = ((uint8_t) 0x0E << 4),
  Powerstep01_TOFF_FAST_32us = ((uint8_t) 0x0F << 4)
} Powerstep01_TOFF_FAST_t;

/// Powerstep01 fall step time options (FAST_STEP values for T_FAST register )
typedef enum {
  Powerstep01_FAST_STEP_2us = ((uint8_t) 0x00),
  Powerstep01_FAST_STEP_4us = ((uint8_t) 0x01),
  Powerstep01_FAST_STEP_6us = ((uint8_t) 0x02),
  Powerstep01_FAST_STEP_8us = ((uint8_t) 0x03),
  Powerstep01_FAST_STEP_10us = ((uint8_t) 0x04),
  Powerstep01_FAST_STEP_12us = ((uint8_t) 0x05),
  Powerstep01_FAST_STEP_14us = ((uint8_t) 0x06),
  Powerstep01_FAST_STEP_16us = ((uint8_t) 0x07),
  Powerstep01_FAST_STEP_18us = ((uint8_t) 0x08),
  Powerstep01_FAST_STEP_20us = ((uint8_t) 0x09),
  Powerstep01_FAST_STEP_22us = ((uint8_t) 0x0A),
  Powerstep01_FAST_STEP_24us = ((uint8_t) 0x0B),
  Powerstep01_FAST_STEP_26us = ((uint8_t) 0x0C),
  Powerstep01_FAST_STEP_28us = ((uint8_t) 0x0D),
  Powerstep01_FAST_STEP_30us = ((uint8_t) 0x0E),
  Powerstep01_FAST_STEP_32us = ((uint8_t) 0x0F)
} Powerstep01_FAST_STEP_t;

/// Powerstep01 overcurrent threshold options (OCD_TH register)
typedef enum {
  Powerstep01_OCD_TH_375mA  = ((uint8_t) 0x00),
  Powerstep01_OCD_TH_750mA  = ((uint8_t) 0x01),
  Powerstep01_OCD_TH_1125mA = ((uint8_t) 0x02),
  Powerstep01_OCD_TH_1500mA = ((uint8_t) 0x03),
  Powerstep01_OCD_TH_1875mA = ((uint8_t) 0x04),
  Powerstep01_OCD_TH_2250mA = ((uint8_t) 0x05),
  Powerstep01_OCD_TH_2625mA = ((uint8_t) 0x06),
  Powerstep01_OCD_TH_3000mA = ((uint8_t) 0x07),
  Powerstep01_OCD_TH_3375mA = ((uint8_t) 0x08),
  Powerstep01_OCD_TH_3750mA = ((uint8_t) 0x09),
  Powerstep01_OCD_TH_4125mA = ((uint8_t) 0x0A),
  Powerstep01_OCD_TH_4500mA = ((uint8_t) 0x0B),
  Powerstep01_OCD_TH_4875mA = ((uint8_t) 0x0C),
  Powerstep01_OCD_TH_5250mA = ((uint8_t) 0x0D),
  Powerstep01_OCD_TH_5625mA = ((uint8_t) 0x0E),
  Powerstep01_OCD_TH_6000mA = ((uint8_t) 0x0F)
} Powerstep01_OCD_TH_t;

/// Powerstep01 STEP_MODE register masks
typedef enum {
  Powerstep01_STEP_MODE_STEP_SEL = ((uint8_t) 0x07),
  Powerstep01_STEP_MODE_SYNC_SEL = ((uint8_t) 0x70)
} Powerstep01_STEP_MODE_Masks_t;

/// Powerstep01 STEP_SEL options for STEP_MODE register
typedef enum {
  Powerstep01_STEP_SEL_1    = ((uint8_t) 0x08),  //full step
  Powerstep01_STEP_SEL_1_2  = ((uint8_t) 0x09),  //half step
  Powerstep01_STEP_SEL_1_4  = ((uint8_t) 0x0A),  //1/4 microstep
  Powerstep01_STEP_SEL_1_8  = ((uint8_t) 0x0B),  //1/8 microstep
  Powerstep01_STEP_SEL_1_16 = ((uint8_t) 0x0C)   //1/16 microstep
} Powerstep01_STEP_SEL_t;

/// Powerstep01 SYNC_SEL options for STEP_MODE register
typedef enum {
  Powerstep01_SYNC_SEL_1_2    = ((uint8_t) 0x80),
  Powerstep01_SYNC_SEL_1      = ((uint8_t) 0x90),
  Powerstep01_SYNC_SEL_2      = ((uint8_t) 0xA0),
  Powerstep01_SYNC_SEL_4      = ((uint8_t) 0xB0),
  Powerstep01_SYNC_SEL_8      = ((uint8_t) 0xC0),
  Powerstep01_SYNC_SEL_UNUSED = ((uint8_t) 0xD0)
} Powerstep01_SYNC_SEL_t;

/// Powerstep01 ALARM_EN register options
typedef enum {
  Powerstep01_ALARM_EN_OVERCURRENT      = ((uint8_t) 0x01),
  Powerstep01_ALARM_EN_THERMAL_SHUTDOWN = ((uint8_t) 0x02),
  Powerstep01_ALARM_EN_THERMAL_WARNING  = ((uint8_t) 0x04),
  Powerstep01_ALARM_EN_UNDERVOLTAGE     = ((uint8_t) 0x08),
  Powerstep01_ALARM_EN_SW_TURN_ON       = ((uint8_t) 0x40),
  Powerstep01_ALARM_EN_WRONG_NPERF_CMD  = ((uint8_t) 0x80)
} Powerstep01_ALARM_EN_t;

/// Powerstep01 CONFIG register masks
typedef enum {
  Powerstep01_CONFIG_OSC_SEL  = ((uint16_t) 0x0007),
  Powerstep01_CONFIG_EXT_CLK  = ((uint16_t) 0x0008),
  Powerstep01_CONFIG_EN_TQREG = ((uint16_t) 0x0020),
  Powerstep01_CONFIG_OC_SD    = ((uint16_t) 0x0080),
  Powerstep01_CONFIG_POW_SR   = ((uint16_t) 0x0300),
  Powerstep01_CONFIG_TOFF      = ((uint16_t) 0x7C00)
} Powerstep01_CONFIG_Masks_t;

/// Powerstep01 clock source options for CONFIG register
typedef enum {
  Powerstep01_CONFIG_INT_16MHZ = ((uint16_t) 0x0000),
  Powerstep01_CONFIG_INT_16MHZ_OSCOUT_2MHZ   = ((uint16_t) 0x0008),
  Powerstep01_CONFIG_INT_16MHZ_OSCOUT_4MHZ   = ((uint16_t) 0x0009),
  Powerstep01_CONFIG_INT_16MHZ_OSCOUT_8MHZ   = ((uint16_t) 0x000A),
  Powerstep01_CONFIG_INT_16MHZ_OSCOUT_16MHZ  = ((uint16_t) 0x000B),
  Powerstep01_CONFIG_EXT_8MHZ_XTAL_DRIVE     = ((uint16_t) 0x0004),
  Powerstep01_CONFIG_EXT_16MHZ_XTAL_DRIVE    = ((uint16_t) 0x0005),
  Powerstep01_CONFIG_EXT_24MHZ_XTAL_DRIVE    = ((uint16_t) 0x0006),
  Powerstep01_CONFIG_EXT_32MHZ_XTAL_DRIVE    = ((uint16_t) 0x0007),
  Powerstep01_CONFIG_EXT_8MHZ_OSCOUT_INVERT  = ((uint16_t) 0x000C),
  Powerstep01_CONFIG_EXT_16MHZ_OSCOUT_INVERT = ((uint16_t) 0x000D),
  Powerstep01_CONFIG_EXT_24MHZ_OSCOUT_INVERT = ((uint16_t) 0x000E),
  Powerstep01_CONFIG_EXT_32MHZ_OSCOUT_INVERT = ((uint16_t) 0x000F)
} Powerstep01_CONFIG_OSC_MGMT_t;

/// Powerstep01 external torque regulation options for CONFIG register
typedef enum {
  Powerstep01_CONFIG_EN_TQREG_TVAL_USED = ((uint16_t) 0x0000),
  Powerstep01_CONFIG_EN_TQREG_ADC_OUT = ((uint16_t) 0x0020)
} Powerstep01_CONFIG_EN_TQREG_t;

/// Powerstep01 over current shutdown options for CONFIG register
typedef enum {
  Powerstep01_CONFIG_OC_SD_DISABLE = ((uint16_t) 0x0000),
  Powerstep01_CONFIG_OC_SD_ENABLE  = ((uint16_t) 0x0080)
} Powerstep01_CONFIG_OC_SD_t;

/// Powerstep01 power bridge output slew_rates options (POW_SR values for CONFIG register)
typedef enum {
  Powerstep01_CONFIG_SR_320V_us    =((uint16_t)0x0000),
  Powerstep01_CONFIG_SR_075V_us    =((uint16_t)0x0100),
  Powerstep01_CONFIG_SR_110V_us    =((uint16_t)0x0200),
  Powerstep01_CONFIG_SR_260V_us    =((uint16_t)0x0300)
} Powerstep01_CONFIG_POW_SR_t;

/// Powerstep01 Off time options (TOFF values for CONFIG register)
typedef enum {
  Powerstep01_CONFIG_TOFF_004us   = (((uint16_t) 0x01) << 10),
  Powerstep01_CONFIG_TOFF_008us   = (((uint16_t) 0x02) << 10),
  Powerstep01_CONFIG_TOFF_012us  = (((uint16_t) 0x03) << 10),
  Powerstep01_CONFIG_TOFF_016us  = (((uint16_t) 0x04) << 10),
  Powerstep01_CONFIG_TOFF_020us  = (((uint16_t) 0x05) << 10),
  Powerstep01_CONFIG_TOFF_024us  = (((uint16_t) 0x06) << 10),
  Powerstep01_CONFIG_TOFF_028us  = (((uint16_t) 0x07) << 10),
  Powerstep01_CONFIG_TOFF_032us  = (((uint16_t) 0x08) << 10),
  Powerstep01_CONFIG_TOFF_036us  = (((uint16_t) 0x09) << 10),
  Powerstep01_CONFIG_TOFF_040us  = (((uint16_t) 0x0A) << 10),
  Powerstep01_CONFIG_TOFF_044us  = (((uint16_t) 0x0B) << 10),
  Powerstep01_CONFIG_TOFF_048us  = (((uint16_t) 0x0C) << 10),
  Powerstep01_CONFIG_TOFF_052us  = (((uint16_t) 0x0D) << 10),
  Powerstep01_CONFIG_TOFF_056us  = (((uint16_t) 0x0E) << 10),
  Powerstep01_CONFIG_TOFF_060us  = (((uint16_t) 0x0F) << 10),
  Powerstep01_CONFIG_TOFF_064us  = (((uint16_t) 0x10) << 10),
  Powerstep01_CONFIG_TOFF_068us  = (((uint16_t) 0x11) << 10),
  Powerstep01_CONFIG_TOFF_072us  = (((uint16_t) 0x12) << 10),
  Powerstep01_CONFIG_TOFF_076us  = (((uint16_t) 0x13) << 10),
  Powerstep01_CONFIG_TOFF_080us  = (((uint16_t) 0x14) << 10),
  Powerstep01_CONFIG_TOFF_084us  = (((uint16_t) 0x15) << 10),
  Powerstep01_CONFIG_TOFF_088us  = (((uint16_t) 0x16) << 10),
  Powerstep01_CONFIG_TOFF_092us  = (((uint16_t) 0x17) << 10),
  Powerstep01_CONFIG_TOFF_096us  = (((uint16_t) 0x18) << 10),
  Powerstep01_CONFIG_TOFF_100us = (((uint16_t) 0x19) << 10),
  Powerstep01_CONFIG_TOFF_104us = (((uint16_t) 0x1A) << 10),
  Powerstep01_CONFIG_TOFF_108us = (((uint16_t) 0x1B) << 10),
  Powerstep01_CONFIG_TOFF_112us = (((uint16_t) 0x1C) << 10),
  Powerstep01_CONFIG_TOFF_116us = (((uint16_t) 0x1D) << 10),
  Powerstep01_CONFIG_TOFF_120us = (((uint16_t) 0x1E) << 10),
  Powerstep01_CONFIG_TOFF_124us = (((uint16_t) 0x1F) << 10)
} Powerstep01_CONFIG_TOFF_t;

///  Powerstep01 STATUS register bit masks
typedef enum {
  Powerstep01_STATUS_HIZ         = (((uint16_t) 0x0001)),
  Powerstep01_STATUS_DIR         = (((uint16_t) 0x0010)),
  Powerstep01_STATUS_NOTPERF_CMD = (((uint16_t) 0x0080)),
  Powerstep01_STATUS_WRONG_CMD   = (((uint16_t) 0x0100)),
  Powerstep01_STATUS_UVLO        = (((uint16_t) 0x0200)),
  Powerstep01_STATUS_TH_WRN      = (((uint16_t) 0x0400)),
  Powerstep01_STATUS_TH_SD       = (((uint16_t) 0x0800)),
  Powerstep01_STATUS_OCD         = (((uint16_t) 0x1000))
} Powerstep01_STATUS_Masks_t;

/// Powerstep01 STATUS register options
typedef enum {
  Powerstep01_STATUS_DIR_FORWARD = (((uint16_t) 0x0001) << 4),
  Powerstep01_STATUS_DIR_REVERSE = (((uint16_t) 0x0000) << 4)
} Powerstep01_STATUS_DIR_t;

/// Powerstep01 internal register addresses
typedef enum {
  Powerstep01_ABS_POS        = ((uint8_t) 0x01),
  Powerstep01_EL_POS         = ((uint8_t) 0x02),
  Powerstep01_MARK           = ((uint8_t) 0x03),
  Powerstep01_RESERVED_REG01 = ((uint8_t) 0x04),
  Powerstep01_RESERVED_REG02 = ((uint8_t) 0x05),
  Powerstep01_RESERVED_REG03 = ((uint8_t) 0x06),
  Powerstep01_RESERVED_REG04 = ((uint8_t) 0x07),
  Powerstep01_RESERVED_REG05 = ((uint8_t) 0x08),
  Powerstep01_RESERVED_REG06 = ((uint8_t) 0x15),
  Powerstep01_TVAL           = ((uint8_t) 0x09),
  Powerstep01_RESERVED_REG07 = ((uint8_t) 0x0A),
  Powerstep01_RESERVED_REG08 = ((uint8_t) 0x0B),
  Powerstep01_RESERVED_REG09 = ((uint8_t) 0x0C),
  Powerstep01_RESERVED_REG10 = ((uint8_t) 0x0D),
  Powerstep01_T_FAST         = ((uint8_t) 0x0E),
  Powerstep01_TON_MIN        = ((uint8_t) 0x0F),
  Powerstep01_TOFF_MIN       = ((uint8_t) 0x10),
  Powerstep01_RESERVED_REG11 = ((uint8_t) 0x11),
  Powerstep01_ADC_OUT        = ((uint8_t) 0x12),
  Powerstep01_OCD_TH         = ((uint8_t) 0x13),
  Powerstep01_RESERVED_REG12 = ((uint8_t) 0x14),
  Powerstep01_STEP_MODE      = ((uint8_t) 0x16),
  Powerstep01_ALARM_EN       = ((uint8_t) 0x17),
  Powerstep01_CONFIG         = ((uint8_t) 0x18),
  Powerstep01_STATUS         = ((uint8_t) 0x19),
  Powerstep01_RESERVED_REG13 = ((uint8_t) 0x1A),
  Powerstep01_RESERVED_REG14 = ((uint8_t) 0x1B),
  Powerstep01_INEXISTENT_REG = ((uint8_t) 0x1F)
} Powerstep01_Registers_t;

/// Powerstep01 command set
typedef enum {
  Powerstep01_NOP           = ((uint8_t) 0x00),
  Powerstep01_SET_PARAM     = ((uint8_t) 0x00),
  Powerstep01_GET_PARAM     = ((uint8_t) 0x20),
  Powerstep01_ENABLE        = ((uint8_t) 0xB8),
  Powerstep01_DISABLE       = ((uint8_t) 0xA8),
  Powerstep01_GET_STATUS    = ((uint8_t) 0xD0),
  Powerstep01_RESERVED_CMD1 = ((uint8_t) 0xEB),
  Powerstep01_RESERVED_CMD2 = ((uint8_t) 0xF8)
} Powerstep01_Commands_t;

///  Direction options
typedef enum {
  FORWARD = HIGH,
  BACKWARD = LOW
} dir_t;

/// Shield state
typedef enum {
  ACCELERATING = 0, 
  DECELERATING = 1, 
  STEADY = 2,
  INACTIVE= 3
} shieldState_t;

/// Shield Commands 
typedef enum {
  RUN_CMD, 
  MOVE_CMD, 
  SOFT_STOP_CMD, 
  NO_CMD
} shieldCommand_t;

/// Powerstep01 shield parameters
typedef struct {
    /// accumulator used to store speed increase smaller than 1 pps
    volatile uint32_t accu;           
    /// Position in steps at the start of the goto or move commands
    volatile int32_t currentPosition; 
    /// position in step at the end of the accelerating phase
    volatile uint32_t endAccPos;      
    /// nb steps performed from the beggining of the goto or the move command
    volatile uint32_t relativePos;    
    /// position in step at the start of the decelerating phase
    volatile uint32_t startDecPos;    
    /// nb steps to perform for the goto or move commands
    volatile uint32_t stepsToTake;   
    
    /// acceleration in pps^2
    volatile uint16_t acceleration;  
    /// deceleration in pps^2
    volatile uint16_t deceleration;  
    /// max speed in pps (speed use for goto or move command)
    volatile uint16_t maxSpeed;      
    /// min speed in pps
    volatile uint16_t minSpeed;      
    /// current speed in pps    
    volatile uint16_t speed;         
    
    /// command under execution
    volatile shieldCommand_t commandExecuted; 
    /// FORWARD or BACKWARD direction
    volatile dir_t direction;                 
    /// Current State of the shield
    volatile shieldState_t motionState;       
}shieldParams_t;

/// Powerstep01 library class
class Powerstep01 {
  public:
    // constructor:
    Powerstep01();
    
    /// @defgroup group1 Shield control functions
    ///@{
    void AttachFlagInterrupt(void (*callback)(void));     //Attach a user callback to the flag Interrupt
    void Begin(uint8_t nbShields);                        //Start the Powerstep01 library
    uint16_t GetAcceleration(uint8_t shieldId);           //Return the acceleration in pps^2
    uint16_t GetCurrentSpeed(uint8_t shieldId);           //Return the current speed in pps
    uint16_t GetDeceleration(uint8_t shieldId);           //Return the deceleration in pps^2
    shieldState_t GetShieldState(uint8_t shieldId);       //Return the shield state
    uint8_t GetFwVersion(void);                           //Return the FW version
    int32_t GetMark(uint8_t shieldId);                    //Return the mark position 
    uint16_t GetMaxSpeed(uint8_t shieldId);               //Return the max speed in pps
    uint16_t GetMinSpeed(uint8_t shieldId);               //Return the min speed in pps
    int32_t GetPosition(uint8_t shieldId);                //Return the ABS_POSITION (32b signed)
    void GoHome(uint8_t shieldId);                        //Move to the home position
    void GoMark(uint8_t shieldId);                        //Move to the Mark position
    void GoTo(uint8_t shieldId, int32_t targetPosition);  //Go to the specified position
    void HardStop(uint8_t shieldId);                      //Stop the motor and disable the power bridge
    void Move(uint8_t shieldId,                           //Move the motor of the specified number of steps
              dir_t direction,
              uint32_t stepCount);    
    void ResetAllShields(void);                              //Reset all Powerstep01 shields
    void Run(uint8_t shieldId, dir_t direction);             //Run the motor 
    bool SetAcceleration(uint8_t shieldId,uint16_t newAcc);  //Set the acceleration in pps^2
    bool SetDeceleration(uint8_t shieldId,uint16_t newDec);  //Set the deceleration in pps^2
    void SetHome(uint8_t shieldId);                          //Set current position to be the home position
    void SetMark(uint8_t shieldId);                          //Set current position to be the Markposition
    bool SetMaxSpeed(uint8_t shieldId,uint16_t newMaxSpeed); //Set the max speed in pps
    bool SetMinSpeed(uint8_t shieldId,uint16_t newMinSpeed); //Set the min speed in pps   
    bool SoftStop(uint8_t shieldId);                         //Progressively stops the motor 
    void WaitWhileActive(uint8_t shieldId);                  //Wait for the shield state becomes Inactive
    ///@}
    
    /// @defgroup group2 Powerstep01 control functions
    ///@{
    void CmdDisable(uint8_t shieldId);              //Send the Powerstep01_DISABLE command
    void CmdEnable(uint8_t shieldId);               //Send the Powerstep01_ENABLE command
    uint32_t CmdGetParam(uint8_t shieldId,          //Send the Powerstep01_GET_PARAM command
                                 Powerstep01_Registers_t param);
    uint16_t CmdGetStatus(uint8_t shieldId);        // Send the Powerstep01_GET_STATUS command
    void CmdNop(uint8_t shieldId);                  //Send the Powerstep01_NOP command
    void CmdSetParam(uint8_t shieldId,              //Send the Powerstep01_SET_PARAM command
                             Powerstep01_Registers_t param,
                             uint32_t value);
    uint16_t ReadStatusRegister(uint8_t shieldId);  // Read the Powerstep01_STATUS register without
                                                    // clearing the flags
    void Reset(void);                               //Set the Powerstep01 reset pin
    void ReleaseReset(void);                        //Release the Powerstep01 reset pin
    void SelectStepMode(uint8_t shieldId,           // Step mode selection
                                Powerstep01_STEP_SEL_t stepMod);
    void SetDirection(uint8_t shieldId,             //Set the Powerstep01 direction pin
                              dir_t direction);      
    ///@}
    
    /// @defgroup group3 Delay functions
    ///@{
    /// @brief Required when 3 Powerstep01 shields are used
    /// to avoid conflicting depencieswith wiring.c 
    /// (redefinition of ISR(TIMER0_OVF_vect).  
    /// When only 2 Powerstep01 shields are used, prefer the use
    /// of standard Arduino functions (delay, delayMicroseconds).
    static void WaitMs(uint16_t msDelay); // Wait for a delay in ms
    static void WaitUs(uint16_t usDelay); // Wait for a delay in us
    ///@}
        
    /// @defgroup group4 Functions for timer ISRs only
    /// @brief To be used inside the library by the timer ISRs only 
    /// Must not be used elsewhere.
    ///@{
    static class Powerstep01 *GetInstancePtr(void);
    void StepClockHandler(uint8_t shieldId); 
    ///@}
    
  private:
    void ApplySpeed(uint8_t pwmId, uint16_t newSpeed);
    void ComputeSpeedProfile(uint8_t shieldId, uint32_t nbSteps);
    int32_t ConvertPosition(uint32_t abs_position_reg); 
    static void FlagInterruptHandler(void);
    void SendCommand(uint8_t shieldId, uint8_t param);
    void SetRegisterToPredefinedValues(uint8_t shieldId);
    void WriteBytes(uint8_t *pByteToTransmit, uint8_t *pReceivedByte);    
    void PwmInit(uint8_t pwmId);
    void Pwm1SetFreq(uint16_t newFreq);
    void Pwm2SetFreq(uint16_t newFreq);
    void Pwm3SetFreq(uint16_t newFreq);
    void PwmStop(uint8_t pwmId);
    void SetShieldParamsToPredefinedValues(void);
    void StartMovement(uint8_t shieldId);
    uint8_t Tval_Current_to_Par(double Tval);
    uint8_t Tmin_Time_to_Par(double Tmin);
    
    // variable members        
    shieldParams_t shieldPrm[MAX_NUMBER_OF_SHIELDS];
    static volatile class Powerstep01 *instancePtr;
    static volatile void(*flagInterruptCallback)(void);
    static volatile bool isrFlag;
    static volatile bool spiPreemtionByIsr;
    static volatile uint8_t numberOfShields;
    static const uint16_t prescalerArrayTimer0_1[PRESCALER_ARRAY_TIMER0_1_SIZE];
    static const uint16_t prescalerArrayTimer2[PRESCALER_ARRAY_TIMER2_SIZE];
    static uint8_t spiTxBursts[Powerstep01_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];
    static uint8_t spiRxBursts[Powerstep01_CMD_ARG_MAX_NB_BYTES][MAX_NUMBER_OF_SHIELDS];
};

#ifdef _DEBUG_POWERSTEP01
uint16_t GetFreeRam (void);
#endif

#endif /* #ifndef __POWERSTEP01_H_INCLUDED */
