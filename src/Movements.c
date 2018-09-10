#include <API.h>

#include "Movement.h"
#include "Pid_Core.h"

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

void turnUp(int ticks){ //Todo, complete with more info.

}
void turnDown(int ticks){ //Todo, complete with more info.

}
