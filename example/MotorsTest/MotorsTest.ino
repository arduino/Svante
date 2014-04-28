#include <Svante.h>

Svante me;

void setup(){
  Serial.begin(9600);
  me.init();
}
void loop(){
  me.go(100,100);
  delay(1000);
  me.stop();
  delay(1000);
  me.go(-100,-100);
  delay(1000);
  me.stop();
  delay(1000);
}
