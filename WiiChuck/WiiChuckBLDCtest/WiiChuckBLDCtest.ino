 #include <math.h>
  #include <Servo.h>
  
  #include "Wire.h"
  #include <WiiChuck.h>
  
  
  WiiChuck chuck = WiiChuck();
  
  Servo esc;
  int bldcPin = 9;
  int speedLimits[4] = {0, 85, 96, 179}; // CCW, Brake, CW speed limits
  int x, y = 0;
  int i, j = 0;
  
  int MEDspeed[2] = {75, 105};
  int LOWspeed[2] = {80, 98};
  
  void setup() {
  
    esc.attach(bldcPin);
    Serial.begin(115200);
    chuck.begin();
    chuck.update();
  
  }
  
  void loop() {
    delay(20); 
 
    y = chuck_status(j);
    
    esc.write(y);   
    
  }
  
  int chuck_status(int joystick_position)
  {
    chuck.update();
    int joy = (int)chuck.readJoyY();
    joy = map(joy, -90, 90, LOWspeed[1], LOWspeed[0]);
    Serial.print(joy);
    Serial.println();
    return joy; 
  }
