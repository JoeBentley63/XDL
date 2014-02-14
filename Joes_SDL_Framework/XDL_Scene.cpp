
#include "XDL_Scene.h"

XDL_GameObject* _temp;
XDL_Scene::XDL_Scene(void)
{
}

XDL_Scene::~XDL_Scene(void)
{
}

void XDL_Scene::Init(SDL_Renderer* _renderer)
{
	this->_renderer = _renderer;
	_spriteBatch = XDL_SpriteBatch::GetInstance();//grab instances
	_spriteBatch->Init(_renderer);
	_keyboard = XDL_Keyboard::GetInstance();
	_camera = XDL_Camera::GetInstance();
	_persistantStorage = XDL_Storage::GetInstance();
	_gameObjectsInScene.clear();
}

void XDL_Scene:: Update()
{
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
