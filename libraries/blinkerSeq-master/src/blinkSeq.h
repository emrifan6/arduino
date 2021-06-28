/*
 * BLINKER Sequential
 * Fahrizal Hari Utama
 * Monday Kliwon [2019.07.29]
 */
#ifndef blinkerSeq_h
#define blinkerSeq_h
#if defined(ESP8266)


#include <Arduino.h>
#include <Ticker.h>


class BlinkerSeq {
  private:
  Ticker LEDticker;
  uint8_t _pinLED;
  bool _ledOn ;
  bool _ledActiveLow;
  uint16_t _ledOnMs;
  uint16_t _ledOffMs;
  uint8_t _ledSeq;
  uint8_t _ledSeqCounter;
  uint16_t _ledOffAfter;
  void _tick();
  void _reset();
 
  public:
  BlinkerSeq(uint8_t pinLED, bool _ledActiveLow = false);
  void set( uint16_t ledOnMs,uint16_t ledOffMs,uint8_t ledSeq,uint16_t ledOffAfter);
  void stop();
  void alwaysOn();
};
#else
#error “Unsupported board selected!”
#error "ESP8266 Only, Sorry"
#endif
#endif
