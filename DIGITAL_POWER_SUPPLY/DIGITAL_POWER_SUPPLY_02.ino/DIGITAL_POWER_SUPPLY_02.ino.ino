/*
 * Example using the Rotary library, dumping integers to the serial
 * port. The integers increment or decrement depending on the direction
 * of rotation.
 *
 * This example uses polling rather than interrupts.
 */

#include <Rotary.h>
 #define Vout 3
 #define Iout 6

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 5 and 6.
Rotary rotary = Rotary(4, 5);



// Counter that will be incremented or decremented by rotation.
int counter = 0;



const int buttonPin = 7;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonStates = LOW;   // the previous reading from the input pin
 //the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTimes = 0;  // the last time the output pin was toggled
unsigned long debounceDelays = 50;    // the debounce time; increase if the output flickers
int V_pwm = 200;
int I_pwm = 40;
int pos = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 300;           // interval at which to blink (milliseconds)



int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 9940.0; // resistance of R1 (100K) -see text!
float R2 = 2697.0; // resistance of R2 (10K) - see text!
int value = 0;




void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  menu();
  analogWrite(Vout, V_pwm);
  analogWrite(Iout, I_pwm);
  Serial.print("Vpwm = ");
  Serial.print(V_pwm);
  Serial.print("\t");
  Serial.print("Ipwm = ");
  Serial.print(I_pwm);
  Serial.print("\t");
  Serial.print("Voltage = ");
  Serial.println(vin);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    voltage();
  }
  

  
  
  
}



void voltage(){ 
  int tmp=0;
  for (int x=0; x<=9; x++){
    value = analogRead(analogInput);
    tmp = tmp+value;
    delay(1);
  }
  value = tmp/10;
  tmp = 0;
  
   vout = (value * 5.0) / 1024.0; // see text
   vin = (vout / (R2/(R1+R2)))*0.966; 
   if (vin<0.09) {
      vin=0.0;//statement to quash undesired reading !
   } 
}





void menu() {
int x = btn();
 Serial.print("Menu = ");
 Serial.print(x);
 Serial.print("\t");
if(x == 0 ){
   V_pwm = rotari(V_pwm);
//  Serial.println(V_pwm);
 }else if (x == 1) {
    I_pwm = rotari(I_pwm);
//    Serial.println(I_pwm);
  }
}




int rotari (int x){
  counter = x;
  unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
    if (counter >= 255){
      counter=255;
    }
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    if (counter <= 0){
      counter=0;
    }
  }
  return counter;
}






 // AWAL FUNGSI BTN
int btn (){
 int reading = digitalRead(buttonPin);
 if (reading != lastButtonStates) {
    // reset the debouncing timer
    lastDebounceTimes = millis();
  }
  if ((millis() - lastDebounceTimes) > debounceDelays) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        pos++;
        if(pos >= 2){
          pos=0;
        }
      }
    }
  }
lastButtonStates = reading;
  return pos;
}
    // AKHIR FUNGSI BTN
