#ifndef _ISOMETRIC_TILE_ENGINE_H
#define _ISOMETRIC_TILE_ENGINE_H

#include <vector>
#include "XDL_Sprite.h"
#include "tinyxml2.h"
#include "IsoLayer.h"

using namespace std;
using namespace tinyxml2;

class IsometricTileEngine 
{
public:
	IsometricTileEngine(SDL_Renderer* _renderer,int _tilesWidth,int _tilesHeight);
	~IsometricTileEngine(void);
	void Update();
	void Draw();
	bool LoadFromXML(char* _pathToTMX);
private :
	static const int _width = 5;
	static const int _height = 5;
	vector<IsoLayer*> _layers;
	SDL_Renderer* _renderer;
	int _tilesWidth;
	int _tilesHeight;
};

#endif
