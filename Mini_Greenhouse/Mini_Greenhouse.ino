#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT11   // DHT 11

#define DHTPIN01 D6

int waterpump =  D1;
int waterlevel = 65 ;

int Vcc_Sensor = D7;


const int PIN_A = D1;
const int PIN_B = D2;
const int PIN_C = D3;

float volt_batt, volt_solar, curr_solar, power_solar = 0.0;


/* Set these to your desired credentials. */
const char *ssid = "ElisaCom_Kos";  //ENTER YOUR WIFI SETTINGS
const char *password = "kosElisa12345";


//Web/Server address to read/write from
const char* host = "emrifan.xyz"; //Do not use http or https in front of host ink
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "b243c193eee93225f5d1d0d342d63fb97534c907";
String Link ;
String apiKeyValue = "muchamadrifan";

DHT dht(DHTPIN, DHTTYPE);
DHT dht01(DHTPIN01, DHTTYPE);
int temperature = 0;
int humidity = 0;
int temperature01 = 0;
int humidity01 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("I'm Wake Up");
  pinMode(Vcc_Sensor, OUTPUT);
  digitalWrite(Vcc_Sensor, HIGH);
  delay(1000);
  dht.begin();
  dht01.begin();
  while (!Serial) {
    delay(100);
  }
  connectwifi();
  pinMode(waterpump, OUTPUT);
  digitalWrite(waterpump, HIGH);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);

}

void loop() {
  cek_dht();
  delay(100);
  cek_dht01();
  delay(100);
  volt_batt = read_adc(0);
  delay(100);
  volt_solar = read_adc(1);
  delay(100);
  curr_solar = read_adc(2);
  delay(100);
  senddata(0, temperature, humidity, temperature01, humidity01, volt_batt, volt_solar, curr_solar);
  // watering(x);
  //digitalWrite(Vcc_Sensor, LOW);
  Serial.println("I'm going into deep sleep mode");
  ESP.deepSleep(6e8); // 6e8=10 menit
}


float read_adc(int pin_gate) {
  gate(pin_gate);
  delay(100);
  int raw = 0;
  for (int i = 0; i < 10; i++){
    int x = analogRead(A0);
    raw = raw + x;
  }
  raw = raw / 10;

  float voltage = 0.0;
  if ( pin_gate == 0) {
    voltage = (raw * (3.3 / 1023)) * 1.55;
  } else if (pin_gate == 1) {
    voltage = raw * (3.3 / 1023) * 2.05;
  } else if (pin_gate == 2) {
    voltage = raw * (3.3 / 1023) * 1.17;
    if(voltage <= 0.15){
      voltage = 0;
    }else if(voltage <= 0.23){
      voltage = 0;
    }else if(voltage <= 0.32){
      voltage = 0.05;
    }else if(voltage <= 0.4){
      voltage = 0.1;
    }else if(voltage <= 0.47){
      voltage = 0.15;
    }else if(voltage <= 0.56){
      voltage = 0.2;
    }else if(voltage <= 0.64){
      voltage = 0.25;
    }else if(voltage <= 0.71){
      voltage = 0.3;
    }else if(voltage <= 0.78){
      voltage = 0.35;
    }else if(voltage <= 0.88){
      voltage = 0.4;
    }else if(voltage <= 0.96){
      voltage = 0.45;
    }else if(voltage <= 1.04){
      voltage = 0.5;
    }else if(voltage <= 1.12){
      voltage = 0.55;
    }else{
      voltage = voltage;
    }
  } else {
    voltage = raw * (3.3 / 1023.0) * 1.17;
  }
  return voltage;
}



void cek_dht01() {
  delay(2000);
  float h = dht01.readHumidity();
  float t = dht01.readTemperature();
  float f = dht01.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht01.computeHeatIndex(f, h);
  float hic = dht01.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  temperature01 = t;
  humidity01 = h;
}



void cek_dht() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  temperature = t;
  humidity = h;
}


void watering(int x) {
  if (x < waterlevel) {
    digitalWrite(waterpump, HIGH);
    Serial.println("WATERPUMP ON");
    delay(7000);
    digitalWrite(waterpump, LOW);
    Serial.println("WATERPUMP OFF");
  } else {
    digitalWrite(waterpump, LOW);
    Serial.println("WATERPUMP OFF");
  }
  Serial.println("==================");
  Serial.println();
}

void senddata(int x, int y, int z, int a, int b, float vbatt, float vsolar, float csolar) {

  int h = x;
  int i = y;
  int j = z;
  int k = a;
  int l = b;

  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  String httpRequestData = "api_key=" + apiKeyValue + "&soil=" + h + "&temperature=" + i + "&humidity=" + j  + "&temperatureout=" + a + "&humidityout=" + b + "&volt_batt=" + vbatt
                           + "&volt_solar=" + vsolar + "&curr_solar=" + csolar;
  Serial.print("httpRequestData: ");


  Link = "/greenhouse/post-esp-data.php?" + httpRequestData; //
  Serial.print("Link = ");
  Serial.println(Link);
  postdata();
}

void postdata() { //function kirim data
  WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
  Serial.println(host);
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(1000);
  Serial.print("HTTPS Connecting");
  int r = 0; //retry counter
  while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
    delay(100);
    Serial.print(".");
    r++;
  }
  if (r == 30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }


  Serial.print("requesting URL: ");
  Serial.println(Link);

  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");

  Serial.println("request sent");

  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while (httpsClient.available()) {
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");
}


void connectwifi() { // function konek ke wifi
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}


void gate (int pin) {
  if (pin == 0) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 1) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 2) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 3) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 4) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 5) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 6) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 7) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
  } else {

  }
}
