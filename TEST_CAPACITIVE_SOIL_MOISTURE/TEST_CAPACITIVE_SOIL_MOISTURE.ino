int sensorPin1 = A1; 
int sensorPin2 = A2; 
int sensorPin3 = A3; 

//Saat kering = 880
//Saat Basah = 630

void setup() {
Serial.begin(9600);
}

void loop() {  
//Serial.print("Sensor 1 = ");
//Serial.print(analogRead(sensorPin1)); 
//Serial.print("    ");
//Serial.print("Sensor 2 = ");
//Serial.print(analogRead(sensorPin2)); 
//Serial.print("    ");
//Serial.print("Sensor 3 = ");
//Serial.println(analogRead(sensorPin3));

Serial.print("Sensor 1 = ");
int x = map(analogRead(sensorPin1), 620, 910, 100, 0); //range pembacaan sensor = 640-850 adc
if(x <= 0){
  x = 0;
}else if( x >= 100){
  x = 100;
}
Serial.print(x); 
Serial.print("%    ");
Serial.print("Sensor 2 = ");
int y = map(analogRead(sensorPin2), 600, 930, 100, 0);
if(y <= 0){
  y = 0;
}else if( y >= 100){
  y = 100;
}
Serial.print(y); 
Serial.print("%    ");
Serial.print("Sensor 3 = ");
int z = map(analogRead(sensorPin3), 845, 885, 100, 0);
if(z <= 0){
  z = 0;
}else if( z >= 100){
  z = 100;
}
Serial.print(z); 
Serial.println("%    ");

}
