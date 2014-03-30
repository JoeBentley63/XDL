#include "XDL_Game.h"
#include "XDL_Debug.h"
#include "XDL_SceneManager.h"
#include "SortingModeDemoScene.h"
#include "TileEngineScene.h"
#include "Breakout.h"
#include "MouseDemo.h"
#include "QuadTreeDemoScene.h"
#include "PathFindingSprite.h"
#include "XDL_Keyboard.h"
#include "XDL_TestScene.h"
int XDL_Game::_r;
int XDL_Game::_g;
int XDL_Game::_b;
int XDL_Game::SCREEN_WIDTH;
int XDL_Game::SCREEN_HEIGHT;
bool XDL_Game::_drawQuadTreeDebug;
SDL_Rect* XDL_Game::_windowsBounds;
XDL_SceneManager* _sceneManager;
XDL_Keyboard* _keyboard;
XDL_Game::XDL_Game(void)
{
	_keyboard = XDL_Keyboard::GetInstance();
	_drawQuadTreeDebug = false;
}
//setup SDL
bool XDL_Game :: Init()
{
	_r = 0;
	_g = 0;
	_b = 0;
	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;

	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Title",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
	_renderer = SDL_CreateRenderer(_window,-1,0);
	SDL_SetRenderDrawBlendMode(_renderer,SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(_renderer,_r,_g,_b,255);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);

	_windowsBounds = new SDL_Rect();
	_windowsBounds->h = SCREEN_HEIGHT;
	_windowsBounds->w = SCREEN_WIDTH;
	_windowsBounds->x = 0;
	_windowsBounds->y = 0;
	_sceneManager = XDL_SceneManager::GetInstance();
	_sceneManager->ChangeScene(new XDL_TestScene(_renderer),"HelloWorld");

	return true; 
}

XDL_Game::~XDL_Game(void)
{
	delete(_window);
	delete(_windowsBounds);
	delete(_renderer);
}

void XDL_Game::Update()
{
	_sceneManager->Update();
	//scene manager, to jump between scenes [for demo only, allows for easy presenting]

	if(_keyboard->IsKeyDown(XDL_Input::ONE))
	{
		_sceneManager->ChangeScene(new SortingModeDemoScene(_renderer),"Sorting Demo");
	}
	else if(_keyboard->IsKeyDown(XDL_Input::TWO))
	{
		_sceneManager->ChangeScene(new TileEngineScene(_renderer),"Tile Engine Demo");
	}
	else if(_keyboard->IsKeyDown(XDL_Input::THREE))
	{
		_sceneManager->ChangeScene(new QuadTreeDemoScene(_renderer),"QUAD-TREE Demo");
	}
	else if(_keyboard->IsKeyDown(XDL_Input::FOUR))
	{
		_sceneManager->ChangeScene(new MouseDemo(_renderer),"Mouse Demo");
	}
	else if(_keyboard->IsKeyDown(XDL_Input::FIVE))
	{
		_sceneManager->ChangeScene(new Breakout(_renderer),"BreakOut");
	}
	

	if(_keyboard->IsKeyDown(XDL_Input::ZERO))
	{
		_drawQuadTreeDebug = true;
	}
	else if(_keyboard->IsKeyDown(XDL_Input::NINE))
	{
		_drawQuadTreeDebug = false;
	}

}
//draw logic should do here
void XDL_Game::Render()
{
	_sceneManager->Draw();
}

void XDL_Game::CleanUp()
{
	SDL_Quit();
}

