#include <Scene.h>
#include <Constants.h>
#include "Background_Lab.h"

Scene* Scene_Create(void* context)
{
	Scene* scene = (Scene*)malloc(sizeof(Scene));
	scene->background = &Background_Lab;
	scene->updateEntities = true;
	
	scene->context = context;
	scene->init = NULL;
	scene->update = NULL;
	scene->draw = NULL;
	scene->destroy = NULL;
	
	Vector_Init(&scene->entities);
	
	return scene;
}

void Scene_Init(Scene* scene)
{	
	if(scene->init != NULL)
	{
		scene->init(scene->context);
	}	
}

void Scene_Update(Scene* scene)
{			
	if(scene->update != NULL)
	{
		scene->update(scene->context);
	}
	
	if(scene->updateEntities)
	{
		for (unsigned int i=0; i < scene->entities.usedElements; ++i) {
			Entity* it = Vector_Get(&scene->entities, i);
			if (it != NULL) {
				if (it->destroyed) {
					Entity_Destroy(it);
					Vector_Set(&scene->entities, i, NULL);
				} else {
					Entity_Update(it);
				}
			}
		}		
	}	
}

void Scene_Draw(Scene* scene, Bitmap* surface)
{	
	DrawRLEBitmap(surface, scene->background, camera->posX * -1, 0);
	
	for (unsigned int i=0; i < scene->entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&scene->entities, i);
	    if (it != NULL) {
    	    Entity_Draw(it, surface);
	    }
	}
	
	if(scene->draw != NULL)
	{
		scene->draw(scene->context, surface);
	}
}

void Scene_Destroy(Scene* this)
{
    for (unsigned int i=0; i < this->entities.usedElements; ++i) {
        Entity* it = Vector_Get(&this->entities, i);
	    if (it != NULL) {
    	    Entity_Destroy(it);
	    }
	}
	
	free(this);
}

Vector* Scene_GetEntities(Scene* this) {
    return &this->entities;
}

void Scene_AddEntity(Scene* scene, Entity* entity) {	
    bool inserted = false;
	for (unsigned int i=0; i < scene->entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&scene->entities, i);
	    if (it == NULL) {
            Vector_Set(&scene->entities, i, entity);
            inserted = true;
            break;
	    }
    }
    
    if (!inserted) {
        Vector_AddElement(&scene->entities, entity);    
    }
}
