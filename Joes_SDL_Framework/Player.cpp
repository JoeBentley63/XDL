#include "Player.h"
#include <random>

using namespace std;
bool Player::_locked;
Player::Player(SDL_Renderer* _renderer,char* _asset,SDL_Rect _rect,int _posX,int _posY,XDL_PathFinder* _pathFinder,XDL_Sprite* _target,int _r,int _g,int _b,int _a) : XDL_Sprite(_asset,XDL_Game::SCREEN_WIDTH/2,XDL_Game::SCREEN_HEIGHT/2,32,32,_renderer,_rect,3)
{
	this->_pathFinder = _pathFinder;
	this->_target = _target;
	this->_posX = _posX;
	this->_posY = _posY;
	this->_r = _r;
	this->_g = _g;
	this->_b = _b;
	this->_a = _a;
	 _path = NULL;
	 _followPath = false;
	 _currentNode = 0;
	 _shouldCheckAgain = 0;
	 _targetTime = (rand() % 100);
	 _locked = false;
}

void Player::StopFollowingPath()
{
	_followPath = false;
	//this->_path = NULL;
	_currentNode = 0;
}

void Player::FollowPath(vector<SDL_Point*>* _path)
{
	if(_path == NULL)
	{
		StopFollowingPath();
	}
	else
	{
		_followPath = true;
		this->_path = _path;
		_currentNode = 0;
	}
}

void Player::Update()
{
	XDL_Sprite::Update();
	if(!_followPath)
	{
		if(_shouldCheckAgain>_targetTime)
		{
			_shouldCheckAgain = 0;
			_targetTime = (rand() % 100);
			if(!_locked)
			{
				_locked = true;
				_pathFinder->TryGetPath(_posX,_posY,_target->_posX,_target->_posY,this);
				_locked = false;
			}
		}
		_shouldCheckAgain++;
	}
	if(_followPath)
	{
		if(_posX < _path->at(_currentNode)->x)
		{
			_posX++;
		}
		else if(_bounds.x > _path->at(_currentNode)->x)
		{
			_posX--;
		}
		if(_posY < _path->at(_currentNode)->y)
		{
			_posY++;
		}
		else if(_posY > _path->at(_currentNode)->y)
		{
			_posY--;
		}
		if(DistanceFrom(_posX,_posY,_path->at(_currentNode)->x,_path->at(_currentNode)->y) < 2)
		{
			_currentNode++;
			if(_currentNode>=_path->size())
			{
				StopFollowingPath();
			}
		}
	}
}
int Player::DistanceFrom(int _startX,int _startY,int _endX,int _endY)
{
	return sqrt((_endX - _startX)*(_endX - _startX) + (_endY - _startY)*(_endY - _startY));
}
void Player::Draw()
{
	XDL_Sprite::Draw();
	if(DEBUG)
	{
		SDL_SetRenderDrawColor(_renderer,_r,_g,_b,_a);
		if(_path!=NULL)
		{
			for(int i = _currentNode; i < _path->size(); i ++)
			{
				if(_currentNode!=0 && _currentNode < _path->size())
				{
					SDL_Point* _point = _path->at(i);
					SDL_Point* _otherPoint = _path->at(i - 1);
			
					SDL_RenderDrawLine(_renderer,_point->x +5,_point->y+5 ,_otherPoint->x+5,_otherPoint->y+5);
			
				}
			}
		}
		SDL_SetRenderDrawColor(_renderer,255,255,255,255);
	}
}
Player::~Player(void)
{
}
