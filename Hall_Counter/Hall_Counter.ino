// When Hall sensor detects LOW, MOSFET turns ON

;
const int SENSOR = 7;
const int LED = 13;
int counter = 0;
bool hall = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
}
void loop(){
  hall = digitalRead(SENSOR); 
  
  if (hall == LOW){
    delay(10);
    digitalWrite(LED, HIGH);
    counter += 1;
    Serial.println(counter);
    delay(100);
  }
  else{
    digitalWrite(LED, LOW);
  }
}



