#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H
class LineFollower{
	public:
		void lineFollowConfig(int KP, int KD, int intergrationTime, int robotSpeed);
		void lineFollowCalibrate(int speed=30, int time=200);
		void startLineFollow();
		
		virtual int getIRArray(int pos);
		virtual void go(int speedL,int speedR);
		virtual void stop();
	private:
		int KP;
		int KD;
		int integrationTime;
		int robotSpeed;
		int IRArray_Max[3];
		int IRArray_Min[3];
		
		int getLineFollowError();
		void doLineFollowCalibrate(int speedL,int speedR,int time);

};

#endif