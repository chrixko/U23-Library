
#include "Bullet.h"

Bullet* Bullet_Create() {
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->entity = Entity_Create(bullet);
    bullet->entity->update = Bullet_Update;
    bullet->entity->destroy = Bullet_Destroy;
    bullet->entity->draw = Bullet_Draw;
    bullet->entity->collisionType = COLLISION_TYPE_BULLET;
    
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

