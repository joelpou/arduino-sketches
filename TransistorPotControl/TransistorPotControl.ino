const int transistorPin = 9;    // connected to the base of the transistor
 
 void setup() {
   // set  the transistor pin as output:
   pinMode(transistorPin, OUTPUT);
   Serial.begin(9600);

 }
 
 void loop() {  
   // read the potentiometer:
   int sensorValue = analogRead(A0);
   // map the sensor value to a range from 0 - 255:
   int outputValue = map(sensorValue, 0, 1023, 255, 0); 
   // use that to control the transistor:
   Serial.println(sensorValue);
   analogWrite(transistorPin, outputValue);
 }
