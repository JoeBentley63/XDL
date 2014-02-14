#ifndef _PLAYER_H
#define _PLAYER_H

#include "XDL_Sprite.h"
#include <vector>
#include "XDL_Game.h"
#include "XDL_PathFinder.h"
class Player :
	public XDL_Sprite
{
public:
	Player(SDL_Renderer* _renderer,char* _asset,SDL_Rect _rect,int _posX,int _posY,XDL_PathFinder* _pathFinder,XDL_Sprite* _target,int _r,int _g,int _b,int _a);
	virtual ~Player(void);
	void StopFollowingPath();
	void FollowPath(vector<SDL_Point*>* _path);
	int DistanceFrom(int _startX,int _startY,int _endX,int _endY);
	void Update();
	void Draw();
	static bool _locked;
	bool _followPath;
private:
	vector<SDL_Point*>* _path;
	int _shouldCheckAgain;
	int _targetTime;
	int _currentNode;
	int _r;
	int _g;
	int _b;
	int _a;
	XDL_PathFinder* _pathFinder;
	XDL_Sprite* _target;
};

#endif

