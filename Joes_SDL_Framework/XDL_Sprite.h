#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL.h>
#include "XDL_Debug.h"
#include "XDL_ContentManager.h"
#include "XDL_GameObject.h"
class XDL_Sprite : public XDL_GameObject
{
public:

#pragma region
	XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer);
	XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect);
	XDL_Sprite(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer,SDL_Rect _sourceRect,int _numFrames);
	
#pragma endregion Constructors

	~XDL_Sprite(void);
	void virtual Update();
	void virtual Draw();
	void virtual Animate();
	int DistanceFrom(XDL_Sprite* _otherSprite);
	int _posX;
	int _posY;
	bool _immovable;
#pragma region
	void SetVelocity(float _x,float _y);
	void SetVelocityX(float _x);
	void SetVelocityY(float _y);
	float GetVelocityX();
	float GetVelocityY();
#pragma endregion Velocity Get and Sets

#pragma region
	void SetAcceleration(float _x,float _y);
	void SetAccelerationX(float _x);
	void SetAccelerationY(float _y);
	float GetAccelerationX();
	float GetAccelerationY();

#pragma endregion Acceleration Get and Sets
	int GetBoundsX();
	int GetBoundsY();
#pragma region 
	bool IsTouchingLeft();
	bool IsTouchingRight();
	bool IsTouchingBottom();
	bool IsTouchingTop();

#pragma endregion IsTouching Functions
	bool CollidedWith(XDL_Sprite* _otherSprite);
protected:
	void Init(char* _asset,float _x,float _y,int _height, int _width,SDL_Renderer* _renderer);
	bool Overlaps(SDL_Rect _sprite,SDL_Rect _otherSprite);
#pragma region
	bool _isTouchingTop;
	bool _isTouchingLeft;
	bool _isTouchingBottom;
	bool _isTouchingRight;
	SDL_Rect _top;
	SDL_Rect _bottom;
	SDL_Rect _left;
	SDL_Rect _right;
#pragma endregion CollisionMembers 
	SDL_Renderer* _renderer;
	float _accelerationX;
	float _accelerationY;
	float _velocityX;
	float _velocityY;
	int _numFrames;
	int _currentFrame;
	SDL_Rect _sourceRect;
	SDL_Rect _drawRect;
	SDL_Rect _bounds;
	SDL_Texture* _texture;
	
	const char* _assetName;
	XDL_ContentManager* _content;
	
};

#endif