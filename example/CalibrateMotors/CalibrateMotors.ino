/*
*
*  Calibrate Motors
*  Though all manufactured from
*  factories, no two motors are exactly
*  the same. Without calibration, your 
*  robot can go in circles.
*  This sketch helps calibrate the motors
*  of your robot. You'll need an IR
*  receiver, a remote controller to run
*  it.
*  Connect the 3 pins of IR receiver to 
*  DP9, 5v, GND respectively.
*  After uploading, you can use the remote
*  control and on-board trim to calibrate
*  the robot. Draw a straight line on a 
*  flat surface, put the robot on the line,
*  see if it's going in a straight line.
*  Use the trim to adjust difference 
*  between the motors. Use "+" and "-" on
*  the remote control to adjust speed.
*  When the robot is going staight, keep 
*  the trim in its position, and press the
*  middle button on remote control. The 3
*  LEDs in the front part of the robot will
*  blink, indicating the calibration is 
*  finished.
*
*	This example is used together with Svante robot
*	verkstad.cc 
*	(c) 2014 Arduino Verkstad
*
*/
#include <Svante.h>
#include <IRremote.h>
#include <IRremoteTools.h>
#include <EEPROM.h>

const int RECV_PIN = DP9;
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
