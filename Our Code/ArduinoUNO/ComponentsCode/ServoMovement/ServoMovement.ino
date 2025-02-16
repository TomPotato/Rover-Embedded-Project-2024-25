#include "Servo.h"
Servo servo;              // define the name of the servo motor
int val;                  // rotation angle
int pos=92;               // start position of the servo

void setup()
{
  Serial.begin(9600);
  servo.attach(9);        //servo pin
}

void servoAtt(void){
  servo.attach(9);
}

void servoFRotation(void){
    for (pos; pos <= 170; pos += 1) {         // rotate counterclockwise to check
    servo.write(pos);
    delay(20);
  }
}

void servoSRotation(void){
  for (pos; pos >= 20; pos -= 1) {          // rotate clockwise to other check
    servo.write(pos);
    delay(20);
  }
}

void servoReturn(void){
  if(pos!=92){
    for (pos; pos <= 92; pos += 1) {        // returns in default position
      servo.write(pos);
      delay(20);
    }
  }
}

void loop()
{
  servoAtt();
  servoFRotation();
  servoSRotation();
  servoReturn();
  delay(500);
  servo.detach();                           // stops the movement of the servo
}