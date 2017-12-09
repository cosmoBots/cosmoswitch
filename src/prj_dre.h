#ifndef _PRJ_DRE_H
#define _PRJ_DRE_H

#include "Arduino.h"

/* Configuracion */
#include "prj_cfg.h"

typedef struct {
  int r;
  int g;
  int b;
}t_color;

typedef struct {
  int comida;
  int veneno;
  int n2;
  int n3;
  int n4;
  int n5;
  int n6;
  int n7;
  int n8;
}t_in_neurona;

typedef struct {
  int izq;
  int der;
  int leds;
}t_out_neurona;


typedef struct {
  t_color veneno;
  t_color comida;
  t_color suelo;
  t_color cuadrante[4];
  int cont_ciclos_prueba;//lleva la cuenta del numero de ciclos realizados en la prueba(sensores-actuadores)

  //Definimos el vector que contendra los valores de todas las neuronas
  t_in_neurona i_neurona;
  t_out_neurona o_neurona; //vector de las neuronas de salida

  //Variable que contienen el valor de la velocidad del motor en el rango
  signed int m_izq;
  signed int m_der;

////////=======================================================Variables temporales==========================================================================///////////////////////////////////////

  int state; //sirve para la calibracion del sensor de luz
  int coincidencia;
  int confirmacion;// sirve para confirmar el estado de la comunicacion por la parte del arduino
  int temp; //es usada en la comunicacion para guardar las instrucciones de navegacion
  unsigned int temp1; //variable usada dentro de las operaciones de cambio de rango para las salidas
  int n; //variable para navegar por la tira de LEDs


  String serial_str;
  int serial_int;

  bool habilita_func;//variable usada en la secuencia de inicio
  int num_comms;//variable temporal usada en la secuencia de inicio
  int timer_comm; // Temporizador para las esperas

  bool boton_inicio;  // Variable para gestionar la pulsacion del boton de inicio.
  int timer_boton;    // Variable para gestionar el filtrado por tiempo del boton.

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
