#include "Arduino.h"
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_pinout.h"

#ifdef CFG_USE_RELAY_SET
int relay_set[CFG_RELAYSET_NUMBER] = CFG_RELAYSET_PINS;
#endif

void prj_output_init(void){
  int i;

  pinMode(CFG_EMGCY_BUT, INPUT_PULLUP);

#ifdef CFG_USE_EMGCY_RELAY
  pinMode(CFG_EMGCY_RELAY_PIN, OUTPUT);
  digitalWrite(CFG_EMGCY_RELAY_PIN,HIGH);
#endif

#ifdef CFG_USE_PULSE_PIN
pinMode(CFG_PULSE_CMD_PIN, OUTPUT);
digitalWrite(CFG_PULSE_CMD_PIN,HIGH);
#endif

  #ifdef CFG_USE_RELAY_SET
  for (i = 0; i < CFG_RELAYSET_NUMBER; i++){
    pinMode(relay_set[i],OUTPUT);
    digitalWrite(relay_set[i],LOW);
  }
  #endif
}

#ifdef DEBUG_PULSE
int tmppin = false;
#endif

void prj_output(void){
  int i;

    if (dre.ovr_emgcy_action == true) {
      dre.emgcy_action_pin = dre.cmd_emgcy_action;
    } else {
      dre.emgcy_action_pin = dre.emgcy_action;
    }

#ifdef CFG_USE_EMGCY_RELAY
    if (dre.emgcy_action_pin == true){
      digitalWrite(CFG_EMGCY_RELAY_PIN,HIGH);
    } else {
      digitalWrite(CFG_EMGCY_RELAY_PIN,LOW);
    }
#endif

  #ifdef DEBUG_PULSE
    if (tmppin != dre.pulse_pin){
      if (dre.pulse_pin){
        Serial.println("Pulso!!!");
      }
      tmppin = dre.pulse_pin;
    }
  #endif
  #ifdef CFG_USE_PULSE_PIN
  if (dre.pulse_pin == true){
    digitalWrite(CFG_PULSE_CMD_PIN,HIGH);
  } else {
    digitalWrite(CFG_PULSE_CMD_PIN,LOW);
  }
  #endif

  #ifdef CFG_USE_RELAY_SET
  for (i = 0; i < CFG_RELAYSET_NUMBER; i++){
    digitalWrite(relay_set[i],HIGH);
  }
  #endif

}
