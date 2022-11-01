/* The state class that describes whci devices are engaged and which are at this moment of time. It can contain up to 21 integers and 3 strings. The code and parameter bitmap are described blow. 
 *  This class should expecially useful when sending the updates to PRi. 
 *  code field encoding looks like follows:
 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
                                         |||| |||| |||| |||| |||| |||| |||| ||||- 0. LCD 16x2 print strString[0], strString[1]
                                         |||| |||| |||| |||| |||| |||| |||| |||-- 1. Left Motor go at intParam[0] speed. Negativa values reverse  
                                         |||| |||| |||| |||| |||| |||| |||| ||--- 2. Right Motor go at intParam[1] speed. Negative value reverse 
                                         |||| |||| |||| |||| |||| |||| |||| |---- 3. Apply emergency brake for all motors
                                         |||| |||| |||| |||| |||| |||| 
                                         |||| |||| |||| |||| |||| |||| ||||------ 4. PAN Servo for camera intParam[2]
                                         |||| |||| |||| |||| |||| |||| |||------- 5. TILT Servo for camera intParam[3]
                                         |||| |||| |||| |||| |||| |||| ||-------- 6. Reserved for Servo intParam[4]
                                         |||| |||| |||| |||| |||| |||| |--------  7. Reserved for Servo intParam[5]
                                         |||| |||| |||| |||| |||| ||||
                                         |||| |||| |||| |||| |||| ||||----------  8. Reserved for Servo intParam[6]
                                         |||| |||| |||| |||| |||| |||-----------  9. Resevred for Servo intParam[7]
                                         |||| |||| |||| |||| |||| ||------------  10. Resevred for Servo intParam[8]
                                         |||| |||| |||| |||| |||| |-------------  11. Current small screen menu position
                                         |||| |||| |||| |||| ||||
                                         |||| |||| |||| |||| ||||--------------- 12. Left Rear light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                         |||| |||| |||| |||| |||---------------- 13. Right Rear light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                         |||| |||| |||| |||| ||----------------- 14. Right Front light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                         |||| |||| |||| |||| |------------------ 15. Left Front light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                         |||| |||| |||| ||||
                                         |||| |||| |||| ||||-------------------- 16. Light Mode 0 - steady, 1 - blink
                                         |||| |||| |||| |||--------------------- 17. Left Front Sonar signal - intParam[9] 
                                         |||| |||| |||| ||---------------------- 18. Middle Front Sonar signal - intParam[10]  
                                         |||| |||| |||| |----------------------- 19. Right Front Sonar Signal - intParam[11]
                                         |||| |||| ||||
                                         |||| |||| ||||------------------------- 20. Reserved Sonar 1 Signal - intParam[12]
                                         |||| |||| |||-------------------------- 21. Reserved Sonar 2 Signal - intParam[13]
                                         |||| |||| ||--------------------------- 22. RPI Power relay
                                         |||| |||| |---------------------------- 23. Own Self Powered relay 
                                         |||| ||||
                                         |||| ||||------------------------------ 24. Relay 3
                                         |||| |||------------------------------- 25, Relay 4
                                         |||| ||-------------------------------- 26. Relay 5
                                         |||| |--------------------------------- 27. Left rear wheel counter intParam[14]
                                         ||||
                                         ||||----------------------------------- 28. Right rear wheel counter intParam[15]
                                         |||------------------------------------ 29. Front right wheel counter intParam[16]
                                         ||------------------------------------- 30. Front left wheel counter intParam[17]
                                         |-------------------------------------- 31. In case of transmission to RPI is it Update(0) or FullImage(1)
 
 "bitMask" is all about params supplied. It is relevenat usually during transmition
 First 21 bit reflect perense or absense of a param in intParam[] while strParam[] is represented by 3 next bits 

 The bit mask encoding for "int" params is as follow:
 0000 0000 0000 0000 0000 0000 0000 0000 
 |||| |||| |||| |||| |||| |||| |||| ||||- 0. Left motor speed value.Negativa values reverse 
 |||| |||| |||| |||| |||| |||| |||| |||-- 1. Right Motor speed value. Negativa values reverse  
 |||| |||| |||| |||| |||| |||| |||| ||--- 2. PAN Servo value; 
 |||| |||| |||| |||| |||| |||| |||| |---- 3. Tilt Servo value
 |||| |||| |||| |||| |||| |||| 
 |||| |||| |||| |||| |||| |||| ||||------ 4. Servo 1 value
 |||| |||| |||| |||| |||| |||| |||------- 5. Servo 2 value
 |||| |||| |||| |||| |||| |||| ||-------- 6. Servo 3 value
 |||| |||| |||| |||| |||| |||| |--------  7. Servo 4 value
 |||| |||| |||| |||| |||| ||||
 |||| |||| |||| |||| |||| ||||----------  8. Number in the small LCD menu
 |||| |||| |||| |||| |||| |||-----------  9. Left Rear light Mode 0 - turn on ones; 1 - long blink; 2 - fast blink (pin 52, see below)
 |||| |||| |||| |||| |||| ||------------  10.Right Rear light Mode 0 - turn on ones; 1 - long blink; 2 - fast blink (pin 49, see below) 
 |||| |||| |||| |||| |||| |-------------  11.Right Front light Mode 0 - turn on ones; 1 - long blink; 2 - fast blink (pin 51, see below)
 |||| |||| |||| |||| ||||
 |||| |||| |||| |||| ||||--------------- 12. Left Front light Mode 0 - turn on ones; 1 - long blink; 2 - fast blink (pin 50)
 |||| |||| |||| |||| |||---------------- 13. Left Rear light Counter.  - Counts the number of blinks and changing accordingly
 |||| |||| |||| |||| ||----------------- 14. Right Rear light Counter - Counts the number of blinks and changing accordingly
 |||| |||| |||| |||| |------------------ 15. Right Front light Counter - Counts the number of blinks and changing accordingly
 |||| |||| |||| ||||
 |||| |||| |||| ||||-------------------- 16. Left Rear light Counter - Counts the number of blinks and changing accordingly 
 |||| |||| |||| |||--------------------- 17.  
 |||| |||| |||| ||---------------------- 18. 
 |||| |||| |||| |----------------------- 19. Left Front Sonar signal distance
 |||| |||| ||||
 |||| |||| ||||------------------------- 20. Middle Front Sonar signal distance 
 |||| |||| |||-------------------------- 21. Right Front Sonar Signal distance
 |||| |||| ||--------------------------- 22. Sonar1 signal distance
 |||| |||| |---------------------------- 23. Sonar2 signal distance  
 |||| ||||
 |||| ||||------------------------------ 24. Left rear wheel counter
 |||| |||------------------------------- 25, Right rear wheel counter
 |||| ||-------------------------------- 26. Front right wheel counter
 |||| |--------------------------------- 27. Front left wheel counter
 ||||
 ||||----------------------------------- 28. 
 |||------------------------------------ 29. 
 ||------------------------------------- 30. 
 |-------------------------------------- 31. 

 The bit mask encoding for String params is as follows:
 0000 0000 0000 0000 0000 0000 0000 0000
                                     |||- Line 1 on the green LCD
                                     ||-- Line 2 on the green LCD 
                                     |--- Line 3 the line that is sent to RPi in order to be printed on a big LCD screen 

*/ 

