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
inline int colorChosen = -1;    // red::1 , blue::0
inline int sideChosen = -1;     // left::0 , middle::1 , right::2
inline bool auton = false;      // false::off , true::on
inline bool center = false;     // false::off , true::on
inline bool longg = false;      // false::off , true::on
inline bool solo = false;       // false::off , true::on

inline bool press = false;      // false::off , true::on
inline bool wing = false;   
#endif