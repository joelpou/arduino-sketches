#define RELAY_ON 0
#define RELAY_OFF 1

#define Relay_1  2      
#define Relay_2  3 

int state = 0;
const int transistorPin = 9;    // connected to the base of the transistor
const int potPin = A0; 


void setup() {
  Serial.begin(9600);
  pinMode(Relay_1, OUTPUT);  
  pinMode(Relay_2, OUTPUT); 
  pinMode(13, OUTPUT); 
//  pinMode(transistorPin, OUTPUT);
}

void loop() {

//  int sensorValue = analogRead(potPin);
//   // map the sensor value to a range from 0 - 255:
//   int outputValue = map(sensorValue, 0 , 1023, 255, 0);
//   // use that to control the transistomir:
//   Serial.println(sensorValue);
//   analogWrite(transistorPin, outputValue);

    state = Serial.read();
    if (state == '1') { 
      do { 
        digitalWrite(Relay_1, RELAY_ON);
        digitalWrite(Relay_2, RELAY_ON);        
        state = Serial.read();
//        Serial.println(state);
      }      
      while (state != '0');
    }
  
    else if (state == '0') {
      do { 
        digitalWrite(Relay_1, RELAY_OFF);
        digitalWrite(Relay_2, RELAY_OFF);
        state = Serial.read();
//        Serial.println(state);
        }

         while (state != '1');
      }
  
    else {
      digitalWrite(13, LOW);
      digitalWrite(Relay_1, RELAY_OFF);
      digitalWrite(Relay_2, RELAY_OFF);
       state = Serial.read();
//        Serial.println(state);
    }
  delay(1000);
}
