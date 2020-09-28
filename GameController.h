/*! @file GameController.h
 *  @brief Code to read the Logitech F310 Game Controller
 *  Creates a DriverCommand object to be sent to the robot controller
 *  Used in the development simulator and in the robot control mode
 */

#ifndef PROJECT_GAMECONTROLLER_H
#define PROJECT_GAMECONTROLLER_H

#include "gamepadCommand.h"


class GameController  {
 public:
 
  void updateGamepadCommand(GamepadCommand &gamepadCommand);
  void findNewController();
  

 
};

#endif  // PROJECT_GAMECONTROLLER_H
