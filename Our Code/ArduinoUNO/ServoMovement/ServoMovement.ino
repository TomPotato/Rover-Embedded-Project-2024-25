#include "Servo.h"
Servo servo;
int val;                //rotation angle
int pos=92;
bool cwRotation, ccwRotation;  //the states of rotation
void setup()
{
  Serial.begin(9600);
  servo.attach(9);     //servo pin
}
void loop()
{
  servo.write(pos);
  delay(500);
  for (pos; pos <= 170; pos += 1) {
    servo.write(pos);
    delay(20);
  }
  for (pos; pos >= 20; pos -= 1) {
    servo.write(pos);
    delay(20);
  }
    for (pos; pos <= 92; pos += 1) {
    servo.write(pos);
    delay(20);
  }
  servo.detach();
}