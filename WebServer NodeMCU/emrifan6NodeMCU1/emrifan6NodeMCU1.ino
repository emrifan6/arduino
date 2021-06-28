#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define WIFI_SSID "R6P"
#define WIFI_PASSWORD "22021998"

#define FIREBASE_HOST "emrifan6nodemcu.firebaseio.com"
#define FIREBASE_AUTH "JuLvqmfnwc7lBAFPmUvR1btQjLmf74tULe2anSp0"

int LedPower = 5;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Wifi.begin(WIFI_SSID, WIFI_PASWORD);
Serial.print("Connecting");
while(Wifi.status() !=WL_CONNECTED) {
    Serial.print(".");
    delay(500);
}

Serial.println();
Serial.print("Connected");
Serial.println(Wifi.localIP());

Firebase.begin(FIREBASE_AUTH);
pinMode(ledPower, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int ledStatus = Firebase.getInt("ledStatus");
  Serial.println(ledStatus);

}
