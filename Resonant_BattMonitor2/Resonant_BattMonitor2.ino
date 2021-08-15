#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219(0x40);

#define MOSFET_Pin 3
#define Bat_Pin A0



float T = 1.0;
float Capacity = 0;
float Sec2Hour = 3600.0;
float Bat_High = 4.3;
float Bat_Low = 2.8;
//float sample1 =0;
float Vcc = 4.44; // Voltage of Arduino 5V pin ( Mesured by Multimeter )
//float busV = 0;
unsigned long time;



void setup() {
  // put your setup code here, to run once:
  pinMode(MOSFET_Pin, OUTPUT);
  digitalWrite(MOSFET_Pin, LOW);  
  Serial.begin(115200);
  ina219.begin();
  //Serial.println("Battery Tester Start:");

}

void loop(void) { 

  time = millis();
  float busV = 0;
  float shuntV = 0;
  float loadV = 0;
  float currentmA = 0;

 /*
  for(int i=0;i< 100;i++)
  {
  
   sample1=sample1+analogRead(Bat_Pin); //read the voltage from the divider circuit
   delay (2);
  }
  sample1=sample1/100; 
  busV = (2*sample1*Vcc)/1024.0; 
  */
  shuntV = ina219.getShuntVoltage_mV();
  busV = ina219.getBusVoltage_V();
  loadV = busV + (shuntV / 1000);


  //Serial.print("Bus Voltage:   "); Serial.print(busV); Serial.println(" V");

  //**************************************************Checking Battery Condition***************************************************************
  
  if ( loadV > Bat_High )
    {
      digitalWrite(MOSFET_Pin, LOW);
      Serial.println("\nHigh Battery!\n");
      delay(T*1000);
    }

   else if ( loadV < Bat_Low )
    {
      digitalWrite(MOSFET_Pin, LOW);
      Serial.println("\nLow Battery!\n");
      Serial.print(loadV);Serial.print("\t");
      Serial.print(currentmA);Serial.print("\t");
      Serial.print(Capacity);Serial.print("\t");
      Serial.print(time/1000);Serial.print("\n");
      delay(T*1000);
    }
    
   else if ( (loadV > Bat_Low) && (loadV < Bat_High) )
    {
      digitalWrite(MOSFET_Pin, HIGH); 
      currentmA = ina219.getCurrent_mA();
      Capacity = Capacity + currentmA*(T/Sec2Hour);
      Serial.print(loadV);Serial.print("\t");
      Serial.print(currentmA);Serial.print("\t");
      Serial.print(Capacity);Serial.print("\t");
      Serial.print(time/1000);Serial.print("\n");
      /*
      Serial.print("Voltage:  "); Serial.print(loadV); Serial.println(" V");
      Serial.print("Current:       "); Serial.print(currentmA); Serial.println(" mA");
      Serial.print("Capacity:      "); Serial.print(Capacity); Serial.println(" mAh");
      Serial.print("Time:          "); Serial.print(time/1000); Serial.println(" s");
      Serial.println("\n");
      */
      delay(T*1000);
    } 
}
