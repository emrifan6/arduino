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
float counter = 0.0;



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
float V_read = 0.0;
float R1 = 9940.0; // resistance of R1 (100K) -see text!
float R2 = 2697.0; // resistance of R2 (10K) - see text!
int value = 0;
float V_set = 5.0;


int analogInput01 = 1;
float V_iout = 0.0;
float I_read = 0.0;
int I_value = 0;
float I_set = 1.0;


void setup() {
  Serial.begin(250000);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  menu();
  analogWrite(Vout, V_pwm);
  analogWrite(Iout, I_pwm);
  Serial.print("Vset = ");
  Serial.print(V_set);
  Serial.print("\t");
  Serial.print("Iset = ");
  Serial.print(I_set);
  Serial.print("\t");
  Serial.print("Voltage = ");
  Serial.print(V_read);
  Serial.print("\t");
  Serial.print("Current = ");
  Serial.print(I_read);
  Serial.println("\t");
 // CC();

  

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
    current();
  }
 
}




void CC(){
  if (I_read >= I_set){
    V_pwm = 255-(((V_read*I_set)/I_read)/0.11)-10;
  }


  
//  if (I_read <= (I_set)){ 
//    if (V_read <= (V_set-0.2)){
//      V_pwm = V_pwm - (((V_set-V_read)/0.11));
//    } else if (V_read >= (V_set+0.2)){
//      V_pwm = V_pwm + (((V_read-V_set)/0.11));
//    }
//   }
}




void current(){
  int tmp=0;
  for (int x=0; x<=4; x++){
    I_value = analogRead(analogInput01);
    tmp = tmp+I_value;
    delay(1);
  }
  I_value = tmp/5;
  tmp=0;
  
  V_iout = (I_value * 5.0) / 1024.0; // see text
  if (V_iout <= 55) {
    I_read =  (V_iout / 22)/0.05;
  } else if(V_iout >= 55 ){
    I_read =  (V_iout / 21)/0.05;
  } else if (V_iout >= 78) {
    I_read =  (V_iout / 20.6)/0.05;
  } else if (V_iout >= 103) {
    I_read =  (V_iout / 20)/0.05;
  } else if (V_iout >= 150) {
    I_read =  (V_iout / 19.6)/0.05;
  } else if (V_iout >= 196) {
    I_read =  (V_iout / 19.33)/0.05;
  } else if (V_iout >= 290) {
    I_read =  (V_iout / 19.2)/0.05;
  } else if (V_iout >= 384) {
    I_read =  (V_iout / 19.12)/0.05;
  } else if (V_iout >= 478) {
    I_read =  (V_iout / 19.06)/0.05;
  } else if (V_iout >= 572) {
    I_read =  (V_iout / 19.02)/0.05;
  }
}



void set_I(){
  I_set = I_rotari(I_set);
  I_pwm = (I_set/0.0196)*0.685;
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
   V_read = (vout / (R2/(R1+R2)))*0.9; 
   if (V_read<0.09) {
      V_read=0.0;//statement to quash undesired reading !
   } 
}

void set_V(){
  V_set = rotari(V_set);
  V_pwm = 255-(V_set/0.11)-13;
}




void menu() {
int x = btn();
 Serial.print("Menu = ");
 Serial.print(x);
 Serial.print("\t");
if(x == 0 ){
   set_V();
 }else if (x == 1) {
    set_I();
  }
}





float I_rotari (float x){
  float I_counter = x;
  unsigned char result = rotary.process();
  if (result == DIR_CW) {
    I_counter = I_counter + 0.05;
    if (I_counter >= 5.0){
      I_counter=5.0;
    }
  } else if (result == DIR_CCW) {
    I_counter = I_counter - 0.05;
    if (I_counter <= 0.0){
      I_counter=0.0;
    }
  }
  return I_counter;
}




float rotari (float x){
  counter = x;
  unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter = counter + 0.1;
    if (counter >= 23.0){
      counter=23;
    }
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter = counter - 0.1;
    if (counter <= 0.0){
      counter=0.0;
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
