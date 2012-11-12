#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Entity.h>
#include <Animation.h>

struct Player
{
	struct Entity* entity;
	struct Animation* animations[2];
	int currentAnimationIndex;
	int health;
};

struct Player* Player_Create();
void Player_Update(void* player);
void Player_Draw(void* player, Bitmap* surface);
void Player_Destroy(struct Player* player);

struct Animation* _Player_getCurrentAnimation(struct Player* player);
void _Player_processInput(struct Player* player);
void _Player_moveBy(struct Player* player, int x, int y);
#endif
