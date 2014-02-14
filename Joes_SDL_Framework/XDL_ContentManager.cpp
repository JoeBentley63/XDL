//simple singleton class so that all the content loading can happen in one class, and not all over the code.
#include "XDL_ContentManager.h"

XDL_ContentManager* XDL_ContentManager::_me;

XDL_ContentManager::XDL_ContentManager(void)
{
}

XDL_ContentManager* XDL_ContentManager::GetInstance()
{
	if(_me == 0)
	{
		_me = new XDL_ContentManager();
	}
	return _me;
}

XDL_ContentManager::~XDL_ContentManager(void)
{
}
/* original load function, but since SDL_image loads bmp's too, its no longer needed,
SDL_Texture* XDL_ContentManager::LoadBMP(char* _path,SDL_Renderer* _renderer) //load a bmp
{
	if(_dictionary.find(_path)!=_dictionary.end())//first we see if the bmp the player is requesting is already loaded.
	{
		//cout<<"Found in Dictionary----------------------------------------------------------------";
		return _dictionary.find(_path)->second;//if already loaded, then return it.
	}
	//cout<<"add to Dictionary----------------------------------------------------------------";
	
	//else, we load it, add it to the dictionary and return it.
	SDL_Surface* _surface =  SDL_LoadBMP(_path);
	SDL_Texture* _texture = SDL_CreateTextureFromSurface(_renderer,_surface);
	_dictionary.insert(std::make_pair(_path,_texture));
	SDL_FreeSurface(_surface);
	return _texture;
}
*/
SDL_Texture* XDL_ContentManager::LoadSprite(char* _path,SDL_Renderer* _renderer) //load an Image
{
	if(_dictionary.find(_path)!=_dictionary.end())//first we see if the image the player is requesting is already loaded.
	{
		//cout<<"Found in Dictionary----------------------------------------------------------------";
		return _dictionary.find(_path)->second;//if already loaded, then return it.
	}
	//cout<<"add to Dictionary----------------------------------------------------------------";
	
	//else, we load it, add it to the dictionary and return it.
	SDL_Surface* _surface =  IMG_Load(_path);//load it
	SDL_Texture* _texture = SDL_CreateTextureFromSurface(_renderer,_surface);
	_dictionary.insert(std::make_pair(_path,_texture));//add it to the dictionary
	SDL_FreeSurface(_surface);
	return _texture;
}