#include <API.h>

#include "Movement.h"
#include "Pid_Core.h"
#include "GameState.h"

struct pid *leftDrive;
struct pid *rightDrive;

void defineDriveMotors(struct pid *left, struct pid *right){
  leftDrive = left;
  rightDrive = right;
}

void driveForward(int ticksIn){
  leftDrive->mtarget += ticksIn;
  rightDrive->mtarget += ticksIn;
}
void driveBackwards(int ticksIn){
  leftDrive->mtarget -= ticksIn;
  rightDrive->mtarget -= ticksIn;
}

void turnUp(int ticks){
  if(isStartRed()){
    rightDrive->mtarget += ticks;
    leftDrive->mtarget -= ticks;
  }else if(isStartBlue()){
    rightDrive->mtarget -= ticks;
    leftDrive->mtarget += ticks;
  }
}

void turnDown(int ticks){
  if(isStartRed()){
    rightDrive->mtarget -= ticks;
    leftDrive->mtarget += ticks;
  }else if(isStartBlue()){
    rightDrive->mtarget += ticks;
    leftDrive->mtarget -= ticks;
  }
}
