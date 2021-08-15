  #include <math.h>
  #include <Servo.h>
  
  #include "Wire.h"
  #include <WiiChuck.h>
  
  
  WiiChuck chuck = WiiChuck();
  
  Servo esc;
  int bldcPin = 9;
  int speedLimits[4] = {0, 85, 96, 179}; // CCW, Brake, CW speed limits
  
  int shaftPin = A1;
  int shaftLimits[2] = {0, 805}; // {MAX (standing), min (sitting)}
  int shaftAngles[2] = {0, 179};  // Calibrate values based on rotary 
                                 // encoder physical limits
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
  
    x = shaft_status(i); 
    y = chuck_status(j);    
  
  if (x > shaftAngles[0] || x < shaftAngles[1]) {      //OR o AND????
  
     esc.write(y);
     
     while(x == shaftAngles[0] || x == shaftAngles[1])
     {
       digitalWrite(bldcPin, LOW);
       Serial.print("I'm here");
       
       int z, k, i, j = 0;
         z = shaft_status(i); 
         k = chuck_status(j);
       
       //if (z == x 
     }
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
    joy = map(joy, -90, 90, 0, 179);
    Serial.print(joy);
    Serial.println();
    return joy; 
  }
  
  

