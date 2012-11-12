#include <game/Game.h>
#include <game/Debug.h>
#include <game/Font.h>

#include <stdio.h>
#include <string.h>

#include <bilder.h>
#include <Entity.h>
#include <Player.h>

void Init(struct Gamestate*);
void Update(uint32_t);
void Draw(Bitmap *);

Gamestate InitState = { Init, NULL, NULL, Update, Draw };
Game* TheGame = &(Game) {&InitState};

Player* player;

void Init(struct Gamestate* state) 
{
	player = Player_Create();
}
void Update(uint32_t tick) 
{
	Entity_Update(player->entity);
}

void Draw(Bitmap* surface)
{
	DrawRLEBitmap(surface, &bg_lab, player->entity->posX *-1, 0);
	Entity_Draw(player->entity, surface);	
}
