//A class that basically includes all transform information that a camera would apply to the scene.
#include "XDL_Camera.h"

XDL_Camera* XDL_Camera::_me;
XDL_Camera::XDL_Camera()
{
	_pos = new SDL_Point;
	_pos->x = 0;//set pos and zoom at beginning
	_pos->y = 0;

	_zoom = 1;
}

XDL_Camera* XDL_Camera::GetInstance()//singleton
{
	if(_me == NULL)
	{
		_me = new XDL_Camera();
	}
	return _me;
}

XDL_Camera::~XDL_Camera(void)
{
}
void XDL_Camera::SetZoom(float _zoom)//simple getters and setters
{
	this->_zoom = _zoom;
}
float XDL_Camera::GetCurrentZoom()
{
	return _zoom;
}
void XDL_Camera::SetPosition(int _x,int _y)//set the current position of the camera
{
	_pos->x = _x;
	_pos->y = _y;
}
SDL_Point* XDL_Camera::GetPosition()
{
	return _pos;
}