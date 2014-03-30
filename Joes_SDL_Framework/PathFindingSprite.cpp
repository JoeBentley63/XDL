#include "PathFindingSprite.h"
#include <random>

using namespace std;
bool PathFindingSprite::_locked;
PathFindingSprite::PathFindingSprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer,XDL_PathFinder* _pathFinder,XDL_Sprite* _target,string _uniqueName): XDL_Sprite(_asset,_x,_y,_height,_width,_z,_renderer,_uniqueName)
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

void PathFindingSprite::StopFollowingPath()
{
	_followPath = false;
	//this->_path = NULL;
	_currentNode = 0;
}

void PathFindingSprite::FollowPath(vector<SDL_Point*>* _path)
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

void PathFindingSprite::Update()
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
int PathFindingSprite::DistanceFrom(int _startX,int _startY,int _endX,int _endY)
{
	return sqrt((_endX - _startX)*(_endX - _startX) + (_endY - _startY)*(_endY - _startY));
}
void PathFindingSprite::Draw()
{
	XDL_Sprite::Draw();
	
	
	
}
PathFindingSprite::~PathFindingSprite(void)
{
}
