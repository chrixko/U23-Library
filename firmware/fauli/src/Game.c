#include <game/Game.h>
#include <game/Debug.h>
#include <game/Font.h>

#include <stdio.h>
#include <string.h>
#include <Constants.h>
#include <LabScene.h>
#include "Background_Lab.h"

void Init(struct Gamestate*);
void Update(uint32_t);
void Draw(Bitmap *);

Gamestate InitState = { Init, NULL, NULL, Update, Draw };
Game* TheGame = &(Game) {&InitState};

void Init(struct Gamestate* state)
{	
	LabScene* s = LabScene_Create();
	currentScene = s->scene;
	Scene_Init(currentScene);
}

void Update(uint32_t tick) 
{
	Scene_Update(currentScene);
}

void Draw(Bitmap* surface)
{	
	Scene_Draw(currentScene, surface);
}
