#include "Level1.h"



XDL_Sprite* _player;

Level1::Level1(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer);

	AddGameObjectToScene(new XDL_Sprite("Face.bmp",1,1,10,10,_renderer),"player");
	AddGameObjectToScene(new XDL_Sprite("Face.bmp",400,100,10,10,_renderer),"player2");
	AddGameObjectToScene(new XDL_Sprite("Face.bmp",100,40,10,10,_renderer),"player3");
	AddGameObjectToScene(new XDL_Sprite("Face.bmp",30,200,10,10,_renderer),"player4");
	_player =(XDL_Sprite*)this->GetGameObjectFromSceneUsingID("player");
}

Level1::~Level1(void)
{
}

void Level1::Update()
{
	if(_input->IsMouseButtonDown(_input->LEFTMOUSEBUTTON) || _input->IsKeyDown(_input->SPACE))
	{
		_player->_posX = _input->GetMousePositionWorld(_spriteBatch->GetCamera()).x;
		_player->_posY = _input->GetMousePositionWorld(_spriteBatch->GetCamera()).y;
	}


	XDL_Scene::Update();
}

void Level1::Draw()
{
	_spriteBatch->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	_spriteBatch->End();//draw everything

}
