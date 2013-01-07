#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <Camera.h>
#include <Scene.h>
#include "Utils.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define FLOOR_HEIGHT 80 + 5

#define HEALTHBAR_HEIGHT 12
#define HEALTHBAR_WIDTH 35

#define COLLISION_TYPE_NONE 0
#define COLLISION_TYPE_PLAYER 1
#define COLLISION_TYPE_BULLET_PLAYER 2
#define COLLISION_TYPE_BULLET_ENEMY 3
#define COLLISION_TYPE_ENEMY  4
#define COLLISION_TYPE_HEALTHPACK_HUMAN 5
#define COLLISION_TYPE_HEALTHPACK_ROBOT 6
Camera* camera;
Scene* currentScene;
Scene* nextScene;

#endif
