//Relay Parameters
#define RELAY_OFF 1
#define RELAY_ON 0

#define Relay_1  3      
#define Relay_2  4 

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
const int OutputCurrentPin = A7;
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

//Led Parameters

#define LED_ON 255
#define LED_OFF 0

int state = 0;
const int led = 9;
const int indicator = 13;
   

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  attachInterrupt(0, rpm_fan, FALLING);   
  pinMode(led, OUTPUT);
  pinMode(Relay_1, OUTPUT);  
  pinMode(Relay_2, OUTPUT); 
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  analogWrite(led, LED_OFF);
}

void loop() {

  state = Serial.read();
 
  switch (state) {
    case '0':    
      Serial.println("ZERO");
      digitalWrite(Relay_1, RELAY_OFF);
      digitalWrite(Relay_2, RELAY_OFF);
      state = Serial.read();
      if (state != '0'){
        break;
      }
    case '1':   
      Serial.println("ONE");
      digitalWrite(Relay_1, RELAY_ON);
      digitalWrite(Relay_2, RELAY_ON);
      state = Serial.read();
      if (state != '1'){
        break;
      }
    case '2':    
      Serial.println("LED OFF");
      analogWrite(led, LED_OFF);
      state = Serial.read();
      if (state != '2'){
        break;
      }
    case '3':    
      Serial.println("LED ON");
      analogWrite(led, LED_ON);
      state = Serial.read();
      if (state != '3'){
        break;
      }
    delay(1);        // delay in between reads for stability
  }

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

// if(in_Amps < 0){
//   in_Amps = 0;
// }

 out_sum = out_sum/numreadings;
 out_Volts = (out_sum/ 1023.0) * 5000; // Get mV
 out_Amps = ((out_Volts - ACSoffset) / mVperAmp);

// if(out_Amps < 0){
//   out_Amps = 0;
// } 
// 
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
      Serial.print("Vin: " ); Serial.print(VoltageSource * 11.132 + 0.5, 2); Serial.println(" V");
      Serial.print("Iin: " ); Serial.print(in_Amps,2); Serial.println(" A");
      Serial.print("Pin: " ); Serial.print(in_Amps*(VoltageSource * 11.132 + 0.5)); Serial.println(" W");
      Serial.print("Vout: " ); Serial.print(VoltageLoad * 11.132 + 0.5, 2); Serial.println(" V");
      Serial.print("Iout: " ); Serial.print(out_Amps,2); Serial.println(" A");
      Serial.print("Pout: " ); Serial.print(out_Amps*(VoltageLoad * 11.132 + 0.5)); Serial.println(" W");
      Serial.println(" ");    
     }
     
      lastmillis = millis(); // Uptade lasmillis
       attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
   }  
}

void rpm_fan(){ /* this code will be executed every time the interrupt 0 (pin2) gets low.*/
  rpmcount++;
  if (rpmcount % 6 == 0){     //modulo operator: remainder = dividend & divisor -->> Ex. x = 7 % 5; x now contains 2
    digitalWrite(indicator, HIGH);
    delay(50);
    digitalWrite(indicator, LOW);
  }
}





