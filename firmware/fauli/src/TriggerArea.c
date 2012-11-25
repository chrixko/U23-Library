
#include "TriggerArea.h"

TriggerArea* TriggerArea_Create(void (*onPlayerEnter)(TriggerArea*, Player*), void (*onPlayerLeave)(TriggerArea*, Player*)) {
    TriggerArea* this = malloc(sizeof(TriggerArea));
    this->entity = Entity_Create(this);
    
    this->entity->update = TriggerArea_Update;
    this->entity->collision = TriggerArea_Collision;
    
    this->entity->posY = 0;
    this->entity->width = 100;
    this->entity->height = SCREEN_HEIGHT;
    this->onPlayerEnter = onPlayerEnter;
    this->onPlayerLeave = onPlayerLeave;
    return this;
}
void TriggerArea_Update(void* context) {
    TriggerArea* this = context;
}
bool TriggerArea_Collision(void* context, Entity* other) {
    TriggerArea* this = context;
    
    if (other->collisionType == COLLISION_TYPE_PLAYER) {
        if (this->onPlayerEnter) {
            this->onPlayerEnter(this, (Player*)other);
        }
    }
    return false;
}
