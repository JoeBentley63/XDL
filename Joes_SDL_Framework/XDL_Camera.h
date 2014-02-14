#ifndef _CAMERA_H
#define _CAMERA_H

#include <SDL.h>

class XDL_Camera
{
public:
	
	~XDL_Camera(void);
	void SetZoom(float _zoom);
	float GetCurrentZoom();
	void SetPosition(int _x,int _y);
	SDL_Point* _pos;
	float _zoom;
	SDL_Point* GetPosition();
	static XDL_Camera* GetInstance();
private:
	static XDL_Camera* _me;
	XDL_Camera();
	
};

#endif