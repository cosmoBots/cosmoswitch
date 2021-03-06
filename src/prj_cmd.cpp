#include "prj_cfg.h"
#include "prj_input.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"
#include "IoT.h"

void process_received_command(void){
  int tmpcursor;
  dre.incoming_bytes[dre.serial_counter-1] = '\0';
  if (dre.serial_counter>=2){
    if (dre.incoming_bytes[dre.serial_counter-2] == '\r'){
      dre.incoming_bytes[dre.serial_counter-2] = '\0';
    }
  }
  strcpy(dre.cmd_storage[dre.cmd_counter],dre.incoming_bytes);
  Serial.println("Comandos: ");
  for (tmpcursor = 0 ; tmpcursor < CFG_CMD_STORAGE_SIZE ; tmpcursor++){
    Serial.print(tmpcursor);
    Serial.print(" : ");
    Serial.print(dre.cmd_storage[tmpcursor]);
    if (tmpcursor == dre.cmd_counter) {
      Serial.print("[c]");
    }
    if (tmpcursor == dre.cmd_base) {
      Serial.print("[b]");
    }
    Serial.println();
  }
  dre.cmd_counter = (dre.cmd_counter + 1) % CFG_CMD_STORAGE_SIZE;
  dre.incoming_bytes[0] = '\0';
}
void process_pulse_cmd(){

}

void prj_cmd_init(void){

}

int estado_func = 0;

void prj_cmd(void){
  int tmpcursor;
  int ret = 0;

#ifdef DEBUG_SERIAL_RX
  ret = dre.serial_counter;
#endif
  ReceiveSysCmd();

  #ifdef DEBUG_SERIAL_RX
  if (ret != dre.serial_counter){
    Serial.println(dre.incoming_bytes);
    for (tmpcursor = 0; tmpcursor < dre.serial_counter; tmpcursor++){
      Serial.print(' ');
    }
    Serial.println('^');
  }
  #endif

  #ifdef DEBUG_ESTADO
  if (ret != estado_func){
    Serial.println(estado_func);
    estado_func = ret;
  }
  #endif

}
