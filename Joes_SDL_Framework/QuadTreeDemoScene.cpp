#include "QuadTreeDemoScene.h"
#include "DemoMoverSprite.h"

vector<XDL_Sprite*> _objects;
bool _mouseDown = false;
int _currentNum = 0;
QuadTreeDemoScene::QuadTreeDemoScene(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_currentNum = 0;
	_zoom = 1;

	XDL_SPRITEBATCH->GetCamera()->SetZoom(1);
	XDL_SPRITEBATCH->GetCamera()->SetPosition(0,0);
}

QuadTreeDemoScene::~QuadTreeDemoScene(void)
{
}

void QuadTreeDemoScene::Update()
{
	
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->UP))
	{
		_zoom-=0.001;
	}
	if(XDL_INPUT->IsKeyDown(XDL_INPUT->DOWN))
	{
		_zoom += 0.001;
	}
	XDL_SPRITEBATCH->GetCamera()->SetZoom(_zoom);

	if(XDL_INPUT->IsMouseButtonDown(3) && _mouseDown == false)
	{
		ostringstream ss;
		ss << _currentNum;
		XDL_Sprite* _temp = new DemoMoverSprite("DemoAssets/Blue.png",XDL_INPUT->GetMousePositionScreen().x,XDL_INPUT->GetMousePositionScreen().y,10,10,1,_renderer,"player" + ss.str());
		_objects.insert(_objects.begin(),_temp);
		_temp->_immovable = true;
		_temp->_collidable = true;
		AddGameObjectToScene(_temp);
		_currentNum++;
		_mouseDown = true;
	}
	else if(XDL_INPUT->IsMouseButtonDown(1) && _mouseDown == false)
	{
		ostringstream ss;
		ss << _currentNum;
		XDL_Sprite* _temp = new DemoMoverSprite("DemoAssets/Green.png",XDL_INPUT->GetMousePositionScreen().x,XDL_INPUT->GetMousePositionScreen().y,10,10,1,_renderer,"player" + ss.str());
		_objects.insert(_objects.begin(),_temp);
		_temp->_immovable = true;
		_temp->_collidable = false;
		AddGameObjectToScene(_temp);
		_currentNum++;
		_mouseDown = true;
	}
	if (XDL_INPUT->IsMouseButtonUp(3) && _mouseDown)
	{
		_mouseDown = false;
	}
	XDL_Scene::Update();
	
}

void QuadTreeDemoScene::Draw()
{
	XDL_SPRITEBATCH->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	XDL_SPRITEBATCH->End();//draw everything

}
