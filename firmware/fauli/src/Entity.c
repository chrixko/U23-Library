#include <Entity.h>

Entity* Entity_Create(void* context)
{
	Entity* entity = (Entity*)malloc(sizeof(Entity));	
	
	entity->posX = 0;
	entity->posY = 0;
	entity->vX = 0;
	entity->vY = 0;
	entity->scrollX = 1;
	entity->scrollY = 1;
	
	//entity->animation = NULL;
	
	entity->context = context;
	entity->update = NULL;
	entity->draw = NULL;
	entity->destroy = NULL;
	entity->destroyed = false;
		
	return entity;
}

void Entity_Update(Entity* entity)
{
	if(entity->update != NULL)
	{		
		entity->update(entity->context);
	}
}

void Entity_Draw(Entity* entity, Bitmap* surface)
{
	if(entity->draw != NULL)
	{
		entity->draw(entity->context, surface);
	}
}

void Entity_Destroy(Entity* entity)
{
    if (entity->destroy != NULL) {
        entity->destroy(entity->context);
    }
	free(entity);
}
