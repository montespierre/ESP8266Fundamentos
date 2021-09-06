// https://www.indiamart.com/superb-technologies/servo-motor.html
// https://www.emoro.eu/shop/index.php?route=product/product&product_id=59
// By default, the min and max pulse width is set to 544 and 2400 microseconds. These values work for most common servos, but sometimes you have to adjust the values slightly.
/* The RM-0090 is RC servo motor with bidirectional continuous rotation and linear response to PWM. 
 *  The default neutral position (N.P.) is at 1500 us, but this can be adjusted by sending an desired PWM width  (eg 1400 us) and holding the red button for 7 sec. 
 *  PWM pulse from 1450 to 1475 (N.P. - 50 to N.P. - 25)
 *  from 1525 to 1550 (N.P. + 25 to N.P. + 50) is for FAST STOP, but PWM pulse from 1475 to 1525 (N.P. +/- 25) is for FREE RUNNING STOP. Pulse widths above the N.P. + 50 result in counterclockwise rotation, with speed increasing as the pulse width increases; pulse widths below the N.P. - 50 result in clockwise rotation, with speed increasing as the pulse width decreases.
*/
#include <Servo.h>; // libreria de servomotor
#define servoPin D2
int minimo = 400;
int maximo = 2500;
Servo myservo;
void setup() {
  // Establece el pin indicado en la variable servo, considerando min el ancho de pulso para la posición 0° y max el ancho de pulso para 180°.Ej:  servo.attach(2,900,2100);
  myservo.attach(servoPin, minimo, maximo);
}

void loop(){
  // Envía al servo el ancho de pulso=tiempo en microsegundos. Ej: servo.writeMicroseconds(1500);  
  myservo.writeMicroseconds(maximo);
  delay(5000);
  myservo.writeMicroseconds(1500);
  delay(5000);
  myservo.writeMicroseconds(minimo);
  delay(5000);

  
}
