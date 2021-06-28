#include <DS3231.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
DS3231  rtc(SDA, SCL);
Time  t;
#define buzzer 4
int Hor;
int Min;
int Sec;

int MotorPin = 10;

int JamPakanPagi = 6;
int MenitPakanPagi = 0;

int JamPakanSiang = 12;
int MenitPakanSiang = 0;

int JamPakanSore = 17;
int MenitPakanSore = 0;

int pakan_sensor = A0;
int limit_pakan_sensor = 700;
//(jika nilai sensor pakan lebih dari 700 berarti pakan habis/macet)

//millis
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
int detik_cekpakan = 0;
int detik_pakan = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  analogWrite(MotorPin, LOW);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  delay(200);
  myservo.write(0);
  delay(200);
  myservo.write(0);
  Wire.begin();
  rtc.begin();
  Serial.begin(9600);
  //   The following lines can be uncommented to set the date and time
  //  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(18, 25, 00);     // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(25, 5, 2021);   // Set the date to January 1st, 2014
  delay(1000);
  rtc_time();
  Serial.print("WAKTU PEMBERIAN PAKAN PAGI  : ");
  Serial.print(JamPakanPagi);
  Serial.print(":");
  Serial.println(MenitPakanPagi);
  Serial.print("WAKTU PEMBERIAN PAKAN SIANG : ");
  Serial.print(JamPakanSiang);
  Serial.print(":");
  Serial.println(MenitPakanSiang);
  Serial.print("WAKTU PEMBERIAN PAKAN SORE  : ");
  Serial.print(JamPakanSore);
  Serial.print(":");
  Serial.println(MenitPakanSore);
}

void loop() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    if (++detik_cekpakan >= 3600) {
      cek_pakan();
      detik_cekpakan = 0;
    }
    if (++detik_pakan >= 60) {
      rtc_time();
      if ( Hor == JamPakanPagi &&  Min == MenitPakanPagi) {
        Serial.println("WAKTU PEMBERIAN PAKAN PAGI");
        Beri_pakan();
      } else if ( Hor == JamPakanSiang &&  Min == MenitPakanSiang) {
        Serial.println("WAKTU PEMBERIAN PAKAN SIANG");
        Beri_pakan();
      } else if ( Hor == JamPakanSore &&  Min == MenitPakanSore) {
        Serial.println("WAKTU PEMBERIAN PAKAN SORE");
        Beri_pakan();
      } else {
      }
      detik_pakan = 0;
    }
  }
}

void cek_pakan() {
  int sensor = analogRead(pakan_sensor);
  Serial.print('Cek Pakan = ');
  Serial.print(sensor);
  if (sensor <= limit_pakan_sensor && sensor >= 100) {
    Serial.println(' PAKAN HABIS');
    buzz_pakan();
  }else{
   Serial.println(' PAKAN MASIH');
  }
  Serial.println();
}

void rtc_time() {
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;
  Serial.print(Hor);
  Serial.print(":");
  Serial.print(Min);
  Serial.print(":");
  Serial.println(Sec);
  Serial.println();
}

void Beri_pakan() {
  buzz();
  delay(500);
  buzz();
  delay(700);
  buzz();
  analogWrite(MotorPin, 75);
  myservo.write(50);
  delay(700);
  myservo.write(0);
  buzz();
  delay(500);
  buzz();
  cek_pakan();
  analogWrite(MotorPin, LOW);
//  delay(60000);
}

void buzz_pakan() {
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
}


void buzz() {
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
}
