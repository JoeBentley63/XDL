#ifndef _MOVER_SPRITE_H
#define _MOVER_SPRITE_H

#include "XDL_Sprite.h"
#include <vector>
#include "XDL_Game.h"
class MoverSprite :
	public XDL_Sprite
{
public:
	MoverSprite(SDL_Renderer* _renderer,char* _asset,SDL_Rect _rect,int _posX,int _posY);
	virtual ~MoverSprite(void);
	void Update();
	void Draw();
private:
	
};

#endif

