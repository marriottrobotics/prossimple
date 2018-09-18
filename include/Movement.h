#pragma once

#include <API.h>
#include "Pid_Core.h"
#include "GameState.h"

//Pi, to probably more decimal places than we'll need.
#define PI 3.14159265359

//Allows the user to instruct the movement what size wheels it will be using as well as what motors are for
void setupMovements(struct pid *left, struct pid *right, float ticksPerRot, float diameter);
//Helper method to tell the movement what the drive motors are without including wheel information.
void defineDriveMotors(struct pid *left, struct pid *right);
//Helper method to tell the movement what the wheel dimensions are without including the drive motors.
void defineWheels(float ticksPerRot, float diameter);

/*Moves the robot a distance based on the ticks imput.
* Variable:
*   ticks - the number of ticks to move in a direction. Positive is forward, negative is backwards.
*   waitTarget - If true, this method will return after the action is completed. Otherwise, it will return immediatly.
*/
void drive(int ticks, bool waitTarget);
/*Moves the robot a distance forward based on the ticks imput.
* Variable:
*   ticks - the number of ticks to move in a direction. Should be positive.
*   waitTarget - If true, this method will return after the action is completed. Otherwise, it will return immediatly.
*/
void driveForward(int ticksIn, bool waitTarget);
/*Moves the robot a distance backwards based on the ticks imput.
* Variable:
*   ticks - the number of ticks to move in a direction. Should be positive.
*   waitTarget - If true, this method will return after the action is completed. Otherwise, it will return immediatly.
*/
void driveBackwards(int ticksIn, bool waitTarget);
/*Moves the robot the number of centimeters indicated using the values passed from setupMovements()
* Variable:
*   cm - the number of centimeters to move in a direction. Positive is forward, negative is backwards.
*   waitTarget - If true, this method will return after the action is completed. Otherwise, it will return immediatly.
*/
void driveCm(float cm, bool waitTarget);
/*Turns the robot a defined number of ticks "up" towards the top of the game board.
*   Requires game state to be properly configured.
*/
void turnUp(int ticks, bool waitTarget);
/*Turns the robot a defined number of ticks "down" towards the top of the game board.
*   Requires game state to be properly configured.
*/
void turnDown(int ticks, bool waitTarget);
