#include "ExecutionQueue.h"

int ExecutionQueue::squizz() {
  int newIndex=0;
  for(int i=0; i<leverIndex; i++) {
    Lever* lever = leverExecutionArray[i];
    if(!lever->isComplete()) {
       leverExecutionArray[newIndex] = leverExecutionArray[i];
       newIndex++;
    }
  }  
  return newIndex;
}

void ExecutionQueue::arduinoLoop() {
  if(leverIndex > Lever_INDEX_SQUIZZ_THRESHOLD) {
    leverIndex = squizz();
  }
  for(int i=0; i<leverIndex; i++) {
    Lever* lever = leverExecutionArray[i];
    if(lever->isCommited()) {
      lever->arduinoLoop();
    } else if(lever->isComplete()) {
      
    }
  }
}

bool ExecutionQueue::addLever(Lever* lever) {
  if(leverIndex < 64) {
    leverExecutionArray[leverIndex] = lever;
    leverIndex++;
    return true;
  } else {
    return false;
  }
}
