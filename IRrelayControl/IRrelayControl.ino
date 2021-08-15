#include <IRLib.h>

#define RELAY_ON 0
#define RELAY_OFF 1
/*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/
#define Relay_1  1      
#define Relay_2  2    //GREEN
#define Relay_3  3    //RED
#define Relay_4  4    //YELLOW
#define Relay_5  5
#define Relay_6  6
#define Relay_7  7
#define Relay_8  8

#define SETUP   0xfd20df
#define BACK    0xfd708f
#define ENTER   0xfd906f

#define UP      0xfda05f
#define RIGHT   0xfd50af
#define DOWN    0xfdb04f
#define LEFT    0xfd10ef

#define ONE     0xfd08f7
#define TWO     0xfd8877
#define THREE   0xfd48b7
#define FOUR    0xfd28d7
#define FIVE    0xfda857
#define SIX     0xfd6897
#define SEVEN   0xfd18e7
#define EIGHT   0xfd9867
#define NINE    0xfd58a7

#define HOLD    9
#define SNAP    10
#define TIME    12

int mode;

IRrecv My_Receiver(11);//receiver on pin 11
IRdecode My_Decoder;//Decoder object 
 
void setup() {  
  Serial.begin(9600);
  My_Receiver.enableIRIn(); // Start the receiver

  //  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);  
//  pinMode(Relay_1, OUTPUT);   
  pinMode(Relay_2, OUTPUT);  
  pinMode(Relay_3, OUTPUT);  
  pinMode(Relay_4, OUTPUT);
  pinMode(HOLD, INPUT);  
  pinMode(SNAP, INPUT);  
  pinMode(TIME, INPUT);
//  digitalWrite(HOLD, LOW);
//  digitalWrite(SNAP, LOW);
//  digitalWrite(TIME, LOW);        
  delay(4000); //Check that all relays are inactive at Reset
}
 
void loop() {
//  Serial.println(digitalRead(11));
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    if (My_Decoder.decode_type== NEC) {
      switch(My_Decoder.value) {
        case UP:  //  Setup relays for Press and Hold  
          Serial.println("CLOSE MODE");
          mode = HOLD;          
          Serial.println(mode);         
          delay(1000);
          break;
        case RIGHT:  //  Setup relays for Press and Release 
          Serial.println("SNAP MODE");
          mode = SNAP;
          Serial.println(mode);        
          delay(1000);
          break;
        case LEFT:  //  Setup relays for Timed Release 
          Serial.println("TIMED MODE");
          mode = TIME;
          Serial.println(mode);       
          delay(1000);
          break;
        case THREE:  //  Relay number 3
          digitalWrite(Relay_3, RELAY_ON);
          Serial.print("THREE");
          delay(1000);
//          digitalWrite(Relay_3, RELAY_OFF);
          break;   
        case FOUR:  //  Relay number 4
          Serial.print("FOUR");
          if(mode == HOLD) {
            digitalWrite(Relay_4, RELAY_ON);
            Serial.print(digitalRead(11));
            delay(2000);
          }
          break;                         
      }
    My_Receiver.resume(); //Restart the receiver
    }   
  }     
}

