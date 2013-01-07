#ifndef _TRIGGERAREA_H__
#define _TRIGGERAREA_H__

#include "Player.h"

typedef struct TriggerArea TriggerArea;
struct TriggerArea {
    Entity* entity;
    void (*onPlayerEnter)(TriggerArea*, Player*);
    void (*onPlayerLeave)(TriggerArea*, Player*);
};

TriggerArea* TriggerArea_Create(void (*onPlayerEnter)(TriggerArea*, Player*), void (*onPlayerLeave)(TriggerArea*, Player*));
void TriggerArea_Update(void* context);
bool TriggerArea_Collision(void* context, Entity* other);
void TrigerArea_Destroy(void* context);


#endif
