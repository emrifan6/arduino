const int PIN_A = 4;
const int PIN_B = 5;
const int PIN_C = 6;

int adc = A1;

int pin = 0;
String inString = "";

float voltage = 0.0;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);

  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      //      Serial.print("Value:");
      //      Serial.println(inString.toInt());
      //      Serial.print("String: ");
      //      Serial.println(inString);
      // clear the string for new input:
      gate(inString.toInt());
      pin = inString.toInt();
      inString = "";
    }
  }

  int value = analogRead(adc);
  Serial.print("PIN ");
  Serial.print(pin);
  Serial.print("   =  Voltage =  ");
    if (pin == 0) {
      voltage = (value * (5.0 / 1023))*1.55;
    } else if (pin == 1) {
      voltage = value * (5.0 / 1023)*2.05; //voltage = voltage + (voltage * (3900 / 4700)); //
    } else {
      voltage = value * (5.0 / 1023.0)*1.17;
    }
  
  Serial.println(voltage);

}





void gate (int pin) {
  if (pin == 0) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 1) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 2) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 3) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
  } else if (pin == 4) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 5) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 6) {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
  } else if (pin == 7) {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
  } else {

  }

}
