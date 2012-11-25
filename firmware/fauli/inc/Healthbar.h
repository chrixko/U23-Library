#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__

#include "Entity.h"
#include "Constants.h"
#include "game/Game.h"

typedef struct {
    Entity* watchedEntity;
    Entity* entity;
    Pixel color;
    int barLength;
} Healthbar;

Healthbar* Healthbar_Create(Entity* watchedEntity);
void Healthbar_Draw(void* healthbar, Bitmap* surface);
void Healthbar_Update(void* healthbar);
void Healthbar_Destroy(void* healthbar);


#endif
