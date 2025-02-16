#include "SoftwareSerial.h"                   // import the serial library for the BLE module communication
#include "Servo.h"                            // Servo motor library

int i=0;
float Travel=0;

#define dir1PinL  2    //Motor direction
#define dir2PinL  4    //Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed
#define dir1PinR  7    //Motor direction
#define dir2PinR  8   //Motor direction
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed
#define speedMotor 255  // sets the "speed" of the motor, from 0, completeley still, to 255, max outtage

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

SoftwareSerial mySerial(10, 11);        // RX (Read Pin), TX (Tell Pin)
int BluetoothData;                      // the data given from Computer
 
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

void TEST(void){                        // testing function, led on/off
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
}

void servoInit(void){                   // Initialise the servo Pin and its starting position
  servo.attach(9);
  servo.write(pos);
}

void servoFRotation(void){              // rotates counter clockwise to check left side
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

void servoSRotation(void){              // rotates clockwise to check left side
  
  for (pos; pos >= 20; pos -= 1) {

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0343148;

    if(distance <= 30 && pos < 92){
      obstacle[i].x = distance*cos(pos);
      obstacle[i].y = distance*sin(pos);
      i++;
    }

    servo.write(pos);
    delay(20);
  }
}

void servoReturn(void){                 // returns the servo in default position (92) and detaches it
  if(pos!=92){
    for (pos; pos <= 92; pos += 1) {
      servo.write(pos);
      delay(20);
    }
    servo.detach();
  }
}

bool IsNear(void){                      // defines if the Rover is near an Obstacle
  bool Near;
  int j = i;
  do{
    if( Travel > (Obstacle{j}.x - 5) || Travel > (Obstacle{j}.y - 5) ){
      Near = True;
    }
    else{
      Near = False;
    }
    j--;
  }while(j!=0);
  return Near;
}

void goForward(void){                   // move  forward(all motors rotate in forward direction)
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
  Travel += 0.5;
}
void goLeft(void){                      // turn left (right side motors rotate in forward direction, left  side motors rotate in reverse)
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void goRight(void){                     // turn right (left side motors rotate in forward direction,  right side motors rotate in reverse)
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void goBack(void){                      // move reverse (all  motors rotate in reverse direction)
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
  Travel += 0.5;
}
void Stop(void){                        // stops all motors
  digitalWrite(dir1PinL,LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}
void set_Motorspeed(int speed_L,int speed_R){
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void loop() 
{                                           // put your main code here, to run repeatedly:

  if(Travel != 0 && IsNear){
    servoInit;
    servoFRotation;
    servoSRotation;
    servoReturn;
  }

  if (mySerial.available() && !IsNear)
  {

    mySerial.write("MotorSpeed =" + String(speedMotor));
    BluetoothData=mySerial.read();
    Serial.println(BluetoothData);

    switch (BluetoothData){
      case 'F':
        TEST();
        goForward();
        set_Motorspeed(speedMotor,speedMotor);
        break;
      case 'B':
        TEST();
        goBack();
        set_Motorspeed(speedMotor,speedMotor);
        break;
      case 'L':
        TEST();
        goLeft();
        set_Motorspeed(speedMotor,speedMotor);
        break;
      case 'R':
        TEST();
        goRight();
        set_Motorspeed(speedMotor,speedMotor);
        break;
      case 'S':
        TEST();
        Stop();
        break;
      case 'W':                                         // a quick check to see if there is communication between BTM e Computer
        digitalWrite(LED_BUILTIN,HIGH);
        break;
      case 'w':                                         // see case 'W':
        digitalWrite(LED_BUILTIN,LOW);
        break;
      default:
        Stop();
        break;
    }
    delay(20);                               // prepare for next data ...
  }
}