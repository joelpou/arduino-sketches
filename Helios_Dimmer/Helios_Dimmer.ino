
#include <PWM.h>
int32_t frequency = 1000;

int led = 9;
int pot = A0;

void setup()
{
  Serial.begin(9600);
  InitTimersSafe();
  bool success = SetPinFrequencySafe(led, frequency);
  if(success) {
    pinMode(led, OUTPUT);
    digitalWrite(13, HIGH);  
  }  
}

void loop()
{
  int dim = analogRead(pot);
  Serial.println(dim);
//  dim = map(dim, 0, 1023, 0, 255);
  analogWrite(9, dim / 4);                    
}

