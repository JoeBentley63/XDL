#include "XDL_PathFinder.h"
#include "PathFindingSprite.h"
XDL_PathFinder* XDL_PathFinder::_me;

XDL_PathFinder::XDL_PathFinder(void)
{
	_free = true;
	_thread = new thread(&XDL_PathFinder::FindPathLoop,this);
}


XDL_PathFinder::~XDL_PathFinder(void)
{
	delete(_sprite);
	delete(_me);
	delete(_finalPath);
	delete(_openList);
	delete(_closedList);
	delete(_layer);
}

XDL_PathFinder* XDL_PathFinder::GetInstance()
{
	if(_me == NULL)
	{
		_me = new XDL_PathFinder();
	}
	return _me;
}
//set the pathfinding's focus. I can technically do pathfinding based on ANY layer of ANY tilemap, even layers that wouldn't ever be seen
void XDL_PathFinder::SetPathFinderFocus(XDL_Layer* _layer,int _tileWidth,int _tileHeight,int _numTilesWide)
{
	this->_layer = _layer;
	this->_tileWidth = _tileWidth;
	this->_tileHeight = _tileHeight;
	this->_numTilesWide = _numTilesWide;
}
//see if the pathfinder is free
void XDL_PathFinder::TryGetPath(int _startX,int _startY,int _endX,int _endY,XDL_Sprite* _sprite)
{
	if(_free)//entry protocol
	{
		this->_sprite = _sprite;//set up variables, so that the running thread sees what needs to be processed
		this->_startX = _startX;
		this->_startY = _startY;
		this->_endX = _endX;
		this->_endY = _endY;
		_free = false;//let it know its got work to do.
	}
}

//thread funciton
void XDL_PathFinder::FindPathLoop()
{
	while(true)
	{
		while(_free)
		{
			//spin while there is no work to be done
		}
		
		KillParents();//reset everything
		_numNodes = 0;
		//cout<<"FindPath"<<endl;
		if(findTile(_startX,_startY) == NULL)//check if the start node is clear/walkable
		{
			((PathFindingSprite*)_sprite)->StopFollowingPath();//tell the npc to stop
			_free = true;//let everyone know that the pathfinder is free
			
		}

		if(findTile(_endX,_endY)== NULL)//check if the end is walkable/clear
		{
			((PathFindingSprite*)_sprite)->StopFollowingPath();
			_free = true;
			
		}
	
		_openList = new vector<XDL_Tile*>();//wipe all the vectors
		_closedList = new vector<XDL_Tile*>();
		_finalPath = new vector<SDL_Point*>();
		_startPoint.x = _startX;//set up variables
		_startPoint.y = _startY;

		_endPoint.x = _endX;
		_endPoint.y = _endY;
	 
		ProcessNode(findTile(_startPoint.x,_startPoint.y));//start recursion loop
		//cout<<"Found Path : " << _finalPath->size() << endl;
		((PathFindingSprite*)_sprite)->FollowPath(_finalPath);//when the recursion ends, we tell the sprite to follow our new path
		_free = true;//let everyone know that the pathfinder is free
	}
}

