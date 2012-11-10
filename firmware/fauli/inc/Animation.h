#ifndef __ANIMATION_H__
#define __ANIMATION_H__

struct Animation
{
	char* name;

	int startIndex;
	int endIndex;
	
	int currentFrameIndex;
	
	int frameCountToNextFrame;
	int frameCounter;	
};

struct Animation* Animation_Create(char* name, int start, int end, int frameCountToNextFrame);
void Animation_Play(struct Animation* animation);

void Animation_Destroy(struct Animation* animation);

#endif
