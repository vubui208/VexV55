    #pragma once
    #include "liblvgl/misc/lv_area.h"
    #include "liblvgl/misc/lv_types.h"
    #include "main.h"
#include "pros/misc.h"
#include "subsystemFiles/define.hpp"
    inline lv_obj_t *screen;

    inline lv_group_t *calibrate;
    inline lv_obj_t* ta = nullptr;
    inline lv_obj_t* ta2 = nullptr;
    inline lv_obj_t* cont = nullptr;
    inline lv_obj_t* cont2 = nullptr;
    inline int value = 10;
    inline int value2 = 20;
    inline int chosen = 1;
    static void _apply_value_to_ui(void*) {
        
        if (!ta) return;  // ta chưa được tạo thì bỏ qua
        char buf[16];
        
        if(chosen == 1 ){
            snprintf(buf, sizeof(buf), "X: %d", value);
            lv_textarea_set_text(ta, buf);
        }else if (chosen == 2){
            snprintf(buf, sizeof(buf), "Y: %d", value2);
            lv_textarea_set_text(ta2, buf);
        }
        
    }
    static void update_ta_style() {
  // X
    lv_obj_set_style_bg_color(
    cont,
    chosen == 1 ? lv_color_hex(0xEF4444) : lv_color_hex(0xE5E7EB),
    LV_PART_MAIN
  );

  lv_obj_set_style_bg_color(
    cont2,
    chosen == 2 ? lv_color_hex(0xEF4444) : lv_color_hex(0xE5E7EB),
    LV_PART_MAIN
  );

  lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(cont2, LV_OPA_COVER, LV_PART_MAIN);
    }

    static void update_value_ui() {
    // Đẩy sang LVGL context để update ổn định
    lv_async_call(_apply_value_to_ui, nullptr);
    }
    inline void handleType(){
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)&& chosen!= 2) {
            chosen = 2;
            update_ta_style();
            master.print(0,0,"2");
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) && chosen != 1) {
            chosen = 1;
            update_ta_style();
            master.print(0,0,"1");
    }
    }
    inline void handleCalibrateController() {
    // master là controller chính trong PROS (main.h thường có sẵn)
    // Nếu project bạn không có, thay bằng: pros::Controller master(pros::E_CONTROLLER_MASTER);

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            if (chosen == 1){
                value--;
                
            }else if (chosen == 2){
                value2--;
            }
            update_value_ui();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            if (chosen == 1){
                value++;
                
            }else if (chosen == 2){
                value2++;
            }
            update_value_ui();
        }
    }


    inline void setupCalibrate(){
        screen = lv_obj_create(NULL);
        cont = lv_obj_create(screen);
        lv_obj_set_size(cont, 260, 70);
        lv_obj_align(cont, LV_ALIGN_TOP_LEFT, 10, 10);

        lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

        ta = lv_textarea_create(cont);
        lv_obj_set_size(ta, 50, 30);
        lv_textarea_set_one_line(ta, true);
        lv_textarea_set_text(ta, "X: 10");
        cont2 = lv_obj_create(screen);
        lv_obj_set_size(cont2, 260, 70);
        lv_obj_align(cont2, LV_ALIGN_TOP_LEFT, 10, 10 + 70 + 10); // dưới cont1

        lv_obj_set_flex_flow(cont2, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(
        cont2,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
        );

        ta2 = lv_textarea_create(cont2);
        lv_obj_set_size(ta2, 50, 30);
        lv_textarea_set_one_line(ta2, true);
        lv_textarea_set_text(ta2, "Y: 20");
        
    }