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
                                 
  //int slack = 10;
  int x, y = 0;
  int i, j = 0;
  
  
  void setup() {
  
    esc.attach(bldcPin);
    Serial.begin(115200);
    chuck.begin();
    chuck.update();
  
  }
  
  void loop() 
	{
		delay(20);    
	  
		x = shaft_status(i);             //Output
		y = chuck_status(j);             //Input

		if ((y >= throttleLimits[0] && y <= throttleLimits[1]) || (y >= throttleLimits[0] && y <= throttleLimits[1]))		//
		{
			switch (x)
			{		
			case shaftAngles[0]:		//user standing, (shaft reads 0)
				while(y < throttleLimits[3] && y > throttleLimits[2] )
				{
					esc.write(y);
				}			
				break;
			case shaftAngles[1]:
				while(y < throttleLimits[1] && y > throttleLimits[0] )
				{
					esc.write(y);
				}			
				break;		
			}
				
		}
		
		while(y >= throttleLimits[1] && y <= throttleLimits[2])
		{
			digitalWrite(bldcPin, LOW);
		}
	}
  
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
    joy = map(joy, 90, -90, 105, 755);    //Adjust last two arguments to control speed
    Serial.print(joy);
    Serial.println();
    return joy; 
  }