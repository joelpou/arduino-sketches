/*****************************************************************
XBee_Serial_Passthrough.ino

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.
*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)



SoftwareSerial XBee(2, 3); // RX, TX

int sensorPin = 0; //analog pin 0
int led = 9;
int light = 13;
int pot = A0;
int var;
void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
    pinMode(light, OUTPUT);
}

void loop()
{
 
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
  int var = XBee.read();
    Serial.println(var,DEC);
    
     if (var == 129) { 
      digitalWrite(light, HIGH);     
      //delay(1000); 
      //analogWrite(9, 1023); 
           
    }
    
    else {
      digitalWrite(light, LOW);
     // delay(1000);
      //analogWrite(9, 0);
            
      }
    //Serial.println();
  //delay(30);
  }
}
