#include <Scene.h>
#include <bilder.h>
#include <Constants.h>

Scene* Scene_Create()
{
	Scene* scene = (Scene*)malloc(sizeof(Scene));
	scene->background = &bg_lab;
	scene->update = NULL;
	scene->draw = NULL;
	scene->destroy = NULL;
	
	Vector_Init(&scene->entities);
	
	return scene;
}

void Scene_Update(void* scene)
{	
	Scene* s = scene;
	
	if(s->update != NULL)
	{
		s->update(s);
	}
	
	for (unsigned int i=0; i < s->entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&s->entities, i);
	    if (it != NULL) {
	        if (it->destroyed) {
    	        Entity_Destroy(it);
	            Vector_Set(&s->entities, i, NULL);
	        } else {
    	        Entity_Update(it);
	        }
	    }
	}	
}

void Scene_Draw(void* scene, Bitmap* surface)
{
	Scene* s = scene;
	
	if(s->draw != NULL)
	{
		s->draw(scene, surface);
	}
	
	DrawRLEBitmap(surface, s->background, camera->posX * -1, 0);
	
	for (unsigned int i=0; i < s->entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&s->entities, i);
	    if (it != NULL) {
    	    Entity_Draw(it, surface);
	    }
	}	
}

void Scene_Destroy(void* this)
{
	Scene* scene = this;
	free(scene);
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
