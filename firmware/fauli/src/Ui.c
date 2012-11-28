#include "Ui.h"


Ui* Ui_Create(Entity* player1, Entity* player2) {
    Ui* ui = malloc(sizeof(Ui));
    ui->storyboard = NULL;
    
    if (player1) {
        ui->player1Healthbar = Healthbar_Create(player1);
        ui->player1Healthbar->entity->posX = 4;
        ui->player1Healthbar->entity->posY = SCREEN_HEIGHT - HEALTHBAR_HEIGHT - 4;
    } else {
        ui->player1Healthbar = NULL;
    }
    
    if (player2) {
        ui->player2Healthbar = Healthbar_Create(player2);
        ui->player2Healthbar->entity->posX = 4;
        ui->player2Healthbar->entity->posY = SCREEN_HEIGHT - (HEALTHBAR_HEIGHT*2) - 8;
    } else {
        ui->player2Healthbar = NULL;
    }
    return ui;
}

void Ui_Draw(Ui* this, Bitmap* surface) {
    if (this->player1Healthbar) {
        Entity_Draw(this->player1Healthbar->entity, surface);
        DrawRLEBitmap(surface, &HealthbarIcon_Robo, this->player1Healthbar->entity->posX, this->player1Healthbar->entity->posY);
    }
    
    if (this->player2Healthbar) {
        Entity_Draw(this->player2Healthbar->entity, surface);
        DrawRLEBitmap(surface, &HealthbarIcon_Prof, this->player2Healthbar->entity->posX, this->player2Healthbar->entity->posY);
    }
    
    if (this->storyboard) {
        Entity_Draw(this->storyboard->entity, surface);
    }
}

void Ui_Update(Ui* this) {
    if (this->player1Healthbar) {
        Entity_Update(this->player1Healthbar->entity);
    }
    
    if (this->player2Healthbar) {
        Entity_Update(this->player2Healthbar->entity);
    }
    
    if (this->storyboard) {
        if (this->storyboard->entity->destroyed) {
            Storyboard* lastStoryboard = this->storyboard;
            if (lastStoryboard->next) {
                this->storyboard = lastStoryboard->next;
            } else {
                this->storyboard = NULL;
            }
            Entity_Destroy(lastStoryboard->entity);  
        } else {
            Entity_Update(this->storyboard->entity);
        }
    }
}

void Ui_Destroy(Ui* this) {
    if (this->player1Healthbar) {
        Entity_Destroy(this->player1Healthbar->entity);
    }
    
    if (this->player2Healthbar) {
        Entity_Destroy(this->player2Healthbar->entity);
    }
    
    if (this->storyboard) {
        Entity_Destroy(this->storyboard->entity);
    }
    free (this);
}

void Ui_SetStoryboard(Ui* this, Storyboard* storyboard) {
    if (this->storyboard) {
        Entity_Destroy(this->storyboard->entity);
    }
    this->storyboard = storyboard;
}
