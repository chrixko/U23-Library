#include <Camera.h>
#include <Constants.h>

Camera* Camera_Create(int posX, int posY)
{
	Camera* cam = (Camera*)malloc(sizeof(Camera));
	cam->posX = 0;
	cam->posY = 0;
	
	return cam;
}

void Camera_FocusOnEntity(Camera* this, Entity* target)
{
	int desiredX = target->posX - (SCREEN_WIDTH / 3);
	int desiredY = target->posY - (SCREEN_HEIGHT / 2);
	if(desiredX >= 0)
	{
		this->posX = desiredX;
	}
	if(desiredY >= 0)
	{
		this->posY = desiredY;
	}	
}
