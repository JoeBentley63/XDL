
#include "XDL_Scene.h"

XDL_Scene::XDL_Scene(void)
{
}

XDL_Scene::~XDL_Scene(void)
{
}

void XDL_Scene::Init(SDL_Renderer* _renderer)
{
	this->_renderer = _renderer;
	_spriteBatch = XDL_SpriteBatch::GetInstance();//grab instances
	_spriteBatch->Init(_renderer);
	_keyboard = XDL_Keyboard::GetInstance();
	_camera = XDL_Camera::GetInstance();
	_persistantStorage = XDL_Storage::GetInstance();
}

void XDL_Scene:: Draw()
{

}
void XDL_Scene:: Update()
{
	
}