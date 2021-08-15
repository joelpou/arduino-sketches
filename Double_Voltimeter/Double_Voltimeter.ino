/*--------------------------------------------------------------
  Program:      volt_measure

  Description:  Reads value on analog input A2 and calculates
                the voltage assuming that a voltage divider
                network on the pin divides by 11.
  
  Hardware:     Arduino Uno with voltage divider on A2.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +

  Date:         22 May 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

// number of analog samples to take per reading
#define NUM_SAMPLES 10

const int Vdrive = A0;
const int Vcharge = A1;


int sum1 = 0;                    // sum of samples taken
int sum2 = 0;

unsigned char sample_count = 0; // current sample number
float Vin = 0.0;            // calculated voltage
float Vout = 0.0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum1 += analogRead(Vdrive);
        sum2 += analogRead(Vcharge);
        sample_count++;
        delay(10);
    }
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 4.55V is the calibrated reference voltage
    Vin = ((float)sum1 / (float)NUM_SAMPLES * 4.55) / 1024.0;
    Vout = ((float)sum2 / (float)NUM_SAMPLES * 4.55) / 1024.0;

    // send voltage for display on Serial Monitor
    // voltage multiplied by 11 when using voltage divider that
    // divides by 11. 11.132 is the calibrated voltage divide
    // value
    Serial.print("Vdrive = "); Serial.print(Vin * 12.25);
    Serial.println (" V");
    Serial.print("Vcharge = "); Serial.print(Vout * 12.25);
    Serial.println (" V");
    sample_count = 0;
    sum1 = 0;
    sum2 = 0;
}
