/***************************************************************
Joseph Bentley P10011026 : TMX Reader Assignment
****************************************************************/
#ifndef _TILE_ENGINE_H
#define _TILE_ENGINE_H

#include <vector>
#include "XDL_Sprite.h"
#include "tinyxml2.h"
#include "XDL_Layer.h"
#include "XDL_SpriteBatch.h"

using namespace std;
using namespace tinyxml2;

class XDL_TileEngine
{
public:
	XDL_TileEngine(SDL_Renderer* _renderer,int _tilesWidth,int _tilesHeight);
	~XDL_TileEngine(void);
	void Update();
	void Draw(XDL_SpriteBatch* _spriteBatch);
	bool LoadFromXML(char* _pathToTMX);
	bool LoadFromTMXAndTSX(char* _pathToTMX);
	int GetTileWidth();
	int GetTileHeight();
	XDL_Layer* GetLayer(int layerNum);

private :
	void LoadFromArray();
	static const int _width = 5;
	static const int _height = 5;
	vector<XDL_Layer*> _layers;
	SDL_Renderer* _renderer;
	int _tilesWidth;
	int _tilesHeight;
};

#endif
