#include <Servo.h>
 
Servo esc;
int throttlePin = A0;
int pot_angle = 3;
const int ledPin = 13;
//int throttle_limits[2] = {74, 114}; // CW/ CCW speed limits
                        //{green led flash, red led flash}
int throttle_limits[2] = {20, 179};


void setup()
{
  esc.attach(9);
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}
 
void loop()
{
  int throttle = analogRead(throttlePin);
  throttle = map(throttle, 0, 1023, throttle_limits[0], throttle_limits[1]);
  //int angle_shaft = analogRead(pot_angle);
  //angle_shaft = map(angle_shaft, 0, 1023, 0, 179);  
  Serial.println(throttle);
 // Serial.print("\t");
  //Serial.println(angle_shaft);
  esc.write(throttle);
}






