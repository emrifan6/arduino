#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int pump = D5;

const char *ssid     = "DEAART";
const char *password = "12345678";

                  //You need to adjust the UTC offset for your timezone in milliseconds. Refer the list of UTC time offsets. Here are some examples for different timezones:
                  //For UTC -5.00 : -5 * 60 * 60 : -18000
                  //For UTC +1.00 : 1 * 60 * 60 : 3600
                  //For UTC +0.00 : 0 * 60 * 60 : 0

const long utcOffsetInSeconds = 25200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int pump_status = LOW;

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  pinMode(pump, OUTPUT);
}




void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  if(timeClient.getMinutes() >= 58 && timeClient.getMinutes() < 59){
    Serial.println("Watering !!");
    pump_status = HIGH;
  }else{
    pump_status = LOW;
  }

  digitalWrite(pump, pump_status);
  delay(1000);
}
