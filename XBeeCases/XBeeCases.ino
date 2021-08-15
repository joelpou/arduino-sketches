
//#include <PWM.h>

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);

//int32_t frequency = 1000;


int light = 9;

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
  //analogWrite(light, 0);  
  //pinMode(light, OUTPUT);

}

void loop()
{
  if (XBee.available()) {
    //Serial.write(XBee.read()); 
          
    switch (XBee.read()) {
      case 'a':       
       do{
        analogWrite(light, 63);
       }while(XBee.read() == 'o');
        //delay(2000);
        break;
      case 'b':
       do{ 
        analogWrite(light, 126);
       }while(XBee.read() == 'o');
        break;
      case 'c':
       do{
        analogWrite(light, 189);
       }while(XBee.read() == 'o');
        break;
      case 'd':
       do{ 
        analogWrite(light, 255);
       }while(XBee.read() == 'o');
        break;
      default:
        analogWrite(light, 0);            
    }
  }
}

