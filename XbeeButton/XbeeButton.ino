
//#include <PWM.h>

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);



int led = 9;
int light = 13;
int pot = A0;


void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);  
}

void loop()
{
  while (XBee.available()) {    
    if (XBee.read() == 'a') {
      Serial.print("on");
      digitalWrite(light, HIGH);     
      delay(2000);      
    }
    
    else {
      Serial.print("off");
      digitalWrite(light, LOW);      
      delay(20);      
      }
    }    
}

