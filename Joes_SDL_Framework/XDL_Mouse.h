//! XDL_Mouse. [Singleton]
/*!
Wrapper class of SDL's Mouse functions.
*/

#ifndef _MOUSE_H
#define _MOUSE_H

#include <SDL.h>
#include "XDL_Camera.h"
class XDL_Mouse
{
	private:
	/*!Pointer to our Instance*/
	static XDL_Mouse* _me;
	/*!The current state of our keyboard keys*/
	Uint32 _buttonState;
	SDL_Point _mousePosition;
	SDL_Point _actualPosition;
public:
	XDL_Mouse(void);
	~XDL_Mouse(void);
	/*!
	\return XDL_Mouse Returns the shared instance of our Keyboard. Creates a new Keyboard if its not already created.
	*/
	static XDL_Mouse* GetInstance();
	/*!
	\return bool , true if button is down, false if its not.
	*/
	bool IsButtonDown(int _button);/*!Check if a button is down*/
	bool IsButtonUp(int _button);/*!Check if a button is up*/
	SDL_Point GetPositionScreen();
	SDL_Point GetPositionWorld(XDL_Camera* XDL_CAMERA);
};

#endif

