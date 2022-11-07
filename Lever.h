#ifndef LEVER
#define LEVER

#include <Arduino.h>
#include <limits.h>
#include "Listener.h"
#include "UsefulDefines.h"

/* Very generic Lever that is tied up to a parental State through its constructor. 
   You have to make a super class that will bring more meaning to very generic
   getters and setters */
class Lever {
  protected:
    unsigned int  tick;
    uint64_t      bitMask;
    unsigned int  pinNumberOut=INT_MAX; // Pin or UART port number that is being used if it is INT_MAX then no pin number is applicable
    unsigned int  pinNumberIn=INT_MAX; // Pin or UART port number that is being used if it is INT_MAX then no pin number is applicable
    int           intParam1=INT_MIN; // INT_MIN is like NULL
    int           intParam2=INT_MIN; // INT_MIN is like NULL
    String        strParam1="";
    String        strParam2="";   
    
    unsigned int commitedOnMillis=0; // when the record was commited 
    unsigned int expiresInMillis=INT_MAX; // how many millis it has to stay valid from now (different from createdOn)!
    unsigned int expiresOnMillis=INT_MAX; // commitedOnMillis + expiresInMillis  

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
    
    unsigned int getPinNumberOut();
    unsigned int getPinNumberIn();
    Listener* listener;

  public:  
    Lever();
    Lever(unsigned int tick,
          uint64_t     bitMask,
          unsigned int pinNumberOut,
          unsigned int pinNumberIn);

    bool isCommited();
    bool isComplete();
    bool isCancelled();
     
    unsigned int getTick(); // Tick gets assigned immediatelly after Lever got generated and it stays the same throughout the commit 
    void commit(unsigned int expiresInMillis, Listener* listener); // Execute Lever now. Anything negative as a param is considered to be never expires. Returns Listener that gets triggered on completion
    void cancel(); // being constantly called in a loop from the State and in the very beginning during commit
    virtual void arduinoLoop(); // being constantly called in a loop from the State
    virtual void arduinoSetup(); // being called once during setting the pin modes up from the State

};
/* Work like real tumbler switch with two positions on and off. It is a good parent for a relay and a LED levers */
class TumblerSwitchLever : public Lever {
  protected:
    bool state = false;
  public:
    TumblerSwitchLever(unsigned int tick,
                       uint64_t     bitMask,
                       unsigned int pinNumberOut,
                       unsigned int pinNumberIn);
    void switchOn(Listener* listener);
    void switchOff(Listener* listener);                   
};

/* Automatically switches on and off periodically. The time it stays ON defined by Param1 and it stays OFF defined by Param2 */
class BlinkSwitchLever : public TumblerSwitchLever {
    BlinkSwitchLever(unsigned int tick,
                     uint64_t     bitMask,
                     unsigned int pinNumberOut,
                     unsigned int pinNumberIn,
                     unsigned int stayOnMillis,
                     unsigned int stayOffMillis);
    void setStayOnMillis(unsigned stayOnMillis); // Alias for Param1
    unsigned int getStayOnMillis();
    void setStayOffMillis(unsigned stayOffMillis); // Alias for Param2
    unsigned int getStayOffMillis();                
};

/* Controls left rear LED blinking frequency you can also making stay on by setting the setStayOnMillis(MAX_INT) */
class LeftRearLightLever : public Lever {
  private:
    bool state = false; // false - off/ true - On
    unsigned int nextStateChangeMillis=0;
  public:
    LeftRearLightLever(unsigned int tick);    
    virtual void arduinoLoop(); // being constantly called in a loop from the State
};


#endif
