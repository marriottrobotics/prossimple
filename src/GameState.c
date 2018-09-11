#include "GameState.h"

bool startRed;
bool startTop;

/*Call in the initalization if sensors are used to define these values.
* if this method isn't called, then nothing is going to work.*/
void init(bool colour, bool end){
  startRed = colour;
  startTop = end;
}

bool isStartRed(){
  if(startRed){
    return true;
  }
  return false;
}
bool isStartBlue(){
  if(!startRed){
    return true;
  }
  return false;
}

bool isStartTop(){
  if(startTop){
    return true;
  }
  return false;
}
bool isStartBottom(){
  if(!startTop){
    return true;
  }
  return false;
}
