#include <Svante.h>

void setup(){
  robot.begin();
}
void loop(){
  int trimPct=map(analogRead(TRIM),0,1023,-100,100);
  robot.setMotorsDiff(trimPct);
  robot.go(100,100);
  delay(100);
}
