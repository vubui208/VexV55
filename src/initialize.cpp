#include "gui/menu.hpp"
#include "main.h"
#include "pros/apix.h"


int auton_id = 0;
const char* mode[4] = {"Red left", "Red right", "Blue left", "Blue right"};
int auton_count = 4;
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


//gui
// int selectedAuton = 0;
// static void btn_red_cb(lv_event_t* e) {
//   if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
//     selectedAuton = 1;
//   }
// }

// static void btn_blue_cb(lv_event_t* e) {
//   if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
//     selectedAuton = 2;
//   }
// }

// void init_gui() {
//   lv_obj_t* scr = lv_disp_get_scr_act(NULL);

//   // Title
//   lv_obj_t* title = lv_label_create(scr);
//   lv_label_set_text(title, "Select Auton");
//   lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

//   // RED
//   lv_obj_t* btnRed = lv_btn_create(scr);
//   lv_obj_set_size(btnRed, 140, 60);
//   lv_obj_align(btnRed, LV_ALIGN_CENTER, -80, 30);
//   lv_obj_add_event_cb(btnRed, btn_red_cb, LV_EVENT_CLICKED, NULL);

//   lv_obj_t* lblR = lv_label_create(btnRed);
//   lv_label_set_text(lblR, "RED");
//   lv_obj_center(lblR);

//   // BLUE
//   lv_obj_t* btnBlue = lv_btn_create(scr);
//   lv_obj_set_size(btnBlue, 140, 60);
//   lv_obj_align(btnBlue, LV_ALIGN_CENTER, 80, 30);
//   lv_obj_add_event_cb(btnBlue, btn_blue_cb, LV_EVENT_CLICKED, NULL);

//   lv_obj_t* lblB = lv_label_create(btnBlue);
//   lv_label_set_text(lblB, "BLUE");
//   lv_obj_center(lblB);
// }
void init_gui(){
    lv_obj_t * my_screen = lv_obj_create(NULL);
    lv_screen_load(my_screen);
    // lv_obj_t * red = lv_button_create(lv_screen_active());
    // lv_obj_t * blue = lv_button_create(lv_screen_active());
    // lv_obj_t * skill = lv_button_create(lv_screen_active());
    lv_obj_t * red = lv_button_create(lv_screen_active());
    /* Set parent-sized width, and content-sized height */
    lv_obj_set_size(red, lv_pct(100), LV_SIZE_CONTENT);
    /* Align to the right center with 20px offset horizontally */
    lv_obj_align(red, LV_ALIGN_RIGHT_MID, -20, 0);

    lv_obj_t * my_label1 = lv_label_create(red);
    lv_label_set_text_fmt(my_label1, "Click me!");
    lv_obj_set_style_text_color(my_label1, lv_color_hex(0xff0000), 0);

}
void initialize() {
  pros::lcd::initialize();
  optical.set_led_pwm(50);
  setupLVGLGUI();
  chassis.calibrate(); // calibrate lemLib
    // pros::Task splashScreenTask(Logo_Popup);
    // autonSelectorGUI();        // hiển thị menu LVGL
    
    // chassis.calibrate();
    // pros::lcd::print(0, "Press center button to change auton");
    // pros::lcd::print(3, "Auton: %s", mode[auton_id]);
    // pros::lcd::register_btn1_cb(on_center_button);
    
}