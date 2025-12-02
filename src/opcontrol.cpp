#include "main.h"
#include "pros/misc.h"

bool DriveMode = true;
const double deadband = 0.03;


double applyDeadband(double value) {
    return (fabs(value) < deadband) ? 0.0 : value;
}

void Marcos() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        GetBall();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        LowTube();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        MidTube();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        HighTube();
    }
    else {
        StopIntake();
    }
    if (master.get_digital_new_press( pros::E_CONTROLLER_DIGITAL_L1)) {
        OpenMouth();
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        TurnLeft();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        TurnRight();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        TurnAround();
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

    double turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double forward = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    const int db = 0.03;
    if (abs(forward) < db) forward = 0;
    if (abs(turn)    < db) turn    = 0;

    // ---- DRIFT MODE ----
    
    double driftForward = expo127(forward, 1.3);
    double driftTurn    = expo127(turn, 0.8) * 0.9;

    // ---- IF STATIONARY → FULL POWER TURN ----
    if (forward == 0) {
        chassis.tank(turn, -turn);       // quay tại chỗ mạnh
    }
    else {
        // -------- BOOSTED CURVATURE --------
        double boostedTurn = driftTurn * 1.5;
        
        // clamp để tránh overflow
        if (boostedTurn > 127) boostedTurn = 127;
        if (boostedTurn < -127) boostedTurn = -127;
        bool quick = (abs(turn) > 80);  
        chassis.arcade(driftForward, boostedTurn, quick);
    }
}








void opcontrol(void) {
    while (true) {
        hybridDrive(chassis, master);
        Marcos();
        pros::delay(20);
    }
}