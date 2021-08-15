#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//This example uses the LCD I2C library available here:
//http://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home

// Set the LCD address to 0x27 (Could be 0x20 if solder jumpers are bridged!)
// Set the pins on the I2C chip used for LCD connections:
//                    addr,en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
    LCD.begin(20, 4);  // 16 lines by 2 rows
    LCD.clear();
    LCD.backlight();
    LCD.setCursor(0,0);
    LCD.print("Hello Joel");
    LCD.setCursor(0,1);
    LCD.print("Hello Line 2");
}

void loop() {
//    delay(500);
//    LCD.clear();
//    LCD.home();
//    LCD.print(millis());
}
