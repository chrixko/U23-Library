
#include "Bullet.h"
#include <Projectile_Laser.h>

Bullet* Bullet_Create(int collisionType) {
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->entity = Entity_Create(bullet);
    bullet->entity->update = Bullet_Update;
    bullet->entity->destroy = Bullet_Destroy;
    bullet->entity->draw = Bullet_Draw;
    bullet->entity->collision = Bullet_Collision;
    bullet->entity->collisionType = collisionType;
    
    bullet->entity->width = 10;
    bullet->entity->height = 7;
    
    bullet->damage = 1;
    bullet->maxLifeTime = 200;
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
    
    DrawRLEBitmap(surface, &Projectile_Laser, this->entity->posX - camera->posX, this->entity->posY);
}

void Bullet_Destroy(void* bullet) {
    Bullet* this = (Bullet*)bullet;
    free(this);
}

bool Bullet_Collision(void* bullet, Entity* otherEntity) {
    Bullet* this = bullet;
    Entity* other;
    
    if (other->collisionType == COLLISION_TYPE_ENEMY) {
        this->entity->destroyed = true;
        return true;
    }
    return false;
}

