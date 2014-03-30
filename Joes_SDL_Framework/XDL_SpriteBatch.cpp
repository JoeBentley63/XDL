//Simple Singleton that takes all Textures that need to be draw, and draws them all together.
//This simplifys drawing code in the actual class that needs to be draw.
#include "XDL_SpriteBatch.h"

XDL_SpriteBatch* XDL_SpriteBatch::_me;
SDL_Texture* XDL_SpriteBatch::_drawTexture;

XDL_SpriteBatch::XDL_SpriteBatch(void)
{
	XDL_CAMERA = XDL_Camera::GetInstance();
}

XDL_SpriteBatch* XDL_SpriteBatch::GetInstance()
{
	if( _me == NULL)
	{
		_me = new XDL_SpriteBatch();
	}
	return _me;
}

void XDL_SpriteBatch::Init(SDL_Renderer* _renderer, int _worldWide,int _worldHeight)//an init function, that is only called when the scene starts, it sets the renderer, so i dont have to pass it in through the GetInstance
{
	this->_renderer = _renderer;
	_drawTexture = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,_worldWide,_worldHeight);
	//draw texture is the texture we draw everything to, which in turn is drawn to the screen
	_clearTexture = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,XDL_Game::SCREEN_WIDTH*4,XDL_Game::SCREEN_HEIGHT*4);
	//clear texture is a blank texture used to clear drawtexture. this is the most optized way to clear an SDL_texture ive found.
	
	_drawTextureBounds = new SDL_Rect();//set the bounds of our "World"
	_drawTextureBounds->x = 0;
	_drawTextureBounds->y = 0;
	_drawTextureBounds->w = _worldWide;//make the world big enough
	_drawTextureBounds->h =	_worldHeight;

	_currentDrawMode = BACKTOFRONT;
}
XDL_SpriteBatch::~XDL_SpriteBatch(void)
{
	delete(_drawTextureBounds);
	delete(_clearTexture);
	delete(_renderer);
	delete(_me);
	delete(XDL_CAMERA);
}
void XDL_SpriteBatch::Begin()//begin clears the screen and creates a new texture for us to draw to.
{
	SDL_SetRenderDrawColor(_renderer,XDL_Game::_r,XDL_Game::_g,XDL_Game::_b,255);
	SDL_SetRenderTarget(_renderer, XDL_SpriteBatch::_drawTexture);//target the drawTexture so we can clear it.
	SDL_RenderCopy(_renderer,_clearTexture,NULL,NULL);//clear it
	SDL_SetRenderTarget(_renderer, NULL);//then change focus back to the screen

	SDL_RenderClear(_renderer);//and clear it
	_thingsToBeDrawn.clear();//remove all items that need to be drawn so we start with a blank slate
}

void XDL_SpriteBatch::Draw(XDL_GameObject* _me)// draw inserts the sprite into the list of things to be drawn
{
	_thingsToBeDrawn.insert(_thingsToBeDrawn.end(),_me);
}


bool compById(XDL_GameObject* a, XDL_GameObject* b)
{
    return (a->_z < b->_z);
}
void XDL_SpriteBatch::End()//End Draws all sprites that need to be drawn. TODO : Sort sprites by Z value.
{
	if(_thingsToBeDrawn.size() >0)
	{
		if(_currentDrawMode == BACKTOFRONT)
		{
			std::sort(_thingsToBeDrawn.begin(), _thingsToBeDrawn.end(), compById);
			for(int i = 0; i < _thingsToBeDrawn.size(); i ++)
			{
				_thingsToBeDrawn[i]->Draw();//call each sprites draw, so we draw em to the texture
			}
		}
		else if(_currentDrawMode == FRONTTOBACK)
		{
			std::sort(_thingsToBeDrawn.begin(), _thingsToBeDrawn.end(), compById);
			for(int i = _thingsToBeDrawn.size()-1; i>=0; i --) 
			{
				_thingsToBeDrawn[i]->Draw();//call each sprites draw, so we draw em to the texture
			}
		}
		else if(_currentDrawMode == UNSORTED)
		{
			//dont sort, just draw.
			for(int i = 0; i < _thingsToBeDrawn.size(); i ++) 
			{
				_thingsToBeDrawn[i]->Draw();//call each sprites draw, so we draw em to the texture
			}
		}
		SDL_SetRenderTarget(_renderer, NULL);//then draw the texture to the screen. this texture can then be scaled, rotated etc
		_drawRect.x = _drawTextureBounds->x + XDL_CAMERA->GetPosition()->x;// apply the camera transforms to the drawTexture
		_drawRect.y = _drawTextureBounds->y + XDL_CAMERA->GetPosition()->y;//doing it this way ensure the actual DrawTexture is not effected, just draw differently
		_drawRect.h = _drawTextureBounds->h * XDL_CAMERA->GetCurrentZoom();
		_drawRect.w = _drawTextureBounds->w * XDL_CAMERA->GetCurrentZoom();
		SDL_RenderCopy(_renderer,_drawTexture, NULL,&_drawRect);//then draw it.
		SDL_RenderPresent(_renderer);
	}
}

void XDL_SpriteBatch::SetDrawMode(DRAWMODES _drawmode)
{
	this->_currentDrawMode = _drawmode;
}

int XDL_SpriteBatch::GetDrawMode()
{
	return _currentDrawMode;
}

void XDL_SpriteBatch::SetCamera(XDL_Camera* XDL_CAMERA)
{
	this->XDL_CAMERA = XDL_CAMERA;
}

XDL_Camera* XDL_SpriteBatch::GetCamera()
{
	return XDL_CAMERA;
}