
#include "XDL_Sprite.h"
#include "XDL_SpriteBatch.h"

//TODO, Make overloads for PNG
/**constructor for a bmp file, where we are going to draw the entire image*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer)
{
	this->_z = _z;
	Init(_asset,_x,_y,_height,_width,_renderer);
}

/**constructor for use with tilesheets.*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer,SDL_Rect _sourceRect)
{
	Init(_asset,_x,_y,_height,_width,_renderer);
	this->_sourceRect = _sourceRect;
	_drawRect = _sourceRect;
	this->_z = _z;
	_currentFrame = 0;
	
}
/**constructor for use with animation.*/
XDL_Sprite::XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,int _z,SDL_Renderer* _renderer,SDL_Rect _sourceRect,int _numFrames)
{
	Init(_asset,_x,_y,_height,_width,_renderer);
	this->_sourceRect = _sourceRect;
	this->_numFrames = _numFrames;
	_drawRect = _sourceRect;
	this->_z = _z;
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
	_currentFrame = 0;
	_immovable = false;
}




XDL_Sprite::~XDL_Sprite(void)
{
	delete(_renderer);
	delete(_texture);
	delete(_assetName);
	delete(_content);
}
//update logic to be overridden by inheriting classes.
void XDL_Sprite::Update()
{
	
	XDL_GameObject::Update();
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
		SDL_SetRenderDrawColor(_renderer,255,0,0,100);
		SDL_RenderDrawRect(_renderer,&_top);
		SDL_RenderDrawRect(_renderer,&_bottom);
		SDL_RenderDrawRect(_renderer,&_left);
		SDL_RenderDrawRect(_renderer,&_right);
		SDL_RenderDrawRect(_renderer,&_bounds);
		
	}
	
}

