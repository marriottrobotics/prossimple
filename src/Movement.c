#include <API.h>

#include "Movement.h"
#include "Pid_Core.h"
#include "GameState.h"

struct pid *leftDriveA;
struct pid *leftDriveB;
struct pid *rightDriveA;
struct pid *rightDriveB;

float ticksPerCm;

float ticksPerDegree;

void waitForTarget(struct pid *left, struct pid *right);

void setupMovements(struct pid *left1, struct pid *left2, struct pid *right1, struct pid *right2, float ticksPerRot, float diameter, float robotDiameter){
  defineDriveMotors(left1, left2, right1, right2);
  defineWheels(ticksPerRot, diameter);
  defineRobot(diameter, robotDiameter, ticksPerRot);
}

void defineDriveMotors(struct pid *left1, struct pid *left2, struct pid *right1, struct pid *right2){
  leftDriveA = left1;
  leftDriveB = left2;
  rightDriveA = right1;
  rightDriveB = right2;
}

void defineWheels(float ticksPerRot, float diameter){
  ticksPerCm = ticksPerRot / diameter * PI;
}

void defineRobot(float wheelDiameter, float robotDiameter, float ticksPerRot){
  float top = (robotDiameter * PI) / (wheelDiameter * PI) * ticksPerRot;
  ticksPerDegree = top/360.0;
}

//Positive is forwards, negative is backwards.
void drive(int ticks, bool waitTarget){
  driveForward(ticks, waitTarget);
}

void driveForward(int ticksIn, bool waitTarget){
  leftDriveA->mtarget += ticksIn;
  leftDriveB->mtarget += ticksIn;
  rightDriveA->mtarget += ticksIn;
  rightDriveB->mtarget += ticksIn;

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void driveBackwards(int ticksIn, bool waitTarget){
  leftDriveA->mtarget -= ticksIn;
  leftDriveB->mtarget -= ticksIn;
  rightDriveA->mtarget -= ticksIn;
  rightDriveB->mtarget -= ticksIn;

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void driveCm(float cm, bool waitTarget){
  leftDriveA->mtarget += cm*ticksPerCm;
  leftDriveB->mtarget += cm*ticksPerCm;
  rightDriveA->mtarget -= cm*ticksPerCm;
  rightDriveB->mtarget -= cm*ticksPerCm;

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void turnUp(int ticks, bool waitTarget){
  if(isStartRed()){
    rightDriveA->mtarget += ticks;
    rightDriveB->mtarget += ticks;
    leftDriveA->mtarget -= ticks;
    leftDriveB->mtarget -= ticks;
  }else if(isStartBlue()){
    rightDriveA->mtarget -= ticks;
    rightDriveB->mtarget -= ticks;
    leftDriveA->mtarget += ticks;
    leftDriveB->mtarget += ticks;
  }

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void turnDown(int ticks, bool waitTarget){
  if(isStartRed()){
    rightDriveA->mtarget -= ticks;
    rightDriveB->mtarget -= ticks;
    leftDriveA->mtarget += ticks;
    leftDriveB->mtarget += ticks;
  }else if(isStartBlue()){
    rightDriveA->mtarget += ticks;
    rightDriveB->mtarget += ticks;
    leftDriveA->mtarget -= ticks;
    leftDriveB->mtarget -= ticks;
  }

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void turnDegrees(float degrees, bool waitTarget){
  rightDriveA->mtarget += degrees * ticksPerDegree;
  rightDriveB->mtarget += degrees * ticksPerDegree;
  leftDriveA->mtarget -= degrees * ticksPerDegree;
  leftDriveB->mtarget -= degrees * ticksPerDegree;

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void turnUpDeg(float degrees, bool waitTarget){
  if(isStartRed()){
    rightDriveA->mtarget += degrees*ticksPerDegree;
    rightDriveB->mtarget += degrees*ticksPerDegree;
    leftDriveA->mtarget -= degrees*ticksPerDegree;
    leftDriveB->mtarget -= degrees*ticksPerDegree;
  }else if(isStartBlue()){
    rightDriveA->mtarget -= degrees*ticksPerDegree;
    rightDriveB->mtarget -= degrees*ticksPerDegree;
    leftDriveA->mtarget += degrees*ticksPerDegree;
    leftDriveB->mtarget += degrees*ticksPerDegree;
  }

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void turnDownDeg(float degrees, bool waitTarget){
  if(isStartRed()){
    rightDriveA->mtarget -= degrees*ticksPerDegree;
    rightDriveB->mtarget -= degrees*ticksPerDegree;
    leftDriveA->mtarget += degrees*ticksPerDegree;
    leftDriveB->mtarget += degrees*ticksPerDegree;
  }else if(isStartBlue()){
    rightDriveA->mtarget += degrees*ticksPerDegree;
    rightDriveB->mtarget += degrees*ticksPerDegree;
    leftDriveA->mtarget -= degrees*ticksPerDegree;
    leftDriveB->mtarget -= degrees*ticksPerDegree;
  }

  if(waitTarget){
    waitForTarget(leftDriveA, rightDriveA);
  }
}

void waitForTarget(struct pid *left, struct pid *right){
  wait_ontarget(left);
  wait_ontarget(right);
}
