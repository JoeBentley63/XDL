#include "XDL_Game.h"
#include "XDL_Debug.h"
#include "XDL_SceneManager.h"
#include "SortingModeDemoScene.h"
#include "CollisionDetectionDemo.h"
#include "IsometricTileEngineScene.h"
#include "MouseDemo.h"
#include "Level1.h"
int XDL_Game::_r;
int XDL_Game::_g;
int XDL_Game::_b;
int XDL_Game::SCREEN_WIDTH;
int XDL_Game::SCREEN_HEIGHT;

SDL_Rect* XDL_Game::_windowsBounds;
XDL_SceneManager* _sceneManager;

XDL_Game::XDL_Game(void)
{
	
}
//initialization logic goes here
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
	_sceneManager->ChangeScene(new Level1(_renderer),"level1");
	
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

