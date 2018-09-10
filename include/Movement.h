#pragma once

#include <API.h>
#include "Pid_Core.h"
#include "GameState.h"

//extern struct pid *leftDrive;
//extern struct pid *rightDrive;

//extern float ticksPerRot; //To implement later.
//extern float distancePerRot; //To implement later.

void defineDriveMotors(struct pid *left, struct pid *right);

void driveForward(int ticksIn);
void driveBackwards(int ticksIn);

void turnUp(int ticks);
void turnDown(int ticks);
