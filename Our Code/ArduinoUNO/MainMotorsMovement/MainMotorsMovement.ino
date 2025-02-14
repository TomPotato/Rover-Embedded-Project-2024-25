char t;
 
void setup() {
pinMode(7,OUTPUT);   //left motors  forward
pinMode(8,OUTPUT);   //left motors reverse
pinMode(2,OUTPUT);   //right  motors forward
pinMode(4,OUTPUT);   //right motors reverse
pinMode(LED_BUILTIN,OUTPUT);   //Led
Serial.begin(9600);
}
 
void goForward(void){               //move  forward(all motors rotate in forward direction)
  digitalWrite(7,HIGH);
  digitalWrite(2,HIGH);
}
void goLeft(void){                  //turn left (right side motors rotate in forward direction, left  side motors rotate in reverse)
  digitalWrite(2,HIGH);
  digitalWrite(8,HIGH);
}
void goRight(void){                 //turn right (left side motors rotate in forward direction,  right side motors rotate in reverse)
  digitalWrite(7,HIGH);
  digitalWrite(4,HIGH);
}
void goBack(void){                  //move reverse (all  motors rotate in reverse direction)
  digitalWrite(8,HIGH);
  digitalWrite(4,HIGH);
}
void Stop(void){
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
}

void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            
  goForward();
}
 
else if(t == 'B'){
  goBack();
}
  
else if(t == 'L'){
  goLeft();
}
 
else  if(t == 'R'){
  goRight();
}

else if(t ==  'W'){    //turn led on or off
  digitalWrite(LED_BUILTIN,HIGH);
  }
else if(t == 'w'){
  digitalWrite(LED_BUILTIN,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  Stop();
}
delay(40);
}