#include <Svante.h>

bool ledState=false;

void setup(){
  Serial.begin(9600);
  robot.init();
  pinMode(IR_3,OUTPUT);
}
void loop(){
  digitalWrite(IR_3,ledState);
  ledState=!ledState;
  int trimVal=analogRead(TRIM);
  Serial.println(trimVal);
  int sped=map(trimVal,0,1023,0,100);
  robot.go(sped,sped);
 delay(100);
}
