// Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.
// Licence: GPL

#ifndef MARLIN_H
#define MARLIN_H

#define  FORCE_INLINE __attribute__((always_inline)) inline

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>


#include "fastio.h"
#include "Configuration.h"
#include "pins.h"

#ifndef AT90USB
#define  HardwareSerial_h // trick to disable the standard HWserial
#endif

#if (ARDUINO >= 100)
# include "Arduino.h"
#else
# include "WProgram.h"
  //Arduino < 1.0.0 does not define this, so we need to do it ourselfs
# define analogInputToDigitalPin(p) ((p) + A0)
#endif

#include "MarlinSerial.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#include "WString.h"

#ifdef AT90USB
  #define MYSERIAL Serial

#else
  #define MYSERIAL MSerial
#endif


//AEther
#define MYSERIAL2 MSerial2


#define SERIAL_PROTOCOL(x) MYSERIAL.print(x);
#define SERIAL_PROTOCOL_F(x,y) MYSERIAL.print(x,y);
#define SERIAL_PROTOCOLPGM(x) serialprintPGM(PSTR(x));
#define SERIAL_PROTOCOLLN(x) do {MYSERIAL.print(x);MYSERIAL.write('\n');} while(0)
#define SERIAL_PROTOCOLLNPGM(x) do{serialprintPGM(PSTR(x));MYSERIAL.write('\n');} while(0)

//AEther

#define SERIAL2_PROTOCOL(x) MYSERIAL2.print(x);
#define SERIAL2_PROTOCOL_F(x,y) MYSERIAL2.print(x,y);
#define SERIAL2_PROTOCOLPGM(x) serial2printPGM(PSTR(x));
#define SERIAL2_PROTOCOLLN(x) do {MYSERIAL2.print(x);MYSERIAL2.write('\n');} while(0)
#define SERIAL2_PROTOCOLLNPGM(x) do{serial2printPGM(PSTR(x));MYSERIAL2.write('\n');} while(0)


const char errormagic[] PROGMEM ="Error:";
const char echomagic[] PROGMEM ="echo:";
#define SERIAL_ERROR_START serialprintPGM(errormagic);
#define SERIAL_ERROR(x) SERIAL_PROTOCOL(x)
#define SERIAL_ERRORPGM(x) SERIAL_PROTOCOLPGM(x)
#define SERIAL_ERRORLN(x) SERIAL_PROTOCOLLN(x)
#define SERIAL_ERRORLNPGM(x) SERIAL_PROTOCOLLNPGM(x)

#define SERIAL_ECHO_START serialprintPGM(echomagic);
#define SERIAL_ECHO(x) SERIAL_PROTOCOL(x)
#define SERIAL_ECHOPGM(x) SERIAL_PROTOCOLPGM(x)
#define SERIAL_ECHOLN(x) SERIAL_PROTOCOLLN(x)
#define SERIAL_ECHOLNPGM(x) SERIAL_PROTOCOLLNPGM(x)

#define SERIAL_ECHOPAIR(name,value) (serial_echopair_P(PSTR(name),(value)))

void serial_echopair_P(const char *s_P, float v);
void serial_echopair_P(const char *s_P, double v);
void serial_echopair_P(const char *s_P, unsigned long v);

//AEther

#define SERIAL2_ERROR_START serial2printPGM(errormagic);
#define SERIAL2_ERROR(x) SERIAL2_PROTOCOL(x)
#define SERIAL2_ERRORPGM(x) SERIAL2_PROTOCOLPGM(x)
#define SERIAL2_ERRORLN(x) SERIAL2_PROTOCOLLN(x)
#define SERIAL2_ERRORLNPGM(x) SERIAL2_PROTOCOLLNPGM(x)

#define SERIAL2_ECHO_START serial2printPGM(echomagic);
#define SERIAL2_ECHO(x) SERIAL2_PROTOCOL(x)
#define SERIAL2_ECHOPGM(x) SERIAL2_PROTOCOLPGM(x)
#define SERIAL2_ECHOLN(x) SERIAL2_PROTOCOLLN(x)
#define SERIAL2_ECHOLNPGM(x) SERIAL2_PROTOCOLLNPGM(x)

#define SERIAL2_ECHOPAIR(name,value) (serial2_echopair_P(PSTR(name),(value)))

void serial2_echopair_P(const char *s_P, float v);
void serial2_echopair_P(const char *s_P, double v);
void serial2_echopair_P(const char *s_P, unsigned long v);



//AEther
void Serial2_begin(int baud);
void Serial2_println(char* s);
void Serial2_printlnint(int a);
void Serial2_printlnxyz(char* f, float, char* x, float, char* y, float, char* z, float, char* e, float);
void Serial2_printlntemp(String x, float f);

//things to write to serial from Programmemory. saves 400 to 2k of RAM.
FORCE_INLINE void serialprintPGM(const char *str)
{
  char ch=pgm_read_byte(str);
  while(ch)
  {
    MYSERIAL.write(ch);
    ch=pgm_read_byte(++str);
  }
}

//AEther

