#ifndef _PATH_FINDER_H
#define _PATH_FINDER_H
#include "XDL_Tile.h"
#include <stdlib.h>
#include "XDL_Layer.h"
#include <vector>
#include <stack>
#include <map>
#include <thread>

using namespace std;

class XDL_PathFinder
{
public:
	static XDL_PathFinder* GetInstance();
	~XDL_PathFinder(void);
	void SetPathFinderFocus(XDL_Layer* _layer,int _tileWidth,int _tileHeight,int _numTilesWide);
	void SetWeight(int _gid,float _weight);
	float GetWeight(int _gid);
	void TryGetPath(int _startX,int _startY,int _endX,int _endY,XDL_Sprite* _sprite);
	XDL_Sprite* _sprite;
	int _startX;
	int _startY;
	int _endX;
	int _endY;
	static const int _WALKABLE = 1;
	static const int _NOT_WALKABLE = 99;
private:
	bool _free;
	static XDL_PathFinder* _me;
	SDL_Point _startPoint;
	SDL_Point _endPoint;
	vector<SDL_Point*>* _finalPath;
	vector<XDL_Tile*>* _openList;
	vector<XDL_Tile*>* _closedList;
	XDL_Layer* _layer;
	int _tileWidth;
	int _tileHeight;
	int _numTilesWide;
	XDL_PathFinder(void);
	void ProcessNode(XDL_Tile* _tile);
	void ReversePath(XDL_Tile* _tile);
	void NoPathFound();
	XDL_Tile* calcNextBestTile();
	void FindPathLoop();
	thread* _thread;
	XDL_Tile* findTile(int _x,int _y);
	bool Contains(vector<XDL_Tile*> _vector,XDL_Tile* _tileToSearchFor);
	int DistanceFrom(int _startX,int _startY,int _endX,int _endY);
	void KillParents();//Batman function
	int _numNodes;
	map<int,float> _weights;
};

#endif