#include "State.h"
#include "ExecutionQueue.h"

State* state;
ExecutionQueue* executionQueue; 

void setup() {
  state = new State();
  state->arduinoSetup();
}

void loop() {
  executionQueue->arduinoLoop();

}
