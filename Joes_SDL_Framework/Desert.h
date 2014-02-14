#ifndef _DESERT_H
#define _DESERT_H

#include "Scene.h"
#include <SDL.h>
#include "TileEngine.h"
class Desert : public Scene
{
public:
	Desert(SDL_Renderer* _renderer);
	~Desert(void);
	void Draw();
	void Update();

private :
	SDL_Renderer* _renderer;
	TileEngine* _tileEngine;
};

#endif
