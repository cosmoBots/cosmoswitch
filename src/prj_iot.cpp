#include "prj_iot.h"
#include "prj_dre.h"

#ifdef CFG_USE_WIFI

#ifdef ESP8266_WEMOS_D1MINI
#include <ESP8266WiFi.h>
#elif ARDUINO_ESP8266_NODEMCU
#include <ESP8266WiFi.h>
#elif ARDUINO_ESP8266_ESP01
#include <ESP8266WiFi.h>
#elif ESP32_DEV
#include <WiFi.h>
#else
#error "No microcontroller defined"
#endif

#endif

#ifdef CFG_USE_MQTT
#include <PubSubClient.h>

/****************************************
* Define Constants
****************************************/
char mqttBroker[]  = CFG_MQTT_BROKER;
char topic[150];
char str_bat[10];
char str_emgcy_action[10];
char str_emgcy_action_pin[10];
char str_pulses_to_send[10];

const char * VARIABLE_LABEL_BAT = "bat"; // Assign the variable label
const char * VARIABLE_LABEL_EMGCY_ACTION= "emgcy_action"; // Assign the variable label
const char * VARIABLE_LABEL_EMGCY_ACTION_PIN= "emgcy_action_pin"; // Assign the variable label
const char * VARIABLE_LABEL_PULSES_TO_SEND= "pulses_to_send"; // Assign the variable label
const char * VARIABLE_LABEL_RECONN_COUNTER = "reconnect_counter"; // Assign the variable label

/****************************************
* Auxiliar Functions
****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
String relayset_cmd_labels [CFG_RELAYSET_NUMBER];
String relayset_ovr_labels [CFG_RELAYSET_NUMBER];


void iot_set_suscriptions(void){
  int i;

  client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"CMD_EMGCY_ACTION_LABEL"/lv");
  client.loop();
  client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"OVR_EMGCY_ACTION_LABEL"/lv");
  client.loop();
  client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"OVR_PULSES_LABEL"/lv");
  client.loop();
  client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"CMD_PULSES_LABEL"/lv");
  client.loop();

  #ifdef CFG_USE_RELAY_SET
  for (i = 0; i < CFG_RELAYSET_NUMBER; i++){
    relayset_ovr_labels[i] = String("/v1.6/devices/") +
    String(DEVICE_LABEL) +
    String("/") +
    String(OVR_RELAYSET_ACTION_LABEL) +
    i +
    String("/lv");
    client.subscribe(relayset_ovr_labels[i].c_str());
    client.loop();
    relayset_cmd_labels[i] = String("/v1.6/devices/") +
    String(DEVICE_LABEL) +
    String("/") +
    String(CMD_RELAYSET_ACTION_LABEL) +
    i +
    String("/lv");
    client.subscribe(relayset_cmd_labels[i].c_str());
    client.loop();
  }
  #endif
}

void callback_ovr(char* topic, byte* payload, unsigned int length) {
  int i;
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.print("***********"); Serial.println(topic);
  if (strcmp_P(topic, "/v1.6/devices/"DEVICE_LABEL"/"OVR_EMGCY_ACTION_LABEL"/lv")==0){
    if (message == "0") {
      dre.ovr_emgcy_action = false;
      Serial.println("EMGCY: Not Override");
    } else {
      dre.ovr_emgcy_action = true;
      Serial.println("EMGCY: Override");
    }
  } else {
    if (strcmp_P(topic, "/v1.6/devices/"DEVICE_LABEL"/"CMD_EMGCY_ACTION_LABEL"/lv")==0){
      if (message == "0") {
        dre.cmd_emgcy_action = false;
        Serial.println("EMGCY: Relay Off");
      } else {
        dre.cmd_emgcy_action = true;
        Serial.println("EMGCY: Relay On");
      }
    } else {
      if (strcmp_P(topic, "/v1.6/devices/"DEVICE_LABEL"/"OVR_PULSES_LABEL"/lv")==0){
        if (message == "0") {
          dre.ovr_pulses = false;
          Serial.println("PULSES: Not Override");
        } else {
          dre.ovr_pulses = true;
          Serial.println("PULSES: Override");
        }
      } else {
        if (strcmp_P(topic, "/v1.6/devices/"DEVICE_LABEL"/"CMD_PULSES_LABEL"/lv")==0){
          dre.cmd_pulses = message.toInt();
          Serial.print("PULSES: ");
          Serial.println(dre.cmd_pulses);
        } else {
          /* Do nothing */
        }
      }
    }
    #ifdef CFG_USE_RELAY_SET
    for (i = 0; i < CFG_RELAYSET_NUMBER; i++){
#ifdef CFG_RELAY_USE_OVERRIDE      
      if (strcmp_P(topic, relayset_ovr_labels[i].c_str())==0){
        Serial.print(i);
        if (message == "0") {
          Serial.println(" Relay: Not Override");
          dre.ovr_relay_action[i] = false;
        } else {
          Serial.println(" Relay: Override");
          dre.ovr_relay_action[i] = true;
        }
      }
#endif
      if (strcmp_P(topic, relayset_cmd_labels[i].c_str())==0){
        Serial.print(i);
        if (message == "0") {
          Serial.println(" Relay: Off");
          dre.cmd_relay_action[i] = false;
        } else {
          Serial.println(" Relay: On");
          dre.cmd_relay_action[i] = true;
        }
      }
    }
    #endif
  }

  //Serial.write(payload, length);
  Serial.println();
}