#ifndef STATE
#define STATE

#include <string>
#include <Arduino.h>
#include "Command.h"
#include "UsefulDefines.h"

using namespace std;


class State {
  private:
    static const int COMMAND_INDEX_SQUIZZ_THRESHOLD = 55;
    unsigned int tick = 0;
    uint64_t     deviceBitMask = 0;
    uint64_t     intParamBitMask=0;
    uint64_t     strParamBitMask=0;
    unsigned int currentTick = 0;
    int          intParam[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    String       strParam[5] = {"", "", "", "", ""}; 
    Command*     commandExecutionArray[64]; // Serves as an execution queue that is fully traversed on every Arduino loop() iteration 
    Command*     commandStorageArray[64]; // Stores all issued commands that are not completed yet otherwise the NULL is stored 
    int commandIndex=0;
    int squizz(); // Goes through commandArray if the command index >= 55 and verifies all completed commands. If the command is complete then deleting it from array and memory if not then try to move it to the left as much as possible 
    
  public:
    State();
    unsigned int getDeviceBitMask();
    unsigned int getCurrentTick();
    int* getIntParamArray();
    String* getStringParamArray();
    Command* printOnLcd();
    Command* leftMotorSpeed( );   // requires intParam[0] to be set
    Command* rightMotorSpeed( );  // requires intParam[1] to be set 
    Command* bothMotors( );       // requires both intParam[0] and intParam[1] to be set 
    Command* haltBothMotors( );   // No params needed in fact both intParamBitMask[0] and intParamBitMask[1] are going to be reset back to zero  
    Command* panServo( );         // requires intParam[2] to be set
    Command* tiltServo( );        // requires intParam[3] to be set
    Command* bothPanAndTilt( );  // requires both intParam[2] and intParam[3] for PAN and TILT servos respectively
    Command* LCDMenuPosition( );  // requires intParam[0]
    Command* isLeftRearLight();
    Command* leftRearLightOn( );  // requires Param[1] to be set to indicate the mode for blinking (it is deliberately done this way so the motor and the blink commands can be concatenated) 
    Command* leftRearLightOff( ); 
    Command* isRightRearLight();  
    Command* rightRearLightOn( ); // requires Param[0] to be set to indicate the mode for blinking
    Command* rightRearLightOff( ); 
    Command* isRightFrontLight();
    Command* rightFrontLightOn( ); // requires Param[3] to be set to indicate the mode for blinking 
    Command* rightFrontLightOff( ); 
    Command* isLeftFrontLight();
    Command* leftFrontLightOn( );   // requires Param[2] to be set to indicate the mode for blinking
    Command* leftFrontLightOff( );    
    Command* leftFrontSonar( );     
    Command* middleFrontSonar( );
    Command* rightFrontSonar( );
    Command* RPIRelayOn( );
    Command* RPIRelayOff( );
    Command* selfPowerRelayOn( );
    Command* selfPowerRelayOff( );
    Command* engageMotorsOn( );
    Command* engageMotorsOff( );
    Command* engageSpeakersOn( );
    Command* engageSpeakersOff( );
    Command* relay5On( );
    Command* relay5Off( );
    Command* leftRearWheelCounter( );  // intParam1 the number of revolutions of the left rear wheel
    Command* rightRearWheelCounter( );  // intParam1 the number of revolutions of the right rear wheel
    Command* rightFrontWheelCounter( );
    Command* leftFrontWheelCounter( ); // intParam1 the number of revolutions of the left front wheel
    void execute(); // Should be called in the Arduino's loop body
    unsigned int getNIncrementTick();
    String toString();

    friend Command;
};


#endif
