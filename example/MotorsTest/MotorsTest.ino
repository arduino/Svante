/*
*
*  MotorsTest
*  Test if the motors are moving, in the right
*  direction.
*
*	This example is used together with Svante robot
*	verkstad.cc 
*	(c) 2014 Arduino Verkstad
*
*/
#include <Svante.h>
#include <EEPROM.h>


void setup(){
  robot.begin();
}
void loop(){
  //Forward
  robot.go(100,100);
  delay(1000);
  robot.stop();
  delay(1000);
  
  //Backward
  robot.go(-100,-100);
  delay(1000);
  robot.stop();
  delay(1000);
  
  //Turn right
  robot.go(100,-100);
  delay(500);
  robot.stop();
  delay(1000);

  //Turn left
  robot.go(-100,100);
  delay(500);
  robot.stop();
  delay(1000);
}
