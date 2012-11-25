
#include "Weapon.h"

Weapon* Weapon_Create(Entity* wielder) {
    Weapon* weapon = malloc(sizeof(Weapon));
    weapon->entity = Entity_Create(weapon);
    weapon->entity->update = Weapon_Update;
    weapon->entity->destroy = Weapon_Destroy;
    weapon->entity->draw = Weapon_Draw;
    weapon->wielder = wielder;
    
    weapon->rotation = 0.f;
    weapon->bulletSpeedX = 3;
    weapon->bulletSpeedY = 0;
    weapon->bulletsPerShot = 1;
    weapon->bulletSpread = 1;
    weapon->cooldownTime = 20;
    weapon->cooldownTimer = 0;
    
    return weapon;
}

void Weapon_Shoot(Weapon* this) {
    if (this->cooldownTimer >= this->cooldownTime) {
        this->cooldownTimer = 0;
        
        int bulletCollisionType;
        if (this->wielder && this->wielder->collisionType == COLLISION_TYPE_PLAYER) {
            bulletCollisionType = COLLISION_TYPE_BULLET_PLAYER;
        } else {
            bulletCollisionType = COLLISION_TYPE_BULLET_ENEMY;        
        }
        
        for (unsigned int i=0; i < this->bulletsPerShot; ++i) {
            Bullet* bullet = Bullet_Create(bulletCollisionType);
            bullet->entity->posX = this->entity->posX;
            bullet->entity->posY = this->entity->posY;

            //TODO make real rotation calculation
            bullet->entity->vX = this->bulletSpeedX;
            bullet->entity->vY = this->bulletSpeedY + this->rotation;
            
            if (this->bulletSpread != 0) {
                if (GetRandomInteger() % 1 != 0) {
                    bullet->entity->posY += GetRandomInteger() % this->bulletSpread;
                } else {
                    bullet->entity->posY -= GetRandomInteger() % this->bulletSpread;
                }
                
                if (GetRandomInteger() % 1 != 0) {
                    bullet->entity->vX += GetRandomInteger() % this->bulletSpread;
                } else {
                    bullet->entity->vY -= GetRandomInteger() % this->bulletSpread;
                }
            }
            
           Scene_AddEntity(currentScene, bullet->entity);
        }        
    }
}

void Weapon_Draw(void* weapon, Bitmap* surface) {
    Weapon* this = weapon;
}

void Weapon_Update(void* weapon) {
    Weapon* this = weapon;
    this->cooldownTimer++;

    // sync position with wielding entity
    if (this->wielder) {
        this->entity->posX = this->wielder->posX;
        this->entity->posY = this->wielder->posY;
    }
}

void Weapon_Destroy(void* weapon) {
    Weapon* this = weapon;
    free(weapon);
}

void Weapon_Rotate(Weapon* this, float delta) {
    float newRotation = this->rotation + delta;
    if (newRotation > -90 && newRotation < 90) {
        this->rotation = newRotation;
    }
}
