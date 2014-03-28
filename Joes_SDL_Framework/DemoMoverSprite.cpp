#include "DemoMoverSprite.h"
#include <random>

using namespace std;

DemoMoverSprite::DemoMoverSprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer) : XDL_Sprite(_asset,_x,_y,_height,_width,_z,_renderer)
{
	this->SetVelocityX((rand() % 5) + 1);	
	this->SetVelocityY((rand() % 5) + 1);
}

DemoMoverSprite::~DemoMoverSprite()
{

}

void DemoMoverSprite::Update()
{
	XDL_Sprite::Update();
	if(GetVelocityX() > 0 && _posX > XDL_Game::SCREEN_WIDTH )
	{
		SetVelocityX(-2);
	}

	else if(GetVelocityX() < 0 && _posX < 0 )
	{
		SetVelocityX(2);
	}

	if(GetVelocityY() > 0 && _posY > XDL_Game::SCREEN_HEIGHT )
	{
		SetVelocityY(-2);
	}

	else if(GetVelocityY() < 0 && _posY < 0 )
	{
		SetVelocityY(2);
	}
}

void DemoMoverSprite::Draw()
{
	XDL_Sprite::Draw();
	
}

