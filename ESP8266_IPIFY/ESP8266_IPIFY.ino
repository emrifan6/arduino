
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/* Set these to your desired credentials. */
const char *ssid = "IYAN";//"ElisaCom_Kos";  //ENTER YOUR WIFI SETTINGS
const char *password = "I_yan12345";//"kosElisa12345";



//Web/Server address to read/write from
const char* host = "pakanikan.emrifan.my.id"; //Do not use http or https in front of host ink
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
//SHA1 finger print of certificate use web browser to view and copy
//const char fingerprint[] PROGMEM = "bddbfc02268f281a72d571a63673835a258cf47d";

void setup() {
  delay(7000);
  Serial.begin(9600);
  //  Serial.println();
  //  Serial.println("I'm Wake Up");
  connectwifi();
  delay(1000);
  get_ip();
}


void loop() {

}

void connectwifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void get_ip() {
  WiFiClientSecure httpsClient;
  httpsClient.setInsecure();
  httpsClient.setTimeout(10000);
  delay(1000);
  int r = 0; //retry counter
  while ((!httpsClient.connect("api.ipify.org", 80)) && (r < 30)) {
    delay(100);
    Serial.print(".");
    r++;
  }
  if (r == 30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected");
  }

  httpsClient.print(String("GET ") + "/"  + " HTTP/1.1\r\n" +
                    "Host: " + "api.ipify.org" + "\r\n" +
                    "Connection: close\r\n\r\n");

  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String line;
  while (httpsClient.available()) {
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
    if (httpsClient.connect("api.ipify.org", 80)) {
      Serial.println("connected");
      httpsClient.println("GET / HTTP/1.0");
      httpsClient.println("Host: api.ipify.org");
      httpsClient.println();
  } else {
      Serial.println("connection failed");
  }
}
