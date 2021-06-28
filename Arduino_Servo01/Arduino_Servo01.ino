/*
  TUGAS 89
  MUCHAMAD RIF'AN
  17.01.53.2021
  ROBOTIKA 2020
  TEKNIK INFORMATIKA
*/

#include <Servo.h>

Servo myservo;    // create servo object to control a servo

int push1 = 2;
int push2 = 3;

int switch1 = 4;
int switch2 = 5;
int switch3 = 6;
int switch4 = 7;

int servoPin = 9;

int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);

  pinMode(push1, INPUT);
  pinMode(push2, INPUT);

  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (digitalRead(push1) == HIGH && digitalRead(push2) == HIGH && digitalRead(switch1) == LOW && digitalRead(switch2) == LOW && digitalRead(switch3) == LOW && digitalRead(switch4) == LOW) {
    myservo.write(0);
  } else if (digitalRead(push1) == HIGH && digitalRead(push2) == LOW && digitalRead(switch1) == HIGH && digitalRead(switch2) == LOW && digitalRead(switch3) == LOW && digitalRead(switch4) == LOW) {
    myservo.write(180);
  } else if (digitalRead(push1) == HIGH && digitalRead(push2) == LOW && digitalRead(switch1) == LOW && digitalRead(switch2) == HIGH && digitalRead(switch3) == LOW && digitalRead(switch4) == LOW) {
    myservo.write(135);
  } else if (digitalRead(push1) == HIGH && digitalRead(push2) == LOW && digitalRead(switch1) == LOW && digitalRead(switch2) == LOW && digitalRead(switch3) == HIGH && digitalRead(switch4) == LOW) {
    myservo.write(90);
  } else if (digitalRead(push1) == HIGH && digitalRead(push2) == LOW && digitalRead(switch1) == LOW && digitalRead(switch2) == LOW && digitalRead(switch3) == LOW && digitalRead(switch4) == HIGH) {
    myservo.write(45);
  } else if (digitalRead(push1) == LOW && digitalRead(push2) == HIGH && digitalRead(switch1) == HIGH && digitalRead(switch2) == LOW && digitalRead(switch3) == LOW && digitalRead(switch4) == LOW) {
    myservo.write(160);
  } else if (digitalRead(push1) == LOW && digitalRead(push2) == HIGH && digitalRead(switch1) == LOW && digitalRead(switch2) == HIGH && digitalRead(switch3) == LOW && digitalRead(switch4) == LOW) {
    myservo.write(115);
  } else if (digitalRead(push1) == LOW && digitalRead(push2) == HIGH && digitalRead(switch1) == LOW && digitalRead(switch2) == LOW && digitalRead(switch3) == HIGH && digitalRead(switch4) == LOW) {
    myservo.write(70);
  } else if (digitalRead(push1) == LOW && digitalRead(push2) == HIGH && digitalRead(switch1) == LOW && digitalRead(switch2) == LOW && digitalRead(switch3) == LOW && digitalRead(switch4) == HIGH) {
    myservo.write(25);
  }else{
    //blink LED
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
