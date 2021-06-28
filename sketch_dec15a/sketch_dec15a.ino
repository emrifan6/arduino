/*
  Arduino TFT text example

  This example demonstrates how to draw text on the
  TFT with an Arduino. The Arduino reads the value
  of an analog sensor attached to pin A0, and writes
  the value to the LCD screen, updating every
  quarter second.

  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald

  http://www.arduino.cc/en/Tutorial/TFTDisplayText

*/

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// pin definition for the Leonardo
// #define cs   7
// #define dc   0

// #define rst  1

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print to the screen
char sensorPrintout[4];

int pompa_air = 7;
int sensor = A0;

void setup() {
  pinMode(pompa_air, OUTPUT);
  digitalWrite(pompa_air, LOW);

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  TFTscreen.background(0, 0, 0);
  // set the stroke color to white
  TFTscreen.stroke(3, 117, 247); // blue,green,red
  TFTscreen.fill(3, 117, 247);
  TFTscreen.rect(0, 0, 109, 59);
  TFTscreen.stroke(6, 97, 5); // blue,green,red
  TFTscreen.fill(6, 97, 5);
  TFTscreen.rect(0, 59, 109, 70);

  TFTscreen.stroke(132, 97, 5); // blue,green,red
  TFTscreen.fill(132, 127, 0);
  TFTscreen.rect(111, 0, 49, 128);




  //  // clear the screen with a black background
  //  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(1);
  // write the text to the top left corner of the screen
  TFTscreen.text("KELEMBABAN TANAH", 10, 5);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(4);
  TFTscreen.text("%", 70, 20);

  TFTscreen.setTextSize(1);
  // write the text to the top left corner of the screen
  TFTscreen.text("ATUR PENYIRAMAN", 7, 65);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(4);
  TFTscreen.text("50%", 20, 80);


  TFTscreen.setTextSize(1);
  // write the text to the top left corner of the screen
  TFTscreen.text("STATUS", 120, 30);
  TFTscreen.text("POMPA", 123, 40);
  TFTscreen.text("AIR", 127, 50);
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
  TFTscreen.text("0FF", 120, 80);
  // draw a diagonal line across the screen's center
  TFTscreen.line(110, 0, 110, 155);
  TFTscreen.line(0, 60, 110, 60);



  TFTscreen.setTextSize(4);

}

void loop() {
  int baca_sensor = analogRead(sensor);
  baca_sensor = map(baca_sensor, 450, 850, 100, 0);

  // Read the value of the sensor on A0
  String sensorVal = String(baca_sensor);
  // convert the reading to a char array
  sensorVal.toCharArray(sensorPrintout, 4);
  TFTscreen.setTextSize(4);
  // set the font color
  TFTscreen.stroke(255, 255, 255);
  // print the sensor value
  TFTscreen.text(sensorPrintout, 15, 20);
  // wait for a moment
  delay(250);

  if (baca_sensor <= 50) {
    digitalWrite(pompa_air, HIGH);
    TFTscreen.setTextSize(2);
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text("0FF", 120, 80);
    TFTscreen.stroke(32, 24, 255); // blue,green,red
    TFTscreen.fill(32, 24, 255);
    TFTscreen.rect(111, 61, 49, 67);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("ON", 125, 80);
    delay(5000);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text("ON", 125, 80);
    TFTscreen.stroke(132, 127, 0); // blue,green,red
    TFTscreen.fill(132, 127, 0);
    TFTscreen.rect(111, 61, 49, 67);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("0FF", 120, 80);
    digitalWrite(pompa_air, LOW);
  }

// erase the text you just wrote
    TFTscreen.setTextSize(4);
    TFTscreen.stroke(3, 117, 247);
    TFTscreen.text(sensorPrintout, 15, 20);

}
