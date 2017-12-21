#include "prj_cfg.h"
#include "prj_dre.h"
#include "Arduino.h"

t_dre dre;

void dre_init(void){
  uint8_t i;

  dre.iot_connected = false;
  dre.iot_go_online = false;
  dre.iot_go_offline = false;
  dre.iot_connect = false;
  dre.iot_disconnect = false;
  dre.iot_publish = false;
  dre.iot_publish_timer = 0;

  dre.emgcy_timer = 0;
  dre.emgcy_button = false;
  dre.emgcy_action = true;
  dre.ovr_emgcy_action = false;
  dre.cmd_emgcy_action = false;

  dre.bat = 0;

  dre.pulses_timer = 0;
  dre.pulses_to_send = 0;
  dre.pulse_pin = false;
  dre.cmd_pulses = 0;
  dre.ovr_pulses = false;
  dre.incoming_bytes[0]='\0';

  dre.cmd_base = 0;
  for ( dre.cmd_counter  = 0 ; dre.cmd_counter < CFG_CMD_STORAGE_SIZE; dre.cmd_counter++ ){
    dre.cmd_storage[dre.cmd_counter][0];
  }
  dre.cmd_counter = 0;

  #ifdef CFG_USE_RELAY_SET
  for (i = 0; i < CFG_RELAYSET_NUMBER; i++){
    dre.ovr_relay_action[i] = false;
    dre.cmd_relay_action[i] = false;
    dre.relay_action[i] = true;

  }
  #endif
}
