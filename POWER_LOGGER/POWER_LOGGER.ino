#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

File myFile;

DS3231  rtc(SDA, SCL);
Time  t;

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
  Serial.println(rtcprint());

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

String ina219print(){
  
  float busvoltage = 0;
  float current_A = 0;
  float power_W = 0;
  float shuntvoltage = 0;
  float loadvoltage = 0;
  
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_A = ina219.getCurrent_mA()/1000;
  power_W = ina219.getPower_mW()/1000;
  loadvoltage = busvoltage + (shuntvoltage / 1000);

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


void loop() {
  // make a string for assembling the data to log:
  String dataString = "";
  dataString += rtcprint();
  dataString += ina219print();
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
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
