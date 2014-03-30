//! Input Demo	
/*!
Simple demo scene that shows how keyboard input and mouse input works.
2 sprites drawn, 1 in world coords of the mouse, the other in screen coords.
*/
#ifndef _MOUSE_DEMO_H
#define _MOUSE_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class MouseDemo :
	public XDL_Scene
{
public:
	MouseDemo(SDL_Renderer* _renderer);
	~MouseDemo(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif