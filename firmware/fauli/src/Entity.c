#include <Entity.h>

struct Entity* Entity_Create(void* context)
{
	struct Entity* entity = (struct Entity*)malloc(sizeof(struct Entity));	
	
	entity->posX = 0;
	entity->posY = 0;
	entity->vX = 0;
	entity->vY = 0;
	
	//entity->animation = NULL;
	
	entity->context = context;
	entity->update = NULL;
	entity->draw = NULL;	
		
	return entity;
}

void Entity_Update(struct Entity* entity)
{
	if(entity->update != NULL)
	{		
		entity->update(entity->context);
	}
}

void Entity_Draw(struct Entity* entity, Bitmap* surface)
{
	if(entity->draw != NULL)
	{
		entity->draw(entity->context, surface);
	}
}

void Entity_Destroy(struct Entity* entity)
{
	free(entity);
}
