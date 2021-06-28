/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */

// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8

float V_set = 24.0;
float I_set = 0.3;

float V_read = 0.1;
float I_read = 0.4;
float W_read = 0.0;

String buff_text="";

char V_Printout[7];
char I_Printout[5];

char Vread_Printout[5];
char Iread_Printout[5];

char W_Printout[5];

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

unsigned long time;

void setup() {
  Serial.begin(9600);

  //initialize the library
  TFTscreen.begin();
  TFTscreen.setRotation(0);

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0); // B,G,R
  //set the text size
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Rifan", 95, 152);
  
}

void loop() {

  buff_text=String(V_set);
  buff_text.toCharArray(V_Printout, 5);
  TFTscreen.stroke(7, 193, 255);
  TFTscreen.rect(10,5,34,13);  
  TFTscreen.setTextSize(1);
  TFTscreen.text("V-SET", 12, 8);
  TFTscreen.setTextSize(2);
  TFTscreen.text(V_Printout, 55, 4);
  TFTscreen.setTextSize(2);
  TFTscreen.text("V", 110, 5);


  buff_text=String(I_set);
  buff_text.toCharArray(I_Printout, 5);
  TFTscreen.stroke(214, 188, 1);
  TFTscreen.rect(10,25,34,13);
  TFTscreen.setTextSize(1);
  TFTscreen.text("I-SET", 12, 28);
  TFTscreen.setTextSize(2);
  TFTscreen.text(I_Printout, 55, 24);
  TFTscreen.setTextSize(2);
  TFTscreen.text("A", 110, 25);


  if(V_read < 1.0) {
    int x = V_read * 1000.0 ;
    buff_text=String(x);
    buff_text.toCharArray(Vread_Printout, 5);
    TFTscreen.stroke(7, 193, 255);  //KUNING
    TFTscreen.setTextSize(3);
    TFTscreen.text(Vread_Printout, 20, 55);
    TFTscreen.text("mV", 85, 55);
  } else if(V_read >= 1.0){
    buff_text=String(V_read);
    buff_text.toCharArray(Vread_Printout, 5);
    TFTscreen.stroke(7, 193, 255);  //KUNING
    TFTscreen.setTextSize(3);
    TFTscreen.text(Vread_Printout, 20, 55);
    TFTscreen.text("V", 95, 55);
  }
 

  
  if( I_read < 1.0 ) {
    int y = I_read * 1000;
    buff_text=String(y);
    buff_text.toCharArray(Iread_Printout, 5);
    TFTscreen.stroke(214, 188, 1);  //BIRU
    TFTscreen.setTextSize(3);
    TFTscreen.text(Iread_Printout, 20, 85);
    TFTscreen.text("mA", 85, 85);
  } else if(I_read >= 1.0) {
    buff_text=String(I_read);
    buff_text.toCharArray(Iread_Printout, 5);
    TFTscreen.stroke(214, 188, 1);  //BIRU
    TFTscreen.setTextSize(3);
    TFTscreen.text(Iread_Printout, 20, 85);
    TFTscreen.text("A", 95, 85);
  }
   



   W_read = V_read * I_read;
   
  if(W_read < 1){
    int z = W_read * 1000;
    buff_text=String(z);
    buff_text.toCharArray(W_Printout, 3);  
    TFTscreen.stroke(176, 48, 176);  //UNGU rgb(176,48,176)
    TFTscreen.setTextSize(3);
    TFTscreen.text(W_Printout, 20, 115);
    TFTscreen.text("mW", 85, 115);
  } else if (W_read >= 1){
    buff_text=String(W_read);
    buff_text.toCharArray(W_Printout, 4);  
    TFTscreen.stroke(176, 48, 176);  //UNGU rgb(176,48,176)
    TFTscreen.setTextSize(3);
    TFTscreen.text(W_Printout, 20, 115);
    TFTscreen.text("W", 95, 115);
  }

  TFTscreen.stroke(255, 108, 0); //  rgb(255,108,0)
  TFTscreen.rect(12,50,112,95); 

  

    //  CLEAR DISPLAY
  delay(5000);
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.text(V_Printout, 55, 4);
  TFTscreen.text(I_Printout, 55, 24);
  TFTscreen.setTextSize(3);
  TFTscreen.text(Vread_Printout, 20, 55);
  TFTscreen.text(Iread_Printout, 20, 85);
  TFTscreen.text("mV", 85, 55);
  TFTscreen.text("V", 95, 55);
  TFTscreen.text("mA", 85, 85);
  TFTscreen.text("A", 95, 85);
  TFTscreen.text("mW", 85, 115);
  TFTscreen.text("W", 95, 115);
  TFTscreen.text(W_Printout, 20, 115);

    V_read = V_read + 0.1; 
    I_read = I_read + 0.05;
    I_set = I_set + 0.05;    
}
