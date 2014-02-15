//! XDL_Layer.
/*!
Layer class for XDL_TileEngine. Basicall its a dumbed down tileEngine, and represents a "Tiled" Layer
*/
#ifndef _LAYER_H
#define _LAYER_H
#include <vector>
#include "XDL_Tile.h"
#include "tinyxml2.h"
#include "XDL_SpriteBatch.h"
using namespace std;
using namespace tinyxml2;

class XDL_Layer
{
public:
	
	XDL_Layer(XMLElement* _layer,int _tilesNumWidth,int _tilesNumHeight,int _tileSheetWidth,char* _nameOfSpriteSheet,int _tilesWidth,int _tilesHeight,SDL_Renderer* _renderer,int _spacing, int _margin,int _gidFixer);
	~XDL_Layer(void);
	void Update();
	void Draw(XDL_SpriteBatch* _spriteBatch);
	int GetNumTilesWide();
	int GetNumTilesHigh();
	vector<XDL_Tile*> _tiles;

private:
	SDL_Renderer* _renderer;
	int _tilesWidth;
	int _tilesHeight;
	int _tilesNumWidth;
	int _tilesNumHeight;
};

#endif