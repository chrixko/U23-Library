#include <Animation.h>
#include <stdlib.h>

Animation* Animation_Create(char* name, int start, int end, int frameCountToNextFrame)
{
	Animation* anim = (Animation*)malloc(sizeof(Animation));
	anim->name = name;
	anim->startIndex = start;
	anim->endIndex = end;
	anim->currentFrameIndex = 0;
	anim->frameCountToNextFrame = frameCountToNextFrame;
	anim-> frameCounter = 0;
	
	return anim;
}

void Animation_Play(Animation* animation)
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

void Animation_Destroy(Animation* animation)
{
	free(animation);
}
