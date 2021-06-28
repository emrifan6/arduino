/*
 * BLINKER CLASS DEFINITION
 */
#include <blinkSeq.h>

    BlinkerSeq::BlinkerSeq(uint8_t pinLED, bool ledActiveLow) {
    _pinLED = pinLED;
    _ledActiveLow =ledActiveLow;
    pinMode(_pinLED, OUTPUT);
    digitalWrite(_pinLED, _ledActiveLow);
    }
   
  void BlinkerSeq::set( uint16_t ledOnMs,uint16_t ledOffMs,uint8_t ledSeq,uint16_t ledOffAfter){
    if (_ledOnMs==ledOnMs&&_ledOffMs==ledOffMs&&_ledSeq==ledSeq&&_ledOffAfter==ledOffAfter) return;
    _ledOnMs = ledOnMs;
    _ledOffMs = ledOffMs;
    _ledSeq = ledSeq;
    if (ledSeq>1) _ledSeqCounter = ledSeq+1;
    else _ledSeqCounter = ledSeq;
    _ledOffAfter = ledOffAfter;
    LEDticker.attach_ms(100,std::bind(&BlinkerSeq::_tick, this));
  }

  void BlinkerSeq::stop(){
      LEDticker.detach();
      digitalWrite(_pinLED,_ledActiveLow);
      _reset();
  }
  void BlinkerSeq::alwaysOn(){
      LEDticker.detach();
      digitalWrite(_pinLED,!_ledActiveLow);
      _reset();
  }

  void BlinkerSeq::_reset(){
      _ledOnMs=0;
      _ledOffMs=0;
      _ledSeq=0;
      _ledOffAfter=0;
  }
  void BlinkerSeq::_tick(){
    if(_ledSeqCounter){
        if (_ledOn){
            digitalWrite(_pinLED, !_ledActiveLow); // On LED
            LEDticker.attach_ms(_ledOnMs, std::bind(&BlinkerSeq::_tick, this));
            _ledOn = !_ledOn;
        } else{
            digitalWrite(_pinLED, _ledActiveLow); // Off LED
            LEDticker.attach_ms(_ledOffMs, std::bind(&BlinkerSeq::_tick, this));
            _ledOn = !_ledOn;
            _ledSeqCounter--;
            if(!_ledSeqCounter){
                LEDticker.attach_ms(_ledOffAfter, std::bind(&BlinkerSeq::_tick, this));
            }
        }
    }else{
        LEDticker.attach_ms(1,std::bind(&BlinkerSeq::_tick, this));
        _ledSeqCounter = _ledSeq;
    }
  }
