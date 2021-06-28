#define SensorPin A1  
float sensorValue = 0; 
void setup() { 
 Serial.begin(9600); 
} 
void loop() { 
 for (int i = 0; i <= 100; i++) 
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(1); 
 }

 sensorValue = sensorValue/100.0; 
 int y = map(sensorValue, 0, 1024, 0, 100); 
 Serial.println(y); 
 delay(30); 
} 
