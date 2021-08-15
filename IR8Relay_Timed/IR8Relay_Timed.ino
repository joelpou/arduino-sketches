/* Timed Switch IR 8 Channel Relay Control

The purpose of this code is to control an 8 channel relay board (Sain Smart)
with an InfraRed remote control. When a button on the remote is pressed
the appropiate relay turns ON an acts as a Timed Switch. This means
that the relay will turn on and stay on based on a pre-defined delay
time.

12/9/2015
By Joel Pou

*/

#include <IRLib.h>

#define RELAY_ON 0
#define RELAY_OFF 1

#define Relay_1  9      
#define Relay_2  2    
#define Relay_3  3   
#define Relay_4  4    
#define Relay_5  5
#define Relay_6  6
#define Relay_7  7
#define Relay_8  8

//#define SETUP   0xfd20df
//#define BACK    0xfd708f
//#define ENTER   0xfd906f
//
//#define UP      0xfda05f
//#define RIGHT   0xfd50af
//#define DOWN    0xfdb04f
//#define LEFT    0xfd10ef

#define ONE     0xfd08f7
#define TWO     0xfd8877
#define THREE   0xfd48b7
#define FOUR    0xfd28d7
#define FIVE    0xfda857
#define SIX     0xfd6897
#define SEVEN   0xfd18e7
#define EIGHT   0xfd9867
//#define NINE    0xfd58a7

const int timeDelay = 3000; // Change value to change amount of seconds for timing switch. 
                            // For example: 3000 = 3000 miliseconds or 3 seconds.

IRrecv My_Receiver(11);   //receiver on pin 11
IRdecode My_Decoder;      //Decoder object 
 
void setup()
{  
  Serial.begin(9600);
  My_Receiver.enableIRIn(); // Start the receiver
  
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);
  digitalWrite(Relay_5, RELAY_OFF);
  digitalWrite(Relay_6, RELAY_OFF);
  digitalWrite(Relay_7, RELAY_OFF);
  digitalWrite(Relay_8, RELAY_OFF);  

  pinMode(Relay_1, OUTPUT);  
  pinMode(Relay_2, OUTPUT);  
  pinMode(Relay_3, OUTPUT);
  pinMode(Relay_4, OUTPUT); 
  pinMode(Relay_5, OUTPUT);  
  pinMode(Relay_6, OUTPUT);  
  pinMode(Relay_7, OUTPUT);
  pinMode(Relay_8, OUTPUT);       

  delay(4000); //Check that all relays are inactive at Reset
}
 
void loop()
{
 if (My_Receiver.GetResults(&My_Decoder))
 {
    My_Decoder.decode();
    if (My_Decoder.decode_type== NEC)
    {
      switch(My_Decoder.value)
      {
        case ONE:  
          digitalWrite(Relay_1, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_1, RELAY_OFF);
          break;
        case TWO:  
          digitalWrite(Relay_2, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_2, RELAY_OFF);
          break;
        case THREE:  
          digitalWrite(Relay_3, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_3, RELAY_OFF);
          break;
        case FOUR:  
          digitalWrite(Relay_4, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_4, RELAY_OFF);
          break;
        case FIVE:  
          digitalWrite(Relay_5, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_5, RELAY_OFF);
          break;
        case SIX:  
          digitalWrite(Relay_6, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_6, RELAY_OFF);
          break;
        case SEVEN:  
          digitalWrite(Relay_7, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_7, RELAY_OFF);
          break;
        case EIGHT:  
          digitalWrite(Relay_8, RELAY_ON);         
          delay(timeDelay);
          digitalWrite(Relay_8, RELAY_OFF);
          break;
      }
      My_Receiver.resume(); //Restart the receiver
    }
  }      
}
