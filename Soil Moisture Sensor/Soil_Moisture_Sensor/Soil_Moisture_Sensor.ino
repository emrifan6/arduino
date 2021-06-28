/* 
 Soil Moisture Sensor  
 modified on 21 Feb 2019 
 by Saeed Hosseini @ Electropeak 
 https://electropeak.com/learn/ 
*/
#define SensorPin A0 
int waterpump =  D0;


//unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 1000;           // interval at which to blink (milliseconds)


void setup() { 
 pinMode(waterpump, OUTPUT); 
 Serial.begin(9600); 
} 
void loop() { 
 int sensorValue = 0;
 for (int i = 0; i<100; i++) 
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(10); 
 } 
 sensorValue = sensorValue/100.0; 
 Serial.print("Sensor Value   = ");
 Serial.println(sensorValue);
 int moisture = map(sensorValue, 1023, 0, 0, 100);
 Serial.print("Moisture Value = ");
 Serial.print(moisture);
 Serial.println("%");
 delay(10);
 if(moisture < 40){
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
 delay(1000); 
} 
