/*
  TUGAS 89
  MUCHAMAD RIF'AN
  17.01.53.2021
  ROBOTIKA 2020
  TEKNIK INFORMATIKA
*/

#include <Servo.h>

Servo myservo;    // create servo object to control a servo

int push1Pin = 2;
int push2Pin = 3;

int switch1Pin = 4;
int switch2Pin = 5;
int switch3Pin = 6;
int switch4Pin = 7;

int servoPin = 9;
int pos = 0;

int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);

  pinMode(push1Pin, INPUT);
  pinMode(push2Pin, INPUT);

  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);



}


void loop() {
  // put your main code here, to run repeatedly:
  cekInput();
  myservo.write(pos);
}





void cekInput() {
  int push1 = digitalRead(push1Pin);
  int push2 = digitalRead(push2Pin);
  int switch1 = digitalRead(switch1Pin);
  int switch2 = digitalRead(switch2Pin);
  int switch3 = digitalRead(switch3Pin);
  int switch4 = digitalRead(switch4Pin);

  if (push1 == HIGH) {
    if (push2 == HIGH && switch1 == LOW && switch2 == LOW && switch3 == LOW && switch4 == LOW) {
      pos = 0;
    } else if (push2 == LOW) {
      if (switch1 == HIGH && switch2 == LOW && switch3 == LOW && switch4 == LOW) {
        pos = 180;
      } else if (switch1 == LOW && switch2 == HIGH && switch3 == LOW && switch4 == LOW) {
        pos = 135;
      } else if (switch1 == LOW && switch2 == LOW && switch3 == HIGH && switch4 == LOW) {
        pos = 90;
      } else if (switch1 == LOW && switch2 == LOW && switch3 == LOW && switch4 == HIGH) {
        pos = 45;
      } else {
        blinkLed();
      }
    }
  } else if (push2 == HIGH) {
    if (switch1 == HIGH && switch2 == LOW && switch3 == LOW && switch4 == LOW) {
      pos = 160;
    } else if (switch1 == LOW && switch2 == HIGH && switch3 == LOW && switch4 == LOW) {
      pos = 115;
    } else if (switch1 == LOW && switch2 == LOW && switch3 == HIGH && switch4 == LOW) {
      pos = 70;
    } else if (switch1 == LOW && switch2 == LOW && switch3 == LOW && switch4 == HIGH) {
      pos = 25;
    } else {
      blinkLed();
    }
  } else {
    blinkLed();
  }
}

void blinkLed() {
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                  // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                  // wait for a second
}
