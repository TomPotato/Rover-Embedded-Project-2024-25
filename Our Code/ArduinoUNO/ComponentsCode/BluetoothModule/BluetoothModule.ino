#include "SoftwareSerial.h"// import the serial library
 
SoftwareSerial mySerial(10, 11); // RX, TX
int BluetoothData; // the data given from Computer
 
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}
 
void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.println(mySerial.available());
  if (mySerial.available())
  {
    Serial.println("Pronto");
    BluetoothData=mySerial.read();
    Serial.println(BluetoothData);
    if(BluetoothData=='1')
    {   
      // if letter 1 is sent from APP   ....
      digitalWrite(LED_BUILTIN,HIGH);
      Serial.println("LED  On D13 ON ! ");
    }
    if (BluetoothData=='0')
    {
      // if Letter 0 is sent from APP ....
      digitalWrite(LED_BUILTIN,LOW);
      Serial.println("LED  On D13 Off ! ");
    }
  }
delay(500);// prepare for next data ...
}