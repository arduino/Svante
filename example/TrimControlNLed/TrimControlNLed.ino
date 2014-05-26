#include <Svante.h>
#include <EEPROM.h>
/*
*  Trim Controlled Speed, Plus A Blinking LED
*  This example is made for testing motor powering 
*  circuit. The on board trim changes speed of the 
*  robot, while a led connected to 3rd IR sensor 
*  blinking.
*
*/
bool ledState=false;

void setup(){
  Serial.begin(9600);
  robot.begin();
  pinMode(IR_3,OUTPUT);
}
void loop(){
  digitalWrite(IR_3,ledState);
  ledState=!ledState;
  int trimVal=analogRead(TRIM);
  Serial.println(trimVal);
  int sped=map(trimVal,0,1023,-100,100);
  robot.go(sped,sped);
 delay(100);
}
