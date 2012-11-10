#include <Animation.h>
#include <stdlib.h>

struct Animation* Animation_Create(char* name, int start, int end, int frameCountToNextFrame)
{
	struct Animation* anim = (struct Animation*)malloc(sizeof(struct Animation));
	anim->name = name;
	anim->startIndex = start;
	anim->endIndex = end;
	anim->currentFrameIndex = 0;
	anim->frameCountToNextFrame = frameCountToNextFrame;
	anim-> frameCounter = 0;
	
	return anim;
}

void Animation_Play(struct Animation* animation)
{
	if(animation->frameCounter >= animation->frameCountToNextFrame)
	{
		animation->frameCounter = 0;
		animation->currentFrameIndex++;	
		
		if(animation->currentFrameIndex > animation->endIndex)
		{
			animation->currentFrameIndex = animation->startIndex;
		}
	}
	else
	{
		animation->frameCounter++;
	}
}

void Animation_Destroy(struct Animation* animation)
{
	free(animation);
}
