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

//int counter = 0;

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
//  rtc.setTime(17, 31, 00);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(25, 5, 2021);   // Set the date to January 1st, 2014
  delay(1000);
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
//  Beri_pakan();
}

void loop() {
//  counter = counter + 1;
//    Serial.println(counter);
//    Beri_pakan();
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;
  Serial.print(Hor);
  Serial.print(":");
  Serial.print(Min);
  Serial.print(":");
  Serial.println(Sec);

  if ( Hor == JamPakanPagi &&  Min == MenitPakanPagi) {
    Serial.println("WAKTU PEMBERIAN PAKAN PAGI");
    Beri_pakan();
  }else if( Hor == JamPakanSiang &&  Min == MenitPakanSiang){
    Serial.println("WAKTU PEMBERIAN PAKAN SIANG");
    Beri_pakan();
  }else if( Hor == JamPakanSore &&  Min == MenitPakanSore){
    Serial.println("WAKTU PEMBERIAN PAKAN SORE");
    Beri_pakan();
  }else{
    
  }
  delay(5000);
}

void Beri_pakan(){
  buzz();
  delay(500);
  buzz();
  delay(700);
  buzz();
//  analogWrite(MotorPin, 75);
  myservo.write(50);
  delay(300);
  myservo.write(0);
//  delay(30000);
//  myservo.write(50);
//  delay(300);
//  myservo.write(0);
  analogWrite(MotorPin, LOW);
}

void buzz() {
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
}
