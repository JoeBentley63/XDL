//Singleton to handle keyboard input. Again, to avoid polling for keyboard input all over our code.
#include "XDL_Keyboard.h"

XDL_Keyboard* XDL_Keyboard::_me;
XDL_Keyboard::XDL_Keyboard(void)
{
	
}


XDL_Keyboard::~XDL_Keyboard(void)
{
}

XDL_Keyboard* XDL_Keyboard::GetInstance()
{
	if(_me == NULL)
	{
		_me = new XDL_Keyboard();
	}
	return _me;
}
/*void XDL_Keyboard::Update()
{
	Originally this had an update that would be called in XDL_Game once a frame to keep track of keys, but SDL2 has a getKeyboardState function that simplifys everything
}*/
bool XDL_Keyboard::IsKeyDown(int _key)
{
	SDL_PumpEvents();//needs to be called before SDL_GetKeyBoardState
	keystate = SDL_GetKeyboardState(NULL);//returns all keys down. Passing in NULL does it for all keys.
	return keystate[_key];//if our keys is down, return true/false.
}
bool XDL_Keyboard::IsKeyUp(int _key)
{
	if(IsKeyDown(_key) == true)//if our key is down, return false, else true. Save us repeating code,just reuse function.
	{
		return false;
	}
	return true;
}