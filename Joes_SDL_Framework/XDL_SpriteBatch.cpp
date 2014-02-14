//Simple Singleton that takes all Textures that need to be draw, and draws them all together.
//This simplifys drawing code in the actual class that needs to be draw.
#include "XDL_SpriteBatch.h"

XDL_SpriteBatch* XDL_SpriteBatch::_me;
SDL_Texture* XDL_SpriteBatch::_drawTexture;

XDL_SpriteBatch::XDL_SpriteBatch(void)
{
	_camera = XDL_Camera::GetInstance();
}

XDL_SpriteBatch* XDL_SpriteBatch::GetInstance()
{
	if( _me == NULL)
	{
		_me = new XDL_SpriteBatch();
	}
	return _me;
}

void XDL_SpriteBatch::Init(SDL_Renderer* _renderer)//an init function, that is only called when the scene starts, it sets the renderer, so i dont have to pass it in through the GetInstance
{
	this->_renderer = _renderer;
	_drawTexture = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,XDL_Game::SCREEN_WIDTH*4,XDL_Game::SCREEN_HEIGHT*4);
	//draw texture is the texture we draw everything to, which in turn is drawn to the screen
	_clearTexture = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,XDL_Game::SCREEN_WIDTH*4,XDL_Game::SCREEN_HEIGHT*4);
	//clear texture is a blank texture used to clear drawtexture. this is the most optized way to clear an SDL_texture ive found.
	
	_drawTextureBounds = new SDL_Rect();//set the bounds of our "World"
	_drawTextureBounds->x = 0;
	_drawTextureBounds->y = 0;
	_drawTextureBounds->w = XDL_Game::SCREEN_WIDTH*4;//make the world big enough
	_drawTextureBounds->h = XDL_Game::SCREEN_HEIGHT*4;

}
XDL_SpriteBatch::~XDL_SpriteBatch(void)
{

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

void XDL_SpriteBatch::Draw(XDL_Sprite* _me)// draw inserts the sprite into the list of things to be drawn
{
	_thingsToBeDrawn.insert(_thingsToBeDrawn.end(),_me);
}

int compareZ(const void* a, const void* b)   // comparison function to sort items based on Z index
{
	int arg1 = ((XDL_Sprite*)a)->_z;
    int arg2 = ((XDL_Sprite*)b)->_z;
    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;

}
void XDL_SpriteBatch::End()//End Draws all sprites that need to be drawn. TODO : Sort sprites by Z value.
{
	//std::qsort(&_thingsToBeDrawn[0],_thingsToBeDrawn.size,sizeof(XDL_Sprite),&compareZ);
	for(int i = 0; i < _thingsToBeDrawn.size(); i ++) //NB TODO: CULL TILES THAT ARE OFFSCREEN : LOOK INTO QUADTREES
	{
		_thingsToBeDrawn[i]->Draw();//call each sprites draw, so we draw em to the texture
	}
	SDL_SetRenderTarget(_renderer, NULL);//then draw the texture to the screen. this texture can then be scaled, rotated etc.

	SDL_Rect _drawRect;
	_drawRect.x = _drawTextureBounds->x + _camera->GetPosition()->x;// apply the camera transforms to the drawTexture
	_drawRect.y = _drawTextureBounds->y + _camera->GetPosition()->y;//doing it this way ensure the actual DrawTexture is not effected, just draw differently
	_drawRect.h = _drawTextureBounds->h * _camera->GetCurrentZoom();
	_drawRect.w = _drawTextureBounds->w * _camera->GetCurrentZoom();
	SDL_RenderCopy(_renderer,_drawTexture, NULL,&_drawRect);//then draw it.
	SDL_RenderPresent(_renderer);
}

