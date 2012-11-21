#ifndef __LABSCENE_H__
#define __LABSCENE_H__

#include <Scene.h>
#include <Player.h>

typedef struct
{
	Scene* scene;
	Player* firstPlayer;
	//Player* secondPlayer;
	
	
} LabScene;

LabScene* LabScene_Create();
void LabScene_Update();
void LabScene_Draw(void* scene, Bitmap* surface);

#endif
