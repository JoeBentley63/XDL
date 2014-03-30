//! Tile Engine Demo Scene
/*!
Simpel scene that shows creation of a tile Engine and pathfinding using it.
*/

#ifndef _ISOMETRIC_DEMO_H
#define _ISOMETRIC_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
#include "XDL_TileEngine.h"
class TileEngineScene :
	public XDL_Scene
{
public:
	TileEngineScene(SDL_Renderer* _renderer);
	virtual ~TileEngineScene(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
	
};

#endif