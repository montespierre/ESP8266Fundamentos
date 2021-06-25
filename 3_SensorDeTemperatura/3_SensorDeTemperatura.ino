#include <DHT.h>
#include <DHT_U.h>

DHT dht(D1, DHT11); //declarando objeto

float temp, hum;

void setup() {
  Serial.begin(9600);
  dht.begin(); // inicializamos objeto

}

void loop() {
  hum = dht.readHumidity(); // leer humedad
  temp = dht.readTemperature(); // leer temperatura

  Serial.println("Temperatura: " + String(temp) + " Humedad: " + String(hum));

  delay(5000);

}
