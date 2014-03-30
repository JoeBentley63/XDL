//sample scene, this one loads in a 2 layered tile map
#include "TileEngineScene.h"
#include "PathFindingSprite.h"

XDL_TileEngine* _tileEngine;
XDL_PathFinder* _pathFinder;
vector<PathFindingSprite*>* _enemies;
XDL_Sprite* _sprite;
int _numInserted = 0;
TileEngineScene::TileEngineScene(SDL_Renderer* _renderer) : XDL_Scene()
{
	_numInserted = 0;
	XDL_Scene::Init(_renderer,640,480);
	_enemies = new vector<PathFindingSprite*>();
	this->_renderer = _renderer;
	
	_tileEngine = new XDL_TileEngine(_renderer,64,64);//create and load the tileEngine
	_tileEngine->LoadFromXML("grass.tmx");

	SDL_Rect _rect = {0,0,32,32};//create player
	_sprite = new XDL_Sprite("runner.png",300,400,32,32,10,_renderer,"PathFindingSprite");	
	_pathFinder = XDL_PathFinder::GetInstance();
	_pathFinder->SetWeight(1,XDL_PathFinder::_WALKABLE);//set your walkable tiles, all other tiles are UNWALKABLE
	_pathFinder->SetPathFinderFocus(_tileEngine->GetLayer(0),_tileEngine->GetTileWidth(),_tileEngine->GetTileHeight(),_tileEngine->GetLayer(0)->GetNumTilesWide());
	
	
	XDL_SPRITEBATCH->GetCamera()->SetZoom(1);
	XDL_SPRITEBATCH->GetCamera()->SetPosition(0,0);
	
}


TileEngineScene::~TileEngineScene(void)
{
}

void TileEngineScene::Update()
{
	if(XDL_INPUT->IsMouseButtonDown(1))
	{
		ostringstream ss;
		ss<<_numInserted;
		_enemies->insert(_enemies->begin(),new PathFindingSprite("chaser.png",XDL_INPUT->GetMousePositionScreen().x,XDL_INPUT->GetMousePositionScreen().y,32 ,32,10,_renderer,_pathFinder,_sprite,"chaser" + ss.str()));
		cout<<"Num Inserted : " << _numInserted << endl;
		_numInserted++;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->D))
	{
		_sprite->_posX++;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->A))
	{
		_sprite->_posX--;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->W))
	{
		_sprite->_posY--;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->S))
	{
		_sprite->_posY++;
	}
	for(int i = 0; i < _enemies->size(); i ++)
	{
		_enemies->at(i)->Update();
	}
}

void TileEngineScene::Draw()
{
	XDL_SPRITEBATCH->Begin();//draw everything
	XDL_SPRITEBATCH->Draw(_sprite);

	for(int i = 0; i < _enemies->size(); i ++)
	{
		XDL_SPRITEBATCH->Draw(_enemies->at(i));
	}
	_tileEngine->Draw(XDL_SPRITEBATCH);
	
	XDL_SPRITEBATCH->End();
}