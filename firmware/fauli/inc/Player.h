#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Entity.h>
#include <Animation.h>

typedef struct
{
	Entity* entity;
	Animation* animations[2];
	int currentAnimationIndex;
	int health;
} Player;

Player* Player_Create();
void Player_Update(void* player);
void Player_Draw(void* player, Bitmap* surface);
void Player_Destroy(Player* player);

Animation* _Player_getCurrentAnimation(Player* player);
void _Player_processInput(Player* player);
void _Player_moveBy(Player* player, int x, int y);
#endif
