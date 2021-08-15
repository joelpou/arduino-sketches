// When Hall sensor detects LOW, MOSFET turns ON

const int MOSFET = 12;
const int SENSOR = 7;

bool hall = 0;

void setup(){
  pinMode(MOSFET, OUTPUT);
  pinMode(SENSOR, INPUT);
//  Serial.begin(9600);
}
void loop(){
  hall = digitalRead(SENSOR); 
  
  if (hall == LOW){
    delay(10);
    digitalWrite(MOSFET, HIGH);
  }
  else{
    digitalWrite(MOSFET, LOW);
  }
}



