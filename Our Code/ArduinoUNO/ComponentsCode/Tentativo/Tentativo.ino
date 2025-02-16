#include "SoftwareSerial.h"// import the serial library
#include "Servo.h"

int i=0;

#define dir1PinL  2    //Motor direction
#define dir2PinL  4    //Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed
#define dir1PinR  7    //Motor direction
#define dir2PinR  8   //Motor direction
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed

#define echoPin 12
#define trigPin 13
float duration, distance;

Servo servo;              // define the name of the servo motor
int val;                  // rotation angle
int pos=92;               // start position of the servo
typedef struct{
  int x;
  int y;
} Obstacle;

Obstacle obstacle[150];

SoftwareSerial mySerial(10, 11); // RX, TX
int BluetoothData; // the data given from Computer
 
void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.attach(9);
  
  pinMode(2,OUTPUT);   //left motors  forward
  pinMode(4,OUTPUT);   //left motors reverse
  pinMode(7,OUTPUT);   //right  motors forward
  pinMode(8,OUTPUT);   //right motors reverse

  pinMode(speedPinL, OUTPUT);
  pinMode(speedPinR, OUTPUT);
  
  Serial.begin(9600);
  
  mySerial.begin(38400);  //serial bluetooth module initializing
  pinMode(LED_BUILTIN,OUTPUT);
}

void TEST(void){
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
}


void servoInit(void){
  servo.attach(9);
  servo.write(pos);
}

void servoFRotation(void){
  for (pos; pos <= 170; pos += 1) {         // rotate counterclockwise to check
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0343148;

    if(distance <= 30){
      obstacle[i].x = distance*cos(pos);
      obstacle[i].y = distance*sin(pos);
      i++;
    }

    servo.write(pos);
    delay(20);
  }
}

void servoSRotation(void){
  for (pos; pos >= 20; pos -= 1) {          // rotate clockwise to other check

    if(distance <= 30 && pos < 92){
      obstacle[i].x = distance*cos(pos);
      obstacle[i].y = distance*sin(pos);
      i++;
    }

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

void goForward(void){               //move  forward(all motors rotate in forward direction)
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void goLeft(void){                  //turn left (right side motors rotate in forward direction, left  side motors rotate in reverse)
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void goRight(void){                 //turn right (left side motors rotate in forward direction,  right side motors rotate in reverse)
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void goBack(void){                  //move reverse (all  motors rotate in reverse direction)
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void Stop(void){
  digitalWrite(dir1PinL,LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void loop() 
{
  
  servo.detach();                           // stops the movement of the servo
  // put your main code here, to run repeatedly:
  if (mySerial.available())
  {
    Serial.println("Pronto");
    BluetoothData=mySerial.read();
    Serial.println(BluetoothData);

    switch (BluetoothData){
      case 'F':
        TEST();
        goForward();
        set_Motorspeed(255,255);
        break;
      case 'B':
        TEST();
        goBack();
        set_Motorspeed(255,255);
        break;
      case 'L':
        TEST();
        goLeft();
        set_Motorspeed(255,255);
        break;
      case 'R':
        TEST();
        goRight();
        set_Motorspeed(255,255);
        break;
      case 'S':
        TEST();
        Stop();
        break;
      case 'W':
        digitalWrite(LED_BUILTIN,HIGH);
        break;
      case 'w':
        digitalWrite(LED_BUILTIN,LOW);
        break;
      default:
        Stop();
        break;
    }
    delay(100);// prepare for next data ...
  }
}