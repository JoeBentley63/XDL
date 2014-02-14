#ifndef _BASIC_MAZE_A_STAR_H
#define _BASIC_MAZE_A_STAR_H

#include "Scene.h"
#include <SDL.h>
#include "TileEngine.h"
#include "XDL_PathFinder.h"
class BasicMazeAStar : public Scene
{
public:
	BasicMazeAStar(SDL_Renderer* _renderer);
	~BasicMazeAStar(void);
	void Draw();
	void Update();

private :
	SDL_Renderer* _renderer;
	TileEngine* _tileEngine;
	vector<XDL_Sprite*>* _enemies;
	XDL_PathFinder* _pathFinder;

};

#endif
