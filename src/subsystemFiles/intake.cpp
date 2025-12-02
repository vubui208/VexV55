#include "main.h"
const int BASE_SPEED = 600;
const int BOOST = 0;
int Speed = BASE_SPEED + BOOST;
bool mouthStatus = false;
bool doubleParking = false;
bool RabbitEar = true;
void GetBall() {
	//High_mid.move_velocity(-Speed);
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed);
	Eatball.move_velocity(-Speed);
}

void LowTube(){
	Floor_one.move_velocity(-Speed);
	Floor_two.move_velocity(-Speed);
	Eatball.move_velocity(Speed);
}

void MidTube(){
	High_mid.move_velocity(Speed);//-speed
	Eatball.move_velocity(-Speed);
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed);
	
}

void HighTube() {
	Eatball.move_velocity(Speed);
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed);
	High_mid.move_velocity(-Speed);//-speed
}

void StopIntake()
{
	Floor_one.move(0);
	Floor_two.move(0);
    High_mid.move(0);
	Eatball.move(0);
}

void OpenMouth()
{
	mouthStatus = !mouthStatus;
	Mouth.set_value(mouthStatus);
}
void parking(){
	doubleParking = !doubleParking;
	Parking.set_value(doubleParking);
}
void ballPush(){
	RabbitEar = !RabbitEar;
	DeScore.set_value(RabbitEar);
}
void TurnRight() {
  	int pose = chassis.getPose().theta;
  	// if (mouthStatus)
	// {
	// 	mouthStatus = !mouthStatus;
	// 	Mouth.set_value(mouthStatus);
	// }
	chassis.turnToHeading(pose + 90, 500);
}
void TurnLeft() {
  	int pose = chassis.getPose().theta;
  	// if (mouthStatus)
	// {
	// 	mouthStatus = !mouthStatus;
	// 	Mouth.set_value(mouthStatus);
	// }
	chassis.turnToHeading(pose - 90, 500);
}
void TurnAround() {
  	int pose = chassis.getPose().theta;
  	if (mouthStatus)
	{
		mouthStatus = !mouthStatus;
		Mouth.set_value(mouthStatus);
	}
	chassis.turnToHeading(pose +90, 500);
}
void StopWheel(void) { chassis.cancelMotion(); }