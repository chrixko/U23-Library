#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <game/Game.h>
#include "Entity.h"
#include "Bullet.h"
#include "Game.h"

typedef struct {
    float rotation;
    unsigned int bulletSpeedX;
    unsigned int bulletSpeedY;
    unsigned int bulletsPerShot;
    unsigned int bulletSpread;
    unsigned int cooldownTime;
    unsigned int cooldownTimer;
    
    int offsetX;
    int offsetY;
    
    Entity* entity;
    Entity* wielder; // Entity using the weapon
} Weapon;

Weapon* Weapon_Create(Entity* wielder);

void Weapon_Draw(void* weapon, Bitmap* surface);
void Weapon_Update(void* weapon);
void Weapon_Destroy(void* weapon);

void Weapon_Rotate(Weapon* this, float delta);
void Weapon_Shoot(Weapon* this);

#endif


