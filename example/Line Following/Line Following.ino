#include <Svante.h>
void setup(){
  robot.begin();
  delay(1000);
  robot.lineFollowCalibrate();
  robot.lineFollowConfig(10,0,10,30);
  
}
void loop(){
  robot.startLineFollow();
}
