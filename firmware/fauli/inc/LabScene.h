#ifndef __LABSCENE_H__
#define __LABSCENE_H__

#include <Scene.h>
#include <Player.h>
#include <Ui.h>
#include "TriggerArea.h"

typedef struct
{
	Ui* ui;
	Scene* scene;
	Player* firstPlayer;
	//Player* secondPlayer;
	
	
} LabScene;

LabScene* LabScene_Create();
void LabScene_Init(void* labScene);
void LabScene_Update(void* labScene);
void LabScene_Draw(void* labScene, Bitmap* surface);

void LabScene_OnSpawnLaserCatsTrigger(TriggerArea* trigger, Player* triggeringPlayer);
void LabScene_OnFinishTrigger(TriggerArea* trigger, Player* triggeringPlayer);
void LabScene_OnFinishStorboardClosed();

#endif
