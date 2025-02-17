#include "SoftwareSerial.h"                   // import the serial library for the BLE module communication
#include "Servo.h"                            // Servo motor library

int i = 0;
int temp = 0;

int count = 10;           // numbers of command S received 
                          //it is used to decide how much time the Rover can stay still before it initialaizes a scan

bool Travel = true;       // check to see if the rover traveled more than 0 cm

int pinTotal = 19;      // defines the total of the pins that are used in the Arduino

#define dir1PinL  8    //Motor direction Forward left side motors
#define dir2PinL  7    //Motor direction Backwards left side motors
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed
#define dir1PinR  4    //Motor direction Forward right side motors
#define dir2PinR  2   //Motor direction Backwards right side motors
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed
#define speedMotor 200  // sets the "speed" of the motor, from 0, completeley still, to 255, max outtage

#define LED_PIN 3       // led accension pins

#define echoPin 13
#define trigPin 12
float duration, distance;  // used to obtain the distance between the ultrasonic component and the obstacle

Servo servo;              // define the name of the servo motor 
int val;                  // rotation angle
int pos=90;               // start position of the servo

/*typedef struct{           // used to define the position in the space of the obstacles and the Rover
  int x;
  int y;
} Obstacle;

Obstacle obstacle[150];   // array of obstacles
Obstacle Me;              // Rover Itself*/
int angle = 90;           // angle from which the rover starts

SoftwareSerial mySerial(10, 11);        // RX (Read Pin), TX (Tell Pin)
int BluetoothData;                      // the data given from Computer

void setup(){                            // setup code, initialaizes the pins etcetera
  servo.attach(9);     //pin 9 for servo
  
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
}

/*bool PINTEST(void){                     // tests if the pins are connected to something or not, might be implementable in the near future
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
        case 3:
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
}*/

void RaiseInterrupt(int num){           // raises an interrupt number in the vector, prints it in the cmd
  if(mySerial.available()){
    mySerial.println(num);
  }
}

void servoInit(void){                   // Initialise the servo Pin and its starting position
  servo.attach(9);  
  pos = 90;
  servo.write(pos);
}

void servoFRotation(void){              // rotates counter clockwise to check left side
  for (pos; pos <= 145; pos += 5) {         
    servo.write(pos);
    delay(100);
  }
}

void servoSRotation(void){              // rotates clockwise to identify the obstacles
  
  for (pos; pos >= 30; pos -= 5) {       

  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  if (duration!=0){
    distance = (duration / 2) * 0.0343;

    if (distance < 25.00){                           // Minimum reliable distance ~2cm
    mySerial.println("degrees " + String(pos) +"------distance " + String(distance));
    }
  }
  servo.write(pos);
  delay(100); // Adjust delay between readings as needed
  }
}


void servoReturn(void){                 // returns the servo in default position (92) and detaches it
  if(pos!=9){
    for (pos; pos <= 90; pos += 5) {
      servo.write(pos);
      delay(100);
    }
    servo.detach();
  }
}


/*bool IsNear(void){                      // defines if the Rover is near an Obstacle 
  int j = i;
  do{
    if( Me.x == (obstacle[j].x - 5) || Me.y == (obstacle[j].y - 5) ){
      mySerial.println("IS NEAR");
      RaiseInterrupt(1);
      return true;
    }
    else{
      return false;
    }
    j--;
  }while(j!=0);
}*/

void goForward(void){                   // move  forward(all motors rotate in forward direction)
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
  /*Me.x += 1*sin(angle);                 // updates the position of the Rover in the space
  Me.y += 1*cos(angle);*/
}
void goLeft(void){                  //turn left (right side motors rotate in forward direction, left  side motors rotate in reverse)
  digitalWrite(dir1PinL,HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
  /*if(angle != 360){                   // updates the rotation angle the rover is, for future implementeations
  angle += 5;
  } else{
    angle = 0;
  }*/
}
void goRight(void){                 //turn right (left side motors rotate in forward direction,  right side motors rotate in reverse)
  digitalWrite(dir1PinL,LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
  /*if(angle != 0){                 // updates the rotation angle the rover is
  angle -= 5;
  } else{
    angle = 360;
  }*/
}
void goBack(void){                      // move reverse (all  motors rotate in reverse direction)
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
  /*Me.x -= 1*sin(angle);               // updates the position of the Rover in the space to implement when sonar
  Me.y -= 1*cos(angle);*/
}
void Stop(void){                        // stops all motors
  digitalWrite(dir1PinL,LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}
void set_Motorspeed(int speed_L,int speed_R){     // sets the motor speed of the Motors
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void loop() {                                           // put your main code here, to run repeatedly:
  
  if (mySerial.available())
  {
    if(Travel && count == 10){// count indicates how
    mySerial.println("Scan Start");
    servoInit();
    servoFRotation();
    servoSRotation();
    servoReturn();
    Travel = false;
    mySerial.println("Scan end");
    }

    /*if(IsNear()){                   // sets Travel and Back to opposite valuse to stop the Rover to implement when sonar
    Travel = true;
    Back = false;
    }*/

    BluetoothData=mySerial.read();
    Serial.println(BluetoothData);

    switch (BluetoothData){
      case 'F':
        goForward();
        set_Motorspeed(speedMotor,speedMotor);
        Travel = true;
        count = 0;
        break;
      case 'B':
        goBack();
        set_Motorspeed(speedMotor,speedMotor);
        Travel = true;
        count = 0;
                              // the rover backed enough from the obstacle, the Ultrasonic sensor restarts, new series of obstacles, to implement when Sonar
        break;
      case 'L':
        goLeft();
        set_Motorspeed(speedMotor,speedMotor);
        Travel = true;
        count = 0;
        break;
      case 'R':
        goRight();
        set_Motorspeed(speedMotor,speedMotor);
        Travel = true;
        count = 0;
        break;
      case 'S':
        count ++;
        Stop();
        break;
      case 'P':
        digitalWrite(LED_PIN,HIGH);
        if(temp==0){
          mySerial.println("LED ON");
          temp=1;
        }
        break;
      case 'W':
        digitalWrite(LED_PIN,LOW);
        if(temp!=0){
          mySerial.println("LED OFF");
          temp=0;
        }
        break;
      default:
        Stop();
        break;
    } 
    //delay(20);                               // prepare for next data ...
  }
}
