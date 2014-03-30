#include "DemoMoverSprite.h"
#include <random>

using namespace std;

DemoMoverSprite::DemoMoverSprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer,string _uniqueName) : XDL_Sprite(_asset,_x,_y,_height,_width,_z,_renderer,_uniqueName)
{
	this->SetVelocityX((rand() % 5) + 1);/*!Set Velocity X to a random Number between 1 and 6*/	
	this->SetVelocityY((rand() % 5) + 1);/*!Set Veloicty Y to a random Number between 1 and 6*/

}

DemoMoverSprite::~DemoMoverSprite()
{

}

void DemoMoverSprite::Update()
{
	XDL_Sprite::Update();
	if(GetVelocityX() > 0 && _posX > XDL_Game::SCREEN_WIDTH )/*!Stop it from falling off the screen*/
	{
		SetVelocityX(-2);
	}

	else if(GetVelocityX() < 0 && _posX < 0 )
	{
		SetVelocityX(2);
	}

	else if(GetVelocityY() > 0 && _posY > XDL_Game::SCREEN_HEIGHT )
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

