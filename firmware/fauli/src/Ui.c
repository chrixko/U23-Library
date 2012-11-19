
#include "Ui.h"

Ui* Ui_Create(Entity* player1, Entity* player2) {
    Ui* ui = malloc(sizeof(Ui));
    
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
    }
    
    if (this->player2Healthbar) {
        Entity_Draw(this->player2Healthbar->entity, surface);
    }
}

void Ui_Update(Ui* this) {
    if (this->player1Healthbar) {
        Entity_Update(this->player1Healthbar->entity);
    }
    
    if (this->player2Healthbar) {
        Entity_Update(this->player2Healthbar->entity);
    }
}