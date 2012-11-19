
#include "Bullet.h"

Bullet* Bullet_Create() {
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->entity = Entity_Create(bullet);
    bullet->entity->update = Bullet_Update;
    bullet->entity->destroy = Bullet_Destroy;
    bullet->entity->draw = Bullet_Draw;
    bullet->entity->collision = Bullet_Collision;
    bullet->entity->collisionType = COLLISION_TYPE_BULLET_PLAYER;
    
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
    DrawRLEBitmap(surface, Sprite_LaserCat[0], this->entity->posX - camera->posX, this->entity->posY);
}

void Bullet_Destroy(void* bullet) {
    Bullet* this = (Bullet*)bullet;
}

bool Bullet_Collision(void* bullet, void* otherEntity) {
    Bullet* this = bullet;
    Entity* other;
    
    if (other->collisionType == COLLISION_TYPE_ENEMY) {
        this->entity->destroyed = true;
        return true;
    }
    return false;
}

