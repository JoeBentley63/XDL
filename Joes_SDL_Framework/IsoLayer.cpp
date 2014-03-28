//special layer class for Isometric tile engine. A layer could be described as a stupider tile engine, or a mini-tile engine, as it doesnt have all the logic a normal on has.
//not that I'm going to question the intelligence of a layer...

//made a sperate class to account for any custom code you would need for isometrix
#include "IsoLayer.h"


IsoLayer::IsoLayer(XMLElement* _layer,int _tilesNumWidth,int _tilesNumHeight,int _tileSheetWidth,char* _nameOfSpriteSheet,int _tilesWidth,int _tilesHeight,SDL_Renderer* _renderer,int _spacing, int _margin,int _gidFixer)
{
	//pass in all the relivant information, including the XMLElement that points to its layer tag in the TMX

	 XMLElement* _mapTiles = _layer->FirstChildElement("data")->FirstChild()->ToElement();//get down to gid level
	 int _att = atoi(_mapTiles->Attribute("gid"));//get the first gid
	
	 for(int i = 0; i < _tilesNumHeight; i ++)
	 {
		for(int j = 0; j < _tilesNumWidth; j ++)
		{
			if(_att!=0)
			{
				int _numTilesInTilemapRow = _tileSheetWidth/(_tilesWidth+_spacing);//calc the number of tiles per row of the tilesheet (for spacing)
				_tileSheetWidth-= ((_margin*2) + (_numTilesInTilemapRow - 1) * _spacing);//calculate the true width of the tilesheet without margins and spacing
				int yPos = 0;
				int xPos = _att*_tilesWidth - _tilesWidth;
				yPos = xPos / _tileSheetWidth;//calculate the X and Y 
				xPos = xPos % _tileSheetWidth;
				yPos *= _tilesHeight;

				int _column = xPos /_tilesWidth;
				int _row = yPos /_tilesHeight;

				xPos += _margin + _column * _spacing;//account for spacing
				yPos += _margin + _row * _spacing;

				int cartX = j * _tilesWidth;//this is the x and y in Cartesion 2d
				int cartY = i * _tilesWidth;


				int isoX = (cartX - cartY) + ((_tilesNumWidth*_tilesWidth));//convert to isometric
				int isoY = ((cartX + cartY) / 2);
				isoX*=0.5;//controls how close the tiles are to each other
				isoY*=0.5;


				_tileSheetWidth += ((_margin*2) + (_numTilesInTilemapRow - 1) * _spacing);//return the width to the actual width (width + margins+ spacing)
				
				SDL_Rect _source =  {xPos,yPos,_tilesWidth,_tilesHeight};//create a new tile, then repeat
				_tiles.insert(_tiles.begin(),new XDL_Sprite(_nameOfSpriteSheet,isoX,isoY,_tilesHeight,_tilesWidth,1,_renderer,_source));
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


IsoLayer::~IsoLayer(void)
{
}
void IsoLayer::Update()//update just calls all the tiles Updates, incase of intelligent tiles, that might animate or move.
{
	//since the tileEngine uses Sprites, you could easily hack it to spawn enemys or place items.
	for(int i = 0; i < _tiles.size(); i ++)
	{
		_tiles[i]->Update();
	}
}

void IsoLayer::Draw()//draw our tiles.
{
	for(int i = 0; i < _tiles.size(); i ++)
	{
		_tiles[i]->Draw();
	}
}