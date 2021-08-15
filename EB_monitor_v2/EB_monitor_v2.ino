#include <Wire.h>

//Setup Display

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 13 - Serial clock out (SCLK)
// pin 11 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 4, 3);

//Voltage Parameters

int in_sum = 0;                    // sum of input voltage samples taken
int out_sum = 0;                   // sum of output voltage samples taken
unsigned char sample_count = 0;    // current sample number
const int InputVoltagePin = A3;
const int OutputVoltagePin = A4;
float VoltageSource = 0.0;         // calculated input voltage
float VoltageLoad = 0.0;           // calculated output voltage


//Current Parameters
const int InputCurrentPin = A1;
const int OutputCurrentPin = A2;
int mVperAmp = 185;       // use 100 for 20A Module and 66 for 30A Module
int ACSoffset = 2500;
double in_Volts = 0;
double in_Amps = 0;
double out_Volts = 0;
double out_Amps = 0;
//int Raw = 0;

//Speed Parameters 
const int numreadings = 10;
int readings[numreadings];
unsigned long average = 0;
int index = 0;
unsigned long total; 

volatile int rpmcount = 0;
unsigned long rpm = 0;
unsigned long lastmillis = 0;
const int led = 13;

void setup(){
  
  
  Serial.begin(9600); 
  display.begin();  
  display.setContrast(60);
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer  
  attachInterrupt(0, rpm_fan, FALLING);   
  pinMode(led, OUTPUT);
}

void loop(){

  while (sample_count < numreadings) {
      in_sum += analogRead(InputVoltagePin);
      out_sum += analogRead(OutputVoltagePin);
      sample_count++;
      delay(10);
  }
  
  VoltageSource = ((float)in_sum / (float)numreadings * 4.79) / 1024.0;
  VoltageLoad = ((float)out_sum / (float)numreadings * 4.79) / 1024.0;
  sample_count = 0;
  in_sum = 0;
  out_sum = 0;

  while (sample_count < numreadings) {
      in_sum += analogRead(InputCurrentPin);
      out_sum += analogRead(OutputCurrentPin);
      sample_count++;
      delay(10);
  }  

 in_sum = in_sum/numreadings;
 in_Volts = (in_sum/ 1023.0) * 5000; // Get mV
 in_Amps = ((in_Volts - ACSoffset) / mVperAmp);

 if(in_Amps < 0){
   in_Amps = 0;
 }

 out_sum = out_sum/numreadings;
 out_Volts = (out_sum/ 1023.0) * 5000; // Get mV
 out_Amps = ((out_Volts - ACSoffset) / mVperAmp);

 if(out_Amps < 0){
   out_Amps = 0;
 } 
 
 sample_count = 0;
 in_sum = 0;
 out_sum = 0;
  
 if (millis() - lastmillis >= 1000){  /*Uptade every one second, this will be equal to reading frecuency (Hz).*/ 
     detachInterrupt(0);    //Disable interrupt when calculating
     total = 0;  
     readings[index] = rpmcount * 60;  /* Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.*/
     
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
    
      Serial.print("Speed: "); Serial.print(rpm/6); Serial.println(" RPM");
//      Serial.print("Vin: " ); Serial.print(VoltageSource * 11.132 + 0.5, 2); Serial.println(" V");
//      Serial.print("Iin: " ); Serial.print(in_Amps,2); Serial.println(" A");
//      Serial.print("Pin: " ); Serial.print(in_Amps*(VoltageSource * 11.132 + 0.5)); Serial.println(" W");
//      Serial.print("Vout: " ); Serial.print(VoltageLoad * 11.132 + 0.5, 2); Serial.println(" V");
//      Serial.print("Iout: " ); Serial.print(out_Amps,2); Serial.println(" A");
//      Serial.print("Pout: " ); Serial.print(out_Amps*(VoltageLoad * 11.132 + 0.5)); Serial.println(" W");
      Serial.println(" ");

      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0,0);
      display.print("Speed: "); display.println(rpm/6); 
      display.print("Pin: "); display.println(in_Amps*(VoltageSource * 11.132 + 0.5)); 
      display.print("Pout: "); display.println(out_Amps*(VoltageLoad * 11.132 + 0.5));
//      display.print("Efficiency: "); display.println(out_Amps,3); 
      display.clearDisplay();   // clears the screen and buffer
      display.display();
//      delay(2000); 
     }
     
      lastmillis = millis(); // Uptade lasmillis
       attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
   }
   
//       delay(4000);
 }

void rpm_fan(){ /* this code will be executed every time the interrupt 0 (pin2) gets low.*/
  rpmcount++;
  if (rpmcount % 6 == 0){     //modulo operator: remainder = dividend & divisor -->> Ex. x = 7 % 5; x now contains 2
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
  }
}
