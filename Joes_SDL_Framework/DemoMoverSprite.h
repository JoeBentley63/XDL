#ifndef _DEMO_MOVER_SPRITE_H
#define _DEMO_MOVER_SPRITE_H

#include "XDL_Sprite.h"
#include <vector>
#include "XDL_Game.h"
class DemoMoverSprite :
	public XDL_Sprite
{
public:
	DemoMoverSprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer);
	virtual ~DemoMoverSprite(void);
	void Update();
	void Draw();
	


	

};

#endif

