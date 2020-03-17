/******** Configuracion / Calibracion *****/
#include "prj_cfg.h"

/***** gatArduinOSEK includes *****/
/*** Types ***/
#include <gttc_types.h>
/*** Timer ***/
#define TIMEBASE_USE_MS 1  // <-- Normally the timer unit is the us (microseconds) but you can use this define to use ms (milliseconds)
#include <gttc_timer.h>


/******** DRE (Data Runtime Environment ********/
#include "prj_dre.h"

/******** Otros modulos del proyecto ********/
#include "prj_input.h"
#include "prj_cmd.h"
#include "prj_output.h"
#include "prj_comm.h"
#include "IoT.h"
#include "prj_iot.h"    // <-- The IoT module contains functions to manage the IoT connection

//=======================SETUP=====================
void setup() {
  dre_init();
  #ifdef CFG_USE_DEEPSLEEP
  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  #endif
  /* Set program cycle time */
  timerSetCycleTime(CYCLE_TIME_IN_MICROS);
  prj_input_init();
  prj_cmd_init();
  prj_output_init();
  prj_comm_init();
  prj_iot_init();
  #ifdef DEBUG_IOT
  Serial.print("iot_connected: ");Serial.println(dre.iot_connected);
  Serial.print("iot_publish: ");Serial.println(dre.iot_publish);
  #endif
}

/***** Main Loop *****/

uint32_t maxElapsedMicros=2L;
bool firstLoop=true;
void loop() {

  prj_input();
  prj_cmd();
  Emergency();
  DispatchSysCmd();
  if (dre.ovr_pulses == true) {
    dre.pulses_to_send = dre.cmd_pulses;
    dre.ovr_pulses = false;
  }
  #ifdef CFG_USE_IOT
  FuncMngr();
  #ifdef DEBUG_IOT
//  Serial.print("dre.iot_connect: ");Serial.println(dre.iot_connect);
//  Serial.print("dre.iot_go_online: ");Serial.println(dre.iot_go_online);
  #endif
  #endif
  PulsingCmd();

  #ifdef CFG_USE_IOT
  IoTMng();
  #endif

  prj_output();
  prj_comm();

  if (dre.pulses_to_send == 0){
    prj_iot();
  }
  // ----------- End of Cycle Synchronization ----------------
  // Now the microcontroller will loose time until the end of cycle sincronization time expires
  boolean timSync=timerSync();
  dre.looptime = elapsedMicros;

  #ifdef DEBUG_TIEMPO_CICLO
  Serial.println(dre.looptime);
  #endif

  #ifdef DEBUG_IOT
  //Serial.print("iot_connected: ");Serial.println(dre.iot_connected);
  //Serial.print("iot_publish: ");Serial.println(dre.iot_publish);
  //Serial.print("iot_connect: ");Serial.println(dre.iot_connect);
  #endif

  while(timSync==false){
    // timerSync returns true when the end of cycle syncronization time expired.
    timSync=timerSync();
  }
  if (firstLoop){
    firstLoop=false;
    busyMicros=0L;
  }
  if (dre.looptime > CYCLE_TIME_IN_MICROS){
    Serial.print("Ciclo violado: ");Serial.println(dre.looptime);
  }
    if (busyMicros>maxElapsedMicros){
      maxElapsedMicros=busyMicros;
      Serial.print("El =");Serial.println(maxElapsedMicros);
    }
}
//===============================================================
