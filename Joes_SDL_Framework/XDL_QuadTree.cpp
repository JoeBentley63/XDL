#include "XDL_QuadTree.h"

int XDL_QuadTree::_capacity;

XDL_QuadTree::XDL_QuadTree(int _capacity,SDL_Rect* _worldBounds,SDL_Renderer* _renderer)
{
	this->_gameObjects.clear();
	this->_capacity = _capacity;
	this->_parent = _parent;
	this->_renderer = _renderer;
	_bounds = _worldBounds;
	_level = 0;

	_northWest = NULL;
	_southWest = NULL;
	_southEast = NULL;
	_northEast = NULL;

	_numInserted = 0;
}

XDL_QuadTree::XDL_QuadTree(XDL_QuadTree* _parent, int _num,SDL_Renderer* _renderer)
{
	this->_gameObjects.clear();
	this->_parent = _parent;
	this->_renderer = _renderer;
	_level = _parent->_level+1;
	_bounds = new SDL_Rect();
	switch (_num)
	{
		 case 0: 
			 _bounds->x = _parent->_bounds->x;
			 _bounds->y = _parent->_bounds->y;
			 _bounds->w = _parent->_bounds->w/2;
			 _bounds->h = _parent->_bounds->h/2;
			 break;
		 case 1:
			 _bounds->x = _parent->_bounds->x + _parent->_bounds->w/2;
			 _bounds->y = _parent->_bounds->y;
			 _bounds->w = _parent->_bounds->w/2;
			 _bounds->h = _parent->_bounds->h/2;
			 break;
		case 2:
			_bounds->x = _parent->_bounds->x + _parent->_bounds->w/2;
			_bounds->y = _parent->_bounds->y + _parent->_bounds->h/2;
			_bounds->w = _parent->_bounds->w/2;
			_bounds->h = _parent->_bounds->h/2;
		break;
		case 3:
			_bounds->x = _parent->_bounds->x;
			_bounds->y = _parent->_bounds->y + _parent->_bounds->h/2;
			_bounds->w = _parent->_bounds->w/2;
			_bounds->h = _parent->_bounds->h/2;
			break;
		default : 
			_bounds->x = _parent->_bounds->x;
			_bounds->y = _parent->_bounds->y;
			_bounds->w = _parent->_bounds->w/2;
			_bounds->h = _parent->_bounds->h/2;
			break;
	}

	_northWest = NULL;
	_southWest = NULL;
	_southEast = NULL;
	_northEast = NULL;

	_numInserted = 0;
}

XDL_QuadTree::~XDL_QuadTree(void)
{
	Clear();
	delete(_northWest);
	delete(_southWest);
	delete(_southEast);
	delete(_northEast);
}
void XDL_QuadTree::Update()
{
}
void XDL_QuadTree::Draw()
{
	if(DEBUG == 1)
	{
		SDL_SetRenderTarget(_renderer, XDL_SpriteBatch::_drawTexture);
		SDL_SetRenderDrawColor(_renderer,0,255,0,100);
		
		if(_gameObjects.size() > 0)
		{
			SDL_SetRenderDrawColor(_renderer,255,0,0,100);
			SDL_RenderFillRect(_renderer,_bounds);
		}
		
		SDL_RenderDrawRect(_renderer,_bounds);
		if(_northEast!=NULL)
		{
			_northWest->Draw();
			_southWest->Draw();
			_southEast->Draw();
			_northEast->Draw();
		}
	}
	
}

bool XDL_QuadTree::RectOverlaps(SDL_Rect* _sprite,SDL_Rect* _otherSprite)
{
	int ThisLeft, OtherLeft;
    int ThisRight, OtherRight;
    int ThisTop, OtherTop;
    int ThisBottom, OtherBottom;

	ThisLeft = _sprite->x;
    ThisRight = _sprite->x + _sprite->w;
    ThisTop = _sprite->y;
    ThisBottom = _sprite->y + _sprite->h;

	OtherLeft = _otherSprite->x;
	OtherRight = _otherSprite->x + _otherSprite->w;
    OtherTop= _otherSprite->y;
    OtherBottom= _otherSprite->y + _otherSprite->h;

     
	if( ThisBottom <= OtherTop )//if my bottom is above your top, then we cant possibly be colliding
    {
        return false;
    }

	if( ThisTop >= OtherBottom ) // or if my top is below your bottom then we cant ever collide
    {
        return false;
    }

	if( ThisRight <= OtherLeft ) // if my right wall is left of your left wall, then we cant collide
    {
        return false;
    }

	if(ThisLeft>= OtherRight )//same logic with right
    {
        return false;
    }
	//if all these conditions arn't met, then we must be colliding.

    return true;
}
bool XDL_QuadTree::Insert(XDL_GameObject* _gameObject)
{
	//DEBUG_MSG("\nTrying to insert at level : " << _level);
	if(!RectOverlaps(_bounds,&_gameObject->_bounds))
	{
		//DEBUG_MSG("\nDoesnt belong here ");
		return false;//doesnt belong here, return false;
	}
	if(_numInserted < _capacity  || _level >= 6)//if there is space
	{
		_gameObjects.insert(_gameObjects.begin(),_gameObject);//insert it here
		//DEBUG_MSG("\nInserted at level : " << _level);
		_numInserted++;
		return true;
	}
	else
	{
		SubDivide();
		
		//DEBUG_MSG("\nTry NW");
		_northWest->Insert(_gameObject);
	
		_southWest->Insert(_gameObject);
		
		_southEast->Insert(_gameObject);
		
		_northEast->Insert(_gameObject);
		
		
		
		return true;
	}
}
void XDL_QuadTree::Clear()
{
	
	if(_northEast!=NULL)
	{
		_northWest->Clear();
		_southWest->Clear();
		_southEast->Clear();
		_northEast->Clear();
	}
	_northWest = NULL;
	_southWest = NULL;
	_southEast = NULL;
	_northEast = NULL;

	_numInserted = 0;
}
bool XDL_QuadTree::SubDivide()
{
	if(_northEast == NULL)
	{
		//DEBUG_MSG("\nSubdividing level : " << _level);
		_northWest = new XDL_QuadTree(this,0,_renderer);
		_northWest ->_level = _level + 1;
		_southWest = new XDL_QuadTree(this,1,_renderer);
		_southWest ->_level = _level + 1;
		_southEast = new XDL_QuadTree(this,2,_renderer);
		_southEast ->_level = _level + 1;
		_northEast = new XDL_QuadTree(this,3,_renderer);
		_northEast ->_level = _level + 1;

		for(int i = 0; i < _gameObjects.size(); i ++)
		{
			_northWest->Insert(_gameObjects[i]);
			_southWest->Insert(_gameObjects[0]);
			_southEast->Insert(_gameObjects[0]);
			_northEast->Insert(_gameObjects[0]);
			
			_gameObjects.clear();
			
		}

	}
	return true;
}

vector<XDL_GameObject*> XDL_QuadTree::ReturnObjects(SDL_Rect _bounds,vector<XDL_GameObject*> _return)
{
	if(RectOverlaps(this->_bounds,&_bounds))
	{
		for(int i = 0; i < _gameObjects.size(); i ++)
		{
			_return.insert(_return.begin(),_gameObjects[i]);
		}
		if(_northEast != NULL)
		{
			_return = _northWest->ReturnObjects(_bounds,_return);
			_return = _southWest->ReturnObjects(_bounds,_return);
			_return = _southEast->ReturnObjects(_bounds,_return);
			_return = _northEast->ReturnObjects(_bounds,_return);
		}
		
	}
	return _return;

}