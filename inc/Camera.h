#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Entity.h>

typedef struct
{
	int posX;
	int posY;
	
} Camera;
Camera* Camera_Create(int posX, int posY);
void Camera_FocusOnEntity(Camera* this, Entity* target);
#endif
