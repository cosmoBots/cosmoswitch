/* ---- This file describes all the pin assignments of the microcontroller --- */

#ifndef _PRJ_PINOUT_H
#define _PRJ_PINOUT_H

#include "gttc_types.h"
#include "prj_input.h"
#include "prj_output.h"

#ifdef ESP8266_WEMOS_D1MINI
#error "TODO: Definir pines para el ESP8266_WEMOS_D1MINI"
#define CFG_BAT_ADC -1
#define CFG_PULSE_CMD_PIN -1 // A través de este pin se va a enviar el comando de temporización del masaje
#define CFG_EMGCY_BUT -1  // A través de este pin se va a recibir la petición de emergencia.
#define CTE_SC_S2_PIN     -1    //Control del filtro de muestreo S2
#define CTE_SC_S3_PIN     -1    // Control del filtro de muestreo S3
#define CTE_SENSOR_SUELO_PIN -1
#elif ARDUINO_ESP8266_NODEMCU
#error "TODO: Definir pines para el ARDUINO_ESP8266_NODEMCU"
#define CFG_BAT_ADC -1
#define CFG_PULSE_CMD_PIN -1 // A través de este pin se va a enviar el comando de temporización del masaje
#define CFG_EMGCY_BUT -1  // A través de este pin se va a recibir la petición de emergencia.
#define CTE_SC_S2_PIN     -1    //Control del filtro de muestreo S2
#define CTE_SC_S3_PIN     -1    // Control del filtro de muestreo S3
#define CTE_SENSOR_SUELO_PIN -1
#elif ESP32_DEV
#define CFG_BAT_ADC 34
#define CFG_PULSE_CMD_PIN 14 // A través de este pin se va a enviar el comando de temporización del masaje
#define CFG_EMGCY_BUT 13  // A través de este pin se va a recibir la petición de emergencia.
#define CTE_SC_S2_PIN     27    //Control del filtro de muestreo S2
#define CTE_SC_S3_PIN     12    // Control del filtro de muestreo S3
#define CTE_SENSOR_SUELO_PIN 26
#elif TEENSY31
#error "TODO: Definir pines para la TEENSY31"
#define CFG_BAT_ADC -1
#define CFG_PULSE_CMD_PIN -1 // A través de este pin se va a enviar el comando de temporización del masaje
#define CFG_EMGCY_BUT -1  // A través de este pin se va a recibir la petición de emergencia.
#define CTE_SC_S2_PIN     -1    //Control del filtro de muestreo S2
#define CTE_SC_S3_PIN     -1    // Control del filtro de muestreo S3
#define CTE_SENSOR_SUELO_PIN -1
#elif ARDUINO_AVR_UNO
#define CFG_BAT_ADC 23
#define CFG_PULSE_CMD_PIN 40 // A través de este pin se va a enviar el comando de temporización del masaje
#define CFG_EMGCY_BUT 41  // A través de este pin se va a recibir la petición de emergencia.
#define CTE_SC_S2_PIN     49    //Control del filtro de muestreo S2
#define CTE_SC_S3_PIN     51    // Control del filtro de muestreo S3
#define CTE_SENSOR_SUELO_PIN 47
#else
#error "No microcontroller defined"
#endif

void pinoutInit(void);

#endif // _PRJ_PINOUT_H
