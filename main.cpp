/*!
 * Test for working of the controller.  
 * Returns value on the leftStickAnalog if found else prints NULL
 */

#include "gamepadCommand.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#define JOY_DEV "/dev/input/js0"


GamepadCommand gamepadCommand;
  


int main()
{
  struct js_event js; 
  int joy_fd;
  int *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
  char *button=NULL, name_of_joystick[80]  ;

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

  fcntl( joy_fd, F_SETFL, O_NONBLOCK ); /* use non-blocking mode */



  while(1)
  {
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

    gamepadCommand.leftBumper = button[4];
    gamepadCommand.rightBumper = button[5];
    gamepadCommand.leftTriggerButton = button[6];
    gamepadCommand.rightTriggerButton = button[7];
    gamepadCommand.back = button[8];
    gamepadCommand.start = button[9];
    gamepadCommand.a = button[1];
    gamepadCommand.b = button[2];
    gamepadCommand.x = button[0];
    gamepadCommand.y = button[3]; 
    gamepadCommand.leftStickButton = button[10];
    gamepadCommand.rightStickButton = button[11];
    gamepadCommand.leftStickAnalog = Vec2<float>(axis[0],axis[1]);
    gamepadCommand.rightStickAnalog = Vec2<float>(axis[2],axis[3]);



  	
    /* print the results */
    printf( "X1: %6d  Y1: %6d  ", axis[0] , axis[1] );
    
    /*
    printf("Left bumper:%d    ",gamepadCommand.leftBumper);
    printf("Right bumper:%d   ",gamepadCommand.rightBumper);
    printf("Left trigger button:%d   ",gamepadCommand.leftTriggerButton);
    printf("Right trigger button:%d   ",gamepadCommand.rightTriggerButton);
    printf("Back button:%d   ",gamepadCommand.back);
    printf("Start button:%d   ",gamepadCommand.start);
    printf("A button:%d   ",gamepadCommand.a);
    printf("B button:%d   ",gamepadCommand.b);
    printf("X button:%d   ",gamepadCommand.x);
    printf("Y button:%d   ",gamepadCommand.y);
    printf("Left joystick button:%d   ",gamepadCommand.leftStickButton);
    printf("Right joystick button:%d   ",gamepadCommand.rightStickButton);

    */

    

    if( num_of_axis > 2 )
      printf("X2: %6d  ", axis[2] );
      
    if( num_of_axis > 3 )
      printf("Y2: %6d  ", axis[3] );

    if( num_of_axis > 4 )
      printf("X3: %6d  ", axis[4] );

    if( num_of_axis > 5 )
      printf("Y3: %6d  ", axis[5] );

    if( num_of_axis > 6 )
      printf("X4: %6d  ", axis[6] );
    
    if( num_of_axis > 7 )
      printf("Y4: %6d  ", axis[7] );
    

      
    for( x=0 ; x<num_of_buttons ; ++x )
      printf("B%d: %d  ", x, button[x] );
    

    printf("  \r");
    fflush(stdout);

  }
  
  close(joy_fd);
  return 0;
  
}