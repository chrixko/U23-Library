#include <Entity.h>
#include <Player.h>

struct Player* Player_Create()
{
	struct Player* player = 0;
	
	player = (struct Player*)malloc(sizeof(struct Player));
	player->entity = Entity_Create(player);
	player->entity->update = Player_Update;
	player->entity->draw = Player_Draw;
	player->health = 100;
	
	return player;	
}

void Player_Update(void* player)
{
	//Player updating
}

void Player_Draw(void* player)
{
	//Player_Drawing
}

void Player_Destroy(struct Player* player)
{
	Entity_Destroy(player->entity);
	free(player);
}
