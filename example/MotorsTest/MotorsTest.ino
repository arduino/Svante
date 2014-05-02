#include <Svante.h>

void setup(){
  robot.init();
}
void loop(){
  robot.go(100,100);
  delay(1000);
  robot.stop();
  delay(1000);
  robot.go(-100,-100);
  delay(1000);
  robot.stop();
  delay(1000);
}
