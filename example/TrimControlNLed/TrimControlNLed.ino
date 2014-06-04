/*
*  Trim Controlled Speed, Plus A Blinking LED
*  This example is made for testing motor powering 
*  circuit. The on board trim changes speed of the 
*  robot, while a led connected to 3rd IR sensor 
*  blinking.
*
*	This example is used together with Svante robot
*	verkstad.cc 
*	(c) 2014 Arduino Verkstad
*
*/

#include <Svante.h>
#include <EEPROM.h>
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
