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