#include <DHT.h>
#include <DHT_U.h>


#include <ESP8266WiFi.h>
                //#include <WiFiClientSecure.h>
                //#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
                //#include <SoftwareSerial.h>

                //SoftwareSerial fromnano(3, 1); //Rx, Tx
#define DHTPIN 2  // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
                 //Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

                  /* Set these to your desired credentials. */
const char* ssid = "*****";  //ENTER YOUR WIFI SETTINGS
const char* password = "******";


        //Web/Server address to read/write from
const char* serverName = "emrifanesp.000webhostapp.com/dht11"; //for https Do not use http or https in front of host ink
const int httpsPort = 80;  //HTTPS= 443 and HTTP = 80

                                          //SHA1 finger print of certificate use web browser to view and copy
                                          //const char fingerprint[] PROGMEM = "02e38f27468d92a865bd505e5ec70ca74f83dc7a";

String Data, getData, Link, station;
                                    //float h = 12.123;
                                    //float t = 9.32; 

String apiKeyValue = "********";

void setup() {
  delay(1000);
  Serial.begin(115200);
                                  // fromnano.begin(9600);
  connectwifi();
                                //  dht.begin();
}
void loop() {
    senddata();
    delay(10000);
}

void senddata() {
                                    // Reading temperature or humidity takes about 250 milliseconds!
                                    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
                                     // Read temperature as Celsius
    float t = dht.readTemperature();

                                    // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
    String httpRequestData = "api_key=" + apiKeyValue + "&temperature=" + t
                          + "&humidity=" + h+"";
    Serial.print("httpRequestData: ");

                                   // Data ="temperature="+t+"humidity="+h;
                                   //GET Data
    Link = "/post-esp-data.php?"+httpRequestData;  //
    Serial.print("Link = ");
    Serial.println(Link);
    postdata();
                                    //    h = h+0.01;
                                    //    t = t+0.01;
}

void postdata() {                     //function kirim data
                                       // WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
  if(WiFi.status()== WL_CONNECTED){
  HTTPClient http;
  Serial.println(serverName);
                        // Your Domain name with URL path or IP address with path
   http.begin(serverName);
                        //Serial.printf("Using fingerprint '%s'\n", fingerprint);
                        //httpsClient.setFingerprint(fingerprint);
                        //httpsClient.setTimeout(15000); // 15 Seconds

                        // Specify content-type header
                        
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
                         //  delay(1000);
                        //  Serial.print("HTTP Connecting");
                        //  int r = 0; //retry counter
                        //  while ((!httpClient.connect(host, httpsPort)) && (r < 30)) {
                        //    delay(100);
                        //    Serial.print(".");
                        //    r++;
                        //  }
                        //  if (r == 30) {
                        //    Serial.println("Connection failed");
                        //  }
                        //  else {
                        //    Serial.println("Connected to web");
                        //  }


 Serial.print("requesting URL: ");
 Serial.println(serverName + Link);
                        //  httpsClient.print(String("POST") + Link + " HTTP/1.1\r\n" +
                        //                    "Host: " + host + "\r\n" +
                        //                    "Connection: close\r\n\r\n");

                    // Send HTTP POST request
  int httpResponseCode = http.POST(Link);
  Serial.println("request sent");
  String payload = http.getString(); 
   Serial.println(payload); 
  if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else  {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    // Free resources
    http.end();
    }
     http.end();
  }
  else {
      Serial.println("WiFi Disconnected");
  }

                      //  while (httpsClient.connected()) {
                      //    String line = httpsClient.readStringUntil('\n');
                      //    if (line == "\r") {
                      //      Serial.println("headers received");
                      //      break;
                      //    }
                      //  }
                      //
                      //  Serial.println("reply was:");
                      //  Serial.println("==========");
                      //  String line;
                      //  while (httpsClient.available()) {
                      //    line = httpsClient.readStringUntil('\n');  //Read Line by Line
                      //    Serial.println(line); //Print response
                      //  }
                      //  Serial.println("==========");
                      //  Serial.println("closing connection");
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
