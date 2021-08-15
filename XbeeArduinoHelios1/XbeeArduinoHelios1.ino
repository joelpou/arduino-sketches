/*****************************************************************
Helios - LED
*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)

SoftwareSerial XBee(2, 3); // RX, TX

int led = 9;
int var;
void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
   
}

void loop()
{
 
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
    int var = XBee.read();
    delay(1000);
    Serial.println(var,DEC);  
    analogWrite(led, var/4);
    
    //delay(10);
  }          

}


