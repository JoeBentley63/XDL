//! Sample Scene for starting off
/*!
use this a basis for all scenes
*/

#ifndef _TEST_SCENE_H
#define _TEST_SCENE_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class XDL_TestScene :
	public XDL_Scene
{
public:
	XDL_TestScene(SDL_Renderer* _renderer);
	virtual ~XDL_TestScene(void);

	void Update();
	void Draw();

};

#endif