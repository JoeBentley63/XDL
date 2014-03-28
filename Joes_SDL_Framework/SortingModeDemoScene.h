#ifndef _SORTING_DEMO_H
#define _SORTING_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class SortingModeDemoScene :
	public XDL_Scene
{
public:
	SortingModeDemoScene(SDL_Renderer* _renderer);
	~SortingModeDemoScene(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif