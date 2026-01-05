#include "main.h"
#include "pros/rtos.hpp"
#include "subsystemFiles/define.hpp"
#include "subsystemFiles/intake.hpp"
// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


// void tunning(){
//     chassis.setPose(0,0,0);
//     chassis.moveToPoint(0, 10, 1000);
// }
    
int auton_mode = 1;
//1 auton trai
//2 auton phai
//3 test wall reset
inline double mmToIn(double mm){
    return mm/25.4;
}
void leftWallReset(void*){
    while(true){
        const int leftWall = 40;
        double d = mmToIn(Dist.get());
        double difference = d - 40;
        chassis.setPose(chassis.getPose().x + difference,chassis.getPose().y,chassis.getPose().theta);
        pros::delay(20000);
    }
    
}
void autonomous() {
    switch(auton_mode){
        case 1:
            pros::Task leftWallReset20s(leftWallReset);
            chassis.setPose(-135,28,180);
            chassis.moveToPoint(-135,120, 1000);
            chassis.turnToHeading(270, 1000);
            Mouth.toggle();
            while(Dist.get() >= 180){
                chassis.tank(127,127);
                pros::delay(10);
            }
            GetBall();
            pros::delay(1300);
            StopIntake();
            pros::delay(1200);
            chassis.moveToPoint(-64, 120,1200, {.forwards = false});
            HighTube();
            pros::delay(3000);
            StopIntake();
            chassis.moveToPoint(-90, 120, 1000);
            chassis.turnToHeading(315, 1000);
            chassis.moveToPoint(-38, 96, 1000,{.forwards = false});
            chassis.moveToPoint(-90.5, 96,1000,{.forwards = false});
            
            chassis.turnToPoint(-62.5, 63,1000);
            GetBall();
            chassis.moveToPoint(-62.5,63,1000);
            chassis.moveToPoint(-53.9, 57.5, 1000);
            Mouth.toggle();
            pros::delay(500);
            Mouth.toggle();
            StopIntake();
            chassis.moveToPoint(-21, -26, 1000);
            LowTube();               
            pros::delay(120);
            StopIntake();
            MidTube();
            break;
        // case 2:
            
        //     chassis.setPose(-135,-28,90);
        //     chassis.turnToPoint(-63.7, -50, 600);
        //     chassis.moveToPoint(-63.7,-50, 1000);
        //     GetBall();
        //     chassis.moveToPoint(-55.731, -57.781, 1300,{.maxSpeed = 70});
        //     StopIntake();
        //     chassis.turnToPoint(-20, -28, 600);
        //     chassis.moveToPoint(-20,-28, 1000);
        //     LowTube();
        //     pros::delay(700);
        //     chassis.moveToPoint(-107, -120, 1500);
        //     chassis.turnToHeading(270, 600);
        //     while(Dist.get() >= 180){
        //         chassis.tank(127,127);
        //         pros::delay(10);
        //     }
        //     GetBall();
        //     pros::delay(1300);
        // case 3: 

    }

    //case 1 4 long goal + 3 lower goal
    
}

