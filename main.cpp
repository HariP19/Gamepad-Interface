/*!
 * Test for working of the controller.  
 * Returns value on the leftStickAnalog if found else prints NULL
 */

#include "GameController.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#define JOY_DEV "/dev/input/js0"

int main()
{
  
  GameController gameController;
  GamepadCommand gamepadCommand;

  while(true)
  {
  	gameController.updateGamepadCommand(gamepadCommand);
  	if(gamepadCommand.leftStickAnalog[0] > 0)
  	{
  		std::cout << "Left X: " << gamepadCommand.leftStickAnalog[0] ;
  		break;
  	}
  	else
  		std::cout << " NULL " << "\n";
    /* print the results */
    printf( "X: %6d  Y: %6d  ", axis[0], axis[1] );
    
    if( num_of_axis > 2 )
      printf("Z: %6d  ", axis[2] );
      
    if( num_of_axis > 3 )
      printf("R: %6d  ", axis[3] );
      
    for( x=0 ; x<num_of_buttons ; ++x )
      printf("B%d: %d  ", x, button[x] );

    printf("  \r");
    fflush(stdout);

  }
  
  close(joy_fd);
  return 0;
  
}