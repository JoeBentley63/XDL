//! XDL_Scene manager {Singleton]
/*!
Loads and Unloads scenes.
Also updates and draws scenes that are active.
*/

#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <stdlib.h>
#include "XDL_Scene.h"
#include <map>

using namespace std;
class XDL_SceneManager
{
public:
	~XDL_SceneManager(void);
	void ChangeScene(XDL_Scene* _levelName,char* _level);
	char* GetCurrentSceneName();
	XDL_Scene* GetCurrentScene();
	static XDL_SceneManager* GetInstance();
	void Update();
	void Draw();
private:
	XDL_SceneManager(void);
	static XDL_SceneManager* _me;
	char* _currentScene;
	XDL_Scene* _scene;
};

#endif