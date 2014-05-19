#include <Svante.h>

/*
*	MotorsTest
*	Test if the motors are moving, in the right
*	direction.
*
*/

void setup(){
  robot.init();
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
