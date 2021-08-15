int STEP = 5;
int DIR = 6;

void setup() {
  // put your setup code here, to run once:
  
  pinMode (STEP, OUTPUT);
  pinMode (DIR, OUTPUT);
  
  digitalWrite(DIR, LOW);
  

}

void loop() {
  // put your main code here, to run repeatedly: 
  
  
  digitalWrite(STEP, HIGH);
  delay(20);
  
}
