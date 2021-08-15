#include <SoftwareSerial.h>

SoftwareSerial XBee(2,3);


int sensorPin = 0; //analog pin 0

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
 //while(XBee.available()){
     
      //int val = analogRead(sensorPin);
     // String val = "129";
      XBee.write(129);
      delay(10);
      XBee.write(0x0A);
      //delay(10);
      Serial.write("129");
      Serial.println();
    //  

  //just to slow down the output - remove if trying to catch an object passing by
      delay(100);
   //}

}
