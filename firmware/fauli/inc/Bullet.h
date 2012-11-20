#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "Constants.h"
#include "Sprite_LaserCat.h"

typedef struct {
    int damage;
    int maxLifeTime;
    int lifeTime;
    Entity* entity;
} Bullet;


Bullet* Bullet_Create();
void Bullet_Update(void* bullet);
void Bullet_Draw(void* bullet, Bitmap* surface);
void Bullet_Destroy(void* bullet);
bool Bullet_Collision(void* bullet, void* otherEntity);

#endif
