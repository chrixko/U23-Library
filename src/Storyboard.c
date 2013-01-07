#include <Storyboard.h>

#include <stdbool.h>
#include <game/Game.h>
#include <Constants.h>
#include <Animation.h>
#include <Entity.h>
#include <game/Font.h>
#include <Fonts.h>
#include "Storyboard_Back.h"


Storyboard* Storyboard_Create(char* text)
{
	Storyboard* storyboard = (Storyboard*)malloc(sizeof(Storyboard));
	
	storyboard->entity = Entity_Create(storyboard);
	storyboard->entity->posY = 0;
	storyboard->entity->posX = 0;
	
	storyboard->entity->width = 320;
	storyboard->entity->height = 100;	
	
	storyboard->entity->update = Storyboard_Update;
	storyboard->entity->draw = Storyboard_Draw;
	storyboard->entity->destroy = Storyboard_Destroy;
	storyboard->text = text;
	storyboard->next = NULL;
	storyboard->buttonDown = false;
	
	storyboard->onClose = NULL;
	
	return storyboard;	
}





void Storyboard_Update(void* storyboard)
{	
	Storyboard* this = storyboard;

    snes_button_state_t controller1 = GetControllerState1();
    snes_button_state_t controller2 = GetControllerState2();
    
    if (this->buttonDown) {
        if (!controller1.buttons.A && !controller2.buttons.A) {
            this->entity->destroyed = true;
            this->buttonDown = false;
        }
    } else {
        if (controller1.buttons.A || controller2.buttons.A) {
            this->buttonDown = true;
        }
    }
}




void Storyboard_Draw(void* storyboard, Bitmap* surface)
{
	Storyboard* this = storyboard;
	extern const RLEBitmap storyboard_back;
	DrawRLEBitmap(surface, &Storyboard_Back, this->entity->posX, this->entity->posY);
	//setFont(Font_White16x16);
	setFont(Font_White7x7);
	DrawText(surface, this->text, this->entity->posX + 10, this->entity->posY + 10);
	
	

}

void Storyboard_Destroy(void* storyboard)
{
    Storyboard* s = storyboard;
    if (s->onClose) {
        s->onClose();
    }
	free(s);
}
