/***************************************************************
Joseph Bentley P10011026 : TMX Reader Assignment
****************************************************************/

//XDL_Layer class. A layer could be described as a stupider tile engine, or a mini-tile engine, as it doesnt have all the logic a normal on has.
//not that I'm going to question the intelligence of a layer...

#include "XDL_Layer.h"
#include "XDL_SpriteBatch.h"

XDL_Layer::XDL_Layer(XMLElement* _layer,int _tilesNumWidth,int _tilesNumHeight,int _tileSheetWidth,char* _nameOfSpriteSheet,int _tilesWidth,int _tilesHeight,SDL_Renderer* _renderer,int _spacing, int _margin,int _gidFixer)
{
	//pass in all the relivant information, including the XMLElement that points to its layer tag in the TMX
	 XMLElement* _mapTiles = _layer->FirstChildElement("data")->FirstChild()->ToElement();//get down to gid level
	 int _att = atoi(_mapTiles->Attribute("gid"));//get the first gid
	 this->_tilesNumWidth = _tilesNumWidth;
	 this->_tilesNumHeight = _tilesNumHeight;
	 for(int i = 0; i < _tilesNumHeight; i ++)
	 {
		for(int j = 0; j < _tilesNumWidth; j ++)
		{
			if(_att!=0)
			{
				int _numTilesInTilemapRow = _tileSheetWidth/(_tilesWidth+_spacing);
				_tileSheetWidth-= ((_margin*2) + (_numTilesInTilemapRow - 1) * _spacing);
				int yPos = 0;
				int xPos = _att*_tilesWidth - _tilesWidth;
				yPos = xPos / _tileSheetWidth;
				xPos = xPos % _tileSheetWidth;
				yPos *= _tilesHeight;

				int _column = xPos /_tilesWidth;
				int _row = yPos /_tilesHeight;

				xPos += _margin + _column * _spacing;
				yPos += _margin + _row * _spacing;
				_tileSheetWidth += ((_margin*2) + (_numTilesInTilemapRow - 1) * _spacing);
				
				SDL_Rect _source =  {xPos,yPos,_tilesWidth,_tilesHeight};
				XDL_Tile* _tempTile = new XDL_Tile(_nameOfSpriteSheet,j * _tilesWidth,i * _tilesHeight,_tilesHeight,_tilesWidth,_renderer,_source,_att);
				_tempTile->_immovable = true;
				_tiles.insert(_tiles.begin(),_tempTile);
			}
			_mapTiles = _mapTiles->NextSiblingElement();
			if(_mapTiles!=NULL)
			{
				_att = atoi(_mapTiles->Attribute("gid"));
			}
		}
	 }
	 //*************************************************
}


XDL_Layer::~XDL_Layer(void)
{
}

int XDL_Layer::GetNumTilesWide()
{
	return _tilesNumWidth;
}
int XDL_Layer::GetNumTilesHigh()
{
	return _tilesNumHeight;
}


void XDL_Layer::Update()//update just calls all the tiles Updates, incase of intelligent tiles, that might animate or move.
{
	//since the tileEngine uses Sprites, you could easily hack it to spawn enemys or place items.
	for(int i = 0; i < _tiles.size(); i ++)
	{
		_tiles[i]->Update();
	}
}

void XDL_Layer::Draw(XDL_SpriteBatch* _spriteBatch)//draw our tiles.
{
	for(int i = 0; i < _tiles.size(); i ++)
	{
		_spriteBatch->Draw(_tiles[i]);
	}
}