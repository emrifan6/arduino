#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

void setup () {



  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("RTC TIDAK TERBACA");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//update rtc dari waktu komputer
  }
}

void loop () {
  DateTime now = rtc.now();
  Serial.print(namaHari[now.dayOfTheWeek()]);
  Serial.print(',');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

//  int jam = now.hour()
  bool siram_pagi = (now.hour()== 18) && (now.minute()<= 19);
  bool siram_siang = (now.hour()== 12) && (now.minute()<= 1);
  
  if(siram_pagi){
    Serial.println("WATERING TIME");
  }

  delay(3000);
}
