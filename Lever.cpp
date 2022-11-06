#include "Lever.h" 
#include <limits.h>

// Redundant constructor but without this method the Lever cmd[64] array is imposible to form 
Lever::Lever() {
};


Lever::Lever(unsigned int  tick,
             uint64_t      bitMask,
             unsigned int  pinNumber) {
  this->tick       = tick;
  this->bitMask   = bitMask;  
  this->pinNumber = pinNumber;
}

int Lever::getIntParam1() {   
  return intParam1;
};

void Lever::setIntParam1(int param1) {
  this->intParam1 = param1;
}

int Lever::getIntParam2() {
  return intParam2; 
}

void Lever::setIntParam2(int param2) {
  this->intParam2 = param2;
}

String Lever::getStrParam1() {   
  return strParam1;
};

void Lever::setStrParam1(String param1) {
  this->strParam1 = param1;
}

String Lever::getStrParam2() {
  return strParam2; 
}

void Lever::setStrParam2(String param2) {
  this->strParam2 = param2;
}



unsigned int Lever::getPinNumber() {
  return this->pinNumber;
};


Listener Lever::commit(unsigned int expiresInMillis) {
  isCompleteFlag = false;
  this->expiresInMillis = expiresInMillis;
  this->commitedOnMillis = millis();
  this->expiresOnMillis = this->commitedOnMillis+expiresInMillis; 
  isCommitedFlag = true;
  arduinoLoop();
};

bool Lever::isCommited() {
  return isCommitedFlag & !isCompleteFlag;
};

bool Lever::isComplete() {
  return isCompleteFlag;
};

void Lever::arduinoLoop() {
  unsigned int now = millis();
  isCompleteFlag = (now>=expiresOnMillis);
  iterationNumber++;
};

/****************************************************************************************************************************************************************/
TumblerSwitchLever::TumblerSwitchLever(unsigned int tick, uint64_t bitMask, unsigned int  pinNumber) : Lever(unsigned int  tick, uint64_t bitMask, unsigned int  pinNumber) {
  
}





/*****************************************************************************************************************************************************************/
LeftRearLightLever::LeftRearLightLever(unsigned int tick) : Lever(tick, BIT12, 52, new int[1], 1, NULL, 0) {
  this->tick = tick;
};

void LeftRearLightLever::setBlinkFreqiency(int howOften) {
  intSourceParams[0] = howOften;
};

void LeftRearLightLever::arduinoLoop() {
  Lever::arduinoLoop();
  if(isComplete()) return; // If all completed then exiting
  int onTime = 0;
  int offTime = INT_MAX;
  switch(intSourceParams[0]){
    case 0: onTime = INT_MAX; offTime = 0; break;
    case 1: onTime = 750; offTime = 500; break;
    case 2: onTime = 300; offTime = 200; break;
    default: onTime=1000; offTime = 300; break;// TODO send the message into the log error message queue 
  }
  if(now > nextStateChange && !state) {
    
  }
  
};
