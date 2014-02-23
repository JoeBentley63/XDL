#ifndef XDL_INPUT_H
#define XDL_INPUT_H
#include "XDL_Keyboard.h"
class XDL_Input
{
public:
	XDL_Keyboard* _keyBoard;
	XDL_Input(void);
	~XDL_Input(void);
	SDL_Point* GetMousePos();
	//bool IsMouseButtonDown(int _button);
	//bool IsMouseButtonUp(int _button);
	bool IsKeyDown(int _key);
	bool IsKeyUp(int _key);
	//possible gamepad functions?
};


#endif
