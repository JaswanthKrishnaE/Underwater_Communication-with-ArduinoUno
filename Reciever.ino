#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>
//#include <DS3231.h>
#include <Wire.h>
RH_ASK driver;
 LiquidCrystal lcd(7,9,10,6,12,13);
void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
         // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //clearPrintTitle();
  lcd.print("Temperature :");
}

void loop()
{
    uint8_t buf[12]={'0'};
    uint8_t buflen = sizeof(buf);
    
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      char a[4];
      int m=0;
      for(int i=0;i<6;i++)
      {
        a[i]=buf[i];
      };
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("temperature: ");
      Serial.println((char*)a);  
      // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print((char*)a);    
  
    }
   
}
