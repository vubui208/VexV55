#pragma once

#include "gui/calibratingAuton.hpp"
#include "liblvgl/misc/lv_area.h"
#include "main.h"

struct AutonInfo {
  std::string name;
  std::string description;
  std::string place;
  std::string accuracy;
};

inline std::vector<AutonInfo> longAuton = {
    {"LongGoal(6)", "6 balls long goal route", "forward", "high"},
    {"LongGoal(3)+Lower(3)", "3 long + 3 lower", "forward", "high"},
    {"Lower(3)+Mid(3)", "3 lower + 3 mid", "forward", "medium"},
    {"Solo", "Solo WP auton", "side", "low"},
};

inline std::vector<AutonInfo> centerAuton = {
    {"Center(4)+Long(2)", "4 center + 2 long", "forward", "high"},
    {"Center(4)+Lower(2)", "4 center + 2 lower", "forward", "medium"},
    {"Solo", "Solo WP auton", "side", "low"},
};

// LVGL objects

inline lv_obj_t *screen1;

inline lv_obj_t *colorButton;
inline lv_obj_t *autonButton;
inline lv_obj_t *sideButton;

inline lv_obj_t *centerCheck;
inline lv_obj_t *longCheck;
inline lv_obj_t *soloCheck;

inline lv_obj_t *title;
inline lv_obj_t *btnLeft;
inline lv_obj_t *btnRight;
inline lv_obj_t *btnMid;
inline lv_obj_t *colorLabel;
inline lv_obj_t *autonLabel;
inline lv_obj_t *pressureCheck;
inline lv_obj_t *wingCheck;

inline lv_obj_t *boxNote;

