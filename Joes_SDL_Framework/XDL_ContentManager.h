#ifndef _CONTENT_MANAGER
#define _CONTENT_MANAGER

#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include <map>
using namespace std;
#include <SDL_image.h>
class XDL_ContentManager
{
public:
	XDL_ContentManager(void);
	~XDL_ContentManager(void);
	static XDL_ContentManager* GetInstance();
	SDL_Texture* LoadBMP(char* _path,SDL_Renderer* _renderer);
	SDL_Texture* LoadSprite(char* _path,SDL_Renderer* _renderer);
private:
	static XDL_ContentManager* _me;
	std::map<char*,SDL_Texture*> _dictionary;
};


#endif
