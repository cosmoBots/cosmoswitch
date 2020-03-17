#include "Arduino.h"
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_pinout.h"

#ifdef ESP8266_WEMOS_D1MINI
  ADC_MODE(ADC_VCC);
#elif ARDUINO_ESP8266_NODEMCU
  ADC_MODE(ADC_VCC);
#elif ARDUINO_ESP8266_ESP01
  ADC_MODE(ADC_VCC);
#elif ESP32_DEV
#elif TEENSY31
#elif ARDUINO_AVR_UNO
#else
#error "No microcontroller defined"
#endif

void prj_input_init(void){
}

void prj_input(void){
  #ifdef ESP8266_WEMOS_D1MINI
  dre.bat = ESP.getVcc();
  #elif ARDUINO_ESP8266_NODEMCU
  dre.bat = ESP.getVcc();
  #elif ARDUINO_ESP8266_ESP01
  dre.bat = ESP.getVcc();
  #elif ESP32_DEV
  dre.bat = analogRead(CFG_BAT_ADC);
  #elif TEENSY31
  dre.bat = analogRead(CFG_BAT_ADC);
  #elif ARDUINO_AVR_UNO
  dre.bat = analogRead(CFG_BAT_ADC);
  #else
  #error "No microcontroller defined"
  #endif

  dre.emgcy_button = (digitalRead(CFG_EMGCY_BUT)==LOW);

}
