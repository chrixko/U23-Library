#include <game/Game.h>
#include <game/Debug.h>
#include <game/Font.h>

#include <stdio.h>
#include <string.h>
#include <Constants.h>
#include <Entity.h>
#include <Player.h>
#include <Vector.h>
#include <Storyboard.h>
#include "Background_Lab.h"
#include "Ui.h"
#include "Healthpack.h"

void Init(struct Gamestate*);
void Update(uint32_t);
void Draw(Bitmap *);

Gamestate InitState = { Init, NULL, NULL, Update, Draw };
Game* TheGame = &(Game) {&InitState};

Storyboard* storyboard;
Player* player;
Ui* ui;
Vector entities;

void Game_AddEntity(Entity* entity) {
    bool inserted = false;
	for (unsigned int i=0; i < entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&entities, i);
	    if (it == NULL) {
            Vector_Set(&entities, i, entity);
            inserted = true;
            break;
	    }
    }
    
    if (!inserted) {
        Vector_AddElement(&entities, entity);    
    }
}

Vector* Game_GetEntities() {
    return &entities;
}

void Init(struct Gamestate* state)
{
	camera = Camera_Create(0,0);
	player = Player_Create();
	ui = Ui_Create(player->entity, NULL);
	Game_AddEntity(player->entity);
	storyboard = Storyboard_Create();
	Game_AddEntity(storyboard->entity);

	Healthpack* h = Healthpack_Create(COLLISION_TYPE_HEALTHPACK_ROBOT);
	h->entity->posX = 20;
	h->entity->posY = 100;
	Game_AddEntity(h->entity);
}

void Update(uint32_t tick) 
{
	for (unsigned int i=0; i < entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&entities, i);
	    if (it != NULL) {
	        if (it->destroyed) {
    	        Entity_Destroy(it);
	            Vector_Set(&entities, i, NULL);
	        } else {
    	        Entity_Update(it);
	        }
	    }
	}
	Camera_FocusOnEntity(camera, player->entity);
	Ui_Update(ui);
}

void Draw(Bitmap* surface)
{
	DrawRLEBitmap(surface, &Background_Lab, camera->posX * -1, 0);
	
	for (unsigned int i=0; i < entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&entities, i);
	    if (it != NULL) {
    	    Entity_Draw(it, surface);
	    }
	}
	Ui_Draw(ui, surface);
}
