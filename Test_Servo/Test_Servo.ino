/*
 * Control a servo motor with Visual Basic 
 * Created by Rui Santos, https://randomnerdtutorials.com
*/
 
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
void setup() 
{ 
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  Serial.begin(9600); //begins serial communication
} 

  
void loop() 
{ 
  delay(5000);
  myservo.write(50);
  delay(200);
  myservo.write(0);
  delay(60000);
  myservo.write(50);
  delay(200);
  myservo.write(0);
}
