#include <Wire.h>
#include "LedControl.h"

/*  pin 12 is connected to the DataIn 
    pin 11 is connected to the CLK 
    pin 10 is connected to LOAD 
    We have only a single MAX72XX. */
LedControl lc=LedControl( D5,D6,D7,1);

void setup () {

/*  The MAX72XX is in power-saving mode on startup,
      we have to do a wakeup call */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,6);
  /* and clear the display */
  lc.clearDisplay(0); 


  Serial.begin(9600);

}
  
void loop () {
  
  lc.setDigit(0,0,1,false);
  lc.setDigit(0,1,2,false);
  lc.setChar(0,2,'-',false);
  lc.setDigit(0,3,3,false);
  lc.setDigit(0,4,4,false);
  lc.setChar(0,5,'-',false);
  lc.setDigit(0,6,5,false);
  lc.setDigit(0,7,6,false);

}
