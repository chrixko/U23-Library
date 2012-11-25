#ifndef __UI_H__
#define __UI_H__

#include "Healthbar.h"
#include "Storyboard.h"

typedef struct {
    Healthbar* player1Healthbar;
    Healthbar* player2Healthbar;
    Storyboard* storyboard;
} Ui;

Ui* Ui_Create(Entity* player1, Entity* player2);
void Ui_Draw(Ui* ui, Bitmap* surface);
void Ui_Update(Ui* ui);
/// set ui->storyboard and make sure existing storyboards are destroyed
void Ui_SetStoryboard(Ui* this, Storyboard* storyboard);

#endif
