#ifndef BATCH_DRAWER_H
#define BATCH_DRAWER_H

#include <vector>
#include "XDL_GameObject.h"
#include "XDL_Camera.h"
#include "XDL_Game.h"
#include <vector>

using namespace std;
class XDL_SpriteBatch
{
public:
	typedef enum
	{
		FRONTTOBACK,//Larger Z means drawn at the back.
		BACKTOFRONT,//Smaller Z's drawn in the back, bigger Z drawn in front
		UNSORTED//no sorting, drawn in same order as they are added
	}DRAWMODES;

	XDL_SpriteBatch(void);
	~XDL_SpriteBatch(void);
	static XDL_SpriteBatch* GetInstance();
	void Init(SDL_Renderer* _renderer);
	void Begin();
	void Draw(XDL_GameObject* _me);
	void End();
	static SDL_Texture* _drawTexture;
	void SetDrawMode(DRAWMODES _drawmode);
	int GetDrawMode();
	SDL_Rect _drawRect;
	SDL_Rect* _drawTextureBounds;
private:
	
	SDL_Texture* _clearTexture;
	SDL_Renderer* _renderer;
	vector<XDL_GameObject*> _thingsToBeDrawn;
	static XDL_SpriteBatch* _me;
	XDL_Camera* _camera;
	DRAWMODES _currentDrawMode;
};

#endif
