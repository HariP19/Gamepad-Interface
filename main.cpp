#include "GameController.h"
#include <iostream>

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
  }
  
}