#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial esp(2,1);

int data = 909;

void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(data);
  Serial.print('\n');
  data++;
  delay(5000);
}
