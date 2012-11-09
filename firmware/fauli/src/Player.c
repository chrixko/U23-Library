#include <game/Game.h>

#include <Entity.h>
#include <Player.h>
#include <bilder.h>

struct Player* Player_Create()
{
	struct Player* player = (struct Player*)malloc(sizeof(struct Player));
	
	player->entity = Entity_Create(player);
	player->entity->posY = 150;	
	player->entity->update = Player_Update;
	player->entity->draw = Player_Draw;	
	player->health = 100;
	
	return player;	
}

void Player_processInput(struct Player* player)
{
	//TODO: Decide by PlayerType wether to poll State1 or 2
	snes_button_state_t state = GetControllerState1();
	
	if(state.buttons.Up)
	{
		Player_moveBy(player, 0, -1);
	}
	
	if(state.buttons.Down)
	{
		Player_moveBy(player, 0, 1);
	}
	
	if(state.buttons.Left)
	{
		Player_moveBy(player, -1, 0);
	}
	
	if(state.buttons.Right)
	{
		Player_moveBy(player, 1, 0);
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
	Player_processInput((struct Player*)player);
}

void Player_Draw(void* player, Bitmap* surface)
{
	struct Player* p = player;
	DrawRLEBitmap(surface, nukular[0], p->entity->posX, p->entity->posY);
}

void Player_Destroy(struct Player* player)
{
	Entity_Destroy(player->entity);
	free(player);
}
