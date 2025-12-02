#include "main.h"

void disabled() {
    pros::lcd::print(0, "Robot disabled");
    StopWheel();
    StopIntake();
    Mouth.set_value(false);
}