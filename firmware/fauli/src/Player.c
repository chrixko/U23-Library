#include <game/Game.h>

#include <Entity.h>
#include <Player.h>

struct Player* Player_Create()
{
	struct Player* player = (struct Player*)malloc(sizeof(struct Player));
	
	player->entity = Entity_Create(player);
	player->entity->update = Player_Update;
	player->entity->draw = Player_Draw;
	player->health = 100;
	
	return player;	
}

void Player_processInput(struct Player* player)
{
	//TODO: Decide by PlayerType wether to poll State1 or 2
	snes_button_state_t state = GetControllerState1();
}

void Player_Update(void* player)
{
	//Player updating
	Player_processInput((struct Player*)player);
}

void Player_Draw(void* player, Bitmap* surface)
{
	//Player_Drawing
}

void Player_Destroy(struct Player* player)
{
	Entity_Destroy(player->entity);
	free(player);
}
