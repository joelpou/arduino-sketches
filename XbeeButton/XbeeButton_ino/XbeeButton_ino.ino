
//#include <PWM.h>

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);

//int32_t frequency = 1000;

int led = 9;
int light = 13;
int pot = A0;

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
  analogWrite(9, 0);
  pinMode(light, OUTPUT);
//  InitTimersSafe();
//  bool success = SetPinFrequencySafe(led, frequency);
//  if(success) {
//    pinMode(led, OUTPUT);
//    digitalWrite(13, HIGH);  
//  }  
}

void loop()
{
  while (XBee.available()) {
    Serial.write(XBee.read());
    if (XBee.read() == 1) {
      digitalWrite(light, HIGH);      
      //analogWrite(9, 1023); 
      delay(20);      
    }
    
    else {
      digitalWrite(light, LOW);
      //analogWrite(9, 0);
      delay(20);      
      }
    }    
}

