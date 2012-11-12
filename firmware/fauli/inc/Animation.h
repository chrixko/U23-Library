#ifndef __ANIMATION_H__
#define __ANIMATION_H__

typedef struct
{
	char* name;

	int startIndex;
	int endIndex;
	
	int currentFrameIndex;
	
	int frameCountToNextFrame;
	int frameCounter;	
} Animation;

Animation* Animation_Create(char* name, int start, int end, int frameCountToNextFrame);
void Animation_Play(Animation* animation);
void Animation_Destroy(Animation* animation);
#endif
