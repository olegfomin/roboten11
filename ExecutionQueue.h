#ifndef EXECUTION_QUEUE
#define EXECUTION_QUEUE

#include "Lever.h"

class ExecutionQueue {
  private:
    static const int Lever_INDEX_SQUIZZ_THRESHOLD = 55;
    Lever*        leverExecutionArray[64]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
                                              NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; 
  public:
    void arduinoLoop(); // Should be called in the Arduino's loop body
    int leverIndex=0; // execution queue index as soon as the index goes above threshold then the squizz procedure is engaged that would move all the active Lever to the left 
    int squizz(); // Goes through LeverArray if the Lever index >= threshold and verifies all completed Levers. If the Lever is complete then deleting it from array and memory if not then try to move it to the left as much as possible 
    bool addLever(Lever* lever);
};

#endif
