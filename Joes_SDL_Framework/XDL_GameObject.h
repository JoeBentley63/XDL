//! XDL_GameObject.
/*!
Pure Virtual (Abstract) Class that serves as the super for all GameObjects in the world.
\sa XDL_Sprite
*/


#ifndef _XDL_GAME_OBJECT_H
#define _XDL_GAME_OBJECT_H

#include <SDL.h>
#include "XDL_Debug.h"
#include <string.h>

using namespace std;
class XDL_GameObject 
{
public:
	XDL_GameObject(string _name);/*!Don't you go trying to call this, thats a big NO!*/
	~XDL_GameObject(void);
	void virtual Init();
	void virtual Update();/*!virtual function so every object that is added to the scene will get auto-updated*/
	void virtual Draw() = 0; /*!virtual function so every object that is added to the scene will get auto-drawn*/
	int _z;/*!set priority when Draws are being called*/
	int _posX;
	int _posY;
	SDL_Rect _bounds;
	bool _immovable;
	void SetVelocity(float _x,float _y);
	void SetVelocityX(float _x);
	void SetVelocityY(float _y);
	float GetVelocityX();
	float GetVelocityY();
	void SetAcceleration(float _x,float _y);
	void SetAccelerationX(float _x);
	void SetAccelerationY(float _y);
	float GetAccelerationX();
	float GetAccelerationY();
	int GetBoundsX();
	int GetBoundsY();
	bool virtual CollidedWith(XDL_GameObject* _otherSprite);
	bool virtual Overlaps(SDL_Rect _sprite,SDL_Rect _otherSprite);
	#pragma region 
	bool virtual IsTouchingLeft();
	bool virtual IsTouchingRight();
	bool virtual IsTouchingBottom();
	bool virtual IsTouchingTop();
	string GetName();
	int virtual DistanceFrom(XDL_GameObject* _otherSprite);

#pragma endregion IsTouching Functions
	float _accelerationX;
	float _accelerationY;
	float _velocityX;
	float _velocityY;
	bool _collidable;
protected:
	bool _isTouchingTop;
	bool _isTouchingLeft;
	bool _isTouchingBottom;
	bool _isTouchingRight;
	SDL_Rect _top;
	SDL_Rect _bottom;
	SDL_Rect _left;
	SDL_Rect _right;
	string _name;
	
};

#endif