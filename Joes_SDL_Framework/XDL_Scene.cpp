
#include "XDL_Scene.h"

XDL_GameObject* _temp;
XDL_Scene::XDL_Scene(void)
{

	
}

XDL_Scene::~XDL_Scene(void)
{
	delete(XDL_INPUT);
	delete(XDL_SPRITEBATCH);
	delete(XDL_CAMERA);

	delete(_renderer);

}

void XDL_Scene::Init(SDL_Renderer* _renderer,int _worldSizeX,int _worldSizeY)
{
	this->_renderer = _renderer;
	XDL_SPRITEBATCH = XDL_SpriteBatch::GetInstance();//grab instances
	XDL_SPRITEBATCH->Init(_renderer,_worldSizeX,_worldSizeY);
	XDL_INPUT = XDL_Input::GetInstance();
	XDL_CAMERA = XDL_Camera::GetInstance();
	XDL_COLLISION_MANAGER = XDL_CollisionManager::GetInstance();
	_gameObjectsInScene.clear();
	SDL_Rect* _bounds = new SDL_Rect();
	_bounds->x = 0;
	_bounds->y = 0;
	_bounds->w = _worldSizeX;
	_bounds->h = _worldSizeY;
	XDL_QUADTREE = new XDL_QuadTree(1,_bounds,_renderer);

	XDL_COLLISION_MANAGER->Init(XDL_QUADTREE,this);
	XDL_SPRITEBATCH->SetDrawMode(XDL_SpriteBatch::BACKTOFRONT);
}

void XDL_Scene:: Update()
{
	RepopulateQuadTree();//start of each frame, repop quadtree
	
	XDL_COLLISION_MANAGER->ProcessCollisions();//then process all collisions
	
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		_temp->Update();//and update everything
	}
	
}

void XDL_Scene:: Draw()//draw all objects in the scene
{
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		XDL_SPRITEBATCH->Draw(_temp);
	}
	XDL_QUADTREE->Draw();//draw the quadtrees debug info
}

void XDL_Scene::RepopulateQuadTree()//insert all objects into the quadtree (if its collidable)
{
	XDL_QUADTREE->Clear();
	int _num= 0;
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_temp = i->second;
		//DEBUG_MSG("\n\n-------------------------------\n\n");
		if(_temp->_collidable == true)
		{
			XDL_QUADTREE->Insert(_temp);
			_num++;
		}
	}
	//cout<<"Blah";
}

bool XDL_Scene::AddGameObjectToScene(XDL_GameObject* _gameobject)//add a gameobject to the scene
{
	if(_gameObjectsInScene.find(_gameobject->GetName())!=_gameObjectsInScene.end())
	{
		return false; //id already used, object not added
	}
	
	_gameObjectsInScene.insert(std::make_pair(_gameobject->GetName(),_gameobject));
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

bool XDL_Scene::RemoveGameObjectFromScene(XDL_GameObject* _gameobject)
{
	if(_gameObjectsInScene.find(_gameobject->GetName())!=_gameObjectsInScene.end())
	{
		_gameObjectsInScene.erase(_gameobject->GetName());
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

vector<XDL_GameObject*> XDL_Scene::GetAllGameObjectsInScene()
{
	vector<XDL_GameObject*> _allObjects;
	for(map<string, XDL_GameObject*>::const_iterator i = _gameObjectsInScene.begin(); i != _gameObjectsInScene.end(); ++i)
	{
		_allObjects.insert(_allObjects.begin(),i->second);
	}
	return _allObjects;
}