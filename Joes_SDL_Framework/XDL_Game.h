#ifndef GAME_H
#define GAME_H

#include "XDL_Debug.h"
#include <SDL.h>
class XDL_Game
{
public:
	XDL_Game(void);
	~XDL_Game(void);

	bool Init();
	void Update();
	void Render();
	bool _isRunning;
	void CleanUp();
	static int SCREEN_WIDTH ;
	static int SCREEN_HEIGHT ;
	static int _r;
	static int _g;
	static int _b;
	static SDL_Rect* _windowsBounds;
    SDL_Renderer* _renderer;
private : 
	bool m_running;
	SDL_Window* _window;
	
};

#endif

