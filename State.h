
#ifndef STATE
#define STATE

#include <string>
#include <Arduino.h>
#include "Lever.h"
#include "UsefulDefines.h"

using namespace std;

/* The command handler and index where the parameters+length for this command are being held */
class LeverNparams {
  private:
    Lever* lever; // Lever currently being executed
    int index2IntParams; // if this value is negative no integer params are expected otherwise it is an index in intParam update where the parameters for this device are stored
    int length2IntParams; // length of params in the intParam array
    int index2StrParams; // if this value is negative string params are expected otherwise it is an index in strParam update where the parameters for this device are stored
    int length2StrParams; // length of params in the strParam array

  public:
    LeverNparams(Lever* lever, int index2IntParams, int lengthOfIntParams, int index2StrParams, int lengthOfStrParams);
    LeverNparams(Lever* lever, int index2IntParams, int lengthOfIntParams);
    LeverNparams(Lever* lever, String index2StrParams, int lengthOfStrParams);
    
    int getIndex2IntParams();
    int getLength2IntParams();
    int getIndex2StrParams();
    int getLength2StrParams();
};

/* The state class that describes which devices are engaged and which are at this moment of time. 
 *  It contains the device array[64] and if the value in array is NULL it means that the Lever is currently not engaged 
 *  otherwise it contains a LeverNparams class that point to the params starting point. 
 *  The array encoding looks like follows:
 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
                                       | |||| |||| |||| |||| |||| |||| |||| ||||- 0. Even bit (makes all the bits in a mask to come to the even number if 0010 001* then the bit would be zero if 0010 101* then the bit would be one)  
                                       | |||| |||| |||| |||| |||| |||| |||| |||-- 1. Left Motor go at intParam[0] speed. Negativa values reverse  
                                       | |||| |||| |||| |||| |||| |||| |||| ||--- 2. Right Motor go at intParam[1] speed. Negative value reverse 
                                       | |||| |||| |||| |||| |||| |||| |||| |---- 3. Apply emergency brake for all motors
                                       | |||| |||| |||| |||| |||| |||| 
                                       | |||| |||| |||| |||| |||| |||| ||||------ 4. PAN Servo for camera intParam[2]
                                       | |||| |||| |||| |||| |||| |||| |||------- 5. TILT Servo for camera intParam[3]
                                       | |||| |||| |||| |||| |||| |||| ||-------- 6. Reserved for Servo intParam[4]
                                       | |||| |||| |||| |||| |||| |||| |--------  7. Reserved for Servo intParam[5]
                                       | |||| |||| |||| |||| |||| ||||
                                       | |||| |||| |||| |||| |||| ||||----------  8. Reserved for Servo intParam[6]
                                       | |||| |||| |||| |||| |||| |||-----------  9. Resevred for Servo intParam[7]
                                       | |||| |||| |||| |||| |||| ||------------  10. LCD 16x2 print strString[0], strString[1]
                                       | |||| |||| |||| |||| |||| |-------------  11. Current small screen menu position
                                       | |||| |||| |||| |||| ||||
                                       | |||| |||| |||| |||| ||||--------------- 12. Left Rear light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                       | |||| |||| |||| |||| |||---------------- 13. Right Rear light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                       | |||| |||| |||| |||| ||----------------- 14. Right Front light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                       | |||| |||| |||| |||| |------------------ 15. Left Front light ON (intParam1 - blinking mode see description below, int param2 - number of blinks remaining)
                                       | |||| |||| |||| ||||
                                       | |||| |||| |||| ||||-------------------- 16. Light Mode 0 - steady, 1 - blink
                                       | |||| |||| |||| |||--------------------- 17. Left Front Sonar signal - intParam[9] 
                                       | |||| |||| |||| ||---------------------- 18. Middle Front Sonar signal - intParam[10]  
                                       | |||| |||| |||| |----------------------- 19. Right Front Sonar Signal - intParam[11]
                                       | |||| |||| ||||
                                       | |||| |||| ||||------------------------- 20. Reserved Sonar 1 Signal - intParam[12]
                                       | |||| |||| |||-------------------------- 21. Reserved Sonar 2 Signal - intParam[13]
                                       | |||| |||| ||--------------------------- 22. RPI Power relay
                                       | |||| |||| |---------------------------- 23. Own Self Powered relay 
                                       | |||| ||||
                                       | |||| ||||------------------------------ 24. Relay 3
                                       | |||| |||------------------------------- 25, Relay 4
                                       | |||| ||-------------------------------- 26. Relay 5
                                       | |||| |--------------------------------- 27. Left rear wheel counter intParam[14]
                                       | ||||
                                       | ||||----------------------------------- 28. Right rear wheel counter intParam[15]
                                       | |||------------------------------------ 29. Front right wheel counter intParam[16]
                                       | ||------------------------------------- 30. Front left wheel counter intParam[17]
                                       | |-------------------------------------- 31. In case of transmission to RPI is it Update(0) or FullImage(1)
                                       |---------------------------------------- 32. Print on a Raspberry Pi screen
 
 Another array contains the list of integer params with the encoding as follows: 
 0000 0000 0000 0000 0000 0000 0000 0000 
 |||| |||| |||| |||| |||| |||| |||| ||||- 0. Even bit 
 |||| |||| |||| |||| |||| |||| |||| |||-- 1. Left motor speed value.Negativa values reverse  
 |||| |||| |||| |||| |||| |||| |||| ||--- 2. Right Motor speed value. Negativa values reverse 
 |||| |||| |||| |||| |||| |||| |||| |---- 3. PAN Servo value;
 |||| |||| |||| |||| |||| |||| 
 |||| |||| |||| |||| |||| |||| ||||------ 4. Tilt Servo value
 |||| |||| |||| |||| |||| |||| |||------- 5. Servo 1 value
 |||| |||| |||| |||| |||| |||| ||-------- 6. Servo 2 value
 |||| |||| |||| |||| |||| |||| |--------  7. Servo 3 value
 |||| |||| |||| |||| |||| ||||
 |||| |||| |||| |||| |||| ||||----------  8.  Servo 4 value
 |||| |||| |||| |||| |||| |||-----------  9.  Number in the small LCD menu
 |||| |||| |||| |||| |||| ||------------  10. Left Rear light how long to stay on (pin 52) 
 |||| |||| |||| |||| |||| |-------------  11. Left Rear light how long to stay off (pin 52) 
 |||| |||| |||| |||| ||||
 |||| |||| |||| |||| ||||--------------- 12. Right Rear right how long to stay on (pin 49)
 |||| |||| |||| |||| |||---------------- 13. Right Rear right how long to stay off (pin 49)
 |||| |||| |||| |||| ||----------------- 14. Right Front light Mode how long to stay on (pin 51)
 |||| |||| |||| |||| |------------------ 15. Right Front light Mode how long to stay off (pin 51)
 |||| |||| |||| ||||
 |||| |||| |||| ||||-------------------- 16. Left Front light Mode how long to stay on (pin 50)  
 |||| |||| |||| |||--------------------- 17. Left Front light Mode how long to stay off (pin 50)  
 |||| |||| |||| ||---------------------- 18. 
 |||| |||| |||| |----------------------- 19. 
 |||| |||| ||||
 |||| |||| ||||------------------------- 20. Left Front Sonar signal distance 
 |||| |||| |||-------------------------- 21. Central Front Sonar signal distance
 |||| |||| ||--------------------------- 22. Right Front Sonar Signal distance
 |||| |||| |---------------------------- 23. RPI relay supplies power to Raspberry Pi
 |||| ||||
 |||| ||||------------------------------ 24. Self powered relay creates an alternative circuit to power Arduino
 |||| |||------------------------------- 25, Motor power relay
 |||| ||-------------------------------- 26. Speaker Power relay
 |||| |--------------------------------- 27. Relay 5 (reserved)
 ||||
 ||||----------------------------------- 28. Left rear wheel counter
 |||------------------------------------ 29. Right rear wheel counter
 ||------------------------------------- 30. Front right wheel counter
 |-------------------------------------- 31. Front left wheel counter

 The String params encoding is as follows:
 0000 0000 0000 0000 0000 0000 0000 0000
                                    |||||- Line 1 on the green LCD
                                    ||||-- Line 2 on the green LCD 
                                    |||--- the line that is sent to RPi in order to be printed on a big LCD screen (white color) 
                                    ||---- the line that is sent to RPi in order to be printed on a big LCD screen (blue color)
                                    |----- the line that is sent to RPi in order to be printed on a big LCD screen (red color)

*/ 

class State {
  private:
    static const int Lever_INDEX_SQUIZZ_THRESHOLD = 55;
    unsigned int tick = 0;
    LeverNparams* leverNparamsArray[64]= {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
                                              NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
                                              
    unsigned int    currentTick = 0;
    int             intParam[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    String          strParam[5] = {"", "", "", "", ""}; 
    // Serves as an execution queue that is fully traversed on every Arduino loop() iteration 
    Lever*        leverExecutionArray[64]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
                                              NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; 
    int             leverIndex=0; // execution queue index as soon as the index goes above threshold then the squizz procedure is engaged that would move all the active Lever to the left 
    int squizz(); // Goes through LeverArray if the Lever index >= threshold and verifies all completed Levers. If the Lever is complete then deleting it from array and memory if not then try to move it to the left as much as possible 
    
  public:
    State();
    void   arduinoSetup();
    Lever* printOnLcd(); // strParam[0], strParam[2]
    bool isLeftMotorEngaged(); 
    Lever* leftMotorSpeed( ); // intParam[0]   
    bool isRightMotorEngaged();
    Lever* rightMotorSpeed( ); // intParam[1]   
    Lever* bothMotors( );      // intParam[0], intParam[1]   
    Lever* haltBothMotors( );     
    Lever* panServo( ); // intParam[1]        
    Lever* tiltServo( );  // intParam[2]      
    Lever* bothPanAndTilt( );  // intParam[1], intParam[2]

    Lever* LCDMenuPosition( ); // intParam(8) 
 
    Lever* leftRearLight( );  
    Lever* rightRearLight( ); 
    Lever* rightFrontLight( ); 
    Lever* leftFrontLight( );   

    Lever* leftFrontSonar( ); // intParam(13) - distance from obstacle in mm or negative value if no obstacle is detected    
    Lever* middleFrontSonar( ); // intParam(14) - distance from obstacle in mm or negative value if no obstacle is detected
    Lever* rightFrontSonar( ); // intParam(15) - distance from obstacle in mm or negative value if no obstacle is detected
    
    Lever* RPIRelayOn( ); // intParam(20)
    Lever* selfPowerRelay( ); // intParam(21)
    Lever* engageMotorsRelay( ); // intParam(22)
    Lever* engageSpeakersRelay( ); // intParam(23)
    Lever* relay5( ); // intParam(24)
    
    Lever* leftRearWheelCounter( ); // intParam(24) the number of wheel revolutions (tuned 60 degrees) so number/6 is really number of revolutions 
    Lever* rightRearWheelCounter( ); // intParam(25) the number of wheel revolutions (tuned 60 degrees) so number/6 is really number of revolutions 
    Lever* rightFrontWheelCounter( ); // intParam(26) the number of wheel revolutions (tuned 60 degrees) so number/6 is really number of revolutions
    Lever* leftFrontWheelCounter( ); // intParam(27) the number of wheel revolutions (tuned 60 degrees) so number/6 is really number of revolutions

    Lever* print2OnRpiScreen(); // StrParam1, StrParam2
    
    void arduinoLoop(); // Should be called in the Arduino's loop body
    unsigned int getNIncrementTick();
    String toString();

    friend Lever;
};


#endif
