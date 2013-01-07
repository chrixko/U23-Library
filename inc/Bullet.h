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


Bullet* Bullet_Create(int collisionType);
void Bullet_Update(void* bullet);
void Bullet_Draw(void* bullet, Bitmap* surface);
void Bullet_Destroy(void* bullet);

void Bullet_Explode(void* this);

bool Bullet_Collision(void* bullet, Entity* otherEntity);

#endif
