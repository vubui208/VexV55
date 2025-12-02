#include "main.h"

lv_obj_t *scr = lv_screen_active();
lv_obj_t *logo = lv_image_create(scr);

AutonSelection autonSelection = RED_LEFT;
static lv_obj_t *auton_label;

static void red_left(lv_event_t *e) {
    autonSelection = RED_LEFT;
    lv_label_set_text(auton_label, "Choose: RED LEFT");
}
static void red_right(lv_event_t *e) {
    autonSelection = RED_RIGHT;
    lv_label_set_text(auton_label, "Choose: RED RIGHT");
}
static void blue_left(lv_event_t *e) {
    autonSelection = BLUE_LEFT;
    lv_label_set_text(auton_label, "Choose: BLUE LEFT");
}
static void blue_right(lv_event_t *e) {
    autonSelection = BLUE_RIGHT;
    lv_label_set_text(auton_label, "Choose: BLUE RIGHT");
}
void saveAutonSelection(int autonSelection) {
    FILE* file = fopen("/static/auton_selection.txt", "w");
    if (file != nullptr) {
        fprintf(file, "%d", autonSelection);
        fclose(file);
    } else {
        pros::lcd::print(0, "Error opening file for writing.");
    }
}
int loadAutonSelection() {
    FILE* file = fopen("/usd/auton_selection.txt", "r");
    int autonSelection = 0;
    if (file != nullptr) {
        fscanf(file, "%d", &autonSelection);
        fclose(file);
    } else {
        pros::lcd::print(0, "Error opening file for reading.");
    }
    return autonSelection;
}
void screen_event_cb(lv_event_t *e) { lv_obj_clean(logo); }

bool logoDismissed = false;

void removeLogo() {
    if (!logoDismissed && logo != NULL) {
        lv_obj_delete(logo);
        logo = NULL;
        logoDismissed = true;
    }
}

static void logo_event_handler(lv_event_t* e) {
    removeLogo();
}

void Logo_Popup(void* param) {
    // Tạo logo
    lv_image_set_src(logo, &Logo);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(logo, logo_event_handler, LV_EVENT_CLICKED, NULL);

    uint32_t startTime = pros::millis();

    while (pros::millis() - startTime < 3000 && !logoDismissed) {
        // Kiểm tra nhấn nút controller
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) ||
            master.get_digital(pros::E_CONTROLLER_DIGITAL_B) ||
            master.get_digital(pros::E_CONTROLLER_DIGITAL_X) ||
            master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            removeLogo();
            break;
        }

        pros::delay(20);
    }

    // Nếu vẫn còn sau 3 giây thì tự xóa
    removeLogo();
    return;
}

void autonSelectorGUI() {
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);

    // Set background to black
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // Create Logo
    


    // Delete Logo
    // uint32_t start_time = pros::millis();
    // while (pros::millis() - start_time < 3000) {
    //   	if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) ||
    //       	master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) ||
    //       	master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) ||
    //       	master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
	// 		lv_obj_clean(logo);
    //     }
    //     lv_obj_add_event_cb(scr, screen_event_cb, LV_EVENT_PRESSED, nullptr);
    // 	pros::delay(15);
	// }
    // lv_obj_clean(logo);
    // Delete Logo

    // lv_obj_t *title = lv_label_create(scr);
    // lv_label_set_text(title, "Choose Auton");
    // lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // // Label hiển thị auton hiện tại
    // auton_label = lv_label_create(scr);
    // lv_label_set_text(auton_label, "Chon: RED LEFT");
    // lv_obj_align(auton_label, LV_ALIGN_BOTTOM_MID, 0, -10);

    // // === Tạo các nút ===
    // // Red Left
    // lv_obj_t *btn_red_left = lv_button_create(scr);
    // lv_obj_set_size(btn_red_left, 200, 80);
    // lv_obj_align(btn_red_left, LV_ALIGN_LEFT_MID, 20, -60);
    // lv_obj_set_style_bg_color(btn_red_left, lv_color_hex(0xCC0000), 0);
    // lv_obj_add_event_cb(btn_red_left, red_left, LV_EVENT_CLICKED, NULL);
    // lv_obj_t *lbl1 = lv_label_create(btn_red_left);
    // lv_label_set_text(lbl1, "RED LEFT");
    // lv_obj_center(lbl1);

    // // Red Right
    // lv_obj_t *btn_red_right = lv_button_create(scr);
    // lv_obj_set_size(btn_red_right, 200, 80);
    // lv_obj_align(btn_red_right, LV_ALIGN_LEFT_MID, 20, 60);
    // lv_obj_set_style_bg_color(btn_red_right, lv_color_hex(0x990000), 0);
    // lv_obj_add_event_cb(btn_red_right, red_right, LV_EVENT_CLICKED, NULL);
    // lv_obj_t *lbl2 = lv_label_create(btn_red_right);
    // lv_label_set_text(lbl2, "RED RIGHT");
    // lv_obj_center(lbl2);

    // // Blue Left
    // lv_obj_t *btn_blue_left = lv_button_create(scr);
    // lv_obj_set_size(btn_blue_left, 200, 80);
    // lv_obj_align(btn_blue_left, LV_ALIGN_RIGHT_MID, -20, -60);
    // lv_obj_set_style_bg_color(btn_blue_left, lv_color_hex(0x004C99), 0);
    // lv_obj_add_event_cb(btn_blue_left, blue_left, LV_EVENT_CLICKED, NULL);
    // lv_obj_t *lbl3 = lv_label_create(btn_blue_left);
    // lv_label_set_text(lbl3, "BLUE LEFT");
    // lv_obj_center(lbl3);

    // // Blue Right
    // lv_obj_t *btn_blue_right = lv_button_create(scr);
    // lv_obj_set_size(btn_blue_right, 200, 80);
    // lv_obj_align(btn_blue_right, LV_ALIGN_RIGHT_MID, -20, 60);
    // lv_obj_set_style_bg_color(btn_blue_right, lv_color_hex(0x003366), 0);
    // lv_obj_add_event_cb(btn_blue_right, blue_right, LV_EVENT_CLICKED, NULL);
    // lv_obj_t *lbl4 = lv_label_create(btn_blue_right);
    // lv_label_set_text(lbl4, "BLUE RIGHT");
    // lv_obj_center(lbl4);
}


void redLeftAuton() {

}
void redRightAuton() {

}
void blueLeftAuton() {

}
void blueRightAuton() {

}