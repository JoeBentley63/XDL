#ifndef _LEVEL_1_H
#define _LEVEL_1_H

#include "XDL_Scene.h"
class Level1 :
	public XDL_Scene
{
public:
	Level1(SDL_Renderer* _renderer);
	~Level1(void);
	void Draw();
	void Update();
	float _zoom;
};

#endif