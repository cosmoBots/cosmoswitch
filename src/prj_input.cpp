#include "Arduino.h"
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_pinout.h"

/*La funcion lee el sensor en RGB, lo compara con el valor de la comida y del veneno
*y si coincide con alguno de los dos se pone a 1 la dre.i_neurona correspondiente y se
*bloquea la lectura hasta que vuelva al valor 0 de forma automatica, siguiendo el protocolo
*aplicado por los investigadores de Lausanne, reduciendo 0,95 pts cada 50ms
*/

#define CICLO_R 0
#define CICLO_G 1
#define CICLO_B 2
#define CICLO_CALC 3

int ciclo = CICLO_R;

void lectura_luz_suelo(void){
  unsigned long tmp;
  switch (ciclo){
    case CICLO_R:
      //Leemos el rojo
      digitalWrite(CTE_SC_S2_PIN, LOW);
      digitalWrite(CTE_SC_S3_PIN, LOW);
      tmp = pulseIn(CTE_SENSOR_SUELO_PIN,LOW,100L);
      if (tmp>0) {
        dre.suelo.r = map(tmp,6,62,255,0);
      } else {
        dre.suelo.r = 0;
      }
      ciclo = CICLO_G;
      break;
    case CICLO_G:
      //Leemos el verde
      digitalWrite(CTE_SC_S2_PIN, HIGH);
      digitalWrite(CTE_SC_S3_PIN, HIGH);
      tmp = pulseIn(CTE_SENSOR_SUELO_PIN,LOW,100L);
      if (tmp>0) {
        dre.suelo.g = map(tmp,6,70,255,0);
      } else {
        dre.suelo.g = 0;
      }
      ciclo = CICLO_B;
      break;
    case CICLO_B:
      //Leemos el blue
      digitalWrite(CTE_SC_S2_PIN, LOW);
      digitalWrite(CTE_SC_S3_PIN, HIGH);
      tmp = pulseIn(CTE_SENSOR_SUELO_PIN,LOW,100L);
      if (tmp>0) {
        dre.suelo.b = map(tmp,1,20,255,0);
      } else {
        dre.suelo.b = 0;
      }
      ciclo = CICLO_CALC;
      break;
    case CICLO_CALC:
      //compara el valor con el del veneno
      if (dre.suelo.r >= (dre.veneno.r - CTE_MR) && dre.suelo.r <= (dre.veneno.r + CTE_MR)){
        dre.coincidencia++;
      }
      if (dre.suelo.g >= (dre.veneno.g - CTE_MG) && dre.suelo.g <= (dre.veneno.g + CTE_MG)){
        dre.coincidencia++;
      }
      if (dre.suelo.b >= (dre.veneno.b - CTE_MB) && dre.suelo.b <= (dre.veneno.b + CTE_MB)){
        dre.coincidencia++;
      }

      if (dre.coincidencia == 3){
        dre.i_neurona.comida = 0;//ponemos la dre.i_neurona de comida a 0
        dre.i_neurona.veneno = 1;//ponemos la dre.i_neurona de veneno a 1
      }
      dre.coincidencia = 0;

      //compara el valor de la comida, solo entra si no esta en la zona de veneno
      if (dre.i_neurona.veneno == 0 ){
        if (dre.suelo.r >= (dre.comida.r - CTE_MR) && dre.suelo.r <= (dre.comida.r + CTE_MR)){
          dre.coincidencia++;
        }
        if (dre.suelo.g >= (dre.comida.g - CTE_MG) && dre.suelo.g <= (dre.comida.g + CTE_MG)){
          dre.coincidencia++;
        }
        if (dre.suelo.b >= (dre.comida.b - CTE_MB) && dre.suelo.b <= (dre.comida.b + CTE_MB)){
          dre.coincidencia++;
        }
        if (dre.coincidencia == 3){
          dre.i_neurona.comida = 1;  //ponemos la dre.i_neurona de comida a 1
          dre.i_neurona.veneno = 0;  //ponemos la dre.i_neurona de veneno a 0
        }
        dre.coincidencia = 0;
      }
      ciclo = CICLO_R;
      break;
  }
}

void lectura_luz_alrededor(void){
  /* TODO */
}

void prj_input_init(void){
  pinMode(CTE_SENSOR_SUELO_PIN, INPUT);
  //Pines sensor color
  pinMode(CTE_SC_S2_PIN, OUTPUT);
  pinMode(CTE_SC_S3_PIN, OUTPUT);
}

void prj_input(void){
  lectura_luz_suelo();
  lectura_luz_alrededor();
}
