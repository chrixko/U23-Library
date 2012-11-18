#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdlib.h>
#include <RLEBitmap.h>
#include <game/Game.h>

typedef struct 
{
	int posX;
	int posY;
	
	int vX;
	int vY;
	
	int scrollX;
	int scrollY;
	
	int width;
	int offsetX;
	int height;
	int offsetY;	
	
	int health;
	int maxHealth;
	
	void* context;
	void (*update)(void*);
	void (*draw)(void*, Bitmap*);
	void (*destroy)(void*);
	bool destroyed;
	
    bool checkCollisionByPixel;
	Bitmap* bitmap;
} Entity;

Entity* Entity_Create(void* context);

void Entity_Update(Entity* entity);
void Entity_Draw(Entity* entity, Bitmap* surface);
void Entity_Destroy(Entity* entity);

bool Entity_CheckCollision(Entity* a, Entity* b);

// private

/// stores an absolute x,y and relative width, height
typedef struct {
    int x, y, width, height;
} Rect;

/// using Entity->width Entity->height as rectSize
/// @return true if the rect of @a is neither left, right above or below the rect of @b
bool Entity_checkRectCollision(Entity* a, Entity* b);
/// using Entity->bitmap->width Entity->bitmap->height as rectSize
/// @return true if the rect of @a is neither left, right above or below the rect of @b
bool Entity_checkRectCollisionByBitmap(Entity* a, Entity* b);
/// @return a rect that contains the overlapping area between two sprites
Rect Entity_collisionSubrect(Entity* a, Entity* b);

////////////////////////////////////////////////////////////////////////////////
/// Step 1 check for boundingbox collision 
/// Step 2 find the colliding sub-rectangle
/// Step 3 check all pixels in the sub-rectangle
///        and return true if both bitmaps have a pixel that is not transparent
///        at the same position
////////////////////////////////////////////////////////////////////////////////
bool Entity_checkPixelCollision(Entity* a, Entity* b);

#endif
