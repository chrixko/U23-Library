#ifndef __STORYBOARD_H__
#define __STORYBOARD_H__

#include <Entity.h>
#include <Animation.h>

typedef struct
{
	Entity* entity;
	char* text;
	
} Storyboard;

Storyboard* Storyboard_Create();
void Storyboard_Draw(void* storyboard, Bitmap* surface);
void Storyboard_Update(void* storyboard);
void Storyboard_Destroy(void* storyboard);
#endif
