//Pure virtual class that just provides a super for scenes so my scene management works.
#ifndef _SCENE_H
#define _SCENE_H

#include "XDL_Sprite.h"
#include "XDL_Input.h"
#include "XDL_SpriteBatch.h"
#include "XDL_Camera.h"
#include "XDL_Storage.h"
#include "XDL_QuadTree.h"
#include "XDL_CollisionManager.h"
#include <map>
#include <vector>
#include <stdio.h>
using namespace std;

class XDL_CollisionManager;

class XDL_Scene
{
public:
	XDL_Scene(void);
	~XDL_Scene(void);
	void Init(SDL_Renderer* _renderer,int _worldSizeX,int _worldSizeY);
	virtual void Draw();//every scene requires an update and a draw minimum
	virtual void Update();
	vector<XDL_GameObject*> GetAllGameObjectsInScene();
	virtual bool AddGameObjectToScene(XDL_GameObject* _gameobject, string _id);
	virtual bool RemoveGameObjectFromScene(string _id);
	virtual XDL_GameObject* GetGameObjectFromSceneUsingID(string _id);

protected:
	XDL_Input* _input;//keyboard, camera and spritebatch will remain, but tile engine will be optional, since this assignment is about tile engines its here.
	XDL_SpriteBatch* _spriteBatch;
	XDL_Camera* _camera;
	XDL_Storage* _persistantStorage;
	XDL_CollisionManager* _collisionManager;
	SDL_Renderer* _renderer;

	map<string,XDL_GameObject*> _gameObjectsInScene;
	XDL_QuadTree* _quadTree;
	
	void RepopulateQuadTree();
};

#endif
