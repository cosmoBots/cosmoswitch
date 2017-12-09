# 1 "/var/folders/jp/3ln2xxc503l9n7kg5mp387fm0000gp/T/tmpnCQ_KX"
#include <Arduino.h>
# 1 "/Users/txinto/dev/cosmoBots/cosmoswitch/src/src.ino"

#include "prj_cfg.h"



#include <gttc_types.h>

#define TIMEBASE_USE_MS 1
#include <gttc_timer.h>



#include "prj_dre.h"


#include "prj_input.h"
#include "prj_output.h"
#include "prj_comm.h"
#include "IoT.h"
#include "prj_iot.h"
void setup();
void loop();
#line 23 "/Users/txinto/dev/cosmoBots/cosmoswitch/src/src.ino"
void setup() {
  dre_init();
  #ifdef CFG_USE_DEEPSLEEP

  print_wakeup_reason();
  #endif

  timerSetCycleTime(CYCLE_TIME_IN_MICROS);
  prj_input_init();
  prj_output_init();
  prj_comm_init();
  prj_iot_init();
  #ifdef DEBUG_IOT
  Serial.print("iot_connected: ");Serial.println(dre.iot_connected);
  Serial.print("iot_publish: ");Serial.println(dre.iot_publish);
  #endif
}



uint32_t maxElapsedMicros=2L;
bool firstLoop=true;
void loop() {

  prj_input();
  Emergency();
  DispatchSysCmd();
  if (dre.ovr_pulses == true) {
    dre.pulses_to_send = dre.cmd_pulses;
    dre.ovr_pulses = false;
  }
  #ifdef CFG_USE_IOT
  FuncMngr();
  #ifdef DEBUG_IOT
  Serial.print("dre.iot_connect: ");Serial.println(dre.iot_connect);
  Serial.print("dre.iot_go_online: ");Serial.println(dre.iot_go_online);
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


  boolean timSync=timerSync();
  dre.looptime = elapsedMicros;

  #ifdef DEBUG_TIEMPO_CICLO
  Serial.println(dre.looptime);
  #endif

  #ifdef DEBUG_IOT
  Serial.print("iot_connected: ");Serial.println(dre.iot_connected);
  Serial.print("iot_publish: ");Serial.println(dre.iot_publish);
  Serial.print("iot_connect: ");Serial.println(dre.iot_connect);
  #endif

  while(timSync==false){

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