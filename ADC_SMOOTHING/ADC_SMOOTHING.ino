int adc01 = A0;
int adc02 = A1;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
}


void loop() {
  Serial.println("\t READ A0");
  float voltageA0 = smooth(adc01) * (5.0 / 1023.0);
  Serial.print("Tegangan A0= \t");
  Serial.println(voltageA0-0.11);
  Serial.println("====================");
  delay(1000);

  

  Serial.println("\t READ A1");
  float voltageA1 = smooth(adc02) * (5.0 / 1023.0);
  Serial.print("Tegangan A1= \t");
  Serial.println(voltageA1-0.11);
  Serial.println("====================");
  delay(1000);



  Serial.println("*********************");
}






int smooth(int pin) {
  const int numReadings = 20;
  int readings[numReadings];      // the readings from the analog input
  int readIndex = 0;              // the index of the current reading
  int total = 0;                  // the running total
  int average = 0;                // the average
  int inputPin = pin;
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // mulai mengambil beberapa data
  for (int i=0; i<numReadings; i++) {
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    Serial.print("Nilai ke- ");
    Serial.print(readIndex);
    Serial.print(" = \t");
    Serial.println(readings[readIndex]);
    readIndex = readIndex + 1;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    delay(20);  // delay in between reads for stability
  }
   // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println();
  Serial.print("Rata-rata = \t");
  Serial.println(average);
  delay(10);       
  return average; 
}
