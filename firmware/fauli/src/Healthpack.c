#include "Healthpack.h"

Healthpack* Healthpack_Create(int collisionType) {
    Healthpack* this = malloc(sizeof(Healthpack));
    this->entity = Entity_Create(this);
    this->entity->width = 32;
    this->entity->height = 32;
    this->entity->draw = Healthpack_Draw;
    this->entity->collisionType = collisionType;

    this->healthBonus = 50;
    return this;
}

void Healthpack_Draw(void* healthpack, Bitmap* surface) {
    Healthpack* this = healthpack;
    DrawRLEBitmap(surface, Sprite_LaserCat[0], this->entity->posX - camera->posX, this->entity->posY);
}
void Healthpack_Destroy(void* healthpack) {
    Healthpack* this = healthpack;
    free(this);
}

