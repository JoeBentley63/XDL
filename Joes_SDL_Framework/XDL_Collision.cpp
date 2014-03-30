#include "XDL_Collision.h"


XDL_Collision::XDL_Collision(XDL_GameObject* _object1,XDL_GameObject* _object2)
{
	this->_object1 = _object1;
	this->_object2 = _object2;
}


XDL_Collision::~XDL_Collision(void)
{
}

XDL_GameObject* XDL_Collision::GetObject1()
{
	return _object1;
}
XDL_GameObject* XDL_Collision::GetObject2()
{
	return _object2;
}

