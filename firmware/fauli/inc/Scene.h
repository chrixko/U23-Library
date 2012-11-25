#ifndef __SCENE_H__
#define __SCENE_H__

#include <Drawing.h>
#include <Entity.h>
#include <Vector.h>

typedef struct 
{
	Vector entities;
	const RLEBitmap *background;
	bool updateEntities;
	
	void* context;
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*, Bitmap*);
	void (*destroy)(void*);	
} Scene;

Scene* Scene_Create(void* context);

void Scene_Init(Scene* scene);
void Scene_Update(Scene* scene);
void Scene_Draw(Scene* scene, Bitmap* surface);
void Scene_Destroy(Scene* this);

void Scene_AddEntity(Scene* scene, Entity* entity);
Vector* Scene_GetEntities(Scene* this);

#endif
