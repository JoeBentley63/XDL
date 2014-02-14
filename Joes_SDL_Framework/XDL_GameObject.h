#ifndef _XDL_GAME_OBJECT_H
#define _XDL_GAME_OBJECT_H

#include <SDL.h>
#include "XDL_Debug.h"
class XDL_GameObject 
{
public:

	XDL_GameObject();
	~XDL_GameObject(void);
	void virtual Update() = 0;
	void virtual Draw() = 0;

};

#endif