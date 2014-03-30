#include "XDL_GameObject.h"


XDL_GameObject::XDL_GameObject(string _name)
{
	this->_name = _name;
	_collidable = false;
}
string XDL_GameObject::GetName()
{
	return _name;
}
void XDL_GameObject::Init()// setup bounds and the other collision boxes used to check if collision happened left,right,up or down etc
{
	_top.x = _bounds.x + 5;
	_top.y = _bounds.y - 5;
	_top.w = _bounds.w -10;
	_top.h = 5;

	_bottom.x = _bounds.x + 5;
	_bottom.y = _bounds.y + _bounds.h;
	_bottom.w = _bounds.w -10;
	_bottom.h = 5;

	_left.x = _bounds.x - 5;
	_left.y = _bounds.y + 5;
	_left.w = 5;
	_left.h = _bounds.h -5;

	_right.x = _bounds.x + _bounds.w;
	_right.y = _bounds.y + 5;
	_right.w = 5;
	_right.h = _bounds.h -5;
}
void XDL_GameObject::Update()//keep our collision boxes up to date
{
	_top.x = _bounds.x + 5;
	_top.y = _bounds.y - 5;

	_bottom.x = _bounds.x + 5;
	_bottom.y = _bounds.y + _bounds.h;

	_left.x = _bounds.x - 5;
	_left.y = _bounds.y + 5;

	_right.x = _bounds.x + _bounds.w;
	_right.y = _bounds.y + 5;

	_velocityX += _accelerationX;//apply acceleration
	_velocityY += _accelerationY;

	_posX += _velocityX;//apply velocity
	_posY += _velocityY;
}


XDL_GameObject::~XDL_GameObject(void)
{
}

bool XDL_GameObject::CollidedWith(XDL_GameObject* _otherSprite)// check if 2 Objects have collided
{
	bool _colliding = false;
	if(Overlaps(_bounds,_otherSprite->_bounds))
	{
		_colliding = true;
	}
	if(_colliding)
	{
		//do more fine grained collision detection here
		if(Overlaps(_top,_otherSprite->_bounds))
		{
			_isTouchingTop = true;
			
		}
		else
		{
			_isTouchingTop = false;
		}
		if(Overlaps(_bottom,_otherSprite->_bounds))
		{
			_isTouchingBottom = true;
			
		}
		else
		{
			_isTouchingBottom = true;
		}
		if(Overlaps(_left,_otherSprite->_bounds))
		{
			_isTouchingLeft = true;
			
		}
		else
		{
			_isTouchingLeft = false;
		}
		if(Overlaps(_right,_otherSprite->_bounds))
		{
			_isTouchingRight = true;
			
		}
		else
		{
			_isTouchingRight = true;
		}
	}
	return _colliding;
}
//returns whether or not this sprite is overlapping another
bool XDL_GameObject::Overlaps(SDL_Rect _sprite,SDL_Rect _otherSprite)
{
	int ThisLeft, OtherLeft;
    int ThisRight, OtherRight;
    int ThisTop, OtherTop;
    int ThisBottom, OtherBottom;

	ThisLeft = _sprite.x;
    ThisRight = _sprite.x + _sprite.w;
    ThisTop = _sprite.y;
    ThisBottom = _sprite.y + _sprite.h;
    
	OtherLeft = _otherSprite.x;
	OtherRight = _otherSprite.x + _otherSprite.w;
    OtherTop= _otherSprite.y;
    OtherBottom= _otherSprite.y + _otherSprite.h;

     
	if( ThisBottom <= OtherTop )//if my bottom is above your top, then we cant possibly be colliding
    {
        return false;
    }

	if( ThisTop >= OtherBottom ) // or if my top is below your bottom then we cant ever collide
    {
        return false;
    }

	if( ThisRight <= OtherLeft ) // if my right wall is left of your left wall, then we cant collide
    {
        return false;
    }

	if(ThisLeft>= OtherRight )//same logic with right
    {
        return false;
    }
	//if all these conditions arn't met, then we must be colliding.

    return true;
}

bool XDL_GameObject::IsTouchingLeft()
{
	return _isTouchingLeft;
}
bool XDL_GameObject::IsTouchingRight()
{
	return _isTouchingRight;
}
bool XDL_GameObject::IsTouchingBottom()
{
	return _isTouchingBottom;
}
bool XDL_GameObject::IsTouchingTop()
{
	return _isTouchingTop;
}

//returns the distance from this sprite(top left corner) to another sprite
int XDL_GameObject::DistanceFrom(XDL_GameObject* _otherSprite)
{
	return sqrt((_otherSprite->_bounds.x - _bounds.x)*(_otherSprite->_bounds.x - _bounds.x) + (_otherSprite->_bounds.y - _bounds.y)*(_otherSprite->_bounds.y - _bounds.y));
}

#pragma region

void XDL_GameObject::SetVelocity(float _x,float _y)
{
	this->_velocityX= _x;
	this->_velocityY = _y;
}
void XDL_GameObject::SetVelocityX(float _x)
{
	this->_velocityX = _x;
}
void XDL_GameObject::SetVelocityY(float _y)
{
	this->_velocityY = _y;
}
float XDL_GameObject::GetVelocityX()
{
	return _velocityX;
}
float XDL_GameObject::GetVelocityY()
{
	return _velocityY;
}

#pragma endregion Velocity Get and Set

int XDL_GameObject::GetBoundsX()
{
	return _bounds.x;
}

int XDL_GameObject::GetBoundsY()
{
	return _bounds.y;
}
#pragma region

void XDL_GameObject::SetAcceleration(float _x,float _y)
{
	this->_accelerationX = _x;
	this->_accelerationY = _y;
}
void XDL_GameObject::SetAccelerationX(float _x)
{
	this->_accelerationX = _x;
}
void XDL_GameObject::SetAccelerationY(float _y)
{
	this->_accelerationY = _y;
}
float XDL_GameObject::GetAccelerationX()
{
	return _accelerationX;
}
float XDL_GameObject::GetAccelerationY()
{
	return _accelerationY;
}

#pragma endregion Acceleration Get and Set