void XDL_PathFinder::ProcessNode(XDL_Tile* _tile)
{
	_numNodes ++;
	//cout<<"ProcessNode"<<endl;
	_closedList->insert(_closedList->begin(),_tile);//add to the closed list
	if(Contains(*_openList,_tile))//check if its in the openList(it should be, but just in case)
	{
		vector<XDL_Tile*>::iterator position = std::find(_openList->begin(), _openList->end(),_tile);
		if (position != _openList->end()) // == vector.end() means the element was not found
			 _openList->erase(position);//remove it
	}
	int _x = _tile->GetBoundsX() - _tileWidth;//get its X and Y
	int _y = _tile->GetBoundsY();

	XDL_Tile* _tempTile = findTile(_x,_y);//find tile based on its world coords.

	//Grab the neighbours----------------------------
	if(_tempTile!=NULL && !Contains(*_closedList,_tempTile) && !Contains(*_openList,_tempTile) && GetWeight(_tempTile->_gid) != _NOT_WALKABLE)
	{
		_tempTile->SetParent(_tile);//set parent
		_openList->insert(_openList->begin(),_tempTile);
	}

	_x = _tile->GetBoundsX() + _tileWidth;
	_y = _tile->GetBoundsY();

	_tempTile = findTile(_x,_y);
	if(_tempTile!=NULL && !Contains(*_closedList,_tempTile) && !Contains(*_openList,_tempTile)&& GetWeight(_tempTile->_gid) != _NOT_WALKABLE)
	{
		_tempTile->SetParent(_tile);
		_openList->insert(_openList->begin(),_tempTile);
	}
	
	_x = _tile->GetBoundsX();
	_y = _tile->GetBoundsY() + _tileHeight;

	_tempTile = findTile(_x,_y);
	if(_tempTile!=NULL && !Contains(*_closedList,_tempTile) && !Contains(*_openList,_tempTile)&& GetWeight(_tempTile->_gid) != _NOT_WALKABLE)
	{
		_tempTile->SetParent(_tile);
		_openList->insert(_openList->begin(),_tempTile);
	}

	_x = _tile->GetBoundsX();
	_y = _tile->GetBoundsY() - _tileHeight;

	_tempTile = findTile(_x,_y);
	if(_tempTile!=NULL && !Contains(*_closedList,_tempTile) && !Contains(*_openList,_tempTile) && GetWeight(_tempTile->_gid) != _NOT_WALKABLE)
	{
		_tempTile->SetParent(_tile);
		_openList->insert(_openList->begin(),_tempTile);
	}

	XDL_Tile* _next = calcNextBestTile(); //get the next XDL_Tile we should explore
	if(_next==NULL || _numNodes >= _layer->_tiles.size())
	{
		NoPathFound();//if no next, or we have explored all the nodes, return NoPath
	}
	else
	{
		int i = DistanceFrom(_next->_posX,_next->_posY,_endPoint.x,_endPoint.y) ;
		if(i < _tileWidth)
		{
			ReversePath(_next);//if we are at the destination, reverse the path
		}
		else
		{
			ProcessNode(_next);//otherwise continue
		}
	}
}
void XDL_PathFinder::NoPathFound()
{
	//cout<<"No Path Found"<<endl;
	_finalPath = NULL;
}
XDL_Tile* XDL_PathFinder::calcNextBestTile()
{
	//cout<<"Calc Next Best XDL_Tile"<<endl;
	int _shortestDist = 99999999;
	XDL_Tile* _tile = NULL;

	for(int i = 0; i < _openList->size(); i ++)
	{
		if((DistanceFrom(_endPoint.x,_endPoint.y,_openList->at(i)->_posX,_openList->at(i)->_posY)* GetWeight(_openList->at(i)->_gid)) < _shortestDist)
		{
			_shortestDist = DistanceFrom(_endPoint.x,_endPoint.y,_openList->at(i)->GetBoundsX(),_openList->at(i)->GetBoundsY()) * GetWeight(_openList->at(i)->_gid);
			_tile = _openList->at(i);
			_closedList->insert(_closedList->begin(),_tile);
		}
	}
	return _tile;
}

void XDL_PathFinder::ReversePath(XDL_Tile* _tile)
{
	
	//cout<<"Reverse Final Path"<<endl;
	stack<XDL_Tile*> _stack;
	_stack.push(_tile);
	while(_tile->GetParent()!=NULL)//pop everything onto a stack
	{
		//cout<<"While : 1"<<endl;
	
		_stack.push(_tile->GetParent());
		_tile = _tile->GetParent();
	}

	while(_stack.empty() == false)//pop em off onto a vector
	{
		//cout<<"While : 2"<<endl;
	
		XDL_Tile* _tile = _stack.top();
		_stack.pop();
		SDL_Point* _pos = new SDL_Point();
		_pos->x = _tile->GetBoundsX();
		_pos->y = _tile->GetBoundsY();
		_finalPath->insert(_finalPath->end(),_pos);
	}
	
	_openList->erase(_openList->begin());
	
	//DEBUG_MSG("fin");
}
bool XDL_PathFinder::Contains(vector<XDL_Tile*> _vector,XDL_Tile* _tileToSearchFor)//check does a vector contain a tile
{
	//cout<<"Contains?"<<endl;
	if(std::find(_vector.begin(), _vector.end(), _tileToSearchFor) != _vector.end()) 
	{
		return true;
	} 
	else 
	{
		return false;
	}
}
XDL_Tile* XDL_PathFinder::findTile(int _x,int _y)//find and return the tile, given its worldSpace coords
{
	//cout<<"FindTile"<<endl;
	_x = _x/_tileWidth;
	_y = _y/_tileHeight;

	int _actualIndex = (_layer->_tiles.size()-1) - (_x + (_y * _numTilesWide));
	try
	{
		return _layer->_tiles.at(_actualIndex);
	}
	catch(const out_of_range& oor)
	{
		return NULL;
	}
}
int XDL_PathFinder::DistanceFrom(int _startX,int _startY,int _endX,int _endY)//get the distance from 1 point to another
{
	//cout<<"Distance From"<<endl;
	return sqrt((_endX - _startX)*(_endX - _startX) + (_endY - _startY)*(_endY - _startY));
}
void XDL_PathFinder::KillParents()//Batman Function
{
	for(int i = 0; i < _layer->_tiles.size(); i ++)
	{
		_layer->_tiles.at(i)->SetParent(NULL);
	}
}

void XDL_PathFinder::SetWeight(int _gid,float _weight)//set the weight of a given gid
{
	_weights.insert(std::make_pair(_gid,_weight));//add it to the dictionary
}

float XDL_PathFinder::GetWeight(int _gid)
{
	if(_weights.find(_gid)!=_weights.end())
	{
	//	cout<<"Found in Dictionary----------------------------------------------------------------";
		return _weights.find(_gid)->second;
	}
	else
	{
		return _NOT_WALKABLE;
	}
}