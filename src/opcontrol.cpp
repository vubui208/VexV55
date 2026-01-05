#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystemFiles/define.hpp"
#include "gui/calibratingAuton.hpp"

bool DriveMode = true;
const double deadband = 0.03;
bool rabbitEar = false;
bool doubleParking = false;
double applyDeadband(double value) {
    return (fabs(value) < deadband) ? 0.0 : value;
}
void descore(){
	rabbitEar = !rabbitEar;
	DeScore.set_value(rabbitEar);
}
void parkingMacro(){
	while(Dist.get() >= 60 || Dist.get()<=50){
		Floor_one.move_velocity(-Speed);
		Floor_two.move_velocity(-Speed);
		Eatball.move_velocity(-Speed+350);
		pros::delay(20);
	}
	
	Parking.toggle();
}
void Marcos() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        DeScore.set_value(true);
        
        GetBall();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        LowTube();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) || master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        LowTube();               // chạy 1 lần
        pros::delay(150);        // chờ 120ms để đẩy bóng lên
}

    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
    MidTube();               // giữ MidTube khi Y còn được nhấn
}
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        DeScore.set_value(false);
        HighTube();
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
        descore();
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
        parkingMacro();
    }
    else {
        StopIntake();
    }
    if (master.get_digital_new_press( pros::E_CONTROLLER_DIGITAL_L1)) {
        OpenMouth();
    }
    
    
}

// 🕹️ Hybrid Drive: tank/curvature
double expo127(double x, double e) {
    double n = x / 127.0;
    double out = pow(fabs(n), e);
    if (n < 0) out = -out;
    return out * 127.0;
}
void hybridDrive(lemlib::Chassis &chassis, pros::Controller &master) {

    double turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    double forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);


    const int db = 0.03;
    if (abs(forward) < db) forward = 0;
    if (abs(turn)    < db) turn    = 0;

    // ---- DRIFT MODE ----
    
    double driftForward = expo127(forward, 1.3);
    double driftTurn    = expo127(turn, 0.8) * 0.9;
    if (forward == 0) {
        chassis.tank(turn, -turn); 
    }
    else {
        // double boostedTurn = driftTurn * 1.5;
        
        // // clamp để tránh overflow
        // if (boostedTurn > 127) boostedTurn = 127;
        // if (boostedTurn < -127) boostedTurn = -127;
        // bool quick = (abs(turn) > 80);  
        // chassis.arcade(driftForward, boostedTurn, quick);
        chassis.arcade(driftForward, driftTurn, true);
    }
}





void setbrake(){
    pros::c::motor_set_brake_mode(20, pros::E_MOTOR_BRAKE_BRAKE); 
    pros::c::motor_set_brake_mode(19, pros::E_MOTOR_BRAKE_BRAKE); 
    pros::c::motor_set_brake_mode(18, pros::E_MOTOR_BRAKE_BRAKE);  
    pros::c::motor_set_brake_mode(17, pros::E_MOTOR_BRAKE_BRAKE); 
}


void opcontrol(void) {
    setbrake();
    while (true) {
        handleType();
        handleCalibrateController();
        hybridDrive(chassis, master);
        Marcos();
        pros::delay(20);
    }
}