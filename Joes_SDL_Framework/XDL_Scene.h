//Pure virtual class that just provides a super for scenes so my scene management works.
#ifndef _SCENE_H
#define _SCENE_H

#include "XDL_Sprite.h"
#include "XDL_Keyboard.h"
#include "XDL_SpriteBatch.h"
#include "XDL_Camera.h"
#include "XDL_Storage.h"
#include <map>
using namespace std;

class XDL_Scene
{
public:
	XDL_Scene(void);
	~XDL_Scene(void);
	void Init(SDL_Renderer* _renderer);
	virtual void Draw();//every scene requires an update and a draw minimum
	virtual void Update();
	XDL_Sprite* _sprite;// just something for every scene to have for me to test. Will be removed 
protected:
	XDL_Keyboard* _keyboard;//keyboard, camera and spritebatch will remain, but tile engine will be optional, since this assignment is about tile engines its here.
	XDL_SpriteBatch* _spriteBatch;
	XDL_Camera* _camera;
	XDL_Storage* _persistantStorage;
	SDL_Renderer* _renderer;
	map<string,XDL_GameObject*> _gameObjectsInScene;
	virtual bool AddGameObjectToScene(XDL_GameObject* _gameobject, string _id);
	virtual bool RemoveGameObjectFromScene(string _id);
	virtual XDL_GameObject* GetGameObjectFromSceneUsingID(string _id);

};

#endif
