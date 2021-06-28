#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>




/* Set these to your desired credentials. */
const char *ssid = "ElisaCom_Kos";  //ENTER YOUR WIFI SETTINGS
const char *password = "kosElisa12345";


//Web/Server address to read/write from
const char* host = "emrifan.xyz"; //Do not use http or https in front of host ink
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "b243c193eee93225f5d1d0d342d63fb97534c907";
String Link ="/greenhouse05/cek_last_control.php";


void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("I'm Wake Up");
  delay(1000);
  while (!Serial) {
    delay(100);
  }
  connectwifi();
}

void loop() {
  Serial.println(" get_control_data() ");
  get_control_data();
  Serial.println(" Selesai ");
  delay(10000);
}

void get_control_data() { //function kirim data
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
    
    const size_t capacity = JSON_OBJECT_SIZE(3) + 30;
    DynamicJsonDocument doc(capacity);
    
    const char* json = "{\"fan\":\"0\",\"mist\":\"0\",\"pump\":\"0\"}";
    
    deserializeJson(doc, line);
    
    const char* fan = doc["fan"]; // "0"
    const char* mist = doc["mist"]; // "0"
    const char* pump = doc["pump"]; // "0"

    Serial.print(" Fan = ");
    Serial.println(fan);
    Serial.print(" Mist = ");
    Serial.println(mist);
    Serial.print(" Pump = ");
    Serial.println(pump);
    
    
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
