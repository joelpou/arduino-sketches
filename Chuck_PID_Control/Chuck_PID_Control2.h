//PID Info: 
//	http://playground.arduino.cc/Code/PIDLibrary
// 	http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/
//
//Review:
//Output = Kp*e(t)+Ki*INT[e(t)*dt)]+Kd*DER[e(t)]
//e(t) = Setpoint - Input

//Servo Info:
//

//WiiChuck Info:
//

#include <math.h>
#include <Servo.h>
#include "Wire.h"
#include <WiiChuck.h>
#include <PID_v1.h>

//Define Variables 
double Input;			//What to measure (ex. speed)
double Output;			//Where you want that measurement to be (ex. desired speed)
double Setpoint;		//Variable to adjust that can make it happend (ex. gas pedal angle)
int Direction;
int Kp = 5; 
int Ki = 2; 
int Kd = 1;
int i, o = 0;
//Default SampleTime = 100; 


//Specify the links and initial tuning parameters
PID chuckPID(&Input, &Output, &Setpoint, Kp, Ki,Kd, Direction);

WiiChuck chuck = WiiChuck();

Servo esc;

int bldcPin = 9;
int shaftPin = A1;
int throttleLimits[4] = {0, 85, 96, 179}; 	// CCW, Brake, CW speed limits
int shaftLimits[2] = {0, 840}; 				// {MAX (standing), min (sitting)}

//speed limits:
int MEDspeed[2] = {75, 105};
int LOWspeed[2] = {80, 100};
			// {MAX (standing), min (sitting)}
//int shaftAngles[2] = {0, 179};  			// Calibrate values based on rotary 
											// shaft pot physical limits
											
int shaftPosition;
								 
void setup(){
	
	esc.attach(bldcPin);
	Serial.begin(115200);
	chuck.begin();
	chuck.update();
	
	Input = (int)chuck.readJoyY();
	//Setpoint =	throttle		//throttleLimits?
	
	//turn the PID on
	chuckPID.SetOutputLimits(throttleLimits[0], throttleLimits[3]);  //Motor shaft limits
	chuckPID.SetMode(AUTOMATIC);	//
	
	//SetSampleTime(SampleTime)
	
}

void loop(){        
  
        shaftPosition = shaft_status(o);
        Input = chuck_status(i);		//read gearbox shaft pot
        //int myInput = Input;
        get_functions();
        chuckPID.Compute();
        
        
	
	//while(Input < throttleLimits[1] && Input > throttleLimits[2]){
		if(Input > throttleLimits[2]){
			Serial.print("FORWARD");
                        Serial.print("\t");
                        Serial.print("\t");
			chuckPID.SetControllerDirection(DIRECT);
			Setpoint = throttleLimits[0];			
			esc.write(Output);
                        Serial.print(Output);
		}
        else if(Input < throttleLimits[1]){
			Serial.print("REVERSE");
                        Serial.print("\t");
                        Serial.print("\t");
			chuckPID.SetControllerDirection(REVERSE);
			Setpoint = throttleLimits[3];
                        esc.write(Output);
                        Serial.print(Output);
		}
		else
		{
		  esc.write(89);		//Brake
		}
//	chuckPID.Compute();
//	esc.write(Input);	
	//}
}


int chuck_status(int joystick_position)
  {
    chuck.update();
    int joy = (int)chuck.readJoyY();
    joy = map(joy, -90, 90, LOWspeed[0], LOWspeed[1]);    //Adjust last two arguments to control speed
    Serial.print(joy);
    Serial.println();
    return joy; 
  }
  
  int shaft_status(int shaft_position)
  {    
    int shaftValue = analogRead(shaftPin);
    shaftValue = map(shaftValue, shaftLimits[0], shaftLimits[1], throttleLimits[0], throttleLimits[3]);
  
    Serial.print(shaftValue);
    Serial.print("\t");     
    return shaftValue;  
  }
  
  void get_functions(){    
    Serial.print(chuckPID.GetMode());
    Serial.print("\t");
    Serial.print(chuckPID.GetDirection());
    Serial.print("\t");
//    Serial.print(chuckPID.GetKp());
//    Serial.print("\t");
//    Serial.print(chuckPID.GetKi());
//    Serial.print("\t");
//    Serial.print(chuckPID.GetKd());
//    Serial.print("\t");
  }

