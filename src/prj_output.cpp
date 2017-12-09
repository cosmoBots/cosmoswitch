#include "Arduino.h"
#include "prj_cfg.h"
#include "prj_dre.h"

#include <Adafruit_NeoPixel.h>

///////===================================== Inicializacion de los componentes ========================================================//////////
Adafruit_NeoPixel strip = Adafruit_NeoPixel(CTE_NUM_LEDS, CTE_STRIP_PIN, NEO_GRB + NEO_KHZ800); //tira de LED's

#ifdef CFG_USE_MOTOR_SHIELD
#include <AFMotor.h>
AF_DCMotor motor1(1);   //motores
AF_DCMotor motor2(2);
#endif

/*Funcion que define el comportamiento de los actuadores, reciben de entrada las neuronas de salida
*Traduce el valor de las neuronas en sentido y modulo de la velocidad, y en uno de los 3 colores posibles
*/

void output_actuadores(void){

  //Cambiamos el rango de [-100,100] a [-255,255] para ambos motores, es una simple regla de 3
  //Notese que si fuera negativo no pasaria nada, porque al convertirlo quedara igualmente como negativo
  dre.m_izq = (255/100)*(dre.o_neurona.izq - 100);
  dre.m_der = (255/100)*(dre.o_neurona.der - 100);

  //Movimiento de la rueda izquierda
  if (dre.m_izq < (-CTE_MM)){
    dre.temp1 = dre.m_izq + 25;
    #ifdef CFG_USE_MOTOR_SHIELD
    motor1.run(BACKWARD);
    motor1.setSpeed(dre.temp1);
    #endif
  }
  else if(dre.m_izq > CTE_MM){
    dre.temp1 = dre.m_izq + 25;
    #ifdef CFG_USE_MOTOR_SHIELD
    motor1.run(FORWARD);
    motor1.setSpeed(dre.temp1);
    #endif
  }
  else if (dre.m_izq > (-CTE_MM) && dre.m_izq < CTE_MM) {
    #ifdef CFG_USE_MOTOR_SHIELD
    motor1.run(RELEASE);
    #endif
  }

  //Movimiento de la rueda derecha
  if (dre.m_der < (-CTE_MM)){
    dre.temp1 = dre.m_der;
    #ifdef CFG_USE_MOTOR_SHIELD
    motor2.run(BACKWARD);
    motor2.setSpeed(dre.temp1);
    #endif
  }
  else if(dre.m_der > CTE_MM){
    dre.temp1 = dre.m_der;
    #ifdef CFG_USE_MOTOR_SHIELD
    motor2.run(FORWARD);
    motor2.setSpeed(dre.temp1);
    #endif
  }
  else if (dre.m_der > (-CTE_MM) && dre.m_der < CTE_MM){
    #ifdef CFG_USE_MOTOR_SHIELD
    motor2.run(RELEASE);
    #endif
  }

  // LEDS
  // Gracias a dre.n, a cada ciclo de programa cambiamos un led de la tira
  if ((dre.o_neurona.leds - 100) < (-CTE_ML)){
    strip.setPixelColor(dre.n, strip.Color(255,0,0));//emite un rojo absoluto, siguiendo los parametros del experimento
    strip.show();
  }
  else if((dre.o_neurona.leds - 100) > CTE_ML){
    strip.setPixelColor(dre.n, strip.Color(0,0,255));//emite un azul absoluto, siguiendo los parametros del experimento
    strip.show();
  }
  else if (((dre.o_neurona.leds - 100) > (-CTE_ML)) && ((dre.o_neurona.leds - 100) < CTE_ML)){
    strip.setPixelColor(dre.n, strip.Color(0,255,0));//emite un verde absoluto, introduciendo un tercer color al experimento
    strip.show();
  }

  dre.n = (dre.n + 1) % CTE_NUM_LEDS;
}

void prj_output_init(void){
  #ifdef CFG_USE_MOTOR_SHIELD
  motor1.run(RELEASE);//iniciamos los motores
  motor2.run(RELEASE);
  #endif
  strip.begin();
  strip.show();//Inicializa la tira como apagada
}

void prj_output(void){
  output_actuadores();
}
