#include <Player.h>

#include <stdbool.h>

#include <game/Game.h>
#include <Animation.h>
#include <bilder.h>

struct Player* Player_Create()
{
	struct Player* player = (struct Player*)malloc(sizeof(struct Player));
	
	player->entity = Entity_Create(player);
	player->entity->posY = 150;	
	player->entity->update = Player_Update;
	player->entity->draw = Player_Draw;	
	
	player->currentAnimationIndex = 0;
	
	player->animations[0] = Animation_Create("walk_left", 0, 5, 10);
	player->animations[1] = Animation_Create("idle", 0, 0, 0);
	
	player->health = 100;
	
	return player;	
}

void Player_processInput(struct Player* player)
{
	//TODO: Decide by PlayerType wether to poll State1 or 2
	snes_button_state_t state = GetControllerState1();
	
	
	
	if(state.buttons.Up)
	{
		player->entity->vY = -1;
	}
	
	if(state.buttons.Down)
	{
		player->entity->vY = 1;	
	}
	
	if(state.buttons.Left)
	{
		player->entity->vX = -1;	
	}
	
	if(state.buttons.Right)
	{
		player->entity->vX = 1;
	}			
}

void Player_moveBy(struct Player* player, int x, int y)
{
	struct Entity* e = player->entity;
	int desiredX = e->posX + x;
	int desiredY = e->posY + y;
	
	if((desiredX >= 0) && (desiredX <= 320-51))
	{
		e->posX = desiredX;
	}
	
	if((desiredY >= 100) && (desiredY <= 200-34))
	{
		e->posY = desiredY;
	}	
}

void Player_Update(void* player)
{
	//Player updating
	struct Player* p = player;
	p->entity->vX = p->entity->vY = 0;
	
	Player_processInput(p);
	Player_moveBy(p, p->entity->vX, p->entity->vY);
	
	if((p->entity->vX != 0) || (p->entity->vY != 0))
	{
		p->currentAnimationIndex = 0;
	}
	else
	{
		p->currentAnimationIndex = 1;
	}
	
}

struct Animation* Player_getCurrentAnimation(struct Player* player)
{
	return player->animations[player->currentAnimationIndex];
}

void Player_Draw(void* player, Bitmap* surface)
{
	struct Player* p = player;
	struct Animation* anim = Player_getCurrentAnimation(p);
	Animation_Play(anim);
	
	DrawRLEBitmap(surface, nukular[anim->currentFrameIndex], p->entity->posX, p->entity->posY);
}

void Player_Destroy(struct Player* player)
{
	Entity_Destroy(player->entity);
	free(player);
}
