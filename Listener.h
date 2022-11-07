#ifndef LISTENER
#define LISTENER

#include <Arduino.h>

/* This class listens on important events occuring inside Levers like for example command expiraton or alike 
 *  0000 0000 0000 0000 0000 0000 0000 0000 - everything went well
 *                            ||| |||| ||||- the left rear engine trouble, the power is on but the hall-effect sensor does not show any revolution (or much less revolutions than expected)  
 *                            ||| |||| |||-- the right rear engine trouble, the power is on but the hall-effect sensor does not show any revolution (or much less revolutions than expected)  
 *                            ||| |||| ||--- the right front engine trouble, the power is on but the hall-effect sensor does not show any revolution (or much less revolutions than expected)
 *                            ||| |||| |---- the left front engine trouble, the power is on but the hall-effect sensor does not show any revolution (or much less revolutions than expected)
 *                            ||| ||||
 *                            ||| ||||------ the left sonar detected unexpected obstacle
 *                            ||| |||------- the central sonar detected unexpected obstacle
 *                            ||| ||-------- the right sonar detected unexpected obstacle
 *                            ||| |--------- low motor battery power
 *                            |||----------- low controlling circuit power
 *                            ||------------ cannot connect to RPi
 *                            |------------- no heart-beat from RPi
*/
class Listener {
  public:
    Listener();
    // If return true it means that brakes must be applied and then motors will halt otherwise the log entry will be passed on the PRi.
    // If the PRi connection is falty then the engines halt and short message will appear on the green screen
    // Short description must not exceed 16 characters
    bool onEvent(unsigned int code, String description, String shortDescription);     
};

#endif
