#include <Entity.h>

struct Entity* Entity_Create(void* context)
{
	struct Entity* entity = 0;
	
	entity = (struct Entity*)malloc(sizeof(struct Entity));
	entity->posX = 0;
	entity->posY = 0;
	
	entity->context = context;
	entity->update = 0;
	entity->draw = 0;
		
	return entity;
}

void Entity_Update(struct Entity* entity)
{
	if(entity->update != 0)
	{
		entity->update(entity->context);
	}
}

void Entity_Draw(struct Entity* entity, Bitmap* surface)
{
	if(entity->draw != 0)
	{
		entity->draw(entity->context, surface);
	}
}

void Entity_Destroy(struct Entity* entity)
{
	free(entity);
}
