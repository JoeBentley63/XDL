#include "XDL_Tile.h"


XDL_Tile::XDL_Tile(char* _asset,int _x,int _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect,int _gid) : XDL_Sprite(_asset,_x,_y,_height, _width,_renderer,_sourceRect)
{
	this->_gid = _gid;
	this->_parent = NULL;
}


XDL_Tile::~XDL_Tile(void)
{
}

void XDL_Tile::SetParent(XDL_Tile* _parent)
{
	this->_parent = _parent;
}
XDL_Tile* XDL_Tile::GetParent()
{
	return _parent;
}
