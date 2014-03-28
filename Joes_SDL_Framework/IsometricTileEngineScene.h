#ifndef _ISOMETRIC_DEMO_H
#define _ISOMETRIC_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class IsometricTileEngineScene :
	public XDL_Scene
{
public:
	IsometricTileEngineScene(SDL_Renderer* _renderer);
	~IsometricTileEngineScene(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif