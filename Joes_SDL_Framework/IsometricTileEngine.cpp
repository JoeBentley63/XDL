//Isometric TileEngine, that loads the xml, create the layers
//made a seperate class because in the future i will be adding Isometric specific code here. Just thinking ahead.
#include "IsometricTileEngine.h"


IsometricTileEngine::IsometricTileEngine(SDL_Renderer* _renderer,int _tilesWidth,int _tilesHeight)
{
	this->_renderer = _renderer;
	this->_tilesHeight = _tilesHeight;
	this->_tilesWidth = _tilesWidth;

}


IsometricTileEngine::~IsometricTileEngine(void)
{
}

bool IsometricTileEngine::LoadFromXML(char* _pathToTMX)
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
	 int _tilesWidth = atoi(_mapInfo->Attribute("tilewidth"));
	 int _tilesHeight = atoi(_mapInfo->Attribute("tileheight"));

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
		 _layers.insert(_layers.end(), new IsoLayer(_mapTiles,_tilesNumWidth,_tilesNumHeight,_tileSheetWidth,_nameOfSpriteSheet,_tilesWidth,_tilesHeight,_renderer,_spacing,_margin,_gidFixer));
		_mapTiles = _mapTiles->NextSiblingElement();//move to next layer. if it exists
		if(_mapTiles==NULL)
		{
			_continue = false;
		}
	 }
	 return true;
}

void IsometricTileEngine::Update()//update all the layers
{
	for(int i = 0; i < _layers.size(); i ++)
	{
		_layers[i]->Update();
	}
}

void IsometricTileEngine::Draw()//draw all the layers.
{
	for(int i = 0; i < _layers.size(); i ++)
	{
		_layers[i]->Draw();
	}
}