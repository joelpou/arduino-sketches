// read RPM and calculate average every ten readings.
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
 attachInterrupt(0, rpm_fan, FALLING);  //First parameter: digitalPinToInterrupt(2)  = 0; where 0 is 
 pinMode(led, OUTPUT);
}

void loop(){   
  
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
    
      Serial.print(" RPM = ");
      Serial.println(rpm/6);  //ecoblades rotor has 6 magnets attached, hence division by 6
     }
     
      lastmillis = millis(); // Uptade lasmillis
       attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
   }
 }

void rpm_fan(){ /* this code will be executed every time the interrupt 0 (pin2) gets low.*/
  rpmcount++;
  if (rpmcount % 6 == 0){     //modulo operator: remainder = dividend & divisor -->> Ex. x = 7 % 5; x now contains 2
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
  }
}
