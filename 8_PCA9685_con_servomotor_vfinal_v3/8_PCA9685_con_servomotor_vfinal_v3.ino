// https://www.youtube.com/watch?v=pne01vHabMw
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
// https://www.youtube.com/watch?v=y8X9X10Tn1k
// https://www.youtube.com/watch?v=EUd4Fqot1Mc&t=114s

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver servos1 = Adafruit_PWMServoDriver();


#define SERVOMIN  1450 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1600 // This is the 'maximum' pulse length count (out of 4096)


#define FREQUENCY 50

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("8 channel Servo test!");

  // Inicializando la libreria para comunicarse con el PCA9685
  servos1.begin();
  
  //pwm.setOscillatorFrequency(27000000);
  servos1.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  delay(FREQUENCY);
}

////////////// Functions (inicio) //////////////////////
void driveMin(){
  servos1.setPWM(servonum, 0, SERVOMIN);
}

void driveMax(){
  servos1.setPWM(servonum, 0, SERVOMAX);
}
////////////// Functions (inicio) //////////////////////

void loop() {
  // Mover motor siguiendo loop ascendente de angulo de 0 a 101 cada 15 grados
  for(int angle = 0; angle <= 361; angle += 45){
    delay(500);
    servos1.setPWM(servonum, 0, convert2angle(angle)); // moviendo el servinum 0
  }
}

// Convertir angulo a pulso
int convert2angle(int myAng){
  int pulse, analog_value;
  pulse = map(myAng, 0, 360, SERVOMIN, SERVOMAX); // 0 grados se vuelve 150 y 180 se vuelve 600 de pulso
  analog_value = int(float(pulse) / 1000000 * FREQUENCY * 4096);
  Serial.println("Angulo/Pulso: ");
  Serial.println(myAng);
  Serial.println(" / ");
  Serial.println(pulse);
  Serial.println(" / ");
  Serial.println(analog_value);
  return analog_value;
}
