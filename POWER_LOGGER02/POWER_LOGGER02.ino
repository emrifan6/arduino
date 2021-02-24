#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

File myFile;

DS3231  rtc(SDA, SCL);
Time  t;

int id = 0;
int mosfet = 2;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 20000;           // interval at which to blink (milliseconds)


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  uint32_t currentFrequency;
  Serial.println("MENJALANKAN INA219");
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  Serial.println("Bus Voltage(V), Current(A), Power(W), Shunt Voltage(mV), Load Voltage(V)");
  Serial.println(ina219print());

  Serial.println("MENJALANKAN RTC");
  Wire.begin();
  rtc.begin();
//  rtc.setTime(14, 31, 0);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(15, 2, 2021);   // Set the date to January 1st, 2014
  Serial.println(rtcprint());

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  pinMode(mosfet, OUTPUT);
  digitalWrite(mosfet, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();
   
  float voltbat = ina219.getBusVoltage_V()+0.25;
  if(voltbat <= 9.6){
    digitalWrite(mosfet, LOW);
    Serial.println("SELESAI");
    while(voltbat <= 9.6) { 
    };
  } else{
      if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      readaccu();
    }
  }  
  delay(1000);
}

void readaccu(){
  // make a string for assembling the data to log:
  String dataString = "";
  dataString += String(id);
  dataString += ",";
  float waktu = float(id)*20/60;
  dataString += String(waktu);
  dataString += ",";
  dataString += rtcprint();
  dataString += ina219print();
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    id++;
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

String ina219print(){
  
  float busvoltage = 0;
  float current_A = 0;
  float power_W = 0;
  float shuntvoltage = 0;
  float loadvoltage = 0;
  
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V()+0.25;
  current_A = ina219.getCurrent_mA()*2.96/1000;
  power_W = ina219.getPower_mW()*2.96/1000;
  loadvoltage = busvoltage + (shuntvoltage / 1000)-0.6;

  if(current_A <= 0.0){
    current_A = 0.0;
    power_W = 0.0;
    shuntvoltage = 0.0;
  }

  String dataINA219 = "";
  dataINA219 += String(busvoltage);
  dataINA219 += ",";
  dataINA219 += String(current_A);
  dataINA219 += ",";
  dataINA219 += String(power_W);
  dataINA219 += ",";
  dataINA219 += String(shuntvoltage);
  dataINA219 += ",";
  dataINA219 += String(loadvoltage);
  dataINA219 += ",";

  return dataINA219;
}

String rtcprint() {
  t = rtc.getTime();
  int Year = t.year;
  int Month = t.mon;
  int Date = t.date;
  int Hor = t.hour;
  int Min = t.min;
  int Sec = t.sec;

  // Send date over serial connection
//  Serial.print(Year);
//  Serial.print("-");
//  Serial.print(Month);
//  Serial.print("-");
//  Serial.print(Date);
//  Serial.print(",");
//
//  Serial.print(Hor);
//  Serial.print(":");
//  Serial.print(Min);
//  Serial.print(":");
//  Serial.println(Sec);
  String dataRTC = "";
  dataRTC += String(Year);
  dataRTC += "-";
  dataRTC += String(Month);
  dataRTC += "-";
  dataRTC += String(Date);
  dataRTC += ",";
  dataRTC += String(Hor);
  dataRTC += ":";
  dataRTC += String(Min);
  dataRTC += ":";
  dataRTC += String(Sec);
  dataRTC += ",";
  return dataRTC;
}
