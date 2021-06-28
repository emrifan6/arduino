
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>


/* Set these to your desired credentials. */
const char *ssid = "ElisaCom_Kos";  //ENTER YOUR WIFI SETTINGS
const char *password = "kosElisa12345";


//Web/Server address to read/write from
const char* host = "emrifan.my.id"; //Do not use http or https in front of host ink
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "bddbfc02268f281a72d571a63673835a258cf47d";
String Link ;
String apiKeyValue = "muchamadrifan";
String Link_get_control = "/pakanikan/input.php";

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("I'm Wake Up");
  connectwifi();
  delay(1000);
}


void loop() {

}

void connectwifi() {
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


void postdata() { //function kirim data
  WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
  //Serial.println(host);
  //  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  //  httpsClient.setFingerprint(fingerprint);
  httpsClient.setInsecure();
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

  String httpRequestData = "api_key=" + apiKeyValue + "&soil=" + 0 + "&temperature=" + data_temperature + "&humidity=" + data_humidity  + "&temperatureout=" + data_temperatureout
                           + "&humidityout=" + data_humidityout + "&volt_batt=" + vbatt + "&volt_solar=" + vsolar + "&curr_solar=" + csolar;
  Serial.print("httpRequestData: ");

  Link = "/greenhouse05/post-esp-data.php?" + httpRequestData; //
  Serial.print("Link = ");
  Serial.print(host);
  Serial.print(Link);


  Serial.print("requesting URL: ");
  Serial.print(host);
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
