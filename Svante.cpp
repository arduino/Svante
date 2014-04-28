#include <Arduino.h>
#include "Svante.h"

Svante::Svante(){

}

void Svante::init(){
	initMotors();
}

void Svante::go(int speedLeft,int speedRight){
	SpeedPair sl,sr;
	sl=procSpeed(speedLeft);
	sr=procSpeed(speedRight);
	motorsWrite(sl.speed1,sl.speed2,sr.speed1,sr.speed2);
}

void Svante::stop(){
	motorsWrite(255,255,255,255);

}

void Svante::initMotors(){
	pinMode(MOTOR_L1, OUTPUT);
	pinMode(MOTOR_L2, OUTPUT);
	pinMode(MOTOR_R1, OUTPUT);
	pinMode(MOTOR_R2, OUTPUT);

}

void Svante::motorsWrite(int speedL1,int speedL2, int speedR1, int speedR2){
	analogWrite(MOTOR_L1,speedL1);
	analogWrite(MOTOR_L2,speedL2);
	analogWrite(MOTOR_R1,speedR1);
	analogWrite(MOTOR_R2,speedR2);

}
int Svante::getTrim(){
	return analogRead(TRIM);
}

SpeedPair Svante::procSpeed(int speedRaw){
	SpeedPair res;
	if(speedRaw==0){
		res.speed1=0;
		res.speed2=0;
		return res;
	}
	int sign=speedRaw/abs(speedRaw);
	
	#ifdef DEBUG
	int speedTest=constrain(map(getTrim(),0,1023,0,255),0,255);
	Serial.println(speedTest);
	int speed=map(speedRaw,0,100,speedTest,255);
	#else 
	int speed=constrain(map(speedRaw,0,100,MIN_MOTOR_VAL,255),0,255);
	#endif
	
	Serial.println(speed);
	if(sign>0){
		res.speed1=speed;
		res.speed2=0;
	}else{
		res.speed1=0;
		res.speed2=-speed;
	}
	return res;
}