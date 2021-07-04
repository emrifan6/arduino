
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

StaticJsonDocument<48> doc;

SoftwareSerial espserial(11, 12); // RX, TX


//millis
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
int detik_cekpakan = 0;
int detik_pakan = 0;
int detik_test = 0;


void setup() {

  Serial.begin(9600);
  delay(1000);

  espserial.begin(9600);
  delay(100);
}

void loop() {
  
  if (espserial.available()) {
    Serial.println();
    String incomingString = espserial.readString();
    Serial.print("ARDUINO received: ");
    Serial.println(incomingString);
  }

  if (millis() - previousMillis >= interval) {
    Serial.print(".");
    previousMillis = millis();
    if (++detik_test >= 60) {
      send_esp("&pakan_ikan=pagi&cek_pakan=masih");
      detik_test = 0;
    }
  }
  
}

void send_esp(String data) {
  Serial.println();
  Serial.print("KIRIM DATA :");
  Serial.println(data);
  espserial.print(data);
  Serial.println();
}
