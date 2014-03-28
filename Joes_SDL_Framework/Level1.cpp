#include "Level1.h"
#include "DemoMoverSprite.h"

vector<XDL_Sprite*> _objects;
bool _mouseDown = false;
int _currentNum = 0;
Level1::Level1(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	_zoom = 1;
}

Level1::~Level1(void)
{
}

void Level1::Update()
{
		
	if(_input->IsKeyDown(_input->UP))
	{
		_zoom-=0.001;
	}
	if(_input->IsKeyDown(_input->DOWN))
	{
		_zoom += 0.001;
	}
	_spriteBatch->GetCamera()->SetZoom(_zoom);

	if(_input->IsMouseButtonDown(3) && _mouseDown == false)
	{
		XDL_Sprite* _temp = new DemoMoverSprite("Face.bmp",_input->GetMousePositionScreen().x,_input->GetMousePositionScreen().y,10,10,1,_renderer);
		_objects.insert(_objects.begin(),_temp);
		_temp->_immovable = true;
		_temp->_collidable = true;
		ostringstream ss;
		ss << _currentNum;
		AddGameObjectToScene(_temp,"player" + ss.str());
		_currentNum++;
		_mouseDown = true;
	}
	if (_input->IsMouseButtonUp(3) && _mouseDown)
	{
		_mouseDown = false;
	}
	XDL_Scene::Update();
	cout<<"Total Collisions this frame : " << _collisionManager->GetCollisions().size() << endl;
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
