#include "main.h"

int auton_id = 0;
const char* mode[4] = {"Red left", "Red right", "Blue left", "Blue right"};
int auton_count = 4;

void on_center_button() {
    auton_id = (auton_id + 1) % auton_count;
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "Auton: %s", mode[auton_id]);
}
void on_left_button() {
  
}
void on_reight_button() {
  
}
void initialize() {
  pros::lcd::initialize();
    chassis.calibrate(); // calibrate lemLib
    // pros::Task splashScreenTask(Logo_Popup);
    // autonSelectorGUI();        // hiển thị menu LVGL
    
    // chassis.calibrate();
    // pros::lcd::print(0, "Press center button to change auton");
    // pros::lcd::print(3, "Auton: %s", mode[auton_id]);
    // pros::lcd::register_btn1_cb(on_center_button);
    pros::Task screenTask([&]() {
        while (true) {
            //gui();
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}