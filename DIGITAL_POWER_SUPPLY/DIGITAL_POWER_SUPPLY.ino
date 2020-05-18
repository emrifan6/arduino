// Rotary Encoder Inputs
 #define inputCLK 4
 #define inputDT 5
 #define Vout 3
 #define Iout 6

int V_pwm = 200;
int I_pwm = 40;
int currentStateCLK;
int previousStateCLK; 
String encdir ="";
const int buttonPin = 7;   
const int ledPin =  13;    
int state = HIGH;    
int reading;           
int previous = LOW;    
long time = 0;     
long debounce = 200;  


 void setup() { 
   pinMode (inputCLK,INPUT_PULLUP);
   pinMode (inputDT,INPUT_PULLUP);
   Serial.begin (9600);
   previousStateCLK = digitalRead(inputCLK);
   pinMode(Vout, OUTPUT);
   pinMode(buttonPin, INPUT_PULLUP); 
 } 



 void loop() { 
  menu();
  analogWrite(Vout, V_pwm);
  analogWrite(Iout, I_pwm);
  Serial.print("Vpwm = ");
  Serial.print(V_pwm);
  Serial.print("\t");
  Serial.print("Ipwm = ");
  Serial.println(I_pwm);
 }


//AWAL FUNGSI MENU
void menu(){
  int x = btn();
  if (x == 0){
    V_pwm = rotary(0);
  }else if (x ==1){
    I_pwm = rotary(1);
  }
}
//AKHIR FUNGSI MENU


// AWAL FUNGSI BTN
int btn(){
  int x;
  reading = digitalRead(buttonPin);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH){
      state = LOW;
      x=0;
    }
    else{
      state = HIGH;
      x=1;
    time = millis();
    }    
  }
  digitalWrite(ledPin, state);
  previous = reading;
  return x;
}
// AKHIR FUNGSI BTN



// AWAL FUNGSI ROTARI
 int rotary(int x){
    int counter;
    if(x==0){
      counter = V_pwm;
    } else if(x==1){
      counter = I_pwm;
    }
    
   currentStateCLK = digitalRead(inputCLK);
   if (currentStateCLK != previousStateCLK && millis() - time > debounce){ 
    if (digitalRead(inputDT) != currentStateCLK && millis() - time > debounce) { 
       counter --;
       if(counter<=0){
        counter=0;
       }
       //encdir ="CCW";
     } else {  // Encoder is rotating clockwise
       counter ++;
       if(counter>=255){
        counter=255;
       }
       //encdir ="CW";      
     }
   }
   previousStateCLK = currentStateCLK; 
   return counter;
 }
 // AKHIR FUNGSI ROTARI
