#include <blinkSeq.h>
#define LED_PIN 12
#define LED_ON_LOW 1

BlinkerSeq ledInternal(4); // blink LED pin 4, sourcing current (active high).
BlinkerSeq ledMonitor(LED_PIN,LED_ON_LOW); // blinking pin LED_PIN, shinking current (active low).

void setup(){
  ledMonitor.set(100,200,2,2000); // on 100ms, off 200ms, 2 blink, delay 2000ms between 2 blink
  ledInternal.set(100,200,5,2000); // on 100ms, off 200ms, 5 blink, delay 2000ms between 5 blink
  delay(1000);
  yield;
  ledMonitor.set(100,200,1,2000);
  yield;
  delay(15000);
  ledMonitor.stop(); // stop it
  delay(15000);
  ledMonitor.set(100,200,1,2000);
}
void loop(){
 // nothing to do
}
