#include "IsometricTileEngineScene.h"
#include "XDL_TileEngine.h"
#include "XDL_SceneManager.h"
#include "SortingModeDemoScene.h"
XDL_TileEngine* _tile;
IsometricTileEngineScene::IsometricTileEngineScene(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_manager = XDL_SceneManager::GetInstance();
	_tile = new XDL_TileEngine(_renderer,32,32);
	_tile->LoadFromXML("grass.tmx");
	_spriteBatch->SetDrawMode(XDL_SpriteBatch::UNSORTED);
}


IsometricTileEngineScene::~IsometricTileEngineScene(void)
{
}

void IsometricTileEngineScene::Update()
{
	if(_input->IsKeyDown(_input->RIGHT))
	{
		_manager->ChangeScene(new SortingModeDemoScene(_renderer),"IsometricTileEngineScene");
	}
	XDL_Scene::Update();
}

void IsometricTileEngineScene::Draw()
{
	_spriteBatch->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	_tile->Draw(_spriteBatch);
	_spriteBatch->End();//draw everything
	
}