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

struct Player* player;

//struct {int xpos; int ypos; int animation; int hp; int dmg; int nextFrameCounter; int timeToNextFrame;} katze = { 0,150, 0,100,5, 0, 10};

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
	DrawRLEBitmap(surface, &bg_lab, 0, 0);
	Entity_Draw(player->entity, surface);	
}
