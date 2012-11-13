#include <game/Game.h>
#include <game/Debug.h>
#include <game/Font.h>

#include <stdio.h>
#include <string.h>
#include <Constants.h>
#include <bilder.h>
#include <Entity.h>
#include <Player.h>
#include <Vector.h>

void Init(struct Gamestate*);
void Update(uint32_t);
void Draw(Bitmap *);

Gamestate InitState = { Init, NULL, NULL, Update, Draw };
Game* TheGame = &(Game) {&InitState};

Player* player;
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

void Init(struct Gamestate* state) 
{
	camera = Camera_Create(0,0);
	player = Player_Create();
	Game_AddEntity(player->entity);
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
}

void Draw(Bitmap* surface)
{
	DrawRLEBitmap(surface, &bg_lab, camera->posX * -1, 0);
	
	for (unsigned int i=0; i < entities.usedElements; ++i) {
	    Entity* it = Vector_Get(&entities, i);
	    if (it != NULL) {
    	    Entity_Draw(it, surface);
	    }
	}
}
