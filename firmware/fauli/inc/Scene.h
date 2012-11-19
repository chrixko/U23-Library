#ifndef __SCENE_H__
#define __SCENE_H__

#include <Drawing.h>
#include <Entity.h>
#include <Vector.h>

typedef struct 
{
	Vector entities;
	const RLEBitmap *background;
	void (*update)(void*);
	void (*draw)(void*, Bitmap*);
	void (*destroy)(void*);	
} Scene;

Scene* Scene_Create();

void Scene_Update();
void Scene_Draw(void* scene, Bitmap* surface);
void Scene_Destroy(void* this);

void Scene_AddEntity(Scene* scene, Entity* entity);

#endif
