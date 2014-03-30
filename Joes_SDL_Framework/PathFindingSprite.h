//! PathFinding Sprite
/*!
Extension of XDL_Sprite, which add simple behaviour to search for and follow paths.
*/

#ifndef _PLAYER_H
#define _PLAYER_H

#include "XDL_Sprite.h"
#include <vector>
#include "XDL_Game.h"
#include "XDL_PathFinder.h"
class PathFindingSprite :
	public XDL_Sprite
{
public:
	PathFindingSprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer,XDL_PathFinder* _pathFinder,XDL_Sprite* _target,string _uniqueName);
	virtual ~PathFindingSprite(void);
	void StopFollowingPath();
	void FollowPath(vector<SDL_Point*>* _path);
	int DistanceFrom(int _startX,int _startY,int _endX,int _endY);
	void Update();
	void Draw();
	static bool _locked;
	bool _followPath;
	XDL_Sprite* _target;
private:
	vector<SDL_Point*>* _path;/*! The path we should follow*/
	int _shouldCheckAgain;/*!Are we finished our path, ie should we check again*/
	int _targetTime;
	int _currentNode;
	int _r;/*!colors for the path debug in rgba*/
	int _g;/*!colors for the path debug in rgba*/
	int _b;/*!colors for the path debug in rgba*/
	int _a;/*!colors for the path debug in rgba*/
	XDL_PathFinder* _pathFinder;/*!pointer to shared pathfinder*/
	
};

#endif

