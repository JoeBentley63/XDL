#include "Level1.h"

XDL_Sprite* _sprite;
Level1::Level1(SDL_Renderer* _renderer)
{
	_sprite = new XDL_Sprite("Face.bmp",0,0,128,128,_renderer);
	XDL_Scene::Init(_renderer);
}

Level1::~Level1(void)
{
}

void Level1::Update()
{
	if(_keyboard->IsKeyDown(_keyboard->UP))
	{
		_sprite->_posY--;
	}
	XDL_Scene::Update();
}

void Level1::Draw()
{
	_spriteBatch->Begin();
	_sprite->Draw();

	_spriteBatch->End();
	XDL_Scene::Draw();
}
