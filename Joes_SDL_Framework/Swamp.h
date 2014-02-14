#ifndef _SWAMP_H
#define _SWAMP_H

#include "Scene.h"
#include <SDL.h>
#include "TileEngine.h"
class Swamp : public Scene
{
public:
	Swamp(SDL_Renderer* _renderer);
	~Swamp(void);
	void Draw();
	void Update();

private :
	SDL_Renderer* _renderer;
	TileEngine* _tileEngine;
};

#endif
