#ifndef __EXPLOSIONENTITY_H__
#define __EXPLOSIONENTITY_H__

#include "Entity.h"
#include "Animation.h"

typedef struct {
	Entity* entity;
	Animation* animation[1];
} ExplosionEntity;

ExplosionEntity* ExplosionEntity_Create(int posX, int posY);
void ExplosionEntity_Update(void* this);
void ExplosionEntity_Draw(void* this, Bitmap* surface);
void ExplosionEntity_Destroy(void* this);

#endif
