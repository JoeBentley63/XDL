#include "XDL_Input.h"


XDL_Input* XDL_Input::_me;

XDL_Input::XDL_Input(void)
{
	XDL_KEYBOARD = XDL_Keyboard::GetInstance();//get an instance of the keyboard and mouse
	XDL_MOUSE = XDL_Mouse::GetInstance();
}


XDL_Input::~XDL_Input(void)
{
	delete(XDL_KEYBOARD);
	delete(XDL_MOUSE);
}

XDL_Input* XDL_Input::GetInstance()
{
	if(_me == NULL)
	{
		_me = new XDL_Input();
	}
	return _me;
}

bool XDL_Input::IsKeyDown(int _key)//wrappers for their functionality. 
{
	return XDL_KEYBOARD->IsKeyDown(_key);
}
bool XDL_Input::IsKeyUp(int _key)
{
	return XDL_KEYBOARD->IsKeyUp(_key);
}

bool XDL_Input::IsMouseButtonDown(int _button)
{
	return XDL_MOUSE->IsButtonDown(_button);
}
bool XDL_Input::IsMouseButtonUp(int _button)
{
	return XDL_MOUSE->IsButtonUp(_button);
}
SDL_Point XDL_Input::GetMousePositionScreen()
{
	return XDL_MOUSE->GetPositionScreen();
}
SDL_Point XDL_Input::GetMousePositionWorld(XDL_Camera* XDL_CAMERA)
{
	return XDL_MOUSE->GetPositionWorld(XDL_CAMERA);
}