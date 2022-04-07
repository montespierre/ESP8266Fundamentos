// https://www.youtube.com/watch?v=8IxdEdTLOGY
// Tutorial
// https://www.youtube.com/watch?v=L6HiulJPzgE
// Mejorar MQTT
// https://github.com/montespierre/ESP8266Fundamentos/blob/version1/4_MQTT_v3-vRPZero/4_MQTT_v3-vRPZero.ino
// OK
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// Variables
#define relay 0

//////////////////////////////////// Setup (inicio) ////////////////////////////////////////////////////
void setup() {
  ///////// Relay (inicio)//////////
  pinMode(relay, OUTPUT);
  ///////// Relay (fin)   //////////
  
  Serial.begin(115200);
  Serial.println("Las lecturas apareceran aqui");
}
//////////////////////////////////// Setup (fin) ////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  digitalWrite(relay, LOW);
  Serial.println("Apagado2");
  delay(5000);
  digitalWrite(relay, HIGH);
  Serial.println("Prendido2");

}
