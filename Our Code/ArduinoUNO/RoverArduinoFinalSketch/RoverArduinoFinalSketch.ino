#include "SoftwareSerial.h"                   // import the serial library for the BLE module communication
#include "Servo.h"                            // Servo motor library

int i=0;
int temp=0;
float Travel=0.5;

int pinTotal = 19;      // defines the total of the pins that are used in the Arduino

#define dir1PinL  8    //Motor direction
#define dir2PinL  7    //Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed
#define dir1PinR  4    //Motor direction
#define dir2PinR  2   //Motor direction
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed
#define speedMotor 200  // sets the "speed" of the motor, from 0, completeley still, to 255, max outtage

#define echoPin 13
#define trigPin 12
float duration, distance;

Servo servo;              // define the name of the servo motor 
int val;                  // rotation angle
int pos=90;               // start position of the servo
typedef struct{
  int x;
  int y;
} Obstacle;

Obstacle obstacle[150];

SoftwareSerial mySerial(0, 1);        // RX (Read Pin), TX (Tell Pin)
int BluetoothData;                      // the data given from Computer

void setup() 
{
   servo.attach(9);
  
  pinMode(2,OUTPUT);   //left motors  forward
  pinMode(4,OUTPUT);   //left motors reverse
  pinMode(7,OUTPUT);   //right  motors forward
  pinMode(8,OUTPUT);   //right motors reverse

  pinMode(speedPinL, OUTPUT);
  pinMode(speedPinR, OUTPUT);
  
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  mySerial.begin(9600);  //serial bluetooth module initializing
  pinMode(LED_BUILTIN,OUTPUT);
}

void TEST(void){                        // testing function, led on/off
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
}

bool PINTEST(void){                     // tests if the pins are connected to something or not      
  do{
    if(digitalRead(pinTotal)==0){
      switch(pinTotal){
        case 0:
          RaiseInterrupt(2);
          Serial.println("Error Pin Rx detached");
          return false;
          break;
        case 1:
          RaiseInterrupt(2);
          Serial.println("Error Pin Tx detached");
          return false;
          break;
        case 2:
          RaiseInterrupt(2);
          Serial.println("Error Pin RMotorB detached");
          return false;
          break;
        case 4:
          RaiseInterrupt(2);
          Serial.println("Error Pin RMotorF detached");
          return false;
          break;
        case 5:
          RaiseInterrupt(2);
          Serial.println("Error Pin SpeedRMotor detached");
          return false;
          break;
        case 6:
          RaiseInterrupt(2);
          Serial.println("Error Pin SpeedLMotor detached");
          return false;
          break;
        case 7:
          RaiseInterrupt(2);
          Serial.println("Error Pin LMotorF detached");
          return false;
          break;
        case 8:
          RaiseInterrupt(2);
          Serial.println("Error Pin LMotorB detached");
          return false;
          break;
        case 9:
          RaiseInterrupt(2);
          Serial.println("Error Pin ServoMotor detached");
          return false;
          break;
        case 11:
          RaiseInterrupt(2);
          Serial.println("Error Pin LED detached");
          return false;
          break;
        case 12:
          RaiseInterrupt(2);
          Serial.println("Error Pin TRIG detached");
          return false;
          break;
        case 13:
          RaiseInterrupt(2);
          Serial.println("Error Pin ECHO detached");
          return false;
          break;
        default:
          RaiseInterrupt(3);
          Serial.println("No CLUE found");
          break;
      }
    }
    pinTotal--;
  }while(pinTotal>=0);
}

void RaiseInterrupt(int num){           // raises an interrupt number in the vector
  if(mySerial.available()){
    Serial.println(num);
  }
}

void servoInit(void){                   // Initialise the servo Pin and its starting position
  servo.attach(9);
  servo.write(pos);
}

void servoFRotation(void){              // rotates counter clockwise to check left side
  for (pos; pos <= 145; pos += 5) {         // rotate counterclockwise to check
    
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343148;
  
  if (distance >= 400){
    Serial.print("Distance>=400cm");
    delay(500);
  }
  else if(distance <= 30){
    Serial.print("Obstacle Too Near");
    delay(500);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
  }
  delay(100);

    /*digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);   
    distance = (duration/2) * 0.0344;
    
    Serial.println(duration);
    servo.write(pos);
    delay(1000);*/
  }
  delay(100);
}

void servoSRotation(void){              // rotates clockwise to check left side
  
  for (pos; pos >= 30; pos -= 5) {

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) * 0.0344;

    Serial.println(duration);
    
    if(distance <= 40 ){
      Serial.println("OBJECT DETECTED");
      obstacle[i].x = distance*cos(pos);
      obstacle[i].y = distance*sin(pos);
      i++;
    }else{
      Serial.println("NO OBJECT DETECTED");
    }
    servo.write(pos);
    delay(100);
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
  bool Near=false;
  int j = i;
  do{
    if( Travel == (obstacle[j].x - 5) || Travel == (obstacle[j].y - 5) ){
      Near = true;
      Serial.println("IS NEAR");
      RaiseInterrupt(1);  
    }
    else{
      Near = false;
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
void goLeft(void){                  //turn left (right side motors rotate in forward direction, left  side motors rotate in reverse)
  digitalWrite(dir1PinL,HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void goRight(void){                 //turn right (left side motors rotate in forward direction,  right side motors rotate in reverse)
  digitalWrite(dir1PinL,LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
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
  //if(PINTEST()){

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343148;
  
  if (distance >= 400){
    Serial.print("Distance>=400cm");
    delay(500);
  }
  else if(distance <= 30){
    Serial.print("Obstacle Too Near");
    delay(500);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
  }
  delay(100);
/*
  if(Travel == 0){
    servoInit();
    servoFRotation();
    servoSRotation();
    servoReturn();
  }else if(!IsNear()){
    servoInit();
    servoFRotation();
    servoSRotation();
    servoReturn();
  }
  else{
      Serial.println("The object is too close fall back");
  }

  if (mySerial.available() && !IsNear())
  {

    Serial.println("MotorSpeed =" + String(speedMotor));
    BluetoothData=mySerial.read();

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
      case 'P':
        digitalWrite(11,HIGH);
        if(temp==0){
          Serial.println("LED ON ");
          temp=1;
        }
        break;
      case 'W':
        digitalWrite(11,LOW);
        if(temp!=0){
          Serial.println("LED OFF");
          temp=0;
        }
        break;
      default:
        Stop();
        break;
    }
    //delay(20);                               // prepare for next data ...
  }*/
//}
}