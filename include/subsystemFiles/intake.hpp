#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "api.h"
#include "lemlib/api.hpp"

extern const int BASE_SPEED;
extern const int BOOST;
extern int Speed;
extern bool mouthStatus;
extern bool highoutStatus;

void GetBall();
void LowTube();
void MidTube();
void HighTube();
void StopIntake();
void OpenMouth();
void PushBack();
void TurnAround();
void StopWheel();
void TurnLeft();
void TurnRight();

#endif