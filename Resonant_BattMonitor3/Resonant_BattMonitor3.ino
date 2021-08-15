#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219_C1(0x40);
Adafruit_INA219 ina219_C2(0x41);
Adafruit_INA219 ina219_C3(0x44);
Adafruit_INA219 ina219_C4(0x45);

typedef struct Cells {
  int cid;
  float busV;
  float shuntV;
  float loadV;
  float currentmA;
  float capacity = 0; //might not be necessary
  int health;
} Cell;

Cell c1; 
Cell c2; 
Cell c3; 
Cell c4; 

const int MOSPin_C1 = 3;  //pin for c1
const int MOSPin_C2 = 4;  //pin for c1
const int MOSPin_C3 = 5;  //pin for c1
const int MOSPin_C4 = 6;  //pin for c1

float T = 1.0;
float Sec2Hour = 3600.0;
float Bat_None = 0.2;
float Bat_High = 4.3;
float Bat_Low = 2.8;
float Vcc = 4.44; // Voltage of Arduino 5V pin ( Mesured by Multimeter )
unsigned long time;
int health = 0;

void setup() {
  
  c1.cid = 1; //TODO: not proud of hardcoding ids like this    
  c2.cid = 2;   
  c3.cid = 3;
  c4.cid = 4;
  
  pinMode(MOSPin_C1, OUTPUT);
  digitalWrite(MOSPin_C1, LOW);
  pinMode(MOSPin_C2, OUTPUT);
  digitalWrite(MOSPin_C2, LOW);  
  pinMode(MOSPin_C3, OUTPUT);
  digitalWrite(MOSPin_C3, LOW);  
  pinMode(MOSPin_C4, OUTPUT);
  digitalWrite(MOSPin_C4, LOW);  
  Serial.begin(115200);
  ina219_C1.begin();
  ina219_C2.begin();
  ina219_C3.begin();
  ina219_C4.begin();
}

void loop(void) { 

  time = millis();   
  
 c1.health = getHealth(&c1, ina219_C1);

 if (c1.health)
    dischargeCell(&c1, MOSPin_C1);

 c2.health = getHealth(&c2, ina219_C2); 

 if (c2.health)
    dischargeCell(&c2, MOSPin_C2); 

    c3.health = getHealth(&c3, ina219_C3); 

 if (c3.health)
    dischargeCell(&c3, MOSPin_C3); 

    c4.health = getHealth(&c4, ina219_C4); 

 if (c4.health)
    dischargeCell(&c4, MOSPin_C4); 

  delay(T*1000);  
}

int getHealth(Cell * cell, Adafruit_INA219 sensor ){

  cell->shuntV = sensor.getShuntVoltage_mV();
  cell->busV = sensor.getBusVoltage_V();
  cell->loadV = cell->busV + (cell->shuntV / 1000);

   if ( cell->loadV > Bat_High )
    {      
      Serial.print("\nHigh Battery!"); Serial.println(cell->cid);
      Serial.print(cell->cid);Serial.print("\t");
      Serial.print(cell->loadV);Serial.print("\t");
      Serial.print(cell->currentmA);Serial.print("\t");
      Serial.println(cell->capacity);  
      delay(T*1000);
      return 0;
    }

   else if (cell->loadV < Bat_Low && (cell->loadV > Bat_None))
    {
      Serial.print("\nLow Battery on Cell ");Serial.println(cell->cid);
      Serial.print(cell->cid);Serial.print("\t");
      Serial.print(cell->loadV);Serial.print("\t");
      Serial.print(cell->currentmA);Serial.print("\t");
      Serial.println(cell->capacity);  
      //Serial.println(cell->loadV);
      delay(T*1000);
      return 0;
    }

    else if ( cell->loadV <= Bat_None )
    {
      Serial.print("Cell: ");Serial.print(cell->cid); Serial.println(" not connected!");
      Serial.print(cell->cid);Serial.print("\t");
      Serial.print(cell->loadV);Serial.print("\t");
      Serial.print(cell->currentmA);Serial.print("\t");
      Serial.println(cell->capacity);  
      //Serial.println(cell->loadV);
      delay(T*1000);
      return 0;
    }
    
    else if ((cell->loadV > Bat_Low) && (cell->loadV < Bat_High))
    {        
      cell->currentmA = sensor.getCurrent_mA();
      cell->capacity = cell->capacity + cell->currentmA*(T/Sec2Hour);        
      Serial.print(cell->cid);Serial.print("\t");
      Serial.print(cell->loadV);Serial.print("\t");
      Serial.print(cell->currentmA);Serial.print("\t");
      Serial.println(cell->capacity);  
      return 1;       
    }  
}
int dischargeCell(Cell * cell, const int pin ){
   if (cell->health) {    
    //Serial.print("Discharging!");     
      digitalWrite(pin, HIGH);     
    }
    else {
      digitalWrite(pin, LOW);
      Serial.print("\nCell: ");Serial.print(cell->cid); Serial.println("done discharging!");
    }
    delay(T*1000);
  }



     
       
      

