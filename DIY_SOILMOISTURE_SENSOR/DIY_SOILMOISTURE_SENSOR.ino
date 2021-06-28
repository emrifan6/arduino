int pwm = 6;
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A5;

void setup() {
  // put your setup code here, to run once:
 // TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz
  
//  TCCR0A = (0<<COM0A1) | (1<<COM0A0) | (0<COM0B1) | (0<<COM0B0) | (0<WGM01) | (0<WGM00);
//  TCCR0B = (0<WGM02) | (0<CS02) | (0<CS01) | (1<CS00);

  TCCR0A = 0x40;
  TCCR0B = 0x01;

  TCNT0 = 0x00;
  OCR0A = 0x00;
  OCR0B = 0x00;

  Serial.begin(9600);
  
   pinMode(pwm, OUTPUT);
   
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
   
}

void loop() {
//  analogWrite(pwm,155);
  
//  // subtract the last reading:
//  total = total - readings[readIndex];
//  // read from the sensor:
//  readings[readIndex] = analogRead(inputPin);
//  // add the reading to the total:
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//
//  // if we're at the end of the array...
//  if (readIndex >= numReadings) {
//    // ...wrap around to the beginning:
//    readIndex = 0;
//  }
//
//  // calculate the average:
//  average = total / numReadings;
//  // send it to the computer as ASCII digits
//  Serial.println(average);
//  delay(1);        // delay in between reads for stability
}
