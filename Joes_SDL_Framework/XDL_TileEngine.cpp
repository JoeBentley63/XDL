/***************************************************************
Joseph Bentley P10011026 : TMX Reader Assignment
****************************************************************/
//XDL_TileEngine, that loads the xml, create the layers
#include "XDL_TileEngine.h"
#include "XDL_SpriteBatch.h"

XDL_TileEngine::XDL_TileEngine(SDL_Renderer* _renderer,int _tilesWidth,int _tilesHeight)
{
	this->_renderer = _renderer;
	this->_tilesHeight = _tilesHeight;
	this->_tilesWidth = _tilesWidth;
	//LoadFromTMXAndTSX("desert.tmx");
	//LoadFromXML("PokemanXML_Layers.tmx");
	//LoadFromArray();
}


XDL_TileEngine::~XDL_TileEngine(void)
{
	delete(_renderer);
}

bool XDL_TileEngine::LoadFromXML(char* _pathToTMX)
{
	 
	 XMLDocument doc;
     int _error = doc.LoadFile(_pathToTMX);//open xml
	 cout<<"Error num:" << _error<<endl;
	 if(_error!=0)//make sure no errors
	 {
		 return false;
		 //error happened.

		 //TODO THROW EXCEPTION!
	 }

	 //**************Get Level Info********************
	 XMLElement* _mapInfo = doc.FirstChildElement("map");
	 int _tilesNumWidth = atoi(_mapInfo->Attribute("width"));
	 int _tilesNumHeight = atoi(_mapInfo->Attribute("height"));
	 _tilesWidth = atoi(_mapInfo->Attribute("tilewidth"));
	 _tilesHeight = atoi(_mapInfo->Attribute("tileheight"));

	 char* _nameOfSpriteSheet =const_cast<char*>( doc.FirstChildElement("map")->FirstChildElement("tileset")->FirstChildElement("image")->Attribute("source"));
	 int _firstGid = atoi(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("firstgid"));
	 int _gidFixer = -_firstGid + 1;
	 
	 int _spacing = 0;
	 if(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("spacing")!=NULL)
	 {
		_spacing = atoi(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("spacing"));
	 }
	 int _margin = 0;
	 if(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("margin")!=NULL)
	 {
		_margin = atoi(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("margin"));
	 }
	 int _tileSheetWidth = atoi(doc.FirstChildElement("map")->FirstChildElement("tileset")->FirstChildElement("image")->Attribute("width"));
	  
	 int _numSpritesPerRow = _tileSheetWidth/_tilesWidth;
	 //************************************************

	 XMLElement* _mapTiles = doc.FirstChildElement("map")->FirstChildElement("layer");
	 bool _continue = true;//get the layer tag, and make layers based of it.
	 while(_continue)
	 {
		 _layers.insert(_layers.end(), new XDL_Layer(_mapTiles,_tilesNumWidth,_tilesNumHeight,_tileSheetWidth,_nameOfSpriteSheet,_tilesWidth,_tilesHeight,_renderer,_spacing,_margin,_gidFixer));
		_mapTiles = _mapTiles->NextSiblingElement();//move to next layer. if it exists
		if(_mapTiles==NULL)
		{
			_continue = false;
		}
	 }
	 return true;
}
bool XDL_TileEngine::LoadFromTMXAndTSX(char* _pathToTMX) // Desert had a tsx as its source, so we use this one instead.
{
	 
	 XMLDocument doc;
     int _error = doc.LoadFile(_pathToTMX);//open xml
	 cout<<"Error num:" << _error<<endl;
	 if(_error!=0)//make sure no errors
	 {
		 return false;
		 //error happened.

		 //TODO THROW EXCEPTION!
	 }

	 //**************Get Level Info********************
	 XMLElement* _mapInfo = doc.FirstChildElement("map");
	 int _tilesNumWidth = atoi(_mapInfo->Attribute("width"));
	 int _tilesNumHeight = atoi(_mapInfo->Attribute("height"));
	 _tilesWidth = atoi(_mapInfo->Attribute("tilewidth"));
	 _tilesHeight = atoi(_mapInfo->Attribute("tileheight"));
	 int _firstGid = atoi(doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("firstgid"));
	 int _gidFixer = -_firstGid + 1;

	 //find the tsx
	 const char* _pathToTSX = const_cast<char*>( doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("source"));

	 
	 XMLDocument TSXdoc;
	 //load the tsx
	 _error = TSXdoc.LoadFile(_pathToTSX);//open xml
	 cout<<"Error num:" << _error<<endl;
	 if(_error!=0)//make sure no errors
	 {
		 return false;
		 //error happened.
		 //TODO THROW EXCEPTION!
	 }

	 int _spacing = atoi(TSXdoc.FirstChildElement("tileset")->Attribute("spacing"));
	 int _margin = atoi(TSXdoc.FirstChildElement("tileset")->Attribute("margin"));

	 char* _nameOfSpriteSheet = const_cast<char*>( TSXdoc.FirstChildElement("tileset")->FirstChildElement("image")->Attribute("source"));

	 int _tileSheetWidth = atoi(TSXdoc.FirstChildElement("tileset")->FirstChildElement("image")->Attribute("width"));
	 int _tileSheetHeight = atoi(TSXdoc.FirstChildElement("tileset")->FirstChildElement("image")->Attribute("height"));
	
	 int _numSpritesPerRow = _tileSheetWidth/_tilesWidth;
	 //************************************************

	 XMLElement* _mapTiles = doc.FirstChildElement("map")->FirstChildElement("layer");
	 bool _continue = true;//get the layer tag, and make layers based of it.
	 while(_continue)
	 {
		 _layers.insert(_layers.end(), new XDL_Layer(_mapTiles,_tilesNumWidth,_tilesNumHeight,_tileSheetWidth,_nameOfSpriteSheet,_tilesWidth,_tilesHeight,_renderer,_spacing,_margin,_gidFixer));
		_mapTiles = _mapTiles->NextSiblingElement();//move to next layer. if it exists
		if(_mapTiles==NULL)
		{
			_continue = false;
		}
	 }
	 return true;
}
void XDL_TileEngine::LoadFromArray()//load from array used for testing the original super simple tile engine. DEPRECATED
{
	//TODO LOAD FROM CSV txt file.

	/*int _intMap [_height][_width] = 
					{{0, 1, 0, 1, 0}, 
					 {0, 1, 0, 1, 0},  
					 {0, 1, 0, 1, 0}, 
					 {0, 1, 1, 1, 0}, 
					 {0, 0, 0, 0, 0}}; 

	for(int i = 0; i < _width; i ++)
	{
		for(int j = 0; j < _height; j ++)
		{
			if(_intMap[j][i] == 0)
			{
				_tiles.insert(_tiles.begin(),new XDL_Sprite("Ground.bmp",i * _tilesWidth,j * _tilesHeight,_tilesHeight,_tilesWidth,_renderer));
			}
		}

	}*/
}

//returns the width of an individual tile in the tile-engine
int XDL_TileEngine::GetTileWidth()
{
	return _tilesWidth;
}
//returns the height of an individual tile in the tile-engine
int XDL_TileEngine::GetTileHeight()
{
	return _tilesHeight;
}

//returns a layer from the tileEngine
XDL_Layer* XDL_TileEngine::GetLayer(int layerNum)
{
	return _layers[layerNum];
}

void XDL_TileEngine::Update()//update all the layers
{
	for(int i = 0; i < _layers.size(); i ++)
	{
		_layers[i]->Update();
	}
}

void XDL_TileEngine::Draw(XDL_SpriteBatch* _spriteBatch)//draw all the layers.
{
	for(int i = 0; i < _layers.size(); i ++)
	{
		_layers[i]->Draw(_spriteBatch);
	}
}