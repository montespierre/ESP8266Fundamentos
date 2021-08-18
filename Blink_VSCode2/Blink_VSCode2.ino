// the setup function runs once when you press reset or power the board
// https://www.youtube.com/watch?v=8jMr94B8iN0
// Lolin NodeMCU v3 ESP8266 LED = 2

void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Hola Mundo");
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(2, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);
  digitalWrite(2, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);
}