FORCE_INLINE void serial2printPGM(const char *str)
{
  char ch=pgm_read_byte(str);
  while(ch)
  {
    MYSERIAL2.write(ch);
    ch=pgm_read_byte(++str);
  }
}


void get_command();
void process_commands();

void manage_inactivity();

#if defined(X_ENABLE_PIN) && X_ENABLE_PIN > -1
  #define  enable_x() WRITE(X_ENABLE_PIN, X_ENABLE_ON)
  #define disable_x() WRITE(X_ENABLE_PIN,!X_ENABLE_ON)
#else
  #define enable_x() ;
  #define disable_x() ;
#endif

#if defined(Y_ENABLE_PIN) && Y_ENABLE_PIN > -1
  #define  enable_y() WRITE(Y_ENABLE_PIN, Y_ENABLE_ON)
  #define disable_y() WRITE(Y_ENABLE_PIN,!Y_ENABLE_ON)
#else
  #define enable_y() ;
  #define disable_y() ;
#endif

#if defined(Z_ENABLE_PIN) && Z_ENABLE_PIN > -1
  #ifdef Z_DUAL_STEPPER_DRIVERS
    #define  enable_z() { WRITE(Z_ENABLE_PIN, Z_ENABLE_ON); WRITE(Z2_ENABLE_PIN, Z_ENABLE_ON); }
    #define disable_z() { WRITE(Z_ENABLE_PIN,!Z_ENABLE_ON); WRITE(Z2_ENABLE_PIN,!Z_ENABLE_ON); }
  #else
    #define  enable_z() WRITE(Z_ENABLE_PIN, Z_ENABLE_ON)
    #define disable_z() WRITE(Z_ENABLE_PIN,!Z_ENABLE_ON)
  #endif
#else
  #define enable_z() ;
  #define disable_z() ;
#endif

#if defined(E0_ENABLE_PIN) && (E0_ENABLE_PIN > -1)
  #define enable_e0() WRITE(E0_ENABLE_PIN, E_ENABLE_ON)
  #define disable_e0() WRITE(E0_ENABLE_PIN,!E_ENABLE_ON)
#else
  #define enable_e0()  /* nothing */
  #define disable_e0() /* nothing */
#endif

#if (EXTRUDERS > 1) && defined(E1_ENABLE_PIN) && (E1_ENABLE_PIN > -1)
  #define enable_e1() WRITE(E1_ENABLE_PIN, E_ENABLE_ON)
  #define disable_e1() WRITE(E1_ENABLE_PIN,!E_ENABLE_ON)
#else
  #define enable_e1()  /* nothing */
  #define disable_e1() /* nothing */
#endif

#if (EXTRUDERS > 2) && defined(E2_ENABLE_PIN) && (E2_ENABLE_PIN > -1)
  #define enable_e2() WRITE(E2_ENABLE_PIN, E_ENABLE_ON)
  #define disable_e2() WRITE(E2_ENABLE_PIN,!E_ENABLE_ON)
#else
  #define enable_e2()  /* nothing */
  #define disable_e2() /* nothing */
#endif


enum AxisEnum {X_AXIS=0, Y_AXIS=1, Z_AXIS=2, E_AXIS=3};


void FlushSerialRequestResend();
void ClearToSend();

void get_coordinates();
#ifdef DELTA
void calculate_delta(float cartesian[3]);
#endif
void prepare_move();
void kill();
#define STOP_REASON_MAXTEMP              1
#define STOP_REASON_MINTEMP              2
#define STOP_REASON_MAXTEMP_BED          3
#define STOP_REASON_HEATER_ERROR         4
#define STOP_REASON_Z_ENDSTOP_BROKEN_ERROR 5
#define STOP_REASON_Z_ENDSTOP_STUCK_ERROR  6
#define STOP_REASON_XY_ENDSTOP_BROKEN_ERROR 7
#define STOP_REASON_XY_ENDSTOP_STUCK_ERROR  8
#define STOP_REASON_SAFETY_TRIGGER       10
void Stop(uint8_t reasonNr);

bool IsStopped();
uint8_t StoppedReason();

void clear_command_queue();
void enquecommand(const char *cmd); //put an ascii command at the end of the current buffer.
void enquecommand_P(const char *cmd); //put an ascii command at the end of the current buffer, read from flash
bool is_command_queued();
uint8_t commands_queued();
void prepare_arc_move(char isclockwise);
void clamp_to_software_endstops(float target[3]);

#ifdef FAST_PWM_FAN
void setPwmFrequency(uint8_t pin, int val);
#endif

#ifndef CRITICAL_SECTION_START
  #define CRITICAL_SECTION_START  unsigned char _sreg = SREG; cli();
  #define CRITICAL_SECTION_END    SREG = _sreg;
#endif //CRITICAL_SECTION_START

extern float homing_feedrate[];
extern bool axis_relative_modes[];
extern int feedmultiply;

//AEther
extern bool header;
extern int type_index;

//FEEDS
extern float brim_feed_d;
extern float brim_feed_n;
extern float brim_feed_b;

