  #include <math.h>
  #include <Servo.h>
  
  #include "Wire.h"
  
  #include <WiiChuck.h>  
  WiiChuck chuck = WiiChuck();
  
  #include <Adafruit_INA219.h>
  Adafruit_INA219 ina219;
  
  Servo esc;
  int bldcPin = 9;
  int speedLimits[4] = {0, 85, 96, 179}; // CCW, Brake, CW throttle limits
  
  int x, y = 0;
  int i, j = 0;
  
  int shaftPin = A0;
  int shaftLimits[2] = {0, 904};         // {MAX (standing), min (sitting)}
  const int upperstop = 7;               
  const int lowerstop = 170;
  const int brake = 89;
  
  int MEDspeed[2] = {75, 105};
  int LOWspeed[2] = {80, 98};
  
  void setup() {
    
    uint32_t currentFrequency;
  
    esc.attach(bldcPin);
    Serial.begin(115200);
    chuck.begin();
    chuck.update();
    
    ina219.begin();
  
  }
  
  void loop() {
    delay(20); 
    
    x = get_input(i);
    y = get_shaft(j);
    
    if (y <= upperstop && x <= speedLimits[2]){    //condition to stop shaft while standing
    esc.write(brake);
    //Serial.print("upper");
    }
    else if (y >= lowerstop && x >= speedLimits[1]){ //condition to stop shaft while sitting
    esc.write(brake);
    //Serial.print("lower");
    }
    else{    
    esc.write(x);
    //Serial.print("run");
    } 
    
    get_current();    
  }
  
  int get_input(int chuck_angle)
  {
    chuck.update();
    int joy = (int)chuck.readJoyY();
    joy = map(joy, -90, 90, LOWspeed[1], LOWspeed[0]);
    Serial.print("Input Joy:      "); Serial.print(joy);
    Serial.println("");
    return joy; 
  }
  
  int get_shaft(int pot_angle)
  {    
    int shaftValue = analogRead(shaftPin);
    shaftValue = map(shaftValue, shaftLimits[0], shaftLimits[1], speedLimits[0], speedLimits[3]);  
    Serial.print("Shaft Angle:    "); Serial.print(shaftValue);
    Serial.println("");
    Serial.println("");     
    return shaftValue;  
  }
  
  void get_current(){
     
    float shuntvoltage = 0;
    float busvoltage = 0;
    float current_mA = 0;
    float loadvoltage = 0;
  
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    loadvoltage = busvoltage + (shuntvoltage / 1000);
    
    Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
    Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
    Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
    Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    Serial.println("");
  
    delay(200); 
  }