inline void CheckEventCb() {
  if (solo == true) {
    if (center == true) {
      if (longg == true) {
        // true true true
        lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      } else {
        // true true false
        lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      }
    } else {
      if (longg == true) {
        // true false true
        lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      } else {
        // true false false
        lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      }
    }
  } else {
    if (center == true) {
      if (longg == true) {
        // false true true
        lv_obj_remove_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      } else {
        // false true false
        lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      }
    } else {
      if (longg == true) {
        // false false true
        lv_obj_remove_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
      } else {
        // false false false
      }
    }
  }
}
inline void setupScreen1() {
  screen1 = lv_obj_create(NULL);

  /* LOGO */ {
    LV_IMAGE_DECLARE(logo);
    lv_obj_t *img = lv_image_create(screen1);
    lv_image_set_src(img, &logo);
    lv_obj_set_size(img, 480, 240);
    lv_image_set_scale(img, 100);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  }

  /* COLOR BUTTON */ {

    title = lv_label_create(screen1);
    lv_label_set_text(title, "Color:");
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN);

    colorButton = lv_button_create(screen1);
    lv_obj_set_pos(colorButton, 90, 10);
    lv_obj_add_event_cb(
        colorButton,
        [](lv_event_t *e) {
          if (colorChosen == -1 || colorChosen == 1) {
            lv_obj_set_style_bg_color(colorButton, lv_color_hex(0x0009FF),
                                      LV_PART_MAIN); // xanh
            lv_label_set_text(colorLabel, "BLUE");
            colorChosen = 0; // blue
          } else {
            lv_obj_set_style_bg_color(colorButton, lv_color_hex(0xE4080A),
                                      LV_PART_MAIN); // đỏ
            lv_label_set_text(colorLabel, "RED");
            colorChosen = 1; // red
          }
        },
        LV_EVENT_CLICKED, NULL);
    colorLabel = lv_label_create(colorButton);
    lv_label_set_text(colorLabel, "NONE");
    lv_obj_set_size(colorButton, LV_SIZE_CONTENT, 30);
    lv_obj_set_style_text_font(colorLabel, &lv_font_montserrat_20,
                               LV_PART_MAIN);
    lv_obj_set_style_bg_color(colorButton, lv_color_hex(0x86867B),
                              LV_PART_MAIN);
    lv_obj_center(colorLabel);
  }

  /* AUTON BUTTON */ {
    // AUTON BUTTON //
    title = lv_label_create(screen1);
    lv_label_set_text(title, "Auton:");
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 10, 50);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN);

    autonButton = lv_switch_create(screen1);
    lv_obj_set_pos(autonButton, 100, 50);
    lv_obj_set_style_bg_color(autonButton, lv_color_hex(0x7DDA58),
                              LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(autonButton, lv_color_hex(0x86867B),
                              LV_PART_MAIN);
    lv_obj_add_event_cb(
        autonButton,
        [](lv_event_t *e) {
          if (lv_obj_has_state(autonButton, LV_STATE_CHECKED)) {
            auton = true;
          } else {
            lv_obj_set_style_bg_color(autonButton, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            auton = false;
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);
  }

  /* SIDE BUTTONS */ {
    title = lv_label_create(screen1);
    lv_label_set_text(title, "Side:");
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 10, 90);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN);

    // Left Button
    btnLeft = lv_button_create(screen1);
    lv_obj_set_size(btnLeft, 30, 30);
    lv_obj_set_pos(btnLeft, 75, 90);
    lv_obj_add_event_cb(
        btnLeft,
        [](lv_event_t *e) {
          {
            sideChosen = 0;
            lv_obj_set_style_bg_color(btnLeft, lv_color_hex(0x00A0FF),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnMid, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnRight, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
          }
        },
        LV_EVENT_CLICKED, NULL);

    lv_obj_t *leftLabel = lv_label_create(btnLeft);
    lv_label_set_text(leftLabel, "<");
    lv_obj_set_style_text_font(leftLabel, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_center(leftLabel);
    // lv_obj_set_style_bg_color(btnLeft,  lv_color_hex(0x00A0FF),
    // LV_PART_MAIN);

    // Mid Button
    btnMid = lv_button_create(screen1);
    lv_obj_set_size(btnMid, 30, 30);
    lv_obj_set_pos(btnMid, 110, 90);
    lv_obj_add_event_cb(
        btnMid,
        [](lv_event_t *e) {
          {
            sideChosen = 1;
            lv_obj_set_style_bg_color(btnLeft, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnMid, lv_color_hex(0x00A0FF),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnRight, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
          }
        },
        LV_EVENT_CLICKED, NULL);

    lv_obj_t *midLabel = lv_label_create(btnMid);
    lv_label_set_text(midLabel, "=");
    lv_obj_set_style_text_font(midLabel, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_center(midLabel);

    // Right Button
    btnRight = lv_button_create(screen1);
    lv_obj_set_size(btnRight, 30, 30);
    lv_obj_set_pos(btnRight, 145, 90);
    lv_obj_add_event_cb(
        btnRight,
        [](lv_event_t *e) {
          {
            sideChosen = 2;
            lv_obj_set_style_bg_color(btnLeft, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnMid, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            lv_obj_set_style_bg_color(btnRight, lv_color_hex(0x00A0FF),
                                      LV_PART_MAIN);
          }
        },
        LV_EVENT_CLICKED, NULL);

    lv_obj_t *rightLabel = lv_label_create(btnRight);
    lv_label_set_text(rightLabel, ">");
    lv_obj_set_style_text_font(rightLabel, &lv_font_montserrat_24,
                               LV_PART_MAIN);
    lv_obj_center(rightLabel);
  }

  /* CENTER CHECK */ {
    centerCheck = lv_checkbox_create(screen1);
    lv_obj_set_pos(centerCheck, 10, 130);
    lv_checkbox_set_text(centerCheck, "Center");

    lv_obj_set_style_width(centerCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_height(centerCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(centerCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_height(centerCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_text_font(centerCheck, &lv_font_montserrat_20,
                               LV_PART_MAIN);

    lv_obj_add_event_cb(
        centerCheck,
        [](lv_event_t *e) {
          if (lv_obj_has_state(centerCheck, LV_STATE_CHECKED)) {
            center = true;
            CheckEventCb();
          } else {
            center = false;
            CheckEventCb();
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);
  }

  /* LONG CHECK */ {
    longCheck = lv_checkbox_create(screen1);
    lv_obj_set_pos(longCheck, 10, 165);
    lv_checkbox_set_text(longCheck, "Long");

    lv_obj_set_style_width(longCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_height(longCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(longCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_height(longCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_text_font(longCheck, &lv_font_montserrat_20, LV_PART_MAIN);

    lv_obj_add_event_cb(
        longCheck,
        [](lv_event_t *e) {
          if (lv_obj_has_state(longCheck, LV_STATE_CHECKED)) {
            longg = true;
            CheckEventCb();
          } else {
            longg = false;
            CheckEventCb();
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);
  }

  /* SOLO CHECK */ {
    soloCheck = lv_checkbox_create(screen1);
    lv_obj_set_pos(soloCheck, 10, 200);
    lv_checkbox_set_text(soloCheck, "Solo");

    lv_obj_set_style_width(soloCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_height(soloCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(soloCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_height(soloCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_text_font(soloCheck, &lv_font_montserrat_20, LV_PART_MAIN);

    lv_obj_add_event_cb(
        soloCheck,
        [](lv_event_t *e) {
          if (lv_obj_has_state(soloCheck, LV_STATE_CHECKED)) {
            solo = true;
            CheckEventCb();
          } else {
            solo = false;
            CheckEventCb();
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);
  }

  /* NOTE BOX*/ {
    boxNote = lv_obj_create(screen1);
    lv_obj_set_size(boxNote, 290, 150);
    lv_obj_align(boxNote, LV_ALIGN_BOTTOM_RIGHT, -5, -5);

    lv_obj_set_style_bg_color(boxNote, lv_color_hex(0xC2C2C2), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(boxNote, LV_OPA_30, LV_PART_MAIN);

    lv_obj_set_style_radius(boxNote, 14, LV_PART_MAIN);

    lv_obj_set_style_border_color(boxNote, lv_color_hex(0xC2C2C2),
                                  LV_PART_MAIN);
    lv_obj_set_style_border_width(boxNote, 2, LV_PART_MAIN);
    lv_obj_set_style_border_opa(boxNote, LV_OPA_40, LV_PART_MAIN);
  }

  /* LONG PRESSURE */ {
    pressureCheck = lv_checkbox_create(screen1);
    lv_obj_set_pos(pressureCheck, 340, 10);
    lv_checkbox_set_text(pressureCheck, "Pressure");

    lv_obj_set_style_width(pressureCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_height(pressureCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(pressureCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_height(pressureCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(pressureCheck, lv_color_hex(0xE4080A),
                              LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_border_color(pressureCheck, lv_color_hex(0xE4080A),
                                  LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_border_color(pressureCheck, lv_color_hex(0xE4080A),
                                  LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(pressureCheck, &lv_font_montserrat_20,
                               LV_PART_MAIN);
    lv_obj_add_event_cb(
        pressureCheck,
        [](lv_event_t *e) {
          if (lv_obj_has_state(pressureCheck, LV_STATE_CHECKED)) {
            press = true;
          } else {
            lv_obj_set_style_bg_color(pressureCheck, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            press = false;
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_flag(pressureCheck, LV_OBJ_FLAG_HIDDEN);
  }

  /* LONG WING */ {
    wingCheck = lv_checkbox_create(screen1);
    lv_obj_set_pos(wingCheck, 340, 50);
    lv_checkbox_set_text(wingCheck, "Wing");

    lv_obj_set_style_width(wingCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_height(wingCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(wingCheck, 100,
                           LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_height(wingCheck, 100,
                            LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(wingCheck, lv_color_hex(0xFFDE59),
                              LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(wingCheck, lv_color_hex(0xFFDE59),
                                  LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(wingCheck, lv_color_hex(0xFFDE59),
                                  LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(wingCheck, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_add_event_cb(
        wingCheck,
        [](lv_event_t *e) {
          if (lv_obj_has_state(wingCheck, LV_STATE_CHECKED)) {
            wing = true;
          } else {
            lv_obj_set_style_bg_color(wingCheck, lv_color_hex(0x86867B),
                                      LV_PART_MAIN);
            wing = false;
          }
        },
        LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_flag(wingCheck, LV_OBJ_FLAG_HIDDEN);
  }
}

inline void setupLVGLGUI() {
  pros::lcd::clear();
  setupCalibrate();
  lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
  lv_screen_load(screen);
}