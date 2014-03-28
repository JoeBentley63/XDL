#include "CollisionDetectionDemo.h"
#include "XDL_SceneManager.h"
#include "SortingModeDemoScene.h"

vector<XDL_Sprite*> _collidables;
vector<XDL_Sprite*> _Immovables;
vector<XDL_Sprite*> _NonCollidables;
XDL_Sprite* _playerCollider;
CollisionDetectionDemo::CollisionDetectionDemo(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_playerCollider = new XDL_Sprite("DemoAssets/Yellow.png",110,15,16,16,1,_renderer);
	AddGameObjectToScene(_playerCollider,"player");
	_manager = XDL_SceneManager::GetInstance();
	_spriteBatch->SetDrawMode(XDL_SpriteBatch::UNSORTED);
	XDL_Sprite* _temp;
	for( int i = 0; i < 10; i ++)
	{
		_temp = new XDL_Sprite("DemoAssets/Blue.png",10,i*50,16,16,1,_renderer);
		_collidables.insert(_collidables.begin(),_temp);
		ostringstream ss;
		ss << i;
		AddGameObjectToScene(_temp,"collidables" + ss.str());
	}
	for( int i = 0; i < 10; i ++)
	{
		_temp = new XDL_Sprite("DemoAssets/Red.png",100,i*50,16,16,1,_renderer);
		_temp->_immovable = true;
		_Immovables.insert(_Immovables.begin(),_temp);
		ostringstream ss;
		ss << i;
		AddGameObjectToScene(_temp,"Immovables" + ss.str());
	}
	for( int i = 0; i < 10; i ++)
	{
		_temp = new XDL_Sprite("DemoAssets/Green.png",200,i*50,16,16,1,_renderer);
		_temp->_immovable = true;
		_NonCollidables.insert(_NonCollidables.begin(),_temp);
		ostringstream ss;
		ss << i;
		AddGameObjectToScene(_temp,"NonCollidables" + ss.str());
	}
}


CollisionDetectionDemo::~CollisionDetectionDemo(void)
{
}

void CollisionDetectionDemo::Update()
{

	if(_input->IsKeyDown(_input->UP))
	{
		_playerCollider->_posY--;
	}
	if(_input->IsKeyDown(_input->DOWN))
	{
		_playerCollider->_posY++;
	}
	if(_input->IsKeyDown(_input->LEFT))
	{
		_playerCollider->_posX--;
	}
	if(_input->IsKeyDown(_input->RIGHT))
	{
		_playerCollider->_posX++;
	}

	XDL_Scene::Update();
}

void CollisionDetectionDemo::Draw()
{
	_spriteBatch->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	_spriteBatch->End();//draw everything
	
}
