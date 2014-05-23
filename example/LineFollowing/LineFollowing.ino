#include <Svante.h>
void setup(){
  robot.begin();
  delay(1000);

  robot.lineFollowCalibrate();

  robot.lineFollowConfig(40,8,10,30);
  delay(1000);
  robot.startLineFollow();
}
void loop(){
  
}
