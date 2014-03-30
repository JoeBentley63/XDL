//! XDL_Collision Manager
/*!
A manager that processes collisions at the beginning of a frame.

Stores processed successfull collisions if a vector, so the programmer 
can query processed collisions, witout having to redo the collision detection.

Takes collision detection away form the programmer, and uses quad-tree to cull possible collisions
before processing and storing colllisions for future use
*/

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
	void Init(XDL_QuadTree* XDL_QUADTREE,XDL_Scene* _currentScene);/*! Initialize function*/
	vector<XDL_Collision*> GetCollisions();/*!Return all the collision pairs that have happened this frame */
	void ProcessCollisions();/*!Process all collisions that should happen this frame*/
	bool DidCollide(XDL_GameObject* _object1,XDL_GameObject* _object2);/*!query vector to see did 2 objects collide*/
private:
	XDL_CollisionManager(void);
	static XDL_CollisionManager* _me;
	vector<XDL_Collision*> _processedCollisions;
	XDL_QuadTree* XDL_QUADTREE;
	XDL_Scene* _currentScene;
};

#endif