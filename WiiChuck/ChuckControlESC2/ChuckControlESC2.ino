  #include <math.h>
  #include <Servo.h>
  
  #include "Wire.h"
  #include <WiiChuck.h>
  
  
  WiiChuck chuck = WiiChuck();
  
  Servo esc;
  int bldcPin = 9;
  int throttleLimits[4] = {0, 85, 96, 179}; // CCW, Brake, CW speed limits
  
  int shaftPin = A1;
  int shaftLimits[2] = {0, 840}; // {MAX (standing), min (sitting)}
  int shaftAngles[2] = {0, 179};  // Calibrate values based on rotary 
                                 // encoder physical limits
                                 
  int slack = 10;
  int x, y = 0;
  int i, j = 0;
  
  
  void setup() {
  
    esc.attach(bldcPin);
    Serial.begin(115200);
    chuck.begin();
    chuck.update();
  
  }
  
  void loop() {
    delay(20);    
  
    x = shaft_status(i);             //Output
    y = chuck_status(j);             //Input
  
  if (y > throttleLimits[2])  {      //Go forward
  
     Serial.print("\t");
     Serial.print("\t");
     Serial.print("Forward");
     esc.write(y);
     
     while(x == shaftAngles[0])      //Brake at MAX ShaftLimit (0)
     {
       digitalWrite(bldcPin, LOW);
       Serial.print("Brake");
       
       arm_sequence();               //Arm Sequence Procedure
     }
    }
    
    else if (y < throttleLimits[1])  {      //Go Reverse
  
     Serial.print("\t");
     Serial.print("\t");
     Serial.print("Reverse");
     esc.write(y);
     
     while(x == shaftAngles[1])      //Brake at min ShaftLimit (179)
     {
       digitalWrite(bldcPin, LOW);
       Serial.print("Brake");
       
       arm_sequence();               //Arm Sequence Procedure
     }
    }
    
    else if (y >= throttleLimits[1] || y <= throttleLimits[2])
    {
      esc.write(y);
    }
    
//    else if (x >= shaftAngles[0])
//    {
//      digitalWrite(bldcPin, LOW);
//      Serial.print("aqui");
//    }
//    
//    else if (x <= shaftAngles[1])
//    {
//      digitalWrite(bldcPin, LOW);
//      Serial.print("hey dude");
//    }
    
  }
  
  int shaft_status(int shaft_position)
  {    
    int shaftValue = analogRead(shaftPin);
    shaftValue = map(shaftValue, shaftLimits[0], shaftLimits[1], shaftAngles[0], shaftAngles[1]);
  
    Serial.print(shaftValue);
    Serial.print("\t");     
    return shaftValue;
  
  }
  
  int chuck_status(int joystick_position)
  {
    chuck.update();
    int joy = (int)chuck.readJoyY();
    joy = map(joy, -90, 90, 75, 105);
    Serial.print(joy);
    Serial.println();
    return joy; 
  }
  
  void arm_sequence()
  {
    while (x == shaftAngles[1] || x == shaftAngles[0])
    {
      Serial.print("\t");
      Serial.print("\t"); 
      Serial.print("Waiting for throttle"); 
      digitalWrite(bldcPin, HIGH);
      esc.write(y);
      
    }
  }
  
  


