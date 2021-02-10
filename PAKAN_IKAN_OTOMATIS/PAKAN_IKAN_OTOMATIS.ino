#include <DS3231.h>
#include <Wire.h>
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
DS3231  rtc(SDA, SCL);
Time  t;
#define buz 11
int Hor;
int Min;
int Sec;

int MotorPin = 10;

int JamPakanPagi = 6;
int MenitPakanPagi = 0;

int JamPakanSore = 17;
int MenitPakanSore = 0;


void setup() {
  analogWrite(MotorPin, LOW);
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  Wire.begin();
  rtc.begin();
  Serial.begin(9600);
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
//  rtc.setTime(22, 41, 10);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(5, 2, 2021);   // Set the date to January 1st, 2014
  delay(1000);
  Serial.print("WAKTU PEMBERIAN PAKAN PAGI : ");
  Serial.print(JamPakanPagi);
  Serial.print(":");
  Serial.println(MenitPakanPagi);
  Serial.print("WAKTU PEMBERIAN PAKAN SORE : ");
  Serial.print(JamPakanSore);
  Serial.print(":");
  Serial.println(MenitPakanSore);
}

void loop() {
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
  }else if( Hor == JamPakanSore &&  Min == MenitPakanSore){
    Serial.println("WAKTU PEMBERIAN PAKAN SORE");
    Beri_pakan();
  }else{
    
  }
  delay(5000);
}

void Beri_pakan(){
  analogWrite(MotorPin, 75);
  myservo.write(50);
  delay(300);
  myservo.write(0);
  delay(60000);
  myservo.write(50);
  delay(300);
  myservo.write(0);
  analogWrite(MotorPin, LOW);
}