int reconnection_counter = 1;

void iot_say_hello(void) {
  bool ret = false;

  dtostrf(reconnection_counter++, 4, 0, str_bat);
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(dre.iot_payload, "%s", ""); // Cleans the payload
  sprintf(dre.iot_payload, "{\"%s\": %s}", VARIABLE_LABEL_RECONN_COUNTER, str_bat); // Adds the variable label
#ifdef DEBUG_IOT
  Serial.print(topic);Serial.print(": ");Serial.println(dre.iot_payload);
#endif
  ret = client.publish(topic, dre.iot_payload);
  if (ret == false) {
    Serial.println("Publication failed!");
  } else {
#ifdef DEBUG_IOT
    Serial.println("Publication worked!");
#endif
    }
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
#ifdef CFG_IOT_ONLY_RX
      // In the case we don't send data, we need a message to say 
      // we have been reconnected
      iot_say_hello();
#endif       
      iot_set_suscriptions();
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

#endif


void iot_init(void){
  #ifdef CFG_USE_WIFI
  WiFi.begin(WIFISSID, PASSWORD);

  Serial.println();
  Serial.print("Wait for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  #endif /* CFG_USE_WIFI */
  #ifdef CFG_USE_MQTT
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback_ovr);
  iot_set_suscriptions(); 
  #endif
}

void prj_iot_init(){
  #ifdef CFG_USE_MQTT
  if (dre.iot_connect == true){
    if (WiFi.status() != WL_CONNECTED){
      iot_init();
    }
    if (!client.connected()) {
      reconnect();
      iot_set_suscriptions();
    }
  }
  dre.iot_connected = client.connected();
  #ifdef DEBUG_IOT
  Serial.print("iot_connected1: ");Serial.println(dre.iot_connected);
  Serial.print("iot_publish1: ");Serial.println(dre.iot_publish);
  #endif
  #endif
  #ifdef DEBUG_IOT
  Serial.print("dre.iot_connect: ");Serial.println(dre.iot_connect);
  Serial.print("dre.iot_go_online: ");Serial.println(dre.iot_go_online);
  #endif
}

int payload_counter = 0;

void prj_iot(){

  bool ret = false;

  #ifdef CFG_USE_MQTT
  if (dre.iot_connect == true){
    if (WiFi.status() != WL_CONNECTED){
      iot_init();
    }
    if (!client.connected()) {
      reconnect();
      iot_set_suscriptions();
    }
  }
  if (client.connected() && dre.iot_publish == true) {
#ifndef CFG_IOT_ONLY_RX
    #ifdef DEBUG_IOT
    Serial.print("Connecting to IoT server with counter "); Serial.println(payload_counter);
    #endif

    switch (payload_counter){
      case 0:
        dtostrf(dre.bat, 4, 0, str_bat);
        dtostrf(dre.emgcy_action, 1, 0, str_emgcy_action);
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
        sprintf(dre.iot_payload, "%s", ""); // Cleans the payload
        sprintf(dre.iot_payload, "{\"%s\": %s,", VARIABLE_LABEL_BAT, str_bat); // Adds the variable label
        sprintf(dre.iot_payload, "%s\"%s\": %s}", dre.iot_payload, VARIABLE_LABEL_EMGCY_ACTION_PIN, str_emgcy_action); // Adds the variable label
        break;
      case 1:
        dtostrf(dre.pulses_to_send, 2, 0, str_pulses_to_send);
        dtostrf(dre.emgcy_action_pin, 1, 0, str_emgcy_action_pin);
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
        sprintf(dre.iot_payload, "%s", ""); // Cleans the payload
        sprintf(dre.iot_payload, "{\"%s\": %s,", VARIABLE_LABEL_PULSES_TO_SEND, str_pulses_to_send); // Adds the variable label
        sprintf(dre.iot_payload, "%s\"%s\": %s}", dre.iot_payload, VARIABLE_LABEL_EMGCY_ACTION, str_emgcy_action_pin); // Adds the variable label
        break;
    }
    payload_counter = (payload_counter + 1) % 2;
    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/

    /* Building the Ubidots request */

    /* Publish the request to Ubidots */
    #ifdef DEBUG_IOT
    Serial.print(topic);Serial.print(": ");Serial.println(dre.iot_payload);
    #endif
    ret = client.publish(topic, dre.iot_payload);
    if (ret == false) {
      Serial.println("Publication failed!");
    } else {
      #ifdef DEBUG_IOT
      Serial.println("Publication worked!");
      #endif
    }
    #ifdef DEBUG_IOT
    if (dre.iot_publish) {
      Serial.println(dre.iot_payload);
    }
    #endif
#endif
    client.loop();
  }
  dre.iot_connected = client.connected();
  #endif
}
