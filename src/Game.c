#include <game/Game.h>
#include <Debug.h>
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
    camera = Camera_Create(0,0);
	LabScene* s = LabScene_Create();
	currentScene = s->scene;
	Scene_Init(currentScene);
}

void Update(uint32_t tick) 
{
    if (nextScene) {
        Scene_Destroy(currentScene);
        currentScene = nextScene;
        nextScene = NULL;
        Scene_Init(currentScene);
    }
	Scene_Update(currentScene);
}

void Draw(Bitmap* surface)
{	
	Scene_Draw(currentScene, surface);
}
