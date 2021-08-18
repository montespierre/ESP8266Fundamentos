// https://www.youtube.com/watch?v=Q2HL8rwZ20A

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>
//#include <WiFiUdp.h>

// Globales
// Crear una ionstancia de WIfi client
WiFiClient espClient;
// Crear una instancia del MQTT client, basado en el cliente Wifi
PubSubClient client(espClient);

// otras variables
long lastMsg = 0;
char msg[50];
int value = 0;

float temperatura = 0; // Senal 1 que queremos publicar al boker
float humedad = 0; // Senal 2 que queremos publicar al boker
const int ledPin1 = 2; // LedPin GPIO2
const int ledPin2 = 4; // LedPin GPIO4
const int ledPin3 = 15; // LedPin GPIO15
//------------- PWM -----------------
const int ledPin4 = 16;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
//------------------------------

// Credenciales para conecatarse al wifi
const char* ssid = "Moche";
const char* password = "97788122";

// Direccion IP de la maquina en la red que corre el broker MQTT
const char* mqtt_server = "pollo.local";

void setup() {
  Serial.begin(9600);
  setup_wifi();

  // Configurar el MQTT client
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin4, ledChannel);

}

void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi conectado");
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
}

// Realizando conexion MQTT
void callback(char* topic, byte* message, unsigned int length){
  Serial.print("Mensaje recibido en topic: ");
  Serial.print(topic);
  Serial.print(", Message: ");
  String messageTemp;
  for(int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Primer output (usando topic: esp8266/output1)
  if(String(topic) == "esp8266/output1"){
    Serial.print("Cambio de salida");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin1, HIGH);
    }else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin1, LOW);
    }
  }

  // Segundo output (usando topic: esp8266/output2)
  if(String(topic) == "esp8266/output2"){
    Serial.print("Cambio de salida");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin2, HIGH);
    }else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin2, LOW);
    }
  }

  // Tercer output (usando topic: esp8266/output3)
  if(String(topic) == "esp8266/output3"){ // Si recibe mensaje sobre topic "esp8266/output3", verifica si es "on" o "off"
    Serial.print("Cambio de salida");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin3, HIGH);
    }else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin3, LOW);
    }
  }

  // Cuarto output (usando topic: esp8266/output4)
  if(String(topic) == "esp8266/output4"){ // Si recibe mensaje sobre topic esp8266/output4 manda al PWM (0255)
    Serial.print("Cambio de salida PWM: ");
    Serial.println("messageTemp");
    ledcWrite(ledChannel, messageTemp.toInt());
  }
}

// Realiza la reconexion en caso de fallo
void reconnect(){
  // Bucle hasta que reconecte
  while(!client.connected()){
      Serial.print("Intentado conexion MQTT");
      if(client.connect("ESP8266Client")){
        Serial.println("conectado");
        client.subscribe("esp8266/output1"); // Topic : 'esp8266/output1'
        client.subscribe("esp8266/output2"); // Topic : 'esp8266/output2'
        client.subscribe("esp8266/output3"); // Topic : 'esp8266/output3'
        client.subscribe("esp8266/output4"); // Topic : 'esp8266/output4'
      }else{
        Serial.print("Fallo, rc =");
        Serial.print(client.state());
        Serial.println(" Intentelo de nuevo en 5s");
        delay(5000);
      }
  }
}

// Realiza conexion MQTT (publisher: envia datos)
void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();

  long now = millis();
  if(now - lastMsg > 100){
    lastMsg = now;

    // Señal 1  que queremos enviar al broker
    temperatura = analogRead(36)*(100.0/4095.0);

    // Convertir el valor a char array
    char tempString[8];
    dtostrf(temperatura, 1, 2, tempString);
    Serial.print("Temperatura: ");
    Serial.println(tempString);
    client.publish("esp8266/temperature", tempString); // Topic: 'esp8266/temperature'

    // Señal 2 que queremos enviar al borker
    humedad = 289.78;

    // Convertir el valor a char array
    char humString[8];
    dtostrf(humedad, 1, 2, humString);
    Serial.print("Humedad: ");
    Serial.println(humString);
    client.publish("esp8266/humidity", humString); // Topic: 'esp8266/humidity'

  }

}
