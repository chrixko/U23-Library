#ifndef __UI_H__
#define __UI_H__

#include "Healthbar.h"

typedef struct {
    Healthbar* player1Healthbar;
    Healthbar* player2Healthbar;
} Ui;

Ui* Ui_Create(Entity* player1, Entity* player2);
void Ui_Draw(Ui* ui, Bitmap* surface);
void Ui_Update(Ui* ui);

#endif