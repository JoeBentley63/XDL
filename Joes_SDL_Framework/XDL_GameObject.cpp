#include "XDL_GameObject.h"


XDL_GameObject::XDL_GameObject(void)
{
	_bounds.x = 1;
	_bounds.y = 1;
	_bounds.w = 1;
	_bounds.h = 1;
	_collidable = false;
}

void XDL_GameObject::Update()
{
	_top.x = _bounds.x + (_bounds.w*.2);
	_top.y = _bounds.y - _bounds.h*.2;
	_bottom.x = _bounds.x + (_bounds.w*.2);
	_bottom.y = _bounds.y + _bounds.h*0.9;
	_left.x = _bounds.x - (_bounds.w*.1);
	_left.y = _bounds.y + _bounds.h*0.2;
	_right.x = _bounds.x + (_bounds.w*.9);
	_right.y = _bounds.y + _bounds.h*0.2;

	_velocityX += _accelerationX;
	_velocityY += _accelerationY;

	_posX += _velocityX;
	_posY += _velocityY;
}


XDL_GameObject::~XDL_GameObject(void)
{
}

bool XDL_GameObject::CollidedWith(XDL_GameObject* _otherSprite)
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
			if(_immovable == false)
			{
				_posY++;
				SetVelocityY(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posY--;
				_otherSprite->SetVelocityY(0);
			}
		}
		else
		{
			_isTouchingTop = false;
		}
		if(Overlaps(_bottom,_otherSprite->_bounds))
		{
			_isTouchingBottom = true;
			if(_immovable == false)
			{
				_posY--;
				SetVelocityY(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posY++;
				_otherSprite->SetVelocityY(0);
			}
		}
		else
		{
			_isTouchingBottom = true;
		}
		if(Overlaps(_left,_otherSprite->_bounds))
		{
			_isTouchingLeft = true;
			if(_immovable == false)
			{
				_posX++;
				SetVelocityX(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posX--;
				_otherSprite->SetVelocityX(0);
			}
		}
		else
		{
			_isTouchingLeft = false;
		}
		if(Overlaps(_right,_otherSprite->_bounds))
		{
			_isTouchingRight = true;
			if(_immovable == false)
			{
				_posX--;
				SetVelocityX(0);
			}
			if(_otherSprite->_immovable == false)
			{
				_otherSprite->_posX++;
				_otherSprite->SetVelocityX(0);
			}
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

//Get function for position, to avoid having to go _bounds.X and _bounds.Y. Position is more normal.

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


