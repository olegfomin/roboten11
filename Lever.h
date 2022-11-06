#ifndef LEVER
#define LEVER

#include <Arduino.h>
#include "Listener.h"
#include "UsefulDefines.h"

/* Very generic Lever that is tied up to a parental State through its constructor. 
   You have to make a super class that will bring more meaning to very generic
   getters and setters */
class Lever {
  protected:
    unsigned int  tick;
    uint64_t      bitMask;
    unsigned int  pinNumber; // Pin or UART port number that is being used
    int           intParam1; // INT_MIN is like NULL
    int           intParam2; // INT_MIN is like NULL
    String        strParam1;
    String        strParam2;   
    
    unsigned int commitedOnMillis; // when the record was commited 
    unsigned int expiresInMillis; // how many millis it has to stay valid from now (different from createdOn)!
    unsigned int expiresOnMillis; // commitedOnMillis + expiresInMillis  

    int  iterationNumber= 0;
    bool isCommitedFlag = false;
    bool isCompleteFlag = false;
    bool isCancelledFlag = false;
    
    int     getIntParam1(); // INT_MIN is like NULL
    void    setIntParam1(int param1); // INT_MIN is like NULL
    int     getIntParam2(); // INT_MIN is like NULL
    void    setIntParam2(int param2);
    
    String  getStrParam1(); // 
    void    setStrParam1(String param1);
    String  getStrParam2(); // 
    void    setStrParam2(String param2); 
    
    unsigned int getPinNumber();

  public:  
    Lever();
    Lever(unsigned int tick,
          uint64_t     bitMask,
          unsigned int pinNumber);

    bool isCommited();
    bool isComplete();
    bool isCancelled();
     
    unsigned int getTick(); // Tick gets assigned immediatelly after Lever got generated and it stays the same throughout the commit 
    Listener commit(unsigned int expiresInMillis); // Execute Lever now. Anything negative as a param is considered to be never expires. Returns Listener that gets triggered on completion
    void cancel(); // being constantly called in a loop from the State and in the very beginning during commit
    virtual void arduinoLoop(); // being constantly called in a loop from the State

};

class TumblerSwitchLever : public Lever {
  protected:
    bool state = false;
  public:
    TumblerSwitchLever(unsigned int tick,
                       uint64_t     bitMask,
                       unsigned int pinNumber);
    Listener switchOn();
    Listener switchOff();                   
};

class BlinkSwitchLever : public TumblerSwitchLever {
    BlinkSwitchLever(unsigned int tick,
                       uint64_t     bitMask,
                       unsigned int pinNumber);
};

class LeftRearLightLever : public Lever {
  private:
    bool isFirstTime = true;
    bool state = false; // false - off/ true - On
    unsigned int nextStateChange=0;
  public:
    LeftRearLightLever(unsigned int tick);    
    void setBlinkFreqiency(int howOften); // 0 - Steady light, 1 - Low frequency (750 mls on/500 mls off), 2 - High frequency (300 mls on/200 mls off)    
    virtual void arduinoLoop(); // being constantly called in a loop from the State and in the very beginning during commit
};


#endif
