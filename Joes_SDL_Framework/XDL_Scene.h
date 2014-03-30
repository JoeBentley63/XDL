//! XDL_Scene
/*!
Pure virtual class that just provides a super for scenes so my scene management works.
*/

#ifndef _SCENE_H
#define _SCENE_H

#include "XDL_Sprite.h"
#include "XDL_Input.h"
#include "XDL_SpriteBatch.h"
#include "XDL_Camera.h"
#include "XDL_QuadTree.h"
#include "XDL_CollisionManager.h"
#include <map>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;

class XDL_CollisionManager;

class XDL_Scene
{
public:
	XDL_Scene(void);
	~XDL_Scene(void);
	void Init(SDL_Renderer* _renderer,int _worldSizeX,int _worldSizeY);
	virtual void Draw();/*!every scene requires an update and a draw minimum */
	virtual void Update();
	vector<XDL_GameObject*> GetAllGameObjectsInScene();
	virtual bool AddGameObjectToScene(XDL_GameObject* _gameobject);
	virtual bool RemoveGameObjectFromScene(string _id);
	virtual bool RemoveGameObjectFromScene(XDL_GameObject* _gameobject);
	virtual XDL_GameObject* GetGameObjectFromSceneUsingID(string _id);

protected:
	XDL_Input* XDL_INPUT;/*pointers to key modules */
	XDL_SpriteBatch* XDL_SPRITEBATCH;
	XDL_Camera* XDL_CAMERA;
	XDL_CollisionManager* XDL_COLLISION_MANAGER;
	SDL_Renderer* _renderer;

	map<string,XDL_GameObject*> _gameObjectsInScene;
	XDL_QuadTree* XDL_QUADTREE;
	
	void RepopulateQuadTree();
};

#endif
