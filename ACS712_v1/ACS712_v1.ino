/*Calibration: 
Analog read produces a value of 0-1023, equating to 0v to 5v
So Analog read 1 = (5/1024) V =4.89mv
Value = (4.89*Analog Read value)/1000 V
But as per data sheets offset is 2.5V (When current zero you will get 2.5V from the sensor's output)
Actual value = (value-2.5) V
Current in amp =actual value*10

ARDUINO CODE: 

// taking 150 samples from sensors with a interval of 2sec and then average the samples data collected
for(int i=0;i<150;i++)
{
sample2+=analogRead(A3); //read the current from sensor
delay(2);
},ml,
sample2=sample2/150;
val =(5.0*sample2)/1024.0;
actualval =val-2.5; // offset voltage is 2.5v
amps =actualval*10;

///////////////////////

SIMPLER APPROACH:

 sensorValue = analogRead(A0);      
  Serial.println(sensorValue);
  //Serial.println((517 - sensorValue) * 75.75 / 1023, 4);  
  delay(1000);                        
*/

double sample2 = 0;
double val = 0;
double actualval = 0;
double amps = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // taking 150 samples from sensors with a interval of 2sec and then average the samples data collected
  for(int i=0;i<150;i++)
  {
  sample2+=analogRead(A0); //read the current from sensor
  delay(20);
  }
  sample2=sample2/150;
  val =(5.0*sample2)/1024;
  actualval = val-2.5; // offset voltage is 2.5v
  amps =actualval*10;
  Serial.println(amps, 4);
}
