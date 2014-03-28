#include "MouseDemo.h"



XDL_Sprite* _playerLocal;

XDL_Sprite* _playerWorld;
int _x = 0;
float _zoom = 1;
MouseDemo::MouseDemo(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_manager = XDL_SceneManager::GetInstance();
	_playerLocal = new XDL_Sprite("DemoAssets/man.png",0,0,106,77,1,_renderer);
	_playerWorld = new XDL_Sprite("DemoAssets/man.png",0,0,106,77,1,_renderer);
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/background.png",0,0,485,810,1,_renderer),"backgroundImage");
	this->AddGameObjectToScene(_playerLocal,"playerLocal");
	this->AddGameObjectToScene(_playerWorld,"playerWorld");

	_spriteBatch->SetDrawMode(XDL_SpriteBatch::UNSORTED);
}


MouseDemo::~MouseDemo(void)
{
}

void MouseDemo::Update()
{
	_playerLocal->_posX = _input->GetMousePositionScreen().x;
	_playerLocal->_posY = _input->GetMousePositionScreen().y;
	
	_playerWorld->_posX = _input->GetMousePositionWorld(_spriteBatch->GetCamera()).x;
	_playerWorld->_posY = _input->GetMousePositionWorld(_spriteBatch->GetCamera()).y;
	
	if(_input->IsKeyDown(_input->RIGHT))
	{
		_x --;
	}
	if(_input->IsKeyDown(_input->LEFT))
	{
		_x ++;
	}

	if(_input->IsKeyDown(_input->UP))
	{
		_zoom-=0.001;
	}
	if(_input->IsKeyDown(_input->DOWN))
	{
		_zoom += 0.001;
	}
	_spriteBatch->GetCamera()->SetPosition(_x,0);
	_spriteBatch->GetCamera()->SetZoom(_zoom);
	XDL_Scene::Update();
}

void MouseDemo::Draw()
{
	_spriteBatch->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing

	_spriteBatch->End();//draw everything
	
}