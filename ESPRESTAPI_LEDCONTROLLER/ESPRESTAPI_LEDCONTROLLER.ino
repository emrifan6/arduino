/*
 *  Simple hello world Json REST response
  *  by Mischianti Renzo <https://www.mischianti.org>
 *
 *  https://www.mischianti.org/
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
 
const char* ssid = "ElisaCom_Kos";
const char* password = "kosElisa12345";

//const char* ssid = "IYAN";
//const char* password = "I_yan12345";
 
ESP8266WebServer server(80);

void setCrossOrigin(){
    server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    server.sendHeader(F("Access-Control-Max-Age"), F("600"));
    server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

void ledmode() {
    setCrossOrigin();
    String postBody = server.arg("plain");
    Serial.println(postBody);
 
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, postBody);
    if (error) {
        Serial.print(F("Error parsing JSON "));
        Serial.println(error.c_str());
 
        String msg = error.c_str();

        server.send(400, F("text/html"),
                "Error in parsin json body! <br>" + msg);
 
    } else {
        JsonObject postObj = doc.as<JsonObject>();
 
//        Serial.print(F("HTTP Method: "));
//        Serial.println(server.method());
 
        if (server.method() == HTTP_POST) {
            if (postObj.containsKey("mode")) {
 
                DynamicJsonDocument doc(512);
                doc["status"] = "OK";
                String buf;
                serializeJson(doc, buf); 
                server.send(201, F("application/json"), buf);
 
            }else {
                DynamicJsonDocument doc(512);
                doc["status"] = "KO";
                doc["message"] = F("No data found, or incorrect!");
                String buf;
                serializeJson(doc, buf);
                server.send(400, F("application/json"), buf);
                Serial.print(F("done."));
            }
        }
    }
}


void setrgb() {
    setCrossOrigin();
    String postBody = server.arg("plain");
    Serial.println(postBody);
 
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, postBody);
    if (error) {
        // if the file didn't open, print an error:
        Serial.print(F("Error parsing JSON "));
        Serial.println(error.c_str());
 
        String msg = error.c_str();

        server.send(400, F("text/html"),
                "Error in parsin json body! <br>" + msg);
 
    } else {
        JsonObject postObj = doc.as<JsonObject>();
 
//        Serial.print(F("HTTP Method: "));
//        Serial.println(server.method());
 
        if (server.method() == HTTP_POST) {
            if (postObj.containsKey("r") && postObj.containsKey("g") && postObj.containsKey("b")) {
 
                DynamicJsonDocument doc(512);
                doc["status"] = "OK";
                String buf;
                serializeJson(doc, buf); 
                server.send(201, F("application/json"), buf);
 
            }else {
                DynamicJsonDocument doc(512);
                doc["status"] = "KO";
                doc["message"] = F("No data found, or incorrect!");
                String buf;
                serializeJson(doc, buf);
                server.send(400, F("application/json"), buf);
                Serial.print(F("done."));
            }
        }
    }
}
 

void sendCrossOriginHeader(){
    server.sendHeader(F("access-control-allow-credentials"), F("false"));
    setCrossOrigin();
    server.send(204);
}
 
// Define routing
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
       server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, F("text/html"),
            F("Welcome to the REST Web Server"));
    });
    
    server.on(F("/ledmode"), HTTP_OPTIONS, sendCrossOriginHeader);
    server.on(F("/ledmode"), HTTP_POST, ledmode);

    server.on(F("/rgb"), HTTP_OPTIONS, sendCrossOriginHeader);
    server.on(F("/rgb"), HTTP_POST, setrgb);
}
 
// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(404, "text/plain", message);
}
 
void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
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
 
  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 
  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
}
