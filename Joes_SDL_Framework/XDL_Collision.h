//! XDL Collision
/*!
An object to store collision information
*/

#ifndef _XDL_COLLISION_H
#define _XDL_COLLISION_H

#include "XDL_GameObject.h"
class XDL_Collision
{
public:
	XDL_Collision(XDL_GameObject* _object1,XDL_GameObject* _object2);
	~XDL_Collision(void);

	XDL_GameObject* GetObject1();/*!Getter for object involved in collision*/
	XDL_GameObject* GetObject2();/*!Getter for object involved in collision*/
private:
	XDL_GameObject* _object1;
	XDL_GameObject* _object2;

};

#endif