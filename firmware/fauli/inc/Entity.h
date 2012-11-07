#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdlib.h>
#include <game/Game.h>

struct Entity
{
	int posX;
	int posY;
	void* context;
	void (*update)(void*);
	void (*draw)(void*, Bitmap*);
};

struct Entity* Entity_Create(void* context);

void Entity_Update(struct Entity* entity);
void Entity_Draw(struct Entity* entity, Bitmap* surface);
void Entity_Destroy(struct Entity* entity);

#endif
