#ifndef BATCH_DRAWER_H
#define BATCH_DRAWER_H

#include <vector>
#include "XDL_Sprite.h"
#include "XDL_Camera.h"
#include "XDL_Game.h"

class XDL_SpriteBatch
{
public:
	XDL_SpriteBatch(void);
	~XDL_SpriteBatch(void);
	static XDL_SpriteBatch* GetInstance();
	void Init(SDL_Renderer* _renderer);
	void Begin();
	void Draw(XDL_Sprite* _me);
	void End();
	static SDL_Texture* _drawTexture;

private:
	SDL_Rect* _drawTextureBounds;
	SDL_Texture* _clearTexture;
	SDL_Renderer* _renderer;
	vector<XDL_Sprite*> _thingsToBeDrawn;
	static XDL_SpriteBatch* _me;
	XDL_Camera* _camera;
};

#endif
