#ifndef _PRJ_DRE_H
#define _PRJ_DRE_H

#include "Arduino.h"

/* Configuracion */
#include "prj_cfg.h"

typedef struct {

  /*** IoT Management ***/
  bool iot_connected;
  bool iot_go_online;
  bool iot_go_offline;
  bool iot_connect;
  bool iot_disconnect;
  char iot_payload[128];
  bool iot_publish;
  int iot_publish_timer;

  int bat;

  int emgcy_timer;
  bool emgcy_button;
  bool emgcy_action;
  bool ovr_emgcy_action;
  bool cmd_emgcy_action;
  bool emgcy_action_pin;

  int pulses_timer;
  int pulses_to_send;
  bool pulse_pin;
  bool ovr_pulses;
  int cmd_pulses;

  int looptime;

  char incoming_bytes[32];
  int serial_counter;

  int cmd_counter;
  int cmd_base;
  char cmd_storage[CFG_CMD_STORAGE_SIZE][CFG_CMD_LENGTH];

}t_dre;

extern t_dre dre;

void dre_init(void);

#endif