extern float first_feed_d;
extern float first_feed_n;
extern float first_feed_b;

extern float support_feed_d;
extern float support_feed_n;
extern float support_feed_b;

extern float interfacetop_feed_d;
extern float interfacetop_feed_n;
extern float interfacetop_feed_b;

extern float bottom_feed_d;
extern float bottom_feed_n;
extern float bottom_feed_b;

extern float outer_feed_d;
extern float outer_feed_n;
extern float outer_feed_b;

extern float inner_feed_d;
extern float inner_feed_n;
extern float inner_feed_b;

extern float infill_feed_d;
extern float infill_feed_n;
extern float infill_feed_b;

extern float top_feed_d;
extern float top_feed_n;
extern float top_feed_b;

extern float interfacebot_feed_d;
extern float interfacebot_feed_n;
extern float interfacebot_feed_b;

extern float travel_feed_d;
extern float travel_feed_n;
extern float travel_feed_b;

//FLOWS
extern int brim_flow_d;
extern int brim_flow_n;
extern int brim_flow_b;

extern int first_flow_d;
extern int first_flow_n;
extern int first_flow_b;

extern int support_flow_d;
extern int support_flow_n;
extern int support_flow_b;

extern int interfacetop_flow_d;
extern int interfacetop_flow_n;
extern int interfacetop_flow_b;

extern int bottom_flow_d;
extern int bottom_flow_n;
extern int bottom_flow_b;

extern int outer_flow_d;
extern int outer_flow_n;
extern int outer_flow_b;

extern int inner_flow_d;
extern int inner_flow_n;
extern int inner_flow_b;

extern int infill_flow_d;
extern int infill_flow_n;
extern int infill_flow_b;

extern int top_flow_d;
extern int top_flow_n;
extern int top_flow_b;

extern int interfacebot_flow_d;
extern int interfacebot_flow_n;
extern int interfacebot_flow_b;

extern int travel_flow_d;
extern int travel_flow_n;
extern int travel_flow_b;

//FANS
extern int brim_fan_d;
extern int brim_fan_n;
extern int brim_fan_b;

extern int first_fan_d;
extern int first_fan_n;
extern int first_fan_b;

extern int support_fan_d;
extern int support_fan_n;
extern int support_fan_b;

extern int interfacetop_fan_d;
extern int interfacetop_fan_n;
extern int interfacetop_fan_b;

extern int bottom_fan_d;
extern int bottom_fan_n;
extern int bottom_fan_b;

extern int outer_fan_d;
extern int outer_fan_n;
extern int outer_fan_b;

extern int inner_fan_d;
extern int inner_fan_n;
extern int inner_fan_b;

extern int infill_fan_d;
extern int infill_fan_n;
extern int infill_fan_b;

extern int top_fan_d;
extern int top_fan_n;
extern int top_fan_b;

extern int interfacebot_fan_d;
extern int interfacebot_fan_n;
extern int interfacebot_fan_b;

extern int travel_fan_d;
extern int travel_fan_n;
extern int travel_fan_b;


extern int extrudemultiply[EXTRUDERS]; // Sets extrude multiply factor (in percent)
extern float current_position[NUM_AXIS] ;
extern float add_homeing[3];
extern float min_pos[3];
extern float max_pos[3];
extern uint8_t fanSpeed;
extern uint8_t fanSpeedPercent;
#ifdef BARICUDA
extern int ValvePressure;
extern int EtoPPressure;
#endif
extern bool position_error;

#ifdef FAN_SOFT_PWM
extern unsigned char fanSpeedSoftPwm;
#endif

#ifdef FWRETRACT
extern bool autoretract_enabled;
extern bool retracted;
extern float retract_length, retract_feedrate, retract_zlift;
#if EXTRUDERS > 1
extern float extruder_swap_retract_length;
#endif
extern float retract_recover_length, retract_recover_feedrate;
#endif

extern unsigned long starttime;
extern unsigned long stoptime;

//The printing state from the main command processor. Is not zero when the command processor is in a loop waiting for a result.
extern uint8_t printing_state;
#define PRINT_STATE_NORMAL      0
#define PRINT_STATE_DWELL       1
#define PRINT_STATE_WAIT_USER   2
#define PRINT_STATE_HEATING     3
#define PRINT_STATE_HEATING_BED 4
#define PRINT_STATE_HOMING      5

//AEther

extern uint8_t print_quality;
#define PRINT_QUALITY_DRAFT      0
#define PRINT_QUALITY_NORMAL     1
#define PRINT_QUALITY_BEST       2

// Handling multiple extruders pins
extern uint8_t active_extruder;

#if EXTRUDERS > 3
  # error Unsupported number of extruders
#elif EXTRUDERS > 2
  # define ARRAY_BY_EXTRUDERS(v1, v2, v3) { v1, v2, v3 }
#elif EXTRUDERS > 1
  # define ARRAY_BY_EXTRUDERS(v1, v2, v3) { v1, v2 }
#else
  # define ARRAY_BY_EXTRUDERS(v1, v2, v3) { v1 }
#endif

#endif
