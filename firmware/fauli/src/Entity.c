#include <Entity.h>

Entity* Entity_Create(void* context)
{
	Entity* entity = (Entity*)malloc(sizeof(Entity));	
	
	entity->posX = 0;
	entity->posY = 0;
	entity->vX = 0;
	entity->vY = 0;
	entity->scrollX = 1;
	entity->scrollY = 1;
	entity->width = 0;
	entity->height = 0;
	entity->offsetX = 0;
	entity->offsetY = 0;	
	
	entity->health = 100;
	entity->maxHealth = 100;
	
	entity->context = context;
	entity->update = NULL;
	entity->draw = NULL;
	entity->destroy = NULL;
	
	entity->destroyed = false;
	entity->checkCollisionByPixel = false;
	entity->bitmap = NULL;
		
	return entity;
}

void Entity_Update(Entity* entity)
{
	if(entity->update != NULL)
	{		
		entity->update(entity->context);
	}
}

void Entity_Draw(Entity* entity, Bitmap* surface)
{
	if(entity->draw != NULL)
	{
		entity->draw(entity->context, surface);
	}
}

void Entity_Destroy(Entity* entity)
{
    if (entity->destroy != NULL) {
        entity->destroy(entity->context);
    }
	free(entity);
}




/*
 Collision
*/

bool Entity_CheckCollision(Entity* a, Entity* b) {
    if ((a->checkCollisionByPixel || b->checkCollisionByPixel) && a->bitmap && b->bitmap) {
        return Entity_checkPixelCollision(a,b);
    }
    return Entity_checkRectCollision(a,b);
}

bool Entity_checkRectCollision(Entity* a, Entity* b) {
    return !(a->posX < b->posX + b->width) &&
           !(a->posX + a->width < b->posX) &&
           !(a->posY < b->posY + b->height) &&
           !(a->posY + a->height < b->posY);
}

bool Entity_checkRectCollisionByBitmap(Entity* a, Entity* b) {
    return !(a->posX < b->posX + b->bitmap->width) &&
           !(a->posX + a->bitmap->width < b->posX) &&
           !(a->posY < b->posY + b->bitmap->height) &&
           !(a->posY + a->bitmap->height < b->posY);
}

Rect Entity_collisionSubrect(Entity* a, Entity* b) {
    Rect subrect;
    subrect.x = a->posX > b->posX ? a->posX : b->posX;
    subrect.y = a->posY > b->posY ? a->posY : b->posY;
    subrect.width  = (a->posX + a->bitmap->width  < b->posX + b->bitmap->width  ? a->posX + a->bitmap->width  : b->posX + b->bitmap->width)  - subrect.x;
    subrect.height = (a->posY + a->bitmap->height < b->posY + b->bitmap->height ? a->posY + a->bitmap->height : b->posY + b->bitmap->height) - subrect.y;

    return subrect;
}

bool Entity_checkPixelCollision(Entity* a, Entity* b) {
    if (Entity_checkRectCollisionByBitmap(a,b)) {
        const Rect collisionRect = Entity_collisionSubrect(a, b);
    
        // x and y as absolute global pixel position        
        for (int y=collisionRect.y; y < collisionRect.y + collisionRect.height; ++y) {
            for (int x=collisionRect.x; x < collisionRect.x + collisionRect.width; ++x) {
                if (*ConstBitmapPixelPointer(a->bitmap, x - a->posX, y - a->posY) != TransparentPixel &&
                    *ConstBitmapPixelPointer(b->bitmap, x - b->posX, y - b->posY) != TransparentPixel) {
                    return true;
                }
            }
        }
    }
    return false;
}

