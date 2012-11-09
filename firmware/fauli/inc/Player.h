#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Entity.h>

struct Player
{
	struct Entity* entity;
	int health;
};

struct Player* Player_Create();
void Player_processInput(struct Player* player);
void Player_moveBy(struct Player* player, int x, int y);
void Player_Update(void* player);
void Player_Draw(void* player, Bitmap* surface);
void Player_Destroy(struct Player* player);

#endif
