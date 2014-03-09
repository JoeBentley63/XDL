
#include "XDL_Scene.h"

XDL_GameObject* _temp;
XDL_Scene::XDL_Scene(void)
{

	
}

XDL_Scene::~XDL_Scene(void)
{
	delete(_sprite);
	delete(_input);
	delete(_spriteBatch);
	delete(_camera);
	delete(_persistantStorage);
	delete(_renderer);

}

void XDL_Scene::Init(SDL_Renderer* _renderer)
{
	this->_renderer = _renderer;
	_spriteBatch = XDL_SpriteBatch::GetInstance();//grab instances
	_spriteBatch->Init(_renderer);
	_input = XDL_Input::GetInstance();
	_camera = XDL_Camera::GetInstance();
	_persistantStorage = XDL_Storage::GetInstance();
	_gameObjectsInScene.clear();
	SDL_Rect* _bounds = new SDL_Rect();
	_bounds->x = 0;
	_bounds->y = 0;
	_bounds->w = 640;
	_bounds->h = 480;
	_quadTree = new XDL_QuadTree(1,_bounds,_renderer);
	AddGameObjectToScene(_quadTree,"QuadTree");
}

void XDL_Scene:: Update()
{
	RepopulateQuadTree();
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		_temp->Update();
	}
}

void XDL_Scene:: Draw()
{
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		_spriteBatch->Draw(_temp);
	}
}

void XDL_Scene::RepopulateQuadTree()
{
	_quadTree->Clear();
	int _num= 0;
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		//DEBUG_MSG("\n\n-------------------------------\n\n");
		_quadTree->Insert(_temp);
		_num++;
	}
	//cout<<"Blah";
}

bool XDL_Scene::AddGameObjectToScene(XDL_GameObject* _gameobject, string _id)
{
	if(_gameObjectsInScene.find(_id)!=_gameObjectsInScene.end())
	{
		return false; //id already used, object not added
	}
	
	_gameObjectsInScene.insert(std::make_pair(_id,_gameobject));
	return true;//added
}
bool XDL_Scene::RemoveGameObjectFromScene(string _id)
{
	if(_gameObjectsInScene.find(_id)!=_gameObjectsInScene.end())
	{
		_gameObjectsInScene.erase(_id);
		return true;//object was removed;
	}
	return false;//object was not found
}

XDL_GameObject* XDL_Scene::GetGameObjectFromSceneUsingID(string _id)
{
	if(_gameObjectsInScene.find(_id)!=_gameObjectsInScene.end())
	{
		return _gameObjectsInScene.find(_id)->second;//object exists
	}
	return NULL; //else, not object, return null
}
