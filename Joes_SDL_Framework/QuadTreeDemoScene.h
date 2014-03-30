//! Quad Tree Demo Scene
/*!
Simple Scene to demo how quad-tree is rebuilt.
*/

#ifndef _QUAD_TREE_DEMO_H
#define _QUAD_TREE_DEMO_H

#include "XDL_Scene.h"
class QuadTreeDemoScene :
	public XDL_Scene
{
public:
	QuadTreeDemoScene(SDL_Renderer* _renderer);
	virtual ~QuadTreeDemoScene(void);
	void Draw();
	void Update();
	float _zoom;
};

#endif