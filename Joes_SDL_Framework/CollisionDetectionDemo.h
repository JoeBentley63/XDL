#ifndef _COLLISION_DETECTION_DEMO_H
#define _COLLISION_DETECTION_DEMO_H

#include "xdl_scene.h"
#include "XDL_SceneManager.h"
class CollisionDetectionDemo :
	public XDL_Scene
{
public:
	CollisionDetectionDemo(SDL_Renderer* _renderer);
	~CollisionDetectionDemo(void);

	void Update();
	void Draw();

protected:
	XDL_SceneManager* _manager;
};

#endif