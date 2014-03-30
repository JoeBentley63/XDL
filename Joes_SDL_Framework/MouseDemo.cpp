#include "MouseDemo.h"



XDL_Sprite* _playerLocal;

XDL_Sprite* _playerWorld;
int _x = 0;
float _zoom = 1;
MouseDemo::MouseDemo(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,3000,2000);
	_manager = XDL_SceneManager::GetInstance();
	_playerLocal = new XDL_Sprite("DemoAssets/man.png",0,0,106,77,1,_renderer,"playerLocal");
	_playerWorld = new XDL_Sprite("DemoAssets/man.png",0,0,106,77,1,_renderer,"playerWorld");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/background.png",0,0,810,485,1,_renderer,"backgroundImage"));
	this->AddGameObjectToScene(_playerLocal);
	this->AddGameObjectToScene(_playerWorld);

	XDL_SPRITEBATCH->SetDrawMode(XDL_SpriteBatch::UNSORTED);

	XDL_SPRITEBATCH->GetCamera()->SetZoom(1);
	XDL_SPRITEBATCH->GetCamera()->SetPosition(0,0);
}


MouseDemo::~MouseDemo(void)
{
}

void MouseDemo::Update()
{
	_playerLocal->_posX = XDL_INPUT->GetMousePositionScreen().x;
	_playerLocal->_posY = XDL_INPUT->GetMousePositionScreen().y;
	
	_playerWorld->_posX = XDL_INPUT->GetMousePositionWorld(XDL_SPRITEBATCH->GetCamera()).x;
	_playerWorld->_posY = XDL_INPUT->GetMousePositionWorld(XDL_SPRITEBATCH->GetCamera()).y;
	
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->RIGHT))
	{
		_x --;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->LEFT))
	{
		_x ++;
	}

	if(XDL_INPUT->IsKeyDown(XDL_INPUT->UP))
	{
		_zoom-=0.001;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->DOWN))
	{
		_zoom += 0.001;
	}
	XDL_SPRITEBATCH->GetCamera()->SetPosition(_x,0);
	XDL_SPRITEBATCH->GetCamera()->SetZoom(_zoom);
	XDL_Scene::Update();
}

void MouseDemo::Draw()
{
	XDL_SPRITEBATCH->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing

	XDL_SPRITEBATCH->End();//draw everything
	
}