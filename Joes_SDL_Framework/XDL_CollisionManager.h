#ifndef _XDL_COLLISION_MANAGER_H
#define _XDL_COLLISION_MANAGER_H
#include <vector>
#include "XDL_Collision.h"
#include "XDL_Scene.h"
#include "XDL_QuadTree.h"
using namespace std;

class XDL_Scene;

class XDL_CollisionManager
{
public:
	static XDL_CollisionManager* GetInstance();
	~XDL_CollisionManager(void);
	void Init(XDL_QuadTree* _quadTree,XDL_Scene* _currentScene);
	vector<XDL_Collision*> GetCollisions();
	void ProcessCollisions();
private:
	XDL_CollisionManager(void);
	static XDL_CollisionManager* _me;
	vector<XDL_Collision*> _processedCollisions;
	XDL_QuadTree* _quadTree;
	XDL_Scene* _currentScene;
};

#endif