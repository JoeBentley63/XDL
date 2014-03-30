//!XDL_Game
/*!
Sets up SDL and our game loop.
*/


#ifndef GAME_H
#define GAME_H

#include "XDL_Debug.h"
#include <SDL.h>
class XDL_Game
{
public:
	XDL_Game(void);
	~XDL_Game(void);

	bool Init();/*!<Sets up our window, initializes SDL and our SceneManager to navigate scenes*/ 
	void Update();/*!<Called every frame (60 times a second). Basically calls SceneManagers Update, which in turn updates the current Scene*/ 
	void Render();/*!<Called every frame (60 times a second). Calls SceneManagers Draw, which in turn leverages XDL_SpriteBatch to draw our Scene*/
	void CleanUp();/*!<Cleans up SDL when game exits*/
	
	static int SCREEN_WIDTH ;/*!<The width of the screen*/
	static int SCREEN_HEIGHT;/*!<The height of the screen*/
	static int _r;/*!<background color : Red (0 -255)*/
	static int _g;/*!<background color : Green (0 -255)*/
	static int _b;/*!<background color : Blue (0 -255)*/
	static SDL_Rect* _windowsBounds;/*!<SDL_Rect to represent the screenbounds*/
    SDL_Renderer* _renderer;/*!<Our Drawing surface*/
	static bool _drawQuadTreeDebug;
private : 
	bool m_running;
	SDL_Window* _window;
	
};

#endif

