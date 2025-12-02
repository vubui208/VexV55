#include "main.h"
#include "pros/rtos.hpp"
#include "subsystemFiles/define.hpp"
#include "subsystemFiles/intake.hpp"
// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


void autonomous() {

    chassis.setPose(-134, -10, 90);

    chassis.turnToPoint(-75.5,-46, 800);
    chassis.moveToPoint(-75.5, -46, 800, {.maxSpeed = 100});
    pros::delay(500);
    GetBall();
    chassis.moveToPoint(-42.3, -64.5, 2000, {.maxSpeed = 40});
    OpenMouth();
    pros::delay(1000);
    chassis.turnToPoint(-8, -110, 800);
    StopIntake();
    OpenMouth();
    chassis.moveToPoint(-8, -110, 1000);
    GetBall();
    OpenMouth();
    pros::delay(600);
    chassis.moveToPoint(-42.3, -64.5, 1500, {.forwards = false});
    StopIntake();
    OpenMouth();
    chassis.turnToPoint(-105.2, -118.2, 600);
    chassis.moveToPoint(-105.2, -118.2, 800, {.maxSpeed = 100});
    chassis.turnToHeading(270, 500);
    OpenMouth();
    GetBall();
    chassis.moveToPoint(-167.1, -118.7, 800);
    pros::delay(2000);
    chassis.moveToPoint(-56.2, -120.2, 800);
    HighTube();
    pros::delay(2000);
    //them phan tai tho sau                                                                                                                                                                                                                                                                                                         Q

    
}
