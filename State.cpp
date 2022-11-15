/* Please see State.h for documentation */

#include "Lever.h"
#include "State.h"
#include <Arduino.h>

LeverNparams::LeverNparams(Lever* lever, int index2IntParams, int lengthOfIntParams, int index2StrParams, int lengthOfStrParams) {
  this->lever = lever;
  this->index2IntParams = index2IntParams;
  this->lengthOfIntParams = lengthOfIntParams;
  this->index2StrParams = index2StrParams;
  this->lengthOfStrParams = lengthOfStrParams;
};
Lever* LeverNparams::getLever() {
  return this->lever;
};
int LeverNparams::getIndex2IntParams() {
  return this->index2IntParams;
};
int LeverNparams::getLength2IntParams() {
  return this->lengthOfIntParams;
};
int LeverNparams::getIndex2StrParams() {
  return this->index2StrParams;
};
int LeverNparams::getLength2StrParams() {
  return this->lengthOfStrParams;
};

State::State() {
  LeftRearLightLever* leftRearLightLever = new LeftRearLightLever();
  leverNparamsArray[12] = new LeverNparams(leftRearLightLever, 10, 2, 0, 0);
  leftRearLightLever->setStayOnMillis(intParam[10]);
  leftRearLightLever->setStayOffMillis(intParam[11]);

  
};

void State::arduinoSetup() {
  for(int i=0; i<64; i++) {
    if(leverNparamsArray[i] != NULL) leverNparamsArray[i]->getLever()->arduinoSetup();
  }
};


unsigned int State::getNIncrementTick() {
  return ++tick;
}

Lever* State::leftRearLight() {
 if(leverNparamsArray[12] != NULL) return leverNparamsArray[12]->getLever();
 else return NULL;
};
