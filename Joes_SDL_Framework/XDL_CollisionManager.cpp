#include "XDL_CollisionManager.h"

 XDL_CollisionManager*  XDL_CollisionManager::_me;

XDL_CollisionManager::XDL_CollisionManager(void)
{
}


XDL_CollisionManager::~XDL_CollisionManager(void)
{
}

XDL_CollisionManager* XDL_CollisionManager::GetInstance()
{
	if(_me == NULL)
	{
		_me = new XDL_CollisionManager();
	}
	return _me;
}


void XDL_CollisionManager::Init(XDL_QuadTree* _quadTree,XDL_Scene* _currentScene)
{
	this->_quadTree = _quadTree;
	this->_currentScene = _currentScene;
}


void XDL_CollisionManager::ProcessCollisions()
{
	_processedCollisions.clear();
	vector<XDL_GameObject*> _collidableObjects;
	vector<XDL_GameObject*> _allObjectsThatAreCollidable =  _currentScene->GetAllGameObjectsInScene();
	for(int i = 0; i <_allObjectsThatAreCollidable.size(); i ++)
	{
		if(_allObjectsThatAreCollidable[i]->_collidable == true)
		{
			_collidableObjects.clear();
			_collidableObjects = _quadTree->ReturnObjects(_allObjectsThatAreCollidable[i]->_bounds,_collidableObjects);
	
			for(int j = 0; j < _collidableObjects.size(); j ++)
			{
				if(_collidableObjects[j] != _allObjectsThatAreCollidable[i])
				{
					if(_allObjectsThatAreCollidable[i]->CollidedWith(_collidableObjects[j]))
					{
						_processedCollisions.insert(_processedCollisions.begin(),new XDL_Collision(_allObjectsThatAreCollidable[i],_collidableObjects[j]));
					}
				}
			}
		}
	}
	_collidableObjects.clear();
}

vector<XDL_Collision*> XDL_CollisionManager::GetCollisions()
{
	return _processedCollisions;
}
