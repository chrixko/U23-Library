#include <Entity.h>
#include "Game.h"
#include "Constants.h"

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
	entity->collision = NULL;
	
	entity->destroyed = false;
	
	entity->checkCollisionByPixel = false;
	entity->bitmap = NULL;
	entity->collisionType = 0;
	entity->sceneCollision = false;
		
	return entity;
}

void Entity_Update(Entity* entity)
{
	if(entity->update != NULL)
	{		
		entity->update(entity->context);
	}
	if (entity->vX != 0 || entity->vY != 0) {
	    Entity_MoveBy(entity, entity->vX, entity->vY);
	}
}

void Entity_Draw(Entity* entity, Bitmap* surface)
{
	if(entity->draw != NULL)
	{
		entity->draw(entity->context, surface);
	}
}

bool Entity_Collision(Entity* entity, Entity* other)
{
	if(entity->collision != NULL)
	{
		return entity->collision(entity->context, other);
	}
	return true;
}

void Entity_Destroy(Entity* entity)
{
    if (entity->destroy != NULL) {
        entity->destroy(entity->context);
    }
	free(entity);
}

void Entity_MoveBy(Entity* this, int x, int y)
{
	int oldX = this->posX;
	int oldY = this->posY;
	
	this->posX = this->posX + x;
	this->posY = this->posY + y;
	
	// check collision
	Vector* entities = Game_GetEntities();
	for (unsigned int i=0; i < entities->usedElements; ++i) {
	    Entity* it = Vector_Get(entities, i);
	    if (it != NULL && it != this) {
	        if (Entity_CheckCollision(this, it)) {
	            if (Entity_Collision(this, it)) {
	                this->posX = oldX;
	                this->posY = oldY;
	            }
	            Entity_Collision(it, this); //TODO maybe don't do this
	        }
	    }
	};

    // background scene collision
    if (this->sceneCollision) {
	    if((this->posX < 0) || (this->posX > 3200-51))
	    {
		    this->posX = oldX;
	    }
	
	    if((this->posY < ((SCREEN_HEIGHT - FLOOR_HEIGHT) - this->height)) || (this->posY > SCREEN_HEIGHT-this->height))
	    {
		    this->posY = oldY;
	    }
    }
}

void Entity_ModifyHealth(Entity* this, int value) {
    this->health += value;
    if (this->health <= 0) {
        //TODO start death animation
        // block animationchanges
        // destroy after animation
        this->health = 0;
    } else if (this->health > this->maxHealth) {
        this->health = this->maxHealth;
    }
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
    return !(a->posX > b->posX+b->width ||
             a->posX+a->width < b->posX ||
             a->posY > b->posY+b->height ||
             a->posY+a->height < b->posY);
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

