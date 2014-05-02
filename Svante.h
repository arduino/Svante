#ifndef SVANTE_H
#define SVANTE_H

#define MOTOR_L1 10
#define MOTOR_L2 9
#define MOTOR_R1 5
#define MOTOR_R2 6

#define TRIM A3

#define IR_1 A2
#define IR_2 A1
#define IR_3 A0

#define D0 15
#define D1 16
#define D2 14
#define D3 13
#define D4 12
#define D5 11
#define D6 8
#define D7 7
#define D8 4
#define D9 3
#define D10 2
#define D11 0
#define D12 1

#define MIN_MOTOR_VAL 70

//#define DEBUG

struct SpeedPair{
	int speed1;
	int speed2;
};

class Svante{
	public:
		Svante();
		void init();
		void go(int speedLeft,int speedRight);
		void stop();
	private:
		void initMotors();
		void motorsWrite(int speedL1,int speedL2, int speedR1, int speedR2);
		int getTrim();
		SpeedPair procSpeed(int speedRaw);

};

#endif