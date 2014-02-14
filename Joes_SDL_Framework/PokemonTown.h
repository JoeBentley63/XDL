#ifndef _POKEMON_TOWN_H
#define _POKEMON_TOWN_H

#include "Scene.h"
#include <SDL.h>
#include "TileEngine.h"
class PokemonTown : public Scene
{
public:
	PokemonTown(SDL_Renderer* _renderer);
	~PokemonTown(void);
	void Draw();
	void Update();

private :
	SDL_Renderer* _renderer;
	TileEngine* _tileEngine;
};

#endif
