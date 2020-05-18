#include <TFT.h>  
#include <SPI.h>

#include <ResponsiveAnalogRead.h>
#include <Rotary.h>

#define Vout 3
#define Iout 6

#define cs   10
#define dc   9
#define rst  8

Rotary rotary = Rotary(4, 5);

float counter = 0.0;

const int buttonPin = 7;    
const int ledPin = 13;      

int ledState = HIGH;         
int buttonState;             
int lastButtonStates = LOW;   

unsigned long lastDebounceTimes = 0; 
unsigned long debounceDelays = 50;   
int V_pwm = 200;
int I_pwm = 40;
int pos = 0;

//unsigned long previousMillis = 0;      
//const long interval = 300;  

float vout = 0.0;
float V_read = 0.0;
float R1 = 9940.0; 
float R2 = 2697.0; 
int value = 0;
float V_set = 5.0;

int analogInput01 = 1;
float V_iout = 0.0;
float I_read = 0.0;
int I_value = 0;
float I_set = 2.0;

ResponsiveAnalogRead analogOne(A0, true);
ResponsiveAnalogRead analogTwo(A1, true);


float V_Dset = V_set;
float I_Dset = I_set;
float last_V_Dset = 0.0;
float last_I_Dset = 0.0;

float V_Dread = V_read;
float I_Dread = I_read;
float W_Dread = V_read*I_read;
float last_V_Dread = 100;
float last_I_Dread = 100;
float last_W_Dread = 100;

String buff_text="";

char V_Printout[7];
char I_Printout[5];

char Vread_Printout[5];
char Iread_Printout[5];
char W_Printout[5];

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);


void setup() {
  Serial.begin(250000);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
 
  digitalWrite(ledPin, ledState);
  
  delay(1000);

  TFTscreen.begin();
  TFTscreen.setRotation(2);
  TFTscreen.background(0, 0, 0); 
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(176, 48, 176);  //UNGU rgb(176,48,176)
  TFTscreen.text("TESTTT", 20, 115);
  delay(3000);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.text("TESTTT", 20, 115);
  TFTscreen.stroke(0, 0, 255); //  rgb(236,29,36)
  TFTscreen.rect(12,50,112,95); 

  TFTscreen.stroke(7, 193, 255);
  TFTscreen.rect(10,5,34,13);  
  TFTscreen.setTextSize(1);
  TFTscreen.text("V-SET", 12, 8);
  TFTscreen.setTextSize(2);
  TFTscreen.text("V", 110, 5);

  TFTscreen.stroke(214, 188, 1);
  TFTscreen.rect(10,25,34,13);
  TFTscreen.setTextSize(1);
  TFTscreen.text("I-SET", 12, 28);
  TFTscreen.setTextSize(2);
  TFTscreen.text("A", 110, 25);
  
}

void loop() {
  analogOne.update();
  analogTwo.update();
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
  Serial.print("\t");
  Serial.print("PWM = ");
  Serial.print(V_iout);
  Serial.println("\t");
  voltage();
  current();



 V_Dset = V_set;
 I_Dset = I_set;
 V_Dread = V_read;
 I_Dread = I_read;
 W_Dread = V_Dread * I_Dread;

  disp_vset(V_Dset);
  disp_iset(I_Dset);
  disp_vread(V_Dread);
  disp_iread(I_Dread);
  disp_wread(W_Dread);

  last_V_Dset = V_Dset;
  last_I_Dset = I_Dset;
  last_V_Dread = V_Dread;
  last_I_Dread = I_Dread;
  last_W_Dread = W_Dread;

//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
//  }
// I_set = I_set+0.1;
}





// Awal fungsi Display

void disp_wread(float i) {

  if ( i != last_W_Dread) {
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.setTextSize(3);
    TFTscreen.text(W_Printout, 20, 115);
    TFTscreen.text("mW", 85, 115);
    TFTscreen.text("W", 100, 115);
      
    if(W_Dread < 1){
      int z = i * 1000;
      buff_text=String(z);
      buff_text.toCharArray(W_Printout, 3);  
      TFTscreen.stroke(176, 48, 176);  //UNGU rgb(176,48,176)
      TFTscreen.setTextSize(3);
      TFTscreen.text(W_Printout, 20, 115);
      TFTscreen.text("mW", 85, 115);
    } else if (W_Dread >= 1){
      buff_text=String(i);
      buff_text.toCharArray(W_Printout, 5);  
      TFTscreen.stroke(176, 48, 176);  //UNGU rgb(176,48,176)
      TFTscreen.setTextSize(3);
      TFTscreen.text(W_Printout, 20, 115);
      TFTscreen.text("W", 100, 115);
    }
  }
}



