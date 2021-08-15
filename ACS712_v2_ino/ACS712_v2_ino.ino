  int sum = 0;                    // sum of samples taken
  unsigned char sample_count = 0; // current sample number 
  const int numreadings = 10;

  const int Current = A3;
  int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
  int ACSoffset = 2500;
  double Volts = 0;
  double Amps = 0;
  
  int Raw = 0;

//  const int pin = 5;

  
  void setup(){
    Serial.begin(9600);
}
void loop(){


  while (sample_count < numreadings) {
      sum += analogRead(Current);
      sample_count++;
      delay(10);
  }  

// Raw = analogRead(Current);
  sum = sum/numreadings;
  Volts = (sum/ 1024.0) * 5000; // Get mV
  Amps = ((Volts - ACSoffset) / mVperAmp);
  

//  Serial.print("Raw Value = " ); // shows pre-scaled value 
//  Serial.print(Raw); 
  Serial.print("\t mV = "); // shows the voltage measured 
  Serial.print(Volts,3); // the '3' after voltage allows you to display 3 digits after decimal point
  Serial.print("\t Amps = "); // shows the voltage measured 
  Serial.println(Amps,4); // the '3' after voltage allows you to display 3 digits after decimal point
  delay(2500);

  sample_count = 0;
  sum = 0;
 
}
  

