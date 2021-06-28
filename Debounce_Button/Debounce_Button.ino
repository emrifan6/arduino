int switchPin = A0;
int ledPin = 11;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup ()
{
  Serial.begin(9600);
pinMode(switchPin, INPUT);
pinMode(ledPin, OUTPUT);
}

boolean debounce (boolean last)
{
boolean current = digitalRead(switchPin);
if (last != current)
{
delay(5);
current = digitalRead(switchPin);
}
return current;
}

void loop ()
{
       Serial.print("lastButton  ");
       Serial.println(lastButton);
       Serial.print("currentButton  ");
       Serial.println(currentButton);
currentButton = debounce(lastButton);
        Serial.print("currentButtonMJD  ");
        Serial.println(currentButton);
  
if ( lastButton == LOW && currentButton == HIGH)
{
        Serial.print("ledOn  ");
        Serial.println(ledOn);
ledOn = !ledOn;
        Serial.print("ledOnMJD  ");
        Serial.println(ledOn);
}
lastButton = currentButton;
        Serial.print("lastButtonAKH  ");
        Serial.println(lastButton);
digitalWrite(ledPin, ledOn);
        Serial.print("ledOn  ");
        Serial.println(ledOn);
        Serial.println("FINISH");
        Serial.println("\n\n\n");
}



























