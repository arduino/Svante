#include <Arduino.h>
#include "LineFollower.h"

void LineFollower::lineFollowCalibrate(int speed, int time){
	for(int i=0;i<3;i++){
		IRArray_Max[i]=0;
		IRArray_Min[i]=1023;
	}
	doLineFollowCalibrate(-speed,speed,time);
	doLineFollowCalibrate(speed,-speed,time*2);
	doLineFollowCalibrate(-speed,speed,time);
	stop();
	
	/*
	for(int i=0;i<3;i++){
		Serial.print(IRArray_Min[i]);
		Serial.print(" ");
		Serial.print(IRArray_Max[i]);
		Serial.print(" | ");
	}
	*/
}
void LineFollower::doLineFollowCalibrate(int speedL,int speedR,int time){
	go(speedL,speedR);
	unsigned long baseTime=millis();
	while(millis()-baseTime<time){
		for(int i=0;i<3;i++){
			int IRVal=getIRArray(i);
			if(IRVal<IRArray_Min[i])IRArray_Min[i]=IRVal;
			if(IRVal>IRArray_Max[i])IRArray_Max[i]=IRVal;
		}
	}
}

void LineFollower::lineFollowConfig(int KP,int KD, int intergrationTime, int robotSpeed){
	this->KP=KP;
	this->KD=KD;
	this->integrationTime=integrationTime;
	this->robotSpeed=robotSpeed;
}


void LineFollower::startLineFollow(){
	int lastError=getLineFollowError();
	int resLimit=500;//*KP/100.0;
	int speedFactor=100;
	while(true){
		getIRArraryVals();
		if(isEndLineReached()){
			stop();
			return;	//end of line reached, stop the robot
		}
		int error=getLineFollowError();
		
		/*
		if(abs(error)<10){
			Serial.println("stop");
		}*/
		
		/*
		Serial.print("error: ");
		Serial.println(error);
		*/
		int result=error/100.0*KP+(error-lastError)*KD;
		

		result=map(result,-resLimit,resLimit,-speedFactor,speedFactor);
		//result=constrain(result,-100,100);
		/*
		Serial.print("result: ");
		Serial.println(result);
		*/


		int speedL=constrain(robotSpeed-result,-100,100);
		int speedR=constrain(robotSpeed+result,-100,100);
		/*
		Serial.print(speedL);
		Serial.print("   ");
		Serial.println(speedR);
		*/
		go(speedL,speedR);
		
		lastError=error;
		delay(integrationTime);
		
	}
}
void LineFollower::getIRArraryVals(){
	for(int i=0;i<3;i++){
		IRArray_vals[i]=map(getIRArray(i),IRArray_Min[i],IRArray_Max[i],0,255);
		Serial.print(IRArray_vals[i]);
		Serial.print(" ");
	}
	Serial.println();

}
bool LineFollower::isEndLineReached(){
	for(int i=0;i<3;i++){
		if(IRArray_vals[i]>ENDLINE_VALUE){
			return false;
		}
	}
	return true;
}
int LineFollower::getLineFollowError(){
	int * v=IRArray_vals;//left, middle, right
	int error=v[2]-v[0];
	
	if(error>0)
		error=error+v[1];
	else
		error=error-v[1];
	return error;
}
