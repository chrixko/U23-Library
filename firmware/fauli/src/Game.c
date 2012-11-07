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

struct {int xpos; int ypos; int animation; int hp; int dmg; int nextFrameCounter; int timeToNextFrame;} katze = { 0,150, 0,100,5, 0, 10};

void Init(struct Gamestate* state) 
{
	player = Player_Create();
}
void Update(uint32_t tick) 
{
	Entity_Update(player->entity);
	
	snes_button_state_t state = GetControllerState1();
	
	if (state.buttons.Up)
	{
		if ((katze.ypos > 100) && (katze.ypos <= 200-34))
		{
			katze.ypos--;/* code */
		}
	}
	if (state.buttons.Down)
	{
		if ((katze.ypos >= 100) && (katze.ypos < 200-34))
		{
			katze.ypos++;/* code */
		}
	}
	if (state.buttons.Left)
	{
		if ((katze.xpos > 0) && (katze.xpos <= 320-51))
		{
			katze.xpos--;/* code */
		}
	}
	if (state.buttons.Right)
	{
		if ((katze.xpos >= 0) && (katze.xpos < 320-51))
		{
			katze.xpos++;/* code */
		}
	}
	
	katze.nextFrameCounter++;
    if (katze.nextFrameCounter >= katze.timeToNextFrame)
    {
    	katze.animation++;
    	katze.nextFrameCounter = 0;
	}
	if (katze.animation >= 6) {
	    katze.animation = 0;
	}
}

void Draw(Bitmap* surface)
{
	Entity_Draw(player->entity, surface);
	
    const RLEBitmap * animationStep = nukular[katze.animation];

	DrawRLEBitmap(surface, &bg_lab, 0, 0);
	DrawRLEBitmap(surface, animationStep, katze.xpos, katze.ypos);
}