void disp_iread(float i){

  if( i != last_I_Dread) {
 
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.setTextSize(3);
    TFTscreen.text(Iread_Printout, 20, 85);
    TFTscreen.text("mA", 85, 85);
    TFTscreen.text("A", 100, 85);
     
    if( I_Dread < 1.0 ) {
      int y = i * 1000;
      buff_text=String(y);
      buff_text.toCharArray(Iread_Printout, 5);
      TFTscreen.stroke(214, 188, 1);  //BIRU
      TFTscreen.setTextSize(3);
      TFTscreen.text(Iread_Printout, 20, 85);
      TFTscreen.text("mA", 85, 85);
    } else if(I_Dread >= 1.0) {
      buff_text=String(i);
      buff_text.toCharArray(Iread_Printout, 5);
      TFTscreen.stroke(214, 188, 1);  //BIRU
      TFTscreen.setTextSize(3);
      TFTscreen.text(Iread_Printout, 20, 85);
      TFTscreen.text("A", 100, 85);
    }
  }
}


void disp_vread(float i){
  
  if (i != last_V_Dread) {
  
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.setTextSize(3);
    TFTscreen.text(Vread_Printout, 20, 55);
    TFTscreen.text("mV", 85, 55);
    TFTscreen.text("V", 100, 55);
    
    if(i < 1.0) {
      int x = i * 1000.0 ;
      buff_text=String(x);
      buff_text.toCharArray(Vread_Printout, 5);
      TFTscreen.stroke(7, 193, 255);  //KUNING
      TFTscreen.setTextSize(3);
      TFTscreen.text(Vread_Printout, 20, 55);
      TFTscreen.text("mV", 85, 55);
    } else if(last_V_Dread >= 1.0){
      buff_text=String(i);
      buff_text.toCharArray(Vread_Printout, 5);
      TFTscreen.stroke(7, 193, 255);  //KUNING
      TFTscreen.setTextSize(3);
      TFTscreen.text(Vread_Printout, 20, 55);
      TFTscreen.text("V", 100, 55);
    }
  }
}


void disp_iset(float x){

  if(x != last_I_Dset) {

    TFTscreen.setTextSize(2);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(I_Printout, 55, 24);
    
    buff_text=String(x);
    buff_text.toCharArray(I_Printout, 5);
    TFTscreen.stroke(214, 188, 1);
    TFTscreen.setTextSize(2);
    TFTscreen.text(I_Printout, 55, 24);
    
  }
}


void disp_vset(float x){
  if(x != last_V_Dset) {
      TFTscreen.setTextSize(2);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.text(V_Printout, 55, 4);
      
      buff_text=String(x);
      buff_text.toCharArray(V_Printout, 5);
      
      TFTscreen.setTextSize(2);
      TFTscreen.stroke(7, 193, 255);
      TFTscreen.text(V_Printout, 55, 4);
  }
}

// Akhir fungsi Display


void current(){
  int tmp=0;
  I_value = analogTwo.getValue();
  tmp=0; 
  V_iout = I_value * (5.0 / 1024.0); 
  if(V_iout <= 0.34){
  I_read =  ((V_iout / 19)/0.05)*0.8043; 
  } 
  else if (V_iout <= 0.5) {
  I_read =  ((V_iout / 19)/0.05)*0.848;
  }
  else if (V_iout <= 0.7) {
  I_read =  ((V_iout / 19)/0.05)*0.86;
  }
  else if (V_iout <= 0.9) {
  I_read =  ((V_iout / 19)/0.05)*0.865;
  } 
  else if (V_iout <= 1.1) {
  I_read =  ((V_iout / 19)/0.05)*0.87;
  }
  else if (V_iout <= 1.3) {
  I_read =  ((V_iout / 19)/0.05)*0.87;
  } else {
    I_read =  ((V_iout / 19)/0.05)*0.88;
  }
}



void set_I(){
  I_set = I_rotari(I_set);
  I_pwm = (I_set/0.0196)*0.685;
}



void voltage(){ 
  int tmp=0;
  value = analogOne.getValue();
  tmp = 0;
   vout = (value * 5.0) / 1024.0; // see text
   V_read = (vout / (R2/(R1+R2)))*0.9275; 
   if (V_read<0.09) {
      V_read=0.0;//statement to quash undesired reading !
   } 
}


void set_V(){
  V_set = rotari(V_set);
  V_pwm = (255-(V_set/0.11))-6;
}


void menu() {
int x = btn();
 Serial.print("Menu = ");
 Serial.print(x);
 Serial.print("\t");
if(x == 0 ){
    set_I();
 }else if (x == 1) {
    set_V();
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


int btn (){
 int reading = digitalRead(buttonPin);
 if (reading != lastButtonStates) {
    // reset the debouncing timer
    lastDebounceTimes = millis();
  }
  if ((millis() - lastDebounceTimes) > debounceDelays) {
    if (reading != buttonState) {
      buttonState = reading;
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
