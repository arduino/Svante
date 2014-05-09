
#include <Svante.h>

int trigR = DP0;
int echoR =DP1;
int trigL = DP9;
int echoL =DP10;

int threshhold = 50;

void setup(){  
  //Initialize the serial communication
  Serial.begin(9600); 
  robot.begin();
}

void loop(){
  //Get the distance in cm
  int disR = getDistance(trigR, echoR);
  int disL = getDistance(trigL, echoL);
  
  if(disL<threshhold && disR<threshhold){
    Serial.println("In front!");
    robot.go(100, 100);
  }
  else if(disL<threshhold){
    Serial.println("To the left!");
    robot.go(10, 100);
  }
  else if(disR<threshhold) {
    Serial.println("To the right!");
    robot.go(100, 10);
  }
  else {
    Serial.println("Nothing there!");
    robot.stop();
  }

  delay(100);
}


int getDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);  
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  
  pinMode(echoPin, INPUT);
  int duration = pulseIn(echoPin, HIGH, 11800);
  int distance = constrain(duration/29/2, 0, 200);
  if(distance==0)distance=200;

  return distance;
}
