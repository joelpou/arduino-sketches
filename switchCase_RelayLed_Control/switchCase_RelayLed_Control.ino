#define RELAY_OFF 1
#define RELAY_ON 0

#define Relay_1  3      
#define Relay_2  4 

#define LED_ON 255
#define LED_OFF 0

int state = 0;
const int led = 9;    // connected to the base of the transistor


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  Serial.begin(9600);
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
}





