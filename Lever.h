#ifndef PAYLOAD
#define PAYLOAD

#include <Arduino.h>
#include "UsefulDefines.h"

/* Very generic Lever that is tied up to a parental State through its constructor. 
   You have to make a super class that will bring more meaning to very generic
   getters and setters */
class Lever {
  private:

    uint64_t* deviceMask;
    uint64_t* intParamMask;
    uint64_t* strParamMask;
    
    int* intParamArray;
    String* strParamArray;
    
    unsigned int tick;
    int intBufArrayIndex = 0;
    int intParamArrayBuffer[5]; // Using this buffers before commit(millis) Lever issued
    int strBufArrayIndex = 0 ;
    String strParamArrayBuffer[3];
    
    unsigned int createdOnMillis;
    unsigned int expiresInMillis;
  protected:
    int  iterationNumber= 0;
    bool isCommitedFlag = false;
    bool isCompleteFlag = false;

    int    getIntParam(int index); // index must be a positive number but less than 5
    String getStrParam(int index); // index must be a positive number but less than 3
    bool   addIntParam(int value); // Can contain upto five elements and then it'll start returning false. Return false if goes over capacity of 5 
    bool   addStrParam(String value); // Can contain upto three elements and after that it'll start returning false

  public:  
    Lever();
    Lever(unsigned int tick, 
            uint64_t* deviceMask,
            uint64_t* intParamMask,
            uint64_t* strParamMask,
            int* intParamArray, 
            String* paramArray);
            
    bool isCommited();
    bool isComplete();
     
    unsigned int getTick(); // Tick gets assigned immediatelly after Lever got generated and it stays the same throughout the commit 
    void commit(unsigned int expiresInMillis); // Execute Lever now
    void cancel(); // remove Lever from queue and delete it from memory
    void execute(); // being constantly called in a loop from the State

};

class LeftRearLight : Lever {
  
};


#endif
