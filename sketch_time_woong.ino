
#include <TimeLib.h>
#include <Time.h>

 void printDigits(int digits){
    Serial.print("; ");
    if (digits < 10)
       Serial.print('0');
    Serial.print(digits);
 }
 void digitalClockDisplay(){
    Serial.print(year());
    Serial.print("/");
    Serial.print(month());
    Serial.print("/");
    Serial.print(day());
    Serial.print("  ");
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.println();
 }
 void setup(){
    Serial.begin(9600);
    
    setTime(23,59,0,26,11,16);
 }
 void loop(){
    digitalClockDisplay();
    delay(1000);
 }

