#include "XDL_Input.h"


XDL_Input::XDL_Input(void)
{
	_keyBoard = XDL_Keyboard::GetInstance();
}


XDL_Input::~XDL_Input(void)
{
}


bool XDL_Input::IsKeyDown(int _key)
{
	return _keyBoard->IsKeyDown(_key);
}
bool XDL_Input::IsKeyUp(int _key)
{
	return _keyBoard->IsKeyUp(_key);
}