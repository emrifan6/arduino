#include <DS3231.h>
#include <Wire.h>

DS3231  rtc(SDA, SCL);
Time  t;
#define buz 11
int Hor;
int Min;
int Sec;

void setup() {
  
  Wire.begin();
  rtc.begin();
  
  Serial.begin(9600);
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
//  rtc.setTime(22, 55, 30);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(10, 2, 2021);   // Set the date to January 1st, 2014
  delay(1000);
  Serial.print("WAKTU PEMBERIAN PAKAN PAGI : ");
}

void loop() {
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;
  Serial.print(Hor);
  Serial.print(":");
  Serial.print(Min);
  Serial.print(":");
  Serial.println(Sec);

  delay(5000);
}
