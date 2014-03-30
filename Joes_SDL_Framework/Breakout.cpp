//! Breakout Demo Scene
/*!
A Demo Scene to show how easy it is to make the classic game breakout in XDL
*/

#include "Breakout.h"
#include "XDL_SceneManager.h"


XDL_Sprite* _ball;
XDL_Sprite* _paddle;
vector<XDL_Sprite*> _blocks;
Breakout::Breakout(SDL_Renderer* _renderer)
{
	XDL_Scene::Init(_renderer,640,480);/*!Setup scene*/
	XDL_SPRITEBATCH->SetDrawMode(XDL_SpriteBatch::BACKTOFRONT);
	XDL_SPRITEBATCH->GetCamera()->SetZoom(1);
	XDL_SPRITEBATCH->GetCamera()->SetPosition(0,0);

	/*!Create our ball*/
	_ball = new XDL_Sprite("DemoAssets/Blue.png",XDL_Game::SCREEN_WIDTH/2,XDL_Game::SCREEN_HEIGHT/2,16,16,10,_renderer,"ball");
	_ball->_collidable = true;
	_ball->_immovable = false;
	_ball->SetVelocity(3,3);
	AddGameObjectToScene(_ball);/*!Add it to scene where it will be auto updated/drawn/collision detection*/

	/*!create our paddle*/
	_paddle = new XDL_Sprite("DemoAssets/Green.png",XDL_Game::SCREEN_WIDTH/2,XDL_Game::SCREEN_HEIGHT - 20,50,16,10,_renderer,"paddle");
	_paddle->_collidable = true;
	_paddle->_immovable = true;
	AddGameObjectToScene(_paddle);


	int _posX = 1;
	int _posY = 1;

	/*!Create all the blocks*/
	for(int i = 0; i < 50; i ++)
	{
		ostringstream ss;
		ss << i;
		XDL_Sprite* _block = new XDL_Sprite("DemoAssets/Yellow.png",_posX % XDL_Game::SCREEN_WIDTH,(_posX / XDL_Game::SCREEN_WIDTH) * 20,62,16,10,_renderer,"block" + ss.str());
		_block->_collidable = true;
		_block->_immovable = true;
		_blocks.insert(_blocks.begin(),_block);
	
		AddGameObjectToScene(_block);
		_posX += 64;
		
	}
}


Breakout::~Breakout(void)
{
	delete(_manager);
}

void Breakout::Update()
{
	XDL_Scene::Update();
	
	if(XDL_INPUT->IsKeyDown(XDL_Input::LEFT) && _paddle->_posX > 0)/*!move paddle left/right depending on key down*/
	{
		_paddle->_posX -= 5;
	}
	else if(XDL_INPUT->IsKeyDown(XDL_Input::RIGHT) && _paddle->_posX < XDL_Game::SCREEN_WIDTH)
	{
		_paddle->_posX += 5;
	}

	if(XDL_COLLISION_MANAGER->DidCollide(_paddle,_ball))/*!if ball hit paddle, change its velocity*/
	{
		_ball->SetVelocityY(-3);
	}

	for(int i = 0; i < _blocks.size(); i ++)
	{
		if(XDL_COLLISION_MANAGER->DidCollide(_blocks[i],_ball))/*!if ball hit paddle, then we move it down, and delete the block*/
		{
			_ball->SetVelocityY(3);
			this->RemoveGameObjectFromScene(_blocks[i]->GetName());
			_blocks.erase(_blocks.begin() + i);
		}
	}

	if(_ball->_posX < 0)/*!stop ball going off screen*/
	{
		_ball->SetVelocityX(3);
	}
	else if(_ball->_posX > XDL_Game::SCREEN_WIDTH)
	{
		_ball->SetVelocityX(-3);
	}
	
}

void Breakout::Draw()
{
	XDL_SPRITEBATCH->Begin();//clear the draw queue
	XDL_Scene::Draw();// call your super, which will take all gameobjects added to the scene, and queue them for drawing
	/*
	Any other drawing the User may need to do.
	*/
	XDL_SPRITEBATCH->End();//draw everything

}