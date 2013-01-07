#include "ExplosionEntity.h"
#include "Explosion.h"
#include "Constants.h"

ExplosionEntity* ExplosionEntity_Create(int posX, int posY) {
	ExplosionEntity* exp = (ExplosionEntity*)malloc(sizeof(ExplosionEntity));
	exp->entity = Entity_Create(exp);
	exp->entity->posX = posX;
	exp->entity->posY = posY;
	
	//exp->entity->update = ExplosionEntity_Update;
	exp->entity->draw = ExplosionEntity_Draw;
	exp->entity->destroy = ExplosionEntity_Destroy;
	
	exp->animation[0] = Animation_Create("explode", 0, 9, 2);
	
	return exp;	
}

void ExplosionEntity_Draw(void* this, Bitmap* surface) {
	ExplosionEntity* e = this;
	Animation* anim = e->animation[0];
	
	if(anim->currentFrameIndex == anim->endIndex)
	{
		e->entity->destroyed = true;
	}
	
	Animation_Play(anim);
	
	DrawRLEBitmap(surface, Explosion[anim->currentFrameIndex], e->entity->posX - camera->posX, e->entity->posY);
}

void ExplosionEntity_Destroy(void* this) {
	ExplosionEntity* e = this;
	
	Animation_Destroy(e->animation[0]);
	
	free(e);
}
