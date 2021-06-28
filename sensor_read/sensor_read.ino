byte led=4;
byte sensor=A0;
void setup() {
pinMode (sensor, INPUT);
pinMode(led, OUTPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println(analogRead(sensor));
if(analogRead(sensor)>=800){
digitalWrite(led, HIGH);
}
else  if (analogRead(sensor)>200){
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);

  
} else {
digitalWrite(led, LOW);
}
delay(200);
}
