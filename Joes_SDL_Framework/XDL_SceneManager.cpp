//Scene manager Work In Progress.
#include "XDL_SceneManager.h"
#include "XDL_Camera.h"

XDL_SceneManager* XDL_SceneManager::_me;

XDL_SceneManager::XDL_SceneManager(void)
{

}

XDL_SceneManager::~XDL_SceneManager(void)
{
	delete(_me);
	delete(_currentScene);
	delete(_scene);
}

XDL_SceneManager* XDL_SceneManager::GetInstance()//singleton
{
	if(_me == NULL)
	{
		_me = new XDL_SceneManager();
	}
	return _me;
}

void XDL_SceneManager::Update()
{

	_scene->Update();
}
void XDL_SceneManager::Draw()
{
	_scene->Draw();
}


void XDL_SceneManager::ChangeScene(XDL_Scene* _levelName,char* _level)
{
	_scene = _levelName;
	_currentScene = _level;
}

char* XDL_SceneManager::GetCurrentSceneName()
{
	return _currentScene;
}
XDL_Scene* XDL_SceneManager::GetCurrentScene()
{
	return _scene;
}