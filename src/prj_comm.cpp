#include "prj_cfg.h"
#include "prj_dre.h"
#include "Arduino.h"

#include "prj_input.h"
#include "prj_output.h"

void prj_comm_init(void){
  Serial.begin(115200); //activamos la comunicacion serial a una frecuencia de 9600 baudios
  Serial.flush(); //hace que cuando se envien datos se espere a que se terminen de enviar
}

void prj_comm(void){
  //Serial.println("Ejecutamos un ciclo");
}
