//! XDL_Keyboard. [Singleton]
/*!
Wrapper class of SDL's keyboard functions.
*/

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <SDL.h>

class XDL_Keyboard
{
	private:
	/*!Pointer to our Instance*/
	static XDL_Keyboard* _me;
	/*!The current state of our keyboard keys*/
	const Uint8* keystate;

public:
	XDL_Keyboard(void);
	~XDL_Keyboard(void);
	/*!
	\return XDL_Keyboard Returns the shared instance of our Keyboard. Creates a new Keyboard if its not already created.
	*/
	static XDL_Keyboard* GetInstance();
	/*!
	\return bool , true if key is down, false if its not.
	*/
	bool IsKeyDown(int _key);/*!Check if a key is down*/

	/*!
	\return bool , false if key is down, true if its not.
	*/
	bool IsKeyUp(int _key);/*!Check if a key is up*/
	
};

#endif

