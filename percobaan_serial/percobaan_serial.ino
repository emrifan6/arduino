int X=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() 
{
if(Serial.read()=='1')
 {X=X+1;}
 else
 {X=X-1;}
 Serial.println(X);
delay(1000);
     

 /* switch (Serial.read())
  {
  case '1' :
  X=X+1;
  break;
  case '2':
  X=X-1;
  break;
  }

  Serial.println(X);
*/
}
