
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
      send_esp("pagi", "masih");
      detik_test = 0;
    }
  }
  
}

void send_esp(String pakan_ikan, String cek_pakan) {
  Serial.println();
  Serial.println("KIRIM DATA");
  Serial.print("DATA pakan_ikan = ");
  Serial.println(pakan_ikan);
  Serial.print("DATA cek_pakan = ");
  Serial.println(cek_pakan);
  StaticJsonDocument<200> doc;
  doc["pakan_ikan"] = pakan_ikan;
  doc["cek_pakan"] = cek_pakan;
  serializeJson(doc, espserial);
  serializeJson(doc, Serial);
  Serial.println();
}
