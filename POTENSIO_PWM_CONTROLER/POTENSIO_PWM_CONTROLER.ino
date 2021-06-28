int potPin = A0;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor
int MotorPin = 10;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  int pwm_persen = map(val, 0, 1024, 0, 100);
  int pwm = map(val, 0, 1024, 0, 255);
  analogWrite(MotorPin, pwm);
  Serial.print("PWM = ");
  Serial.println(pwm_persen);
}
