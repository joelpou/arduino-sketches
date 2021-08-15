 // read RPM
 int half_revolutions = 0;
 int rpm = 0;
 unsigned long lastmillis = 0;
  const int pin = 13;

 void setup(){
 Serial.begin(9600); 
 attachInterrupt(0, rpm_fan, FALLING);
 pinMode(pin, OUTPUT);
 }
 void loop(){ 
 if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
    detachInterrupt(0);//Disable interrupt when calculating
    rpm = half_revolutions * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
    Serial.print("RPM =\t"); //print the word "RPM" and tab.
    Serial.print(rpm/6); // print the rpm value.
    Serial.print("\t Hz=\t"); //print the word "Hz".
    Serial.println(half_revolutions); //print revolutions per second or Hz. And print new line or enter.
    half_revolutions = 0; // Restart the RPM counter
    lastmillis = millis(); // Uptade lasmillis
    attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
  }
 }
 // this code will be executed every time the interrupt 0 (pin2) gets low.
 void rpm_fan(){
  half_revolutions++;
   if (half_revolutions % 6 == 0){     //modulo operator: remainder = dividend & divisor -->> Ex. x = 7 % 5; x now contains 2
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
  }
 }
