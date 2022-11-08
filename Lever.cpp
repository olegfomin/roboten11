#include "Lever.h" 
#include <limits.h>

// Redundant constructor but without this method the Lever cmd[64] array is imposible to form 
Lever::Lever() {
};

Lever::Lever(unsigned int  tick,
             uint64_t      bitMask,
             unsigned int  pinNumberOut,
             unsigned int  pinNumberIn) {
  this->tick       = tick;
  this->bitMask   = bitMask;  
  this->pinNumberOut = pinNumberOut;
  this->pinNumberIn = pinNumberIn;
};

int Lever::getIntParam1() {   
  return intParam1;
};

void Lever::setIntParam1(int param1) {
  this->intParam1 = param1;
};

int Lever::getIntParam2() {
  return intParam2; 
};

void Lever::setIntParam2(int param2) {
  this->intParam2 = param2;
};

String Lever::getStrParam1() {   
  return strParam1;
};

void Lever::setStrParam1(String param1) {
  this->strParam1 = param1;
};

String Lever::getStrParam2() {
  return strParam2; 
};

void Lever::setStrParam2(String param2) {
  this->strParam2 = param2;
}

unsigned int Lever::getPinNumberOut() {
  return this->pinNumberOut;
};

unsigned int Lever::getPinNumberIn() {
  return this->pinNumberIn;
};

void Lever::commit(unsigned int expiresInMillis, Listener* listener) {
  isCompleteFlag = false;
  this->expiresInMillis = expiresInMillis;
  this->commitedOnMillis = millis();
  this->expiresOnMillis = this->commitedOnMillis+expiresInMillis; 
  isCommitedFlag = true;
  this->listener = listener;
  arduinoLoop();
};

bool Lever::isCommited() {
  return isCommitedFlag & !isCompleteFlag;
};

bool Lever::isComplete() {
  return isCompleteFlag;
};

void Lever::arduinoSetup() {
  if(pinNumberOut != INT_MAX) pinMode(pinNumberOut, OUTPUT);
  if(pinNumberIn != INT_MAX) pinMode(pinNumberIn, INPUT);
};

bool Lever::arduinoLoop() { // If true then the client should continue calling the loop otherwise it should stop 
  now = millis();
  isCompleteFlag = (now>=expiresOnMillis);
  if(isCompleteFlag) {
    listener->onEvent(0, "", "");
    return false;
  }
  iterationNumber++;
  return true;
};

/****************************************************************************************************************************************************************/
TumblerSwitchLever::TumblerSwitchLever(unsigned int tick, uint64_t bitMask, unsigned int  pinNumberOut, unsigned int  pinNumberIn) : Lever(tick, bitMask, pinNumberOut, pinNumberIn) {
  
};

void TumblerSwitchLever::switchOn(Listener* listener) {
  digitalWrite(pinNumberOut, HIGH);
  if(listener != NULL) listener->onEvent(0, String(""), String(""));
};

void TumblerSwitchLever::switchOff(Listener* listener) {
  digitalWrite(pinNumberOut, LOW);
  if(listener != NULL) listener->onEvent(0, String(""), String(""));
};


/*****************************************************************************************************************************************************************/
BlinkSwitchLever::BlinkSwitchLever(unsigned int tick, uint64_t bitMask, unsigned int  pinNumberOut, unsigned int  pinNumberIn, int stayOnMillis, int stayOffMillis) : TumblerSwitchLever(tick, bitMask, pinNumberOut, pinNumberIn) {
};

void BlinkSwitchLever::setStayOnMillis(int stayOnMillis) { // Alias for Param1
  this->setIntParam1(stayOnMillis);
}
int BlinkSwitchLever::getStayOnMillis() {
  return this->getIntParam1();
}
void BlinkSwitchLever::setStayOffMillis(int stayOffMillis) { // Alias for Param2
   this->setIntParam2(stayOffMillis);
};
int BlinkSwitchLever::getStayOffMillis() {
   this->getIntParam2();
};
bool BlinkSwitchLever::arduinoLoop() {
  if(!Lever::arduinoLoop()) return false;
  if(now > nextStateChangeMillis) {
    int period = INT_MAX;
    if(state) { // if true it means that currently it is ON so we have to switch it off
      switchOff(listener);
      period = getStayOffMillis();
    } else { // if false it means that currently it is OFF so we have to switch it on
      switchOn(listener);
      period = getStayOnMillis();
    }
    nextStateChangeMillis = now + period; // Calculating next time when we have to swap the state
  }
  return true;
  
};                
/********************************************************************************************************************************************************************/


LeftRearLightLever::LeftRearLightLever(unsigned int tick) : Lever(tick, BIT12, 52, 0) {
  this->tick = tick;
};
