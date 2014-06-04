#include <Arduino.h>
#include <EEPROM.h>
#include "Svante.h"

Svante::Svante(){

}
extern void stopServo(){
	sbi(TCCR1B, CS11);		// set timer 3 prescale factor to 64
	sbi(TCCR1B, CS10);
	sbi(TCCR1A, WGM10);		// put timer 3 in 8-bit phase correct pwm mode
}
extern void stopMusic(){
	sbi(TCCR3B, CS31);		// set timer 3 prescale factor to 64
	sbi(TCCR3B, CS30);
	sbi(TCCR3A, WGM30);		// put timer 3 in 8-bit phase correct pwm mode
}


void Svante::begin(){
	initMotors();
	int motorCalibEEP=EEPROM.read(EEPROM_MOTORS_CALIB)-100;
	#ifdef DEBUG
	Serial.print("MotorCalib from EEPROM: ");
	Serial.println(motorCalibEEP);
	#endif
	if(!(motorCalibEEP<=100 && motorCalibEEP>=-100)){
		motorCalibEEP=0;
	}
	setMotorsDiff(motorCalibEEP);
}
void Svante::begin(int motorsDiff){
	initMotors();
	setMotorsDiff(motorsDiff);
}

void Svante::go(int speedLeft,int speedRight){
	//Dirty and ugly hack so the robot can go back with a remote control
	if(speedLeft==-100 && speedRight==-100){
		motorsWrite(0,255,0,255);
		return ;
	}
	//end of dirty and ugly hack, Yuks!
	
	SpeedPair sl,sr;
	#ifdef DEBUG
	Serial.print("left ");
	#endif
	sl=procSpeed(speedLeft,leftMotorMulti);
	#ifdef DEBUG
	Serial.print("right ");
	#endif

	sr=procSpeed(speedRight,rightMotorMulti);
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

void Svante::setMotorsDiff(int diff){
	diff=constrain(diff,-100,100);
	if(diff>0){
		leftMotorMulti=1;
		rightMotorMulti=1-diff/MOTOR_CALIB_MULTI;
	}else{
		leftMotorMulti=1+diff/MOTOR_CALIB_MULTI;
		rightMotorMulti=1;
	}
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

SpeedPair Svante::procSpeed(int speedRaw,float motorMulti){
	SpeedPair res;
	speedRaw*=motorMulti;
	
	if(speedRaw==0){
		res.speed1=0;
		res.speed2=0;
		return res;
	}
	int sign=speedRaw/abs(speedRaw);
	speedRaw=abs(speedRaw);
	
	#ifdef DEBUG_SPEED
	int speedTest=constrain(map(getTrim(),0,1023,0,255),0,255);
	Serial.println(speedTest);
	int speed=map(speedRaw,0,100,speedTest,255);
	#else 
	int speed=constrain(map(speedRaw,0,100,MIN_MOTOR_VAL,255),0,255);
	#endif
	
	if(sign>0){
		res.speed1=speed;
		res.speed2=0;
	}else{
		res.speed1=0;
		res.speed2=speed;
	}
	#ifdef DEBUG
	Serial.print(res.speed1);
	Serial.print(" ");
	Serial.println(res.speed2);
	#endif
	return res;
}
int Svante::getIRArray(int pos){
	//possible parameters: IR_1, IR_2, IR_3
	int IRPin;
	switch(pos){
		case 0:
			IRPin=IR_1;
			break;
		case 1:
			IRPin=IR_2;
			break;
		case 2:
			IRPin=IR_3;
			break;
	}

	return analogRead(IRPin);
}

Svante robot=Svante();