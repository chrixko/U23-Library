#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Entity.h>
#include <Animation.h>
#include "Weapon.h"

#define PLAYER_ANIMATION_WALKING 0
#define PLAYER_ANIMATION_IDLE    1

typedef struct
{
	Entity* entity;
	Animation* animations[2];
	int currentAnimationIndex;
	int health;
	Weapon* weapon;
} Player;

Player* Player_Create();
void Player_Update(void* player);
void Player_Draw(void* player, Bitmap* surface);
void Player_Destroy(void* player);
void Player_Shoot(Player* player);
bool Player_Collision(void* player, Entity* other);


Animation* _Player_getCurrentAnimation(Player* player);
void _Player_processInput(Player* player);
void _Player_moveBy(Player* player, int x, int y);
#endif
