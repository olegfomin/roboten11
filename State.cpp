/* Please see State.h for documentation */

#include "Lever.h"
#include "State.h"
#include <Arduino.h>

State::State() {
  leverNparamsArray[0] = new LeverNparams(

};

void State::arduinoSetup() {
  pinMode(LEFT_REAR_LED, OUTPUT);
  pinMode(RIGHT_REAR_LED, OUTPUT);
  pinMode(RIGHT_FRONT_LED, OUTPUT);
  pinMode(LEFT_FRONT_LED, OUTPUT); 
};


unsigned int State::getNIncrementTick() {
  return ++tick;
}

Lever* State::leftRearLight() {
//   if(LeverNparamsArray[11] != NULL) return LeverStorageArray[11];
   uint64_t bit12 = BIT12;
   uint64_t bit9 = BIT9;
   Lever* lever = new Lever(getNIncrementTick(), &bit12, &bit9, NULL, intParam, strParam); 
   leverExecutionArray[leverIndex] = lever;
   return lever;
};

void State::arduinoLoop() {
  if(leverIndex > Lever_INDEX_SQUIZZ_THRESHOLD) {
    leverIndex = squizz();
  }
  for(int i=0; i<leverIndex; i++) {
    Lever* lever = leverExecutionArray[i];
    if(lever->isCommited()) {
      lever->execute();
    } else if(lever->isComplete()) {
      
    }
  }
}

int State::squizz() {
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
