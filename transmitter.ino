#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
pinMode(A0,INPUT);
if (!driver.init())
         Serial.println("init failed");

}
void loop() {
    int a;
    a=get_temp();
    float temp = a * 0.48828125*100;
    Serial.print("TEMPERATURE = ");
    Serial.print(temp);
    Serial.print("*C");
    Serial.println();


    float  val = temp;  // test value
    char x[10] = {' '} ;
    int val_int = (int) val;   // compute the integer part of the float
    float val_float = (abs(val) - abs(val_int)) * 100000;
    int val_fra = (int)val_float;
    sprintf (x, "%d.%d", val_int, val_fra);
    Serial.println ( x ) ;

    
    const char *msg = x;
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}

int get_temp(){
  int temp = analogRead(A0);
   return temp;
   delay(1000); // update sensor reading each one second
}
