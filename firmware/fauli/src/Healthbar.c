#include "Healthbar.h"

Healthbar* Healthbar_Create(Entity* watchedEntity) {
    Healthbar* healthbar = malloc(sizeof(Healthbar));
    healthbar->entity = Entity_Create(healthbar);
    healthbar->entity->update = Healthbar_Update;
    healthbar->entity->draw = Healthbar_Draw;
    healthbar->entity->width = HEALTHBAR_WIDTH;
    healthbar->entity->height = HEALTHBAR_HEIGHT;
    
    healthbar->color = RGB(0,255,0);
    healthbar->watchedEntity = watchedEntity;
    healthbar->barLength = 0;
    
    return healthbar;
}

void Healthbar_Draw(void* healthbar, Bitmap* surface) {
    Healthbar* this = healthbar;

    // TODO this doesn't look like it was planned, but this style looks cooler.
    // Atm. some pixels are drawn 2 times (overlapping), this should be avoided.
    
    // draw border
    DrawHorizontalLine(surface, this->entity->posX, this->entity->posY, this->entity->width, RGB(25,25,25));
    DrawHorizontalLine(surface, this->entity->posX, this->entity->posY+this->entity->height-1, this->entity->width, RGB(25,25,25));
    DrawVerticalLine(surface,this->entity->posX, this->entity->posY+1, this->entity->height-2, RGB(25,25,25));
    DrawVerticalLine(surface,this->entity->posX+this->entity->width, this->entity->posY+1, this->entity->height-2, RGB(25,25,25));
    // draw background
    for (unsigned int i=0; i < this->entity->height-1; ++i) {
        DrawHorizontalLine(surface,
                           this->entity->posX+1+this->barLength,
                           this->entity->posY+1+i, this->entity->width - 1 - this->barLength,
                           RGB(100,100,100));
    }    
    // draw healthbar
    for (unsigned int i=0; i < this->entity->height-1; ++i) {
        DrawHorizontalLine(surface, this->entity->posX+1, this->entity->posY+i, this->barLength, this->color);
    }
}

void Healthbar_Update(void* healthbar) {
    Healthbar* this = healthbar;
    this->barLength = ((float)this->watchedEntity->health / (float)this->watchedEntity->maxHealth) * (this->entity->width-2);
    
    // set color
    if (this->watchedEntity->health < this->watchedEntity->maxHealth/4*3) {
        if (this->watchedEntity->health < this->watchedEntity->maxHealth/4*2) {
            if (this->watchedEntity->health < this->watchedEntity->maxHealth/4) {
                this->color = RGB(255, 100, 100); // red 0 - 25%
            } else {
                this->color = RGB(255, 255, 0); // yellow 25% - 49%
            }
        } else {
            this->color = RGB(0, 255, 0); // light green 50% - 99%
        }
    } else {
        this->color = RGB(0, 175, 0); // dark green 75% - 100%
    }
}
