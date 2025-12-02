#ifndef DEFINE_HPP
#define DEFINE_HPP

#include "api.h"
#include "lemlib/api.hpp"

// --------- Drivetrain ----------
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern lemlib::Drivetrain drivetrain;

extern pros::Imu imu;
extern lemlib::OdomSensors sensors;

extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;

extern lemlib::Chassis chassis;

extern pros::Controller master;

// --------- Motors ----------
extern pros::Motor Lower;
extern pros::Motor UpperOut;
extern pros::Motor Storage;
extern pros::Motor UpperIn;

// --------- Pistons ----------
extern pros::adi::Pneumatics HighOut;

extern pros::adi::Pneumatics Mouth;

#endif