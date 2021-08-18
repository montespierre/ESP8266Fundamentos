// Definiendo variables del ESP8266
#define LED1 D1
#define LED2 D2

void setup() {
  // Configurando pines como salidas
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

}

void loop() {
  // Prendiendo y apagando leds
  digitalWrite(LED1, HIGH);
  delay(5000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2,HIGH);
  delay(1700);
  digitalWrite(LED2, LOW);
  delay(100);

}
