#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);
/* for normal hardware wire use above */

void setup ()
{
    Serial.begin(9600);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
   
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    if (!Rtc.IsDateTimeValid())
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }
    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled)
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled)
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
    Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);
}
void loop ()
{
    if (!Rtc.IsDateTimeValid())
    {
        Serial.println("RTC lost confidence in the DateTime!");
    }
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    delay(1000);
}
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    Serial.print(dt.Day());
    Serial.print("/");
    Serial.print(dt.Month());
    Serial.print("/");
    Serial.println(dt.Year());
    Serial.print(dt.Hour());
    Serial.print(":");
    Serial.print(dt.Minute());
    Serial.print(":");
    Serial.println(dt.Second());
}
