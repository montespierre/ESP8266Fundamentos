#include <Servo.h>; // libreria de servomotor
int SERVO_PIN = D2; // asignar el pin 8

Servo myservo; // instanciando el objeto Servo

//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  myservo.attach(SERVO_PIN); // se asigna el servomotor al pin9

}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  myservo.write(0); //Spin in one direction
  delay(3000);
  myservo.write(90); // Stop
  delay(500);
  myservo.write(180);  // Spin in opposite direction
  delay(3000);
  myservo.write(90);  // Stop
  delay(500);

}
