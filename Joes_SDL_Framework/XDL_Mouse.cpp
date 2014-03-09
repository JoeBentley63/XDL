//Singleton to handle keyboard input. Again, to avoid polling for keyboard input all over our code.
#include "XDL_Mouse.h"

XDL_Mouse* XDL_Mouse::_me;

XDL_Mouse::XDL_Mouse(void)
{
	_mousePosition.x = 0;
	_mousePosition.y = 0;
}


XDL_Mouse::~XDL_Mouse(void)
{
}


XDL_Mouse* XDL_Mouse::GetInstance()
{

	if(_me == NULL)
	{
		_me = new XDL_Mouse();
	}
	return _me;
}


bool XDL_Mouse::IsButtonDown(int _button)
{
	SDL_PumpEvents();//needs to be called before SDL_GetKeyBoardState
	if(SDL_GetMouseState(&_mousePosition.x, &_mousePosition.y)&SDL_BUTTON(_button))
	{
		return true;
	}
	return false;
}


bool XDL_Mouse::IsButtonUp(int _button)
{
	if(IsButtonDown(_button) == true)//if our key is down, return false, else true. Save us repeating code,just reuse function.
	{
		return false;
	}
	return true;
}

SDL_Point XDL_Mouse::GetPositionScreen()//return actual position
{
	SDL_PumpEvents();
	SDL_GetMouseState(&_mousePosition.x, &_mousePosition.y);
	return _mousePosition;
}

SDL_Point XDL_Mouse::GetPositionWorld(XDL_Camera* _camera)//counteract camera position
{
	GetPositionScreen();
	_actualPosition.x =  _mousePosition.x - _camera->GetPosition()->x;
	_actualPosition.y =  _mousePosition.y - _camera->GetPosition()->y;
	return _actualPosition;
}