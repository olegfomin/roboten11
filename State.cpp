/* Please see State.h for documentation */

#include "Command.h"
#include "State.h"
#include <Arduino.h>


State::State() {
  pinMode(LEFT_REAR_LED, OUTPUT);
  pinMode(RIGHT_REAR_LED, OUTPUT);
  pinMode(RIGHT_FRONT_LED, OUTPUT);
  pinMode(LEFT_FRONT_LED, OUTPUT); 
};

unsigned int State::getNIncrementTick() {
  return ++tick;
}

Command* State::leftRearLightOn() {
   if(commandStorageArray[11] != NULL) return commandStorageArray[11];
   uint64_t bit12 = BIT12;
   uint64_t bit9 = BIT9;
   Command* command = new Command(getNIncrementTick(), &bit12, &bit9, NULL, intParam, strParam); 
   commandExecutionArray[commandIndex] = command;
   commandStorageArray[11] = command;
   return command;
};

void State::execute() {
  if(commandIndex > COMMAND_INDEX_SQUIZZ_THRESHOLD) {
    commandIndex = squizz();
  }
  for(int i=0; i<commandIndex; i++) {
    Command* command = commandExecutionArray[i];
    if(command->isCommited()) {
      command->execute();
    } else if(command->isComplete()) {
      
    }
  }
}

int State::squizz() {
  Command newcommandExecutionArray[64];
  int newIndex=0;
  for(int i=0; i<commandIndex; i++) {
    Command* command = commandExecutionArray[i];
    if(!command->isComplete()) {
       commandExecutionArray[newIndex] = commandExecutionArray[i];
       newIndex++;
    }
  }  
  return newIndex;
}
