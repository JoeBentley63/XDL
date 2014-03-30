#include "XDL_TestScene.h"
#include "XDL_SceneManager.h"



XDL_TestScene::XDL_TestScene(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);
	XDL_SPRITEBATCH->GetCamera()->SetZoom(1);
	XDL_SPRITEBATCH->GetCamera()->SetPosition(0,0);

	this->AddGameObjectToScene(new XDL_Sprite("HelloWorldSplash.png",0,0,640,480,6,_renderer,"HelloWorld"));
	XDL_SPRITEBATCH->SetDrawMode(XDL_SpriteBatch::UNSORTED);
}


XDL_TestScene::~XDL_TestScene(void)
{
}

void XDL_TestScene::Update()
{
	XDL_Scene::Update();
}

void XDL_TestScene::Draw()
{
	XDL_SPRITEBATCH->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	XDL_SPRITEBATCH->End();//draw everything

}