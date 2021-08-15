#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>

LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// read RPM and calculate average every ten readings.
const int numreadings = 10;
int readings[numreadings];
unsigned long average = 0;
int index = 0;
unsigned long total; 

volatile int rpmcount = 0;
unsigned long rpm = 0;
unsigned long lastmillis = 0;

// ACS72 Current Sensor Parameters
const int Current = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
int ACSoffset = 2500;
double Volts = 0;
double Amps = 0;
int Raw = 0;

void setup(){
 Serial.begin(9600); 
  attachInterrupt(0, rpm_fan, FALLING); 
  LCD.begin(20, 4);  // 16 lines by 2 rows
  LCD.clear();
  LCD.backlight(); 
}

void loop(){ 
  
 Raw = analogRead(Current);
 Volts = (Raw/ 1023.0) * 5000; // Get mV
 Amps = ((Volts - ACSoffset) / mVperAmp);
  
 if (millis() - lastmillis >= 1000){  /*Uptade every one second, this will be equal to reading frecuency (Hz).*/ 
     detachInterrupt(0);    //Disable interrupt when calculating
     total = 0;  
     readings[index] = rpmcount * 10;  /* Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.*/
     
     for (int x=0; x<=9; x++){
       total = total + readings[x];
     }
     
     average = total / numreadings;
     rpm = average;
     
     rpmcount = 0; // Restart the RPM counter
     index++;
     if(index >= numreadings){
      index=0; 
     }  
     
     if (millis() > 11000){  // wait for RPMs average to get stable
    
      Serial.print(" RPM = ");
      Serial.print(rpm/6);      
      LCD.setCursor(0,0);
      LCD.print("RPM = ");
      LCD.setCursor(6,0);
      LCD.print(rpm);
      Serial.print("\t Amps = " ); // shows pre-scaled value 
      Serial.println(Amps, 4); 
      LCD.setCursor(10,0);
      LCD.print("Amps = ");
      LCD.setCursor(16,0);
      LCD.print(Amps, 4);
      
//      delay(500);
     }
     
      lastmillis = millis(); // Uptade lasmillis
       attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
   }
 }

void rpm_fan(){ /* this code will be executed every time the interrupt 0 (pin2) gets low.*/
  rpmcount++;
}
