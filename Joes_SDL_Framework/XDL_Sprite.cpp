
#include "XDL_Sprite.h"
#include "XDL_SpriteBatch.h"

//TODO, Make overloads for PNG
/**constructor for a bmp file, where we are going to draw the entire image*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer)
{
	Init(_asset,_x,_y,_height,_width,_renderer);
}

/**constructor for use with tilesheets.*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect)
{
	Init(_asset,_x,_y,_height,_width,_renderer);
	this->_sourceRect = _sourceRect;
	_drawRect = _sourceRect;
	_z = 0;
	_currentFrame = 0;
	
}
/**constructor for use with animation.*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect,int _numFrames)
{
	Init(_asset,_x,_y,_height,_width,_renderer);
	this->_sourceRect = _sourceRect;
	this->_numFrames = _numFrames;
	_drawRect = _sourceRect;
	_z = 0;
	_currentFrame = 0;
}

void XDL_Sprite::Init(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer)
{
	_assetName = _asset;//set all our attributes, and load our texture.
	_velocityX = 0;
	_velocityY = 0;
	_accelerationX = 0;
	_accelerationY = 0;

	this->_renderer = _renderer;
	_content = XDL_ContentManager::GetInstance();
	_isTouchingTop = false;
	_isTouchingLeft = false;
	_isTouchingBottom = false;
	_isTouchingRight = false;
	_texture = _content->LoadSprite(_asset,_renderer); //Content.Load :D,
	_bounds.w = _width;//init our rects
	_bounds.h = _height;
	_bounds.x = _x;
	_bounds.y = _y;

	_posX = _x;
	_posY = _y;

	_top.x = _bounds.x + (_bounds.w*.2);
	_top.y = _bounds.y - _bounds.h*.2;
	_top.w = _bounds.w *0.7;
	_top.h = _bounds.w *0.3;

	_bottom.x = _bounds.x + (_bounds.w*.2);
	_bottom.y = _bounds.y + _bounds.h*0.9;
	_bottom.w = _bounds.w *0.7;
	_bottom.h = _bounds.w *0.3;

	_left.x = _bounds.x - (_bounds.w*.1);
	_left.y = _bounds.y + _bounds.h*0.2;
	_left.w = _bounds.w *0.3;
	_left.h = _bounds.h *0.6;

	_right.x = _bounds.x + (_bounds.w*.9);
	_right.y = _bounds.y + _bounds.h*0.2;
	_right.w = _bounds.w *0.3;
	_right.h = _bounds.h *0.6;

	_sourceRect.x = 0;
	_sourceRect.y = 0;
	_sourceRect.w= _width;
	_sourceRect.h= _width;
	_drawRect = _sourceRect;
	_z = 0;//not impemented just yet.
	_currentFrame = 0;//used for animation, again not really working as of yet.
	_immovable = false;
}

bool XDL_Sprite::IsTouchingLeft()
{
	return _isTouchingLeft;
}
bool XDL_Sprite::IsTouchingRight()
{
	return _isTouchingRight;
}
bool XDL_Sprite::IsTouchingBottom()
{
	return _isTouchingBottom;
}
bool XDL_Sprite::IsTouchingTop()
{
	return _isTouchingTop;
}

//Get function for position, to avoid having to go _bounds.X and _bounds.Y. Position is more normal.

//returns the distance from this sprite(top left corner) to another sprite
int XDL_Sprite::DistanceFrom(XDL_Sprite* _otherSprite)
{
	return sqrt((_otherSprite->_bounds.x - _bounds.x)*(_otherSprite->_bounds.x - _bounds.x) + (_otherSprite->_bounds.y - _bounds.y)*(_otherSprite->_bounds.y - _bounds.y));
}

bool XDL_Sprite::CollidedWith(XDL_Sprite* _otherSprite)
{
	bool _colliding = false;
	if(Overlaps(_bounds,_otherSprite->_bounds))
	{
		_colliding = true;
	}
	if(_colliding)
	{
		//do more fine grained collision detection here
		if(Overlaps(_top,_otherSprite->_bounds))
		{
			_isTouchingTop = true;
			if(_immovable == false)
			{
				_posY++;
				SetVelocityY(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posY--;
				_otherSprite->SetVelocityY(0);
			}
		}
		else if(Overlaps(_bottom,_otherSprite->_bounds))
		{
			_isTouchingBottom = true;
			if(_immovable == false)
			{
				_posY--;
				SetVelocityY(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posY++;
				_otherSprite->SetVelocityY(0);
			}
		}
		if(Overlaps(_left,_otherSprite->_bounds))
		{
			_isTouchingLeft = true;
			if(_immovable == false)
			{
				_posX++;
				SetVelocityX(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posX--;
				_otherSprite->SetVelocityX(0);
			}
		}
		else if(Overlaps(_right,_otherSprite->_bounds))
		{
			_isTouchingRight = true;
			if(_immovable == false)
			{
				_posX--;
				SetVelocityX(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posX++;
				_otherSprite->SetVelocityX(0);
			}
		}
	}
	return _colliding;
}
//returns whether or not this sprite is overlapping another
bool XDL_Sprite::Overlaps(SDL_Rect _sprite,SDL_Rect _otherSprite)//collision works, but its too course grained at the moment. you are either colliding or not.
{//in the future i would like to make it much more fine grained, with bools to check "colliding left", "colliding bottom" etc.
	int ThisLeft, OtherLeft;
    int ThisRight, OtherRight;
    int ThisTop, OtherTop;
    int ThisBottom, OtherBottom;

	ThisLeft = _sprite.x;
    ThisRight = _sprite.x + _sprite.w;
    ThisTop = _sprite.y;
    ThisBottom = _sprite.y + _sprite.h;

	_isTouchingTop = false;
	_isTouchingLeft = false;
	_isTouchingBottom = false;
	_isTouchingRight = false;
    
	OtherLeft = _otherSprite.x;
	OtherRight = _otherSprite.x + _otherSprite.w;
    OtherTop= _otherSprite.y;
    OtherBottom= _otherSprite.y + _otherSprite.h;

     
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

XDL_Sprite::~XDL_Sprite(void)
{

}
//update logic to be overridden by inheriting classes.
void XDL_Sprite::Update()
{
	_top.x = _bounds.x + (_bounds.w*.2);
	_top.y = _bounds.y - _bounds.h*.2;
	_bottom.x = _bounds.x + (_bounds.w*.2);
	_bottom.y = _bounds.y + _bounds.h*0.9;
	_left.x = _bounds.x - (_bounds.w*.1);
	_left.y = _bounds.y + _bounds.h*0.2;
	_right.x = _bounds.x + (_bounds.w*.9);
	_right.y = _bounds.y + _bounds.h*0.2;

	_velocityX += _accelerationX;
	_velocityY += _accelerationY;

	_posX += _velocityX;
	_posY += _velocityY;

}
//simple animation, just changes our source rect each frame.//not technically working right
void XDL_Sprite::Animate()
{
	_currentFrame++;
	if(_currentFrame>_numFrames)
	{
		_currentFrame = 0;
	}
	_drawRect = _sourceRect;

	_drawRect.x += _sourceRect.w * _currentFrame;
}

//draws this sprite to our screen
void XDL_Sprite::Draw()
{	
	SDL_SetRenderTarget(_renderer, XDL_SpriteBatch::_drawTexture);//draw to our big texture first.
	_bounds.x = _posX;
	_bounds.y = _posY;

	SDL_RenderCopy(_renderer,_texture,&_drawRect,&_bounds);
	if(DEBUG == 1)
	{
		SDL_SetRenderDrawColor(_renderer,255,0,0,255);
		//SDL_RenderDrawRect(_renderer,&_top);
		//SDL_RenderDrawRect(_renderer,&_bottom);
		//SDL_RenderDrawRect(_renderer,&_left);
	//	SDL_RenderDrawRect(_renderer,&_right);
		//SDL_RenderDrawRect(_renderer,&_bounds);
		
	}
	//SDL_RenderPresent(_renderer);
}

#pragma region

void XDL_Sprite::SetVelocity(float _x,float _y)
{
	this->_velocityX= _x;
	this->_velocityY = _y;
}
void XDL_Sprite::SetVelocityX(float _x)
{
	this->_velocityX = _x;
}
void XDL_Sprite::SetVelocityY(float _y)
{
	this->_velocityY = _y;
}
float XDL_Sprite::GetVelocityX()
{
	return _velocityX;
}
float XDL_Sprite::GetVelocityY()
{
	return _velocityY;
}

#pragma endregion Velocity Get and Set
int XDL_Sprite::GetBoundsX()
{
	return _bounds.x;
}

int XDL_Sprite::GetBoundsY()
{
	return _bounds.y;
}
#pragma region

void XDL_Sprite::SetAcceleration(float _x,float _y)
{
	this->_accelerationX = _x;
	this->_accelerationY = _y;
}
void XDL_Sprite::SetAccelerationX(float _x)
{
	this->_accelerationX = _x;
}
void XDL_Sprite::SetAccelerationY(float _y)
{
	this->_accelerationY = _y;
}
float XDL_Sprite::GetAccelerationX()
{
	return _accelerationX;
}
float XDL_Sprite::GetAccelerationY()
{
	return _accelerationY;
}

#pragma endregion Acceleration Get and Set