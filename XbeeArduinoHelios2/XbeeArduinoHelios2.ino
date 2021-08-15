/*****************************************************************
Helios - SONAR - LDR
*****************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial XBee(2,3);  // RX, TX


int sonar = 0; //ultrasonic proximity sensor pin
int ldr = 2;   //light dependent resistor pint


void setup() {
  
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() { 
     
      int car = analogRead(sonar);
      int sun = analogRead(ldr);
      
      if(sun < 800){
        XBee.write(1);
        delay(1000);
        Serial.print(sun);
        Serial.println();
      }
     
      else {
     
      XBee.write(car);
      delay(1000);
    
      Serial.print(car);
      Serial.println();
      }   
      
}
