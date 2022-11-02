#include "State.h"

State* state;

void setup() {
  state = new State();
  state->arduinoSetup();
}

void loop() {
  state->arduinoLoop();

}
