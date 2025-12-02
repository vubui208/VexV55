#ifndef GUI_H
#define GUI_H

#include "main.h"

enum AutonSelection {
    RED_LEFT,
    RED_RIGHT,
    BLUE_LEFT,
    BLUE_RIGHT
};

extern AutonSelection autonSelection;

static void red_left(lv_event_t *e);
static void red_right(lv_event_t *e);
static void blue_left(lv_event_t *e);
static void blue_right(lv_event_t *e);
extern bool logoDismissed;

void removeLogo();

static void logo_event_handler(lv_event_t* e);

void Logo_Popup();
void autonSelectorGUI();


void redLeftAuton();
void redRightAuton();
void blueLeftAuton();
void blueRightAuton();
#endif