#ifndef _VARIABLE_TERRAIN_H
#define _VARIABLE_TERRAIN_H

#include "Scene.h"
#include <SDL.h>
#include "TileEngine.h"
#include "XDL_PathFinder.h"
class VariableTerrain : public Scene
{
public:
	VariableTerrain(SDL_Renderer* _renderer);
	~VariableTerrain(void);
	void Draw();
	void Update();

private :
	SDL_Renderer* _renderer;
	TileEngine* _tileEngine;
	vector<XDL_Sprite*>* _enemies;
	XDL_PathFinder* _pathFinder;
};

#endif
