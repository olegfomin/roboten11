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
    unsigned int now; // being called from arduinoLoop() once for every iteration

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
    Lever(uint64_t     bitMask,
          unsigned int pinNumberOut,
          unsigned int pinNumberIn);

    bool isCommited();
    bool isComplete();
    bool isCancelled();

    unsigned int getTick(); // Tick gets assigned immediatelly after Lever got commited and it stays the same throughout the commit 

    void commit(unsigned int expiresInMillis, Listener* listener, unsigned int tickNumber); // Execute Lever now. Anything negative as a param is considered to be never expires. Returns Listener that gets triggered on completion. Tick number is a unique counter being incremented on each commit
    void cancel(); // being constantly called in a loop from the State and in the very beginning during commit
    virtual bool arduinoLoop(); // being constantly called in a loop from the State
    virtual void arduinoSetup(); // being called once during setting the pin modes up from the State

};
/* Work like real tumbler switch with two positions on and off. It is a good parent for a relay and a LED levers */
class TumblerSwitchLever : public Lever {
  protected:
    bool state = false;
  public:
    TumblerSwitchLever(uint64_t     bitMask,
                       unsigned int pinNumberOut,
                       unsigned int pinNumberIn);
    void switchOn(Listener* listener);
    void switchOff(Listener* listener);                   
};

/* Automatically switches on and off periodically. The time it stays ON defined by Param1 and it stays OFF defined by Param2 */
class BlinkSwitchLever : public TumblerSwitchLever {
  private:
    bool state = false; // false - off/ true - On
    unsigned int nextStateChangeMillis=0;

  public: 
    BlinkSwitchLever(uint64_t     bitMask,
                     unsigned int pinNumberOut,
                     unsigned int pinNumberIn,
                     int          stayOnMillis,
                     int          stayOffMillis);
    void setStayOnMillis(int stayOnMillis); // Alias for Param1
    int getStayOnMillis();
    void setStayOffMillis(int stayOffMillis); // Alias for Param2
    int getStayOffMillis();                
    virtual bool arduinoLoop(); // being constantly called in a loop from the State
};

/* Controls left rear LED blinking frequency you can also making stay on all the time by setting the setStayOnMillis(MAX_INT) */
class LeftRearLightLever : public BlinkSwitchLever {
  private:
  public:
    LeftRearLightLever(); 
};

/* Controls right rear LED blinking frequency you can also making stay on all the time by setting the setStayOnMillis(MAX_INT) */
class RightRearLightLever : public BlinkSwitchLever {
  private:
  public:
    RightRearLightLever(); 
};

/* Controls right front LED blinking frequency you can also making stay on all the time by setting the setStayOnMillis(MAX_INT) */
class RightFrontLightLever : public BlinkSwitchLever {
  private:
  public:
    RightFrontLightLever(); 
};

/* Controls left front LED blinking frequency you can also making stay on all the time by setting the setStayOnMillis(MAX_INT) */
class LeftFrontLightLever : public BlinkSwitchLever {
  private:
  public:
    LeftFrontLightLever(); 
};



#endif
