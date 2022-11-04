#include "Lever.h" 
#include <limits.h>

// Redundant constructor but without this method the Lever cmd[64] array is imposible to form 
Lever::Lever() {
};


Lever::Lever(unsigned int  tick,
            uint64_t       bitMask, 
             int*          intSourceParams,
             int           intSourceIndex,
             String*       strSourceParams,
             int           strSourceIndex ) {
  this->tick = tick;
  this->bitMask = bitMask;            
  this->intSourceParams = intSourceParams;
  this->intSourceIndex  = intSourceIndex;
  this->strSourceParams = strSourceParams;
  this->strSourceIndex  = strSourceIndex;
}

int Lever::getIntParam(int index) { // index must be zero or a positive number but less than 5
  if(index > intSourceIndex || index < 0) return INT_MIN;
  return intSourceParams[index];
}; 
String* Lever::getStrParam(int index){ // index must be a zero or positive number but less than 5
  if(index > strSourceIndex || index < 0) return NULL;
  return &strSourceParams[index];
}; 

bool Lever::addIntParam(int value) { //index must be a zero or positive number but less than 5
   if(intSourceIndex > 4) return false; 
   intSourceParams[intSourceIndex] = value ;              
   intSourceIndex++;
   return true;
}; 
bool Lever::addStrParam(String value){ // index must be a positive number but less than 5
   if(strSourceIndex > 4) return false; 
   strSourceParams[strSourceIndex] = value;
   strSourceIndex++;
   return true;
}; 

void Lever::commit(unsigned int expiresInMillis) {
  isCommitedFlag = true;
}

bool Lever::isCommited() {
  return isCommitedFlag & !isCompleteFlag;
}

bool Lever::isComplete() {
  return isCompleteFlag;
}

void Lever::arduinoLoop() {
  iterationNumber++;
}
