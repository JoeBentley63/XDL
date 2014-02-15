//!XDL_Tile
/*!
Used in XDL_TileEngine, inherits from sprite, and adds extra variables and functions to allow pathfinding etc.
*/


#ifndef _TILE_H
#define _TILE_H

#include "XDL_Sprite.h"
class XDL_Tile :
	public XDL_Sprite
{
public:
	XDL_Tile(char* _asset,int _x,int _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect,int _gid);
	virtual ~XDL_Tile(void);
	int _gid;
	void SetParent(XDL_Tile* _parent); 
	XDL_Tile* GetParent();

private:
	XDL_Tile* _parent;
	XDL_Tile* _child;
};

#endif

