#include "Arduino.h"
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_pinout.h"

void prj_output_init(void){

  pinMode(CFG_EMGCY_BUT, INPUT_PULLUP);
  pinMode(CFG_PULSE_CMD_PIN, OUTPUT);
  pinMode(CFG_EMGCY_RELAY_PIN, OUTPUT);

  digitalWrite(CFG_EMGCY_RELAY_PIN,HIGH);
  digitalWrite(CFG_PULSE_CMD_PIN,HIGH);
}

#ifdef DEBUG_PULSE
int tmppin = false;
#endif

void prj_output(void){
    if (dre.ovr_emgcy_action == true) {
      dre.emgcy_action_pin = dre.cmd_emgcy_action;
    } else {
      dre.emgcy_action_pin = dre.emgcy_action;
    }

    if (dre.emgcy_action_pin == true){
      digitalWrite(CFG_EMGCY_RELAY_PIN,HIGH);
    } else {
      digitalWrite(CFG_EMGCY_RELAY_PIN,LOW);
    }

  #ifdef DEBUG_PULSE
    if (tmppin != dre.pulse_pin){
      if (dre.pulse_pin){
        Serial.println("Pulso!!!");
      }
      tmppin = dre.pulse_pin;
    }
  #endif
    if (dre.pulse_pin == true){
      digitalWrite(CFG_PULSE_CMD_PIN,HIGH);
    } else {
      digitalWrite(CFG_PULSE_CMD_PIN,LOW);
    }

  }
