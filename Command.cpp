#include "Command.h" 

// Redundant constructor but without this method the Command cmd[64] array is imposible to form 
Command::Command() {
};


Command::Command(unsigned int tick, 
                 uint64_t* deviceMask, 
                 uint64_t* intParamMask,
                 uint64_t* strParamMask,
                 int* intParamArray, 
                 String* strParamArray) {
  this->tick = tick;
  this->deviceMask = deviceMask;
  this->intParamMask = intParamMask;
  this->strParamMask = strParamMask;
  this->intParamArray = intParamArray;
  this->strParamArray = strParamArray;
}

int    Command::getIntParam(int index) { // index must be zero or a positive number but less than 5
  return intParamArrayBuffer[index];
}; 
String Command::getStrParam(int index){ // index must be a zero or positive number but less than 3
  return strParamArrayBuffer[index];
  intBufArrayIndex = intParamArrayBuffer[index];
}; 
bool Command::addIntParam(int value) { //index must be a zero or positive number but less than 5
   if(intBufArrayIndex > 4) return false; 
   intParamArrayBuffer[intBufArrayIndex] = value ;              
   intBufArrayIndex++;
   return true;
}; 
bool Command::addStrParam(String value){ // index must be a positive number but less than 3
   if(strBufArrayIndex > 2) return false; 
   strParamArrayBuffer[strBufArrayIndex] = value;
   strBufArrayIndex++;
   return true;
}; 

void Command::commit(unsigned int expiresInMillis) {
/*  for(int i=0; i<intBufArrayIndex, i++) {
    
    
  }
  this->expiresInMillis = expiresInMillis; */
  isCommitedFlag = true;
}

bool Command::isCommited() {
  return isCommitedFlag & !isCompleteFlag;
}

bool Command::isComplete() {
  return isCompleteFlag;
}

void Command::execute() {
  iterationNumber++;
}
