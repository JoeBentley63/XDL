//! Sorting Mode Demo Scene
/*!
Demo scene to show off sorting mode of the spritebatch
*/

#ifndef _SORTING_DEMO_H
#define _SORTING_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class SortingModeDemoScene :
	public XDL_Scene
{
public:
	SortingModeDemoScene(SDL_Renderer* _renderer);
	virtual ~SortingModeDemoScene(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif