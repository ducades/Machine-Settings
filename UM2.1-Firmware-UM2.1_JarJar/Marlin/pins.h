#ifndef PINS_H
#define PINS_H

#define X_MS1_PIN -1
#define X_MS2_PIN -1
#define Y_MS1_PIN -1
#define Y_MS2_PIN -1
#define Z_MS1_PIN -1
#define Z_MS2_PIN -1
#define E0_MS1_PIN -1
#define E0_MS2_PIN -1
#define E1_MS1_PIN -1
#define E1_MS2_PIN -1
#define DIGIPOTSS_PIN -1
#define MOTOR_CURRENT_PWM_XY_PIN -1
#define MOTOR_CURRENT_PWM_Z_PIN -1
#define MOTOR_CURRENT_PWM_E_PIN -1

#if MOTHERBOARD == 72
#define KNOWN_BOARD
/*****************************************************************
* Ultiboard v2.0 pin assignment
******************************************************************/

#ifndef __AVR_ATmega2560__
 #error Oops!  Make sure you have 'Arduino Mega 2560' selected from the 'Tools -> Boards' menu.
#endif

#define LARGE_FLASH true

#define X_STEP_PIN 25
#define X_DIR_PIN 23
#define X_STOP_PIN 22
#define X_ENABLE_PIN 27

#define Y_STEP_PIN 32
#define Y_DIR_PIN 33
#define Y_STOP_PIN 26
#define Y_ENABLE_PIN 31

#define Z_STEP_PIN 35
#define Z_DIR_PIN 36
#define Z_STOP_PIN 29
#define Z_ENABLE_PIN 34

#define HEATER_BED_PIN 4
#define TEMP_BED_PIN 10

#define HEATER_0_PIN  2
#define TEMP_0_PIN 8

#define HEATER_1_PIN 3
#define TEMP_1_PIN 9

#define HEATER_2_PIN -1
#define TEMP_2_PIN -1

#define E0_STEP_PIN         42
#define E0_DIR_PIN          43
#define E0_ENABLE_PIN       37

#define E1_STEP_PIN         49
#define E1_DIR_PIN          47
#define E1_ENABLE_PIN       48

#define SDPOWER            -1
#define SDSS               53
#define MAX6675_SS         13
#define LED_PIN            8
#define FAN_PIN            7
#define PS_ON_PIN          24
#define KILL_PIN           -1
#define SUICIDE_PIN        -1  //PIN that has to be turned on right after start, to keep power flowing.
#define SAFETY_TRIGGERED_PIN     28 //PIN to detect the safety circuit has triggered
#define MAIN_VOLTAGE_MEASURE_PIN 14 //Analogue PIN to measure the main voltage, with a 100k - 4k7 resitor divider.

#undef MOTOR_CURRENT_PWM_XY_PIN
#undef MOTOR_CURRENT_PWM_Z_PIN
#undef MOTOR_CURRENT_PWM_E_PIN
#define MOTOR_CURRENT_PWM_XY_PIN 44
#define MOTOR_CURRENT_PWM_Z_PIN 45
#define MOTOR_CURRENT_PWM_E_PIN 46
//Motor current PWM conversion, PWM value = MotorCurrentSetting * 255 / range
#define MOTOR_CURRENT_PWM_RANGE 2000

//arduino pin witch triggers an piezzo beeper
#define BEEPER 18

#define LCD_PINS_RS 20
#define LCD_PINS_ENABLE 15
#define LCD_PINS_D4 14
#define LCD_PINS_D5 21
#define LCD_PINS_D6 5
#define LCD_PINS_D7 6

//buttons are directly attached
#define BTN_EN1 40
#define BTN_EN2 41
#define BTN_ENC 19  //the click

#define BLEN_C 2
#define BLEN_B 1
#define BLEN_A 0

#define SDCARDDETECT 39

//encoder rotation values
#define encrot0 0
#define encrot1 1
#define encrot2 3
#define encrot3 2

#endif//MOTHERBOARD == 72

#ifndef KNOWN_BOARD
#error Unknown MOTHERBOARD value in configuration.h
#endif

//List of pins which to ignore when asked to change by gcode, 0 and 1 are RX and TX, do not mess with those!
#define _E0_PINS E0_STEP_PIN, E0_DIR_PIN, E0_ENABLE_PIN, HEATER_0_PIN,
#if EXTRUDERS > 1
  #define _E1_PINS E1_STEP_PIN, E1_DIR_PIN, E1_ENABLE_PIN, HEATER_1_PIN,
#else
  #define _E1_PINS
#endif
#if EXTRUDERS > 2
  #define _E2_PINS E2_STEP_PIN, E2_DIR_PIN, E2_ENABLE_PIN, HEATER_2_PIN,
#else
  #define _E2_PINS
#endif

#ifdef X_STOP_PIN
  #if X_HOME_DIR < 0
    #define X_MIN_PIN X_STOP_PIN
    #define X_MAX_PIN -1
  #else
    #define X_MIN_PIN -1
    #define X_MAX_PIN X_STOP_PIN
  #endif
#endif

#ifdef Y_STOP_PIN
  #if Y_HOME_DIR < 0
    #define Y_MIN_PIN Y_STOP_PIN
    #define Y_MAX_PIN -1
  #else
    #define Y_MIN_PIN -1
    #define Y_MAX_PIN Y_STOP_PIN
  #endif
#endif

#ifdef Z_STOP_PIN
  #if Z_HOME_DIR < 0
    #define Z_MIN_PIN Z_STOP_PIN
    #define Z_MAX_PIN -1
  #else
    #define Z_MIN_PIN -1
    #define Z_MAX_PIN Z_STOP_PIN
  #endif
#endif

#ifdef DISABLE_MAX_ENDSTOPS
#define X_MAX_PIN          -1
#define Y_MAX_PIN          -1
#define Z_MAX_PIN          -1
#endif

#ifdef DISABLE_MIN_ENDSTOPS
#define X_MIN_PIN          -1
#define Y_MIN_PIN          -1
#define Z_MIN_PIN          -1
#endif

#define SENSITIVE_PINS {0, 1, X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN, Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN, Z_STEP_PIN, Z_DIR_PIN, Z_ENABLE_PIN, Z_MIN_PIN, Z_MAX_PIN, PS_ON_PIN, \
                        HEATER_BED_PIN, FAN_PIN,                  \
                        _E0_PINS _E1_PINS _E2_PINS             \
                        analogInputToDigitalPin(TEMP_0_PIN), analogInputToDigitalPin(TEMP_1_PIN), analogInputToDigitalPin(TEMP_2_PIN), analogInputToDigitalPin(TEMP_BED_PIN) }
#endif

