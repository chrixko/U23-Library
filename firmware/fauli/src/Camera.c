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
	this->posX = target->posX - (SCREEN_WIDTH / 1.5);
	this->posY = target->posY - (SCREEN_HEIGHT / 2);
}
