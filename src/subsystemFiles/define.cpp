#include "define.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"

// --------- Drivetrain ----------
pros::MotorGroup leftMotors({-20, 19},pros::MotorGearset::blue);
pros::MotorGroup rightMotors({18, -17},pros::MotorGearset::blue);

lemlib::Drivetrain drivetrain(&leftMotors,                   // left motor group
                              &rightMotors,                 // right motor group
                              9.5,                           // 9.5 inch track width
                              lemlib::Omniwheel::NEW_275,   // using new 4" omniwheels
                              500,                                  // drivetrain rpm is 200
                              0                         // horizontal drift is 0 (for now)
);


// --------- Sensors ----------
pros::Imu imu(11);
pros::Distance Dist(12);

lemlib::OdomSensors sensors(nullptr,                          // vertical tracking wheel
                            nullptr,                          // vertical tracking wheel 2
                            nullptr,                        // horizontal tracking wheel
                            nullptr,                        // horizontal tracking wheel 2
                            &imu);

lemlib::ControllerSettings linearController(15,                      // proportional gain
                                            0.005,                       // integral gain
                                            40,                       // derivative gain
                                            30,              // anti windup
                                            0.5,               // small error range, in inches
                                            300,      // small error range timeout, in milliseconds
                                            1.5,               // in inches
                                            500,      // in milliseconds
                                            5
);

lemlib::ControllerSettings angularController(4, // proportional gain
                                             0.03, // integral gain
                                             20, // derivative gain
                                            3,              // anti windup
                                            0.01,               // small error range, in inches
                                            300,      // small error range timeout, in milliseconds
                                            1,               // in inches
                                            500,      // in milliseconds
                                            0
);

lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);


// --------- Chassis ----------
lemlib::Chassis chassis(drivetrain,
                        linearController,
                        angularController,
                        sensors,
                        &throttleCurve,
                        &steerCurve
                    );



// --------- Controller ----------
pros::Controller master(pros::E_CONTROLLER_MASTER);


// --------- Motors ----------

pros::Motor Eatball(16,pros::MotorGearset::blue);
pros::Motor Floor_two(1,pros::MotorGearset::blue);
pros::Motor Floor_one(9,pros::MotorGearset::blue);
pros::Motor High_mid(10,pros::MotorGearset::blue);
// --------- Pistons ----------
pros::adi::Pneumatics Parking('B',false);

pros::adi::Pneumatics Mouth('A', false);
pros::adi::Pneumatics DeScore('C',true);
