/*! @file GameController.cpp
 *  @brief Code to read the Logitech F310 Game Controller
 *  Creates a DriverCommand object to be sent to the robot controller
 *  Used in the development simulator and in the robot control mode
 *

#include "GameController.h"
#include <iostream>

/*!
 * By default, the game controller selects the "first" joystick, printing a
 * warning if there are multiple joysticks On Linux, this is /dev/input/js0 If
 * no joystick is found, it will print an error message, and will return zero.
 * It is possible to change/add a joystick later with findNewController
 */

int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
char *button=NULL, name_of_joystick[80];
struct js_event js;  
GameController::findNewController();

/*!
 * Re-run the joystick finding code to select the "first" joystick. This can be
 * used to set up the joystick if the simulator is started without a joystick
 * plugged in
 */
void GameController::findNewController() {
  if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
  {
    printf( "Couldn't open joystick\n" );
    return -1;
  }
  ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
  ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
  ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

  axis = (int *) calloc( num_of_axis, sizeof( int ) );
  button = (char *) calloc( num_of_buttons, sizeof( char ) );

  printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
    , name_of_joystick
    , num_of_axis
    , num_of_buttons );

  fcntl( joy_fd, F_SETFL, O_NONBLOCK );
}

/*!
 * Overwrite a driverCommand with the current joystick state.  If there's no
 * joystick, sends zeros
 * TODO: what happens if the joystick is unplugged?
 */
void GameController::updateGamepadCommand(GamepadCommand &gamepadCommand) {

    /* read the joystick state */
    read(joy_fd, &js, sizeof(struct js_event));
    
      /* see what to do with the event */
    switch (js.type & ~JS_EVENT_INIT)
    {
      case JS_EVENT_AXIS:
        axis   [ js.number ] = js.value;
        break;
      case JS_EVENT_BUTTON:
        button [ js.number ] = js.value;
        break;
    }

    /*Note that the buttons assigned might not be mapped properly. If these variables are to be used, please calibrate and set the correct buttons to the correct x array values. 
    eg. gamepadCommand.leftBumper may not be x[0], it can be x[1], depending on how the new controller detected is being mapped. Also, this program did not record the values of
    leftTriggerAnalog and rightTriggerAnalog */

    gamepadCommand.leftBumper = x[4];
    gamepadCommand.rightBumper = x[5];
    gamepadCommand.leftTriggerButton = x[6];
    gamepadCommand.rightTriggerButton = x[7];
    gamepadCommand.back = x[8];
    gamepadCommand.start = x[9];
    gamepadCommand.a = x[1];
    gamepadCommand.b = x[2];
    gamepadCommand.x = x[0];
    gamepadCommand.y = x[3]; 
    gamepadCommand.leftStickButton = x[10];
    gamepadCommand.rightStickButton = x[11];
    gamepadCommand.leftStickAnalog = Vec2<float>(axis[0],axis[1]);
    gamepadCommand.rightStickButton = Vec2<float>(axis[2],axis[3]);


}


