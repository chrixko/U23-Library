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
	
	return storyboard;	

}





void Storyboard_Update(void* player)
{	
	
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
	
	
	free(s);
}
