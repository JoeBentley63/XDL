//! XDL_QuadTree
/*!
Quadtree used to cull collision detection in game. can also be used to cull draw calls 
by passing in the screenbounds and drawing all objects returned
*/

#ifndef _XDL_QUAD_TREE
#define _XDL_QUAD_TREE
#include "XDL_GameObject.h"
#include "XDL_Debug.h"
#include "XDL_SpriteBatch.h"
#include <vector>
#include <SDL.h>
using namespace std;
class XDL_QuadTree
{
public:
	static int _capacity;
	XDL_QuadTree(int _capacity,SDL_Rect* _worldBounds,SDL_Renderer* _renderer);
	XDL_QuadTree(XDL_QuadTree* _parent, int _num,SDL_Renderer* _renderer);
	~XDL_QuadTree(void);
	XDL_QuadTree* _northEast;
	XDL_QuadTree* _southEast;
	XDL_QuadTree* _southWest;
	XDL_QuadTree* _northWest;
	int _level;
	bool Insert(XDL_GameObject* _gameObject);
	bool SubDivide();
	void Clear();
	void virtual Update();
	void virtual Draw();
	vector<XDL_GameObject*> ReturnObjects(SDL_Rect _bounds,vector<XDL_GameObject*> _return);
private:
	bool RectOverlaps(SDL_Rect* _sprite,SDL_Rect* _otherSprite);
	int _numInserted;
	vector<XDL_GameObject*> _gameObjects;
	SDL_Rect* _bounds;
	XDL_QuadTree* _parent;
	SDL_Renderer* _renderer;
	
};
#endif
