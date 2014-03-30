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


void XDL_CollisionManager::Init(XDL_QuadTree* XDL_QUADTREE,XDL_Scene* _currentScene)
{
	this->XDL_QUADTREE = XDL_QUADTREE;
	this->_currentScene = _currentScene;
}

bool XDL_CollisionManager::DidCollide(XDL_GameObject* _object1,XDL_GameObject* _object2)
{
	/*To check if a collision happened, we simply loop through  all the collisions that have happened, and return true if a match is found*/
	for(int i = 0; i < _processedCollisions.size(); i ++)
	{
		if(_processedCollisions[i]->GetObject1() == _object1 && _processedCollisions[i]->GetObject2() == _object2)
		{
			return true;
		}
		if(_processedCollisions[i]->GetObject2() == _object1 && _processedCollisions[i]->GetObject1() == _object2)
		{
			return true;
		}
	}
	return false;
}

void XDL_CollisionManager::ProcessCollisions()
{
	//Process all possible collisions
	_processedCollisions.clear();//remove last frames saved collisions, as they are no longer relivant
	vector<XDL_GameObject*> _collidableObjects;
	vector<XDL_GameObject*> _allObjectsThatAreCollidable =  _currentScene->GetAllGameObjectsInScene();// get all objects in scene
	for(int i = 0; i <_allObjectsThatAreCollidable.size(); i ++)//loop through them all
	{
		//make sure our object is collidable, and can move
		//If its not collidable, then it doesnt make sense to check collisions
		//If its "Immovable", it means its static object, so we don't need to check it against everything, but we should still check non-immovable objects against it
		if(_allObjectsThatAreCollidable[i]->_collidable == true && _allObjectsThatAreCollidable[i]->_immovable == false)
		{
			_collidableObjects.clear();
			_collidableObjects = XDL_QUADTREE->ReturnObjects(_allObjectsThatAreCollidable[i]->_bounds,_collidableObjects);
			//get all the objects the current object could collide with
			for(int j = 0; j < _collidableObjects.size(); j ++)
			{
				if(_collidableObjects[j] != _allObjectsThatAreCollidable[i])//make sure they are not the same object
				{
					if(_allObjectsThatAreCollidable[i]->CollidedWith(_collidableObjects[j]) && !DidCollide(_allObjectsThatAreCollidable[i],_collidableObjects[j])) 
					{
						_processedCollisions.insert(_processedCollisions.begin(),new XDL_Collision(_allObjectsThatAreCollidable[i],_collidableObjects[j]));// add the collision, so the programmer/game knows it happened
						
						_collidableObjects.erase(_collidableObjects.begin() + j);

					}
				}
				
				
			}
		}
	}
	_collidableObjects.clear();
}

vector<XDL_Collision*> XDL_CollisionManager::GetCollisions()//return all the collisions that happened this frame
{
	return _processedCollisions;
}
