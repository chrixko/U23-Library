#ifndef __HEALTHPACK_H__
#define __HEALTHPACK_H__

#include "Constants.h"
#include "Entity.h"
#include "Healthpack_Battery.h"

typedef struct {
    Entity* entity;
    int healthBonus;
} Healthpack;

Healthpack* Healthpack_Create(int type);

void Healthpack_Draw(void* healthpack, Bitmap* surface);
void Healthpack_Destroy(void* healthpack);

#endif
