#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN D5  
#define DHTTYPE DHT11   // DHT 11

#define DHTPIN01 D6


#define SensorPin A0
 
int waterpump =  D1;
int waterlevel = 65 ;

int Vcc_Sensor = D7;
                       
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

unsigned long previousMillis = 0;        
const long interval = 1000;  

DHT dht(DHTPIN, DHTTYPE);
DHT dht01(DHTPIN01, DHTTYPE);
int temperature = 0;
int humidity = 0;
int temperature01 = 0;
int humidity01 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("I'm Wake Up");
  pinMode(Vcc_Sensor, OUTPUT);
  digitalWrite(Vcc_Sensor, HIGH);
  delay(1000);
  dht.begin();
  dht01.begin();
  while(!Serial){
    delay(100);
  }
  connectwifi();
  pinMode(waterpump, OUTPUT);
  digitalWrite(waterpump, HIGH);
  
}

void loop() {
  cek_dht();
  cek_dht01();
  int x = smooth();
  senddata(x, temperature, humidity, temperature01, humidity01);
  watering(x);
  digitalWrite(Vcc_Sensor, LOW);
  Serial.println("I'm going into deep sleep mode");
  ESP.deepSleep(6e8); // 6e8=10 menit
}


void cek_dht01(){
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht01.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht01.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht01.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht01.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
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



void cek_dht(){
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
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
  if(x < waterlevel){
  digitalWrite(waterpump, HIGH);
  Serial.println("WATERPUMP ON");
  delay(7000);
  digitalWrite(waterpump, LOW);
  Serial.println("WATERPUMP OFF");
  }else {
    digitalWrite(waterpump, LOW);
    Serial.println("WATERPUMP OFF");
 }
 Serial.println("==================");
 Serial.println();
}


int soil() { 
 int sensorValue = 0;
 for (int i = 0; i<100; i++) 
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(10); 
 } 
 sensorValue = sensorValue/100; 
// Serial.print("Sensor Value   = ");
// Serial.println(sensorValue);
 int moisture = map(sensorValue, 1023, 0, 0, 100);
// Serial.print("Moisture Value = ");
// Serial.print(moisture);
// Serial.println("%");
 delay(10);
 return moisture;
 delay(1000); 
}



void senddata(int x, int y, int z, int a, int b) {

    int h = x;
    int i = y;
    int j = z;
    int k = a;
    int l = b;
                     
      if (isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
    String httpRequestData = "api_key=" + apiKeyValue +"&soil="+h +"&temperature="+i +"&humidity="+j  +"&temperatureout="+a +"&humidityout="+b;
    Serial.print("httpRequestData: ");

                                
    Link = "/greenhouse/post-esp-data.php?"+httpRequestData;  //
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

int smooth() {
  const int numReadings = 20;
  int readings[numReadings];      // the readings from the analog input
  int readIndex = 0;              // the index of the current reading
  int total = 0;                  // the running total
  int average = 0;                // the average
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // mulai mengambil beberapa data
  for (int i=0; i<numReadings; i++) {
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = soil();
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    Serial.print("Nilai ke- ");
    Serial.print(readIndex);
    Serial.print(" = \t");
    Serial.println(readings[readIndex]);
    readIndex = readIndex + 1;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    delay(20);  // delay in between reads for stability
  }
   // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println();
  Serial.print("Rata-rata = \t");
  Serial.println(average);
  delay(10);       
  return average; 
}
