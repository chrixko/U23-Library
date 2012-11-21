#ifndef _LASER_CAT_H_
#define _LASER_CAT_H_


#include "Entity.h"
#include "Weapon.h"
#include "Animation.h"

#define LASERCAT_ANIMATION_WALKING 0
#define LASERCAT_ANIMATION_IDLE 1

typedef struct {
	Entity* entity;
	Animation* animations[2];
	int currentAnimationIndex;
	Weapon* weapon;
	Entity* target;
} LaserCat;

LaserCat* LaserCat_Create();
void LaserCat_Update(void* laserCat);
void LaserCat_Draw(void* laserCat, Bitmap* surface);
void LaserCat_Destroy(void* laserCat);
void LaserCat_Shoot(LaserCat* this);
bool LaserCat_Collision(void* laserCat, Entity* other);

#endif
