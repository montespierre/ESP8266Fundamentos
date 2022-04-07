// https://www.youtube.com/watch?v=8IxdEdTLOGY
// Tutorial
// https://www.youtube.com/watch?v=L6HiulJPzgE
// Mejorar MQTT
// https://github.com/montespierre/ESP8266Fundamentos/blob/version1/4_MQTT_v3-vRPZero/4_MQTT_v3-vRPZero.ino
// Falta !!!!!
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// Variables
int relay = 0;

/////////////////////////////// wifi credentials (inicio) ////////////////////////////////////////////
// Credenciales para conecatarse al wifi
const char* ssid = "CI_ICHL";
const char* password = "df97xBTSeCKy";
/////////////////////////////// wifi credentials (fin) ////////////////////////////////////////////

/////////////////////////////// mqtt credentials (inicio) ////////////////////////////////////////////
const char* mqtt_server = "mono.local";
// Crear una ionstancia de WIfi client
WiFiClient espClient;
// Crear una instancia del MQTT client, basado en el cliente Wifi
PubSubClient client(espClient);
/////////////////////////////// mqtt credentials (fin) ////////////////////////////////////////////

//////////////////////////////////// Funcion MQTT (inicio) ////////////////////////////////////////////////////
// Funcion que recibira mensajes MQTT payload desde nodered y lo llevara a pines de arduino
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensaje recibido en topic: ");
  Serial.print(topic);
  Serial.print("Message: ");

  String message;
  // Concatenando mensajes en variable mensaje
  for(int i = 0; i < length; i++){
    message = message + (char)payload[i]; // char convierte *byte a String
  }
  Serial.print(message);
  if(message == "0"){
    digitalWrite(relay, LOW);
  }
  // SI el mensaj es 1 prender relay
  if(message == "1"){
    digitalWrite(relay, HIGH);
  }
  Serial.println();
}
//////////////////////////////////// Funcion MQTT (fin) ////////////////////////////////////////////////////

//////////////////////////////////// Setup (inicio) ////////////////////////////////////////////////////
void setup() {
  ///////// Relay (inicio)//////////
  pinMode(relay, OUTPUT);
  ///////// Relay (fin)   //////////
  
  Serial.begin(115200);
  Serial.println("Las lecturas apareceran aqui");

  ///////// wifi conexion (inicio)//////////
  WiFi.begin(ssid, password);
  Serial.print("Conectando... ");
  while(WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi conectado");
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
  //////// wifi conexion (fin) /////////////

  //////// MQTT client (inicio) /////////////
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //////// MQTT client (fin) /////////////

  //////// Relay (inicio) /////////////
  // El topic se llama inLight con mensajes 0 y 1
  if(client.connect("Light")){ // Publisher name: "Light" otro caso "ESP8266Client"
    Serial.println("Light - MQTT - OK");
    client.subscribe("inLight"); // Topic : "inLight" ok
  }else{
    Serial.println("Light - MQTT - Error");
  }
  //////// Relay (fin) /////////////
}
//////////////////////////////////// Setup (fin) ////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  client.loop();

}
