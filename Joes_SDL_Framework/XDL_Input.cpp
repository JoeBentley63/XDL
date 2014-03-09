#include "XDL_Input.h"


XDL_Input* XDL_Input::_me;

XDL_Input::XDL_Input(void)
{
	_keyBoard = XDL_Keyboard::GetInstance();
	_mouse = XDL_Mouse::GetInstance();
}


XDL_Input::~XDL_Input(void)
{
	delete(_keyBoard);
	delete(_mouse);
}

XDL_Input* XDL_Input::GetInstance()
{
	if(_me == NULL)
	{
		_me = new XDL_Input();
	}
	return _me;
}

bool XDL_Input::IsKeyDown(int _key)
{
	return _keyBoard->IsKeyDown(_key);
}
bool XDL_Input::IsKeyUp(int _key)
{
	return _keyBoard->IsKeyUp(_key);
}

bool XDL_Input::IsMouseButtonDown(int _button)
{
	return _mouse->IsButtonDown(_button);
}
bool XDL_Input::IsMouseButtonUp(int _button)
{
	return _mouse->IsButtonUp(_button);
}
SDL_Point XDL_Input::GetMousePositionScreen()
{
	return _mouse->GetPositionScreen();
}
SDL_Point XDL_Input::GetMousePositionWorld(XDL_Camera* _camera)
{
	return _mouse->GetPositionWorld(_camera);
}