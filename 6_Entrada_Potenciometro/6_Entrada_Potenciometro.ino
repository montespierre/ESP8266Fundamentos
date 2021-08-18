
void setup() {
  pinMode(A0, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  int x = analogRead(A0);
  Serial.println(x);
  delay(1000);

}
