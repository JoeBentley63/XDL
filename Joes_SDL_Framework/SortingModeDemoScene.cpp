#include "SortingModeDemoScene.h"
#include "XDL_SceneManager.h"



SortingModeDemoScene::SortingModeDemoScene(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_manager = XDL_SceneManager::GetInstance();
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Red.png",0,0,100,100,1,_renderer),"Red");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Orange.png",50,50,100,100,2,_renderer),"Orange");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Yellow.png",100,100,100,100,3,_renderer),"Yellow");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Green.png",150,150,100,100,4,_renderer),"Green");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Blue.png",200,200,100,100,5,_renderer),"Blue");
	this->AddGameObjectToScene(new XDL_Sprite("DemoAssets/Pink.png",250,250,100,100,6,_renderer),"Pink");
	_spriteBatch->SetDrawMode(XDL_SpriteBatch::UNSORTED);
}


SortingModeDemoScene::~SortingModeDemoScene(void)
{
}

void SortingModeDemoScene::Update()
{
	if(_input->IsKeyDown(_input->A))
	{
		_spriteBatch->SetDrawMode(XDL_SpriteBatch::BACKTOFRONT);
	}
	if(_input->IsKeyDown(_input->S))
	{
		_spriteBatch->SetDrawMode(XDL_SpriteBatch::FRONTTOBACK);
	}
	if(_input->IsKeyDown(_input->RIGHT))
	{
	//	_manager->ChangeScene(new IsometricTileEngineScene(_renderer),"IsometricTileEngineScene");
	}
	XDL_Scene::Update();
}

void SortingModeDemoScene::Draw()
{
	_spriteBatch->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	_spriteBatch->End();//draw everything

}