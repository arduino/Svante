#ifndef SVANTE_H
#define SVANTE_H

#include "LineFollower.h"

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



#define MOTOR_L1 10
#define MOTOR_L2 9
#define MOTOR_R1 5
#define MOTOR_R2 6

#define TRIM A3

#define IR_1 A2
#define IR_2 A1
#define IR_3 A0

#define EEPROM_MOTORS_CALIB 10

#define DP0 1
#define DP1 0
#define DP2 2
#define DP3 3
#define DP4 4
#define DP5 7
#define DP6 8
#define DP7 11
#define DP8 12
#define DP9 13
#define DP10 14
#define DP11 16
#define DP12 15


#define MIN_MOTOR_VAL 70
#define MOTOR_CALIB_MULTI 1000.0

//#define DEBUG
//#define DEBUG_SPEED

struct SpeedPair{
	int speed1;
	int speed2;
};

class Svante : public LineFollower{
	public:
		Svante();
		void begin();
		void begin(int motorsDiff);
		void setMotorsDiff(int diff);

		void go(int speedLeft,int speedRight);
		void stop();
		
		int getIRArray(int pos);
	private:
		float leftMotorMulti,rightMotorMulti;
		
		void initMotors();
		void motorsWrite(int speedL1,int speedL2, int speedR1, int speedR2);
		int getTrim();
		SpeedPair procSpeed(int speedRaw,float motorPow);

};

extern Svante robot;
extern void stopMusic();
extern void stopServo();
#endif
