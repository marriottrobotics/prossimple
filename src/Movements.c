#include <API.h>

#include "Movement.h"
#include "Pid_Core.h"
#include "GameState.h"

struct pid *leftDrive;
struct pid *rightDrive;

float ticksPerCm;

void waitForTarget(struct pid *left, struct pid *right);

void setupMovements(struct pid *left, struct pid *right, float ticksPerRot, float diameter){
  defineDriveMotors(left, right);
  defineWheels(ticksPerRot, diameter);
}

void defineDriveMotors(struct pid *left, struct pid *right){
  leftDrive = left;
  rightDrive = right;
}

void defineWheels(float ticksPerRot, float diameter){
  ticksPerCm = ticksPerRot / diameter * PI;
}

//Positive is forwards, negative is backwards.
void drive(int ticks, bool waitTarget){
  driveForward(ticks, waitTarget);
}

void driveForward(int ticksIn, bool waitTarget){
  leftDrive->mtarget += ticksIn;
  rightDrive->mtarget += ticksIn;

  if(waitTarget){
    waitForTarget(leftDrive, rightDrive);
  }
}

void driveBackwards(int ticksIn, bool waitTarget){
  leftDrive->mtarget -= ticksIn;
  rightDrive->mtarget -= ticksIn;

  if(waitTarget){
    waitForTarget(leftDrive, rightDrive);
  }
}

void driveCm(float cm, bool waitTarget){
  leftDrive->mtarget += cm*ticksPerCm;
  rightDrive->mtarget -= cm*ticksPerCm;

  if(waitTarget){
    waitForTarget(leftDrive, rightDrive);
  }
}

void turnUp(int ticks, bool waitTarget){
  if(isStartRed()){
    rightDrive->mtarget += ticks;
    leftDrive->mtarget -= ticks;
  }else if(isStartBlue()){
    rightDrive->mtarget -= ticks;
    leftDrive->mtarget += ticks;
  }

  if(waitTarget){
    waitForTarget(leftDrive, rightDrive);
  }
}

void turnDown(int ticks, bool waitTarget){
  if(isStartRed()){
    rightDrive->mtarget -= ticks;
    leftDrive->mtarget += ticks;
  }else if(isStartBlue()){
    rightDrive->mtarget += ticks;
    leftDrive->mtarget -= ticks;
  }

  if(waitTarget){
    waitForTarget(leftDrive, rightDrive);
  }
}

void waitForTarget(struct pid *left, struct pid *right){
  wait_ontarget(left);
  wait_ontarget(right);
}
