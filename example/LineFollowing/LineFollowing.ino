/*
*
*  Line following
*  Make the robot follow a line.
*  First make a track, typically a black line on a 
*  white surface. Then place the robot along the line, 
*  and turn it on. The robot will first calibrate
*  itself, then start following the line.
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
  delay(1000);

  robot.lineFollowCalibrate();
  //parameters for lineFollowConfig can be improved.
  //They're KP, KD, integration time and speed.
  //The speed goes from 0 to 100, try make it go
  //faster

  robot.lineFollowConfig(40,8,10,30);
  delay(1000);
  robot.startLineFollow();
}
void loop(){
  
}
