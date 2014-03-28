#include "MoverSprite.h"

MoverSprite::MoverSprite(SDL_Renderer* _renderer,char* _asset,SDL_Rect _rect,int _posX,int _posY) : XDL_Sprite(_asset,XDL_Game::SCREEN_WIDTH/2,XDL_Game::SCREEN_HEIGHT/2,32,32,1,_renderer,_rect,3)
{
	this->SetVelocity(1,1);
}


void MoverSprite::Update()
{
	XDL_Sprite::Update();
	if(this->_posX < 0)
	{
		this->SetVelocityX(1);
	}
	else if(this->_posX > XDL_Game::SCREEN_WIDTH)
	{
		this->SetVelocityX(-1);
	}
	if(this->_posY < 0)
	{
		this->SetVelocityY(1);
	}
	else if(this->_posY > XDL_Game::SCREEN_HEIGHT)
	{
		this->SetVelocityY(-1);
	}
}

void MoverSprite::Draw()
{
	XDL_Sprite::Draw();
	
}
MoverSprite::~MoverSprite(void)
{
}
