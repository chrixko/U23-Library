#ifndef __STORYBOARD_H__
#define __STORYBOARD_H__

#include <Entity.h>
#include <Animation.h>

typedef struct Storyboard Storyboard;
struct Storyboard
{
	Entity* entity;
	char* text;
	Storyboard* next;
	bool buttonDown;
	void (*onClose)();
};

Storyboard* Storyboard_Create(char* text);
void Storyboard_Draw(void* storyboard, Bitmap* surface);
void Storyboard_Update(void* storyboard);
void Storyboard_Destroy(void* storyboard);
#endif
