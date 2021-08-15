#define MOSFET_Pin 3
#define Bat_Pin A0
#define Res_Pin A1

 
float Capacity = 0.0; // Capacity in mAh
float Res_Value = 10.0;  // Resistor Value in Ohm
float Vcc = 4.85; // Voltage of Arduino 5V pin ( Mesured by Multimeter )
float Current = 0.0; // Current in Amp
float mA=0;         // Current in mA
float Bat_Volt = 0.0;  // Battery Voltage 
float Res_Volt = 0.0;  // Voltage at lower end of the Resistor 
float Bat_High = 4.3; // Battery High Voltage
float Bat_Low = 2.9; // Discharge Cut Off Voltage
unsigned long previousMillis = 0; // Previous time in ms
unsigned long millisPassed = 0;  // Current time in ms
float sample1 =0;
float sample2= 0;



//*******************************Setup Function ***************************************************************
  
  void setup() {
   Serial.begin(9600);
   pinMode(MOSFET_Pin, OUTPUT);
   digitalWrite(MOSFET_Pin, LOW);  // MOSFET is off during the start
   Serial.println("CLEARDATA");
   Serial.println("LABEL,Time,Bat_Volt,capacity");
   
   //Serial.println("Arduino Battery Capacity Tester v1.0");
   //Serial.println("BattVolt Current mAh");
  }
  //********************************Main Loop Function***********************************************************
  void loop() {
 // Vcc = readVcc()/1000.0; // Conevrrt mV to Volt

  
  // Voltage devider Out = Bat_Volt * R2/(R1+R2 ) // R1 =10K and R2 =10K 
  
  //************ Measuring Battery Voltage ***********
  
  for(int i=0;i< 100;i++)
  {
  
   sample1=sample1+analogRead(Bat_Pin); //read the voltage from the divider circuit
   sample2=sample2+analogRead(Res_Pin); //read the voltage from the divider circuit
   delay (2);
  }
  sample1=sample1/100; 
  Bat_Volt = (2*sample1*Vcc)/1024.0; 
  sample2=sample2/100;
  Res_Volt = (2*sample2*Vcc)/1024.0;
  Serial.print("Vbatt = "); Serial.println(Bat_Volt);
  Serial.print("Vres = "); Serial.println(Res_Volt);
    sample1 = 0;
      sample2 = 0;


  if ( Bat_Volt > Bat_High){
    digitalWrite(MOSFET_Pin, LOW); // Turned Off the MOSFET // No discharge 
    Serial.println( "Warning High-V! ");
    delay(1000);
    }
   
  else if(Bat_Volt < Bat_Low){
    digitalWrite(MOSFET_Pin, LOW);
    Serial.println( "Warning Low-V! ");
    delay(1000);
    }
      
  else if(Bat_Volt > Bat_Low && Bat_Volt < Bat_High  ) { // Check if the battery voltage is within the safe limit
      digitalWrite(MOSFET_Pin, HIGH);
      millisPassed = millis() - previousMillis;
      Current = (Bat_Volt - Res_Volt) / Res_Value;
      mA = Current * 1000.0 ;
      Capacity = Capacity + mA * (millisPassed / 3600000.0); // 1 Hour = 3600000ms
      previousMillis = millis();
      Serial.print("DATA,TIME,"); Serial.print(Bat_Volt); Serial.print(","); Serial.println(Capacity);
      
      delay(4000); 
     }
  
 }    

