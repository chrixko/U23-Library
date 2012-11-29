
#include "Bullet.h"
#include "ExplosionEntity.h"
#include <Projectile_Laser.h>
#include "Projectile_Big.h"

Bullet* Bullet_Create(int collisionType) {
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->entity = Entity_Create(bullet);
    bullet->entity->update = Bullet_Update;
    bullet->entity->destroy = Bullet_Destroy;
    bullet->entity->draw = Bullet_Draw;
    bullet->entity->collision = Bullet_Collision;
    bullet->entity->collisionType = collisionType;
    
    if(collisionType == COLLISION_TYPE_BULLET_PLAYER)
    {
		bullet->entity->width = 6;
		bullet->entity->height = 4;
	}
	else
	{
		bullet->entity->width = 10;
		bullet->entity->height = 7;		
	}
    
    bullet->damage = 10;
    bullet->maxLifeTime = 250;
    bullet->lifeTime = 0;
    
    return bullet;
}


void Bullet_Update(void* bullet) {
    Bullet* this = (Bullet*)bullet;
    
    this->lifeTime++;
    if (this->lifeTime > this->maxLifeTime) {
        this->entity->destroyed = true;
    }
}

void Bullet_Draw(void* bullet, Bitmap* surface) {
    Bullet* this = (Bullet*)bullet;
	if(this->entity->collisionType == COLLISION_TYPE_BULLET_ENEMY)
	{
		DrawRLEBitmap(surface, &Projectile_Laser, this->entity->posX - camera->posX, this->entity->posY);
	}
	else
	{
		DrawRLEBitmap(surface, &Projectile_Big, this->entity->posX - camera->posX, this->entity->posY);
	}    
}

void Bullet_Destroy(void* bullet) {
    Bullet* this = (Bullet*)bullet;
    free(this);
}

void Bullet_Explode(void* bullet) {
	Bullet* b = bullet;
	ExplosionEntity* exp = ExplosionEntity_Create(b->entity->posX + (5 * b->entity->vX), b->entity->posY - 5);
	Scene_AddEntity(currentScene, exp->entity);	
	b->entity->destroyed = true;
}

bool Bullet_Collision(void* bullet, Entity* otherEntity) {
    Bullet* this = bullet;
    
      
    return false;
}

