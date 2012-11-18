#include <Storyboard.h>

#include <stdbool.h>

#include <game/Game.h>
#include <Constants.h>
#include <Animation.h>
#include <bilder.h>
#include <Entity.h>
#include <game/Font.h>
#include <Fonts.h>


Storyboard* Storyboard_Create()
{
	Storyboard* storyboard = (Storyboard*)malloc(sizeof(Storyboard));
	
	storyboard->entity = Entity_Create(storyboard);
	storyboard->entity->posY = 10;
	storyboard->entity->posX = 10;
	
	storyboard->entity->width = 200;
	storyboard->entity->height = 200;	
	
	storyboard->entity->update = Storyboard_Update;
	storyboard->entity->draw = Storyboard_Draw;
	storyboard->entity->destroy = Storyboard_Destroy;
	storyboard->text = "Lorem ipsum dolor\nsit amet, consetetur\nsadipscing elitr,\ned diam nonumy,\n";
	
	return storyboard;	

}





void Storyboard_Update(void* player)
{	
	
}




void Storyboard_Draw(void* storyboard, Bitmap* surface)
{
	Storyboard* s = storyboard;
	extern const RLEBitmap storyboard_back;
	DrawRLEBitmap(surface, &storyboard_back, 0, 0);
	//setFont(Font_White16x16);
	setFont(Font_White7x7);
	DrawText(surface, s-> text, 0,20);
	
	

}

void Storyboard_Destroy(void* storyboard)
{
    Storyboard* s = storyboard;
	
	
	free(s);
}
