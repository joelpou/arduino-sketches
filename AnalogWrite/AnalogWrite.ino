int pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
}
                                                                             
void loop() {
  // put your main code here, to run repeatedly: 
  analogWrite(pin, 100);
}
