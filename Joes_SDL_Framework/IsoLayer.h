
#ifndef _ISO_LAYER_H
#define _ISO_LAYER_H

#include <vector>
#include "XDL_Sprite.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class IsoLayer
{
public:
	IsoLayer(XMLElement* _layer,int _tilesNumWidth,int _tilesNumHeight,int _tileSheetWidth,char* _nameOfSpriteSheet,int _tilesWidth,int _tilesHeight,SDL_Renderer* _renderer,int _spacing, int _margin,int _gidFixer);
	~IsoLayer(void);
	void Update();
	void Draw();
	vector<XDL_Sprite*> _tiles;
private:
	static const int _width = 5;
	static const int _height = 5;
	SDL_Renderer* _renderer;
	int _tilesWidth;
	int _tilesHeight;
};

#endif