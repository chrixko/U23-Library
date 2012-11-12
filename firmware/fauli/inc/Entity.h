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
	
	void* context;
	void (*update)(void*);
	void (*draw)(void*, Bitmap*);
	bool destroyed;
} Entity;

Entity* Entity_Create(void* context);

void Entity_Update(Entity* entity);
void Entity_Draw(Entity* entity, Bitmap* surface);
void Entity_Destroy(Entity* entity);

#endif
