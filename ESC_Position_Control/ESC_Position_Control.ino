#include <Servo.h>
 
Servo esc;
int bldcPin =9;
int pot_angle = A0;
const int shaft_limits[2] = {35, 177};        //Shaft min and max angle

int throttlePin = A2;                       //Input potentiometer
int throttle_limits[4] = {0, 85, 96, 179}; // CCW, Brake, CW speed limits
const int numReadings = 10;
int throttle_readings[numReadings];      // the readings from the analog input
int index = 0;                          // the index of the current reading
int total = 0;                         // the running total
int throttle_average = 0;             // the average
int x, y;
int i, j = 0;

//const int buttonPin = 2;        // the number of the pushbutton pin
//const int ledPin =  13;

void setup()
{  
  esc.attach(bldcPin);
  //pinMode(ledPin, OUTPUT); 
  // pinMode(buttonPin, INPUT);
  Serial.begin(9600); 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    throttle_readings[thisReading] = 0;
}
 
void loop()
{            
      x = check_throttle(i);  //read input potentiometer
      y = check_shaft(j);     //read shaft potentiometer  
     
      Serial.print("\t");
      Serial.print(esc.attached());         
      
      if(x >= throttle_limits[0] && x < throttle_limits[1])
      {
        Serial.print("\t");
        Serial.println("SIT"); //BLDC moving CW for standing position
        if (y <= shaft_limits[0] && esc.attached() == 1)
        {
         esc.detach();
         i = 0;
         while(check_throttle(i) != throttle_limits[1])
         {
         Serial.print("\t"); 
         Serial.print(esc.attached());
         Serial.print("\t");
         Serial.println("SITTING, NEED TO ARM");                  
         }
         esc.attach(bldcPin);
        }
      }
      else if(x > throttle_limits[2] && x <= throttle_limits[3])
      {
        Serial.print("\t");
        Serial.println("STAND"); //BLDC moving CCW for sitting position 
        if (y >= shaft_limits[1] && esc.attached() == 1)
        {
         esc.detach();
         j = 0;
         while(check_throttle(j) != throttle_limits[2])
         {
         Serial.print("\t");
         Serial.print(esc.attached());
         Serial.print("\t");
         Serial.println("STANDING, NEED TO ARM");                  
         }
         esc.attach(bldcPin);
        }
      }
      else
      {
        Serial.print("\t");
        Serial.println("STOP"); //motor stops
      }
   }

int check_throttle(int throttle_position)
{    
     // subtract the last reading: 
    total = total - throttle_readings[index];     
     // read from the sensor:
    throttle_readings[index] = analogRead(throttlePin);    
    throttle_readings[index] = map(throttle_readings[index], 0, 1023, throttle_limits[0], throttle_limits[3]);
     // add the reading to the total:
    total= total + throttle_readings[index]; 
     // advance to the next position in the array:  
    index = index + 1;   
     // if we're at the end of the array...
    if (index >= numReadings)              
     // ...wrap around to the beginning: 
    index = 0;          
     //calculate the average of throttle readings
    throttle_average = total/ numReadings; 
    Serial.print(throttle_average);    
    esc.write(throttle_average);
    delay(50);  
    return throttle_average;
}

int check_shaft(int shaft_position)
{
    int angle_shaft = analogRead(pot_angle);
    angle_shaft = map(angle_shaft, 0, 1023, 0, 179);
    Serial.print("\t");
    Serial.print(angle_shaft);
    return angle_shaft;
}


