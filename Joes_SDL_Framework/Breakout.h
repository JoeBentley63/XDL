//! Breakout Demo Scene
/*!
A Demo Scene to show how easy it is to make the classic game breakout in XDL
*/

#ifndef _BREAK_OUT_H
#define _BREAK_OUT_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class Breakout :
	public XDL_Scene
{
public:
	Breakout(SDL_Renderer* _renderer);
	virtual ~Breakout(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif