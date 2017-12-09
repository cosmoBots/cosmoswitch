#include "prj_cfg.h"
#include "prj_dre.h"
#include "Arduino.h"

t_dre dre;

void dre_init(void){
  uint8_t i;

  //define el valor RGB de la tira de comida, se le asigna un valor en el setup (rojo oscuro)
  dre.veneno.r  = 228;
  dre.veneno.g  = 155;
  dre.veneno.b  = 192;

  //define el valor RGB de la tira de veneno, se le asigna un valor en el setup (azul claro)
  dre.comida.r  = 192;
  dre.comida.g  = 232;
  dre.comida.b  = 229;

  dre.cont_ciclos_prueba = 0; //lleva la cuenta del numero de ciclos realizados en la prueba(sensores-actuadores)

  //Variables para almacenar el valor RGB del sensor de forma independiente
  dre.suelo.r = 0;
  dre.suelo.g = 0;
  dre.suelo.b = 0;

  //Variable que contienen el valor de la velocidad del motor en el rango
  dre.m_izq = 0;
  dre.m_der = 0;

////////=======================================================Variables temporales==========================================================================///////////////////////////////////////

  dre.state = 0; //sirve para la calibracion del sensor de luz
  dre.coincidencia = 0;
  dre.confirmacion = 0;// sirve para confirmar el estado de la comunicacion
  dre.temp = 0; //es usada en la comunicacion para guardar las instrucciones de navegacion
  dre.temp1 = 0; //variable usada dentro de las operaciones de cambio de rango para las salidas
  dre.n = 0; //variable para navegar por la tira de LED's
  dre.habilita_func = false;//variable usada en la secuencia de inicio
  dre.num_comms = 0;//variable temporal usada en la secuencia de inicio

  // Inicializamos las neuronas de entrada
  dre.i_neurona.comida = 0;
  dre.i_neurona.veneno = 0;
  dre.i_neurona.n2 = 0;
  dre.i_neurona.n3 = 0;
  dre.i_neurona.n4 = 0;
  dre.i_neurona.n5 = 0;
  dre.i_neurona.n6 = 0;
  dre.i_neurona.n7 = 0;
  dre.i_neurona.n8 = 0;

  // Inicializamos las neuronas de salida
  dre.o_neurona.izq = 0;
  dre.o_neurona.der = 0;
  dre.o_neurona.leds = 0;

  dre.iot_connected = false;
  dre.iot_go_online = false;
  dre.iot_go_offline = false;
  dre.iot_connect = false;
  dre.iot_disconnect = false;
  dre.iot_publish = false;
  dre.iot_publish_timer = 0;

  dre.looptime = 0;

  dre.emgcy_timer = 0;
  dre.emgcy_button = false;
  dre.emgcy_action = false;
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


}
