//! XDL_GameObject.
/*!
Pure Virtual (Abstract) Class that serves as the super for all GameObjects in the world.
\sa XDL_Sprite
*/


#ifndef _XDL_GAME_OBJECT_H
#define _XDL_GAME_OBJECT_H

#include <SDL.h>
#include "XDL_Debug.h"
class XDL_GameObject 
{
public:
	XDL_GameObject();/*!Don't you go trying to call this, thats a big NO!*/
	~XDL_GameObject(void);
	void virtual Update() = 0;/*!virtual function so every object that is added to the scene will get auto-updated*/
	void virtual Draw() = 0; /*!virtual function so every object that is added to the scene will get auto-drawn*/
	int _z;/*!set priority when Draws are being called*/
	SDL_Rect _bounds;
private:
	
};

#endif