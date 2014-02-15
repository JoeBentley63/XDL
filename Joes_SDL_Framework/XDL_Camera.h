//! XDL_Camaera. [Singleton]
/*!
Not technically a camera, but a structure to control the scale and position of our drawing surface.
*/

#ifndef _CAMERA_H
#define _CAMERA_H

#include <SDL.h>

class XDL_Camera
{
public:
	
	~XDL_Camera(void);
	 /*!
	\param _zoom Zoom level, set it to 1 as default.
	*/
	void SetZoom(float _zoom);/*!<Sets the zoom of our world, in reality, it sets the scale of our drawing surface, after all drawing has occurred */ 
	 /*!
	\param _zoom Zoom level, set it to 1 as default.
	*/

	 /*!
	\return current Zoom level as a float.
	*/
	float GetCurrentZoom();/*!< Getter for Zoom*/ 
	

	 /*!
	\param _x X position of the world.
	\param _y Y position of the world.
	*/
	void SetPosition(int _x,int _y); /*!<Set the worlds position relative to the window. By default its (0,0), which means anything left/above of the screen will never be drawn. Because of this, it might not be a bad idea to move it*/ 
	

	 /*!
	\return pointer to an SDL_Point, which contains the X and Y position of the world.
	*/
	SDL_Point* GetPosition();/*!<Getter for position*/
	

	/*!
	\return pointer to the camera instance.Creates one if none exists[LazyLoading]
	*/
	static XDL_Camera* GetInstance();/*!<Get Instance, which will return a pointer to our camera*/
	
private:
	static XDL_Camera* _me;/*!<Pointer to our camera instance*/
	XDL_Camera(); /*!< private constructor, do not call, instead call GetInstance() */
	SDL_Point* _pos;/*!<Where the world is relative to the window*/
	float _zoom;/*!<zoom level*/
};

#endif