//!XDL_Main	
/*!
Runs game loop and enforces FPS
*/


#include <stdlib.h>
#include "XDL_Game.h"
#include "XDL_Debug.h"
#include <chrono>
#include <thread>

XDL_Game* _game;
bool _running = true;
int FPS=60; 

Uint32 start=SDL_GetTicks();
using namespace std;
int main( int argc, char* args[])
{
	 bool cap = true; 
	 DEBUG_MSG("go");
	_game = new XDL_Game();
	_game->Init();
	
	while(_running)
	{
		_game->Update();
		_game->Render();

		if(1000/FPS>SDL_GetTicks()-start)
		{ 
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
		} 
		start=SDL_GetTicks(); 
		// re initialise }
	}
	_game->CleanUp();
	return 0;
}