#include <Svante.h>
#include <IRremote.h>
#include <IRremoteTools.h>
#include <EEPROM.h>

const int RECV_PIN = 13;
int motorsSpeed=100;

void setup(){
  robot.begin();
  Serial.begin(9600);
  beginIRremote(RECV_PIN);
  beginLEDs();
}
void loop(){
  int trimVal=analogRead(TRIM);
  int motorCalib=map(trimVal,0,1023,-100,100);
  robot.setMotorsDiff(motorCalib);
  robot.go(motorsSpeed,motorsSpeed);

  if(IRrecived()){

    unsigned long command=getIRresult();
    if(command==REMOTE_PLUS){
      motorsSpeed+=10;
      if(motorsSpeed>100){
        motorsSpeed=100;
      }
    }else if(command==REMOTE_MINUS){
      motorsSpeed-=10;
      if(motorsSpeed<0){
        motorsSpeed=0;
      }
    }else if(command==REMOTE_MIDDLE){
      EEPROM.write(EEPROM_MOTORS_CALIB,motorCalib+100);
      blinkLEDs();
    }
    resumeIRremote();
  }
}

void beginLEDs(){
  pinMode(IR_1,OUTPUT);
  pinMode(IR_2,OUTPUT);  
  pinMode(IR_3,OUTPUT);
}
void blinkLEDs(){
  boolean ledState=true;
  for(int i=0;i<3;i++){
    for(int j=0;j<2;j++){
      digitalWrite(IR_1,ledState);
      digitalWrite(IR_2,ledState);
      digitalWrite(IR_3,ledState);
      ledState=!ledState;
      delay(75);
    }
  }
}