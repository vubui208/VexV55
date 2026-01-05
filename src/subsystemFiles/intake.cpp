#include "main.h"

const int BASE_SPEED = 600;
const int BOOST = 0;
int Speed = BASE_SPEED + BOOST;
bool mouthStatus = true;
inline int get_color(){
	double hue = optical.get_hue();
	if (hue < 20 || hue > 340){
		return 1;
	}else if (hue > 200 && hue < 250){
		return 0;
	}else{
		return -1;
	}
}
int chosen_color = 1;
void GetBall() {
	int check = 1;
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed-300);
	Eatball.move_velocity(Speed);
	
	High_mid.move_velocity(-Speed+100);
}
	


void LowTube(){
	Floor_one.move_velocity(-Speed);
	Floor_two.move_velocity(-Speed);
	Eatball.move_velocity(-Speed+200);
}

void MidTube(){
	
	High_mid.move_velocity(Speed);//-speed
	Eatball.move_velocity(Speed);
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed);
	
}

void HighTube() {
	Eatball.move_velocity(Speed);
	Floor_one.move_velocity(Speed);
	Floor_two.move_velocity(Speed-200);
	
	if(optical.get_proximity() >= 250){
		if(get_color() == chosen_color || get_color() == -1){
			High_mid.move_velocity(-Speed+100);//-speed
			
	}else{
		
		High_mid.move_velocity(Speed);//-speed
		pros::delay(100);
		
	}
	}else{
		High_mid.move_velocity(-Speed+300);//-speed
		
	};//-speed
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