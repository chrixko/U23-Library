#include <Player.h>

#include <stdbool.h>

#include <game/Game.h>
#include <Constants.h>
#include <Animation.h>
#include "Bullet.h"
#include "Healthpack.h"
#include "Sprite_Robo.h"
#include "Sprite_Prof.h"

Player* Player_Create(int PlayerID)
{
	Player* player = (Player*)malloc(sizeof(Player));
	
	player->entity = Entity_Create(player);
	player->entity->posY = 80;
	
	player->entity->width = 47;
	player->entity->height = 71;	
	
	player->entity->update = Player_Update;
	player->entity->draw = Player_Draw;
	player->entity->destroy = Player_Destroy;
	player->entity->collision = Player_Collision;
	
	player->entity->collisionType = COLLISION_TYPE_PLAYER;
	player->entity->sceneCollision = true;
	player->ID = PlayerID;
	
	if (player->ID == 1)
	{		
		player->entity->width = 40;
		player->entity->height = 65;	
		player->animations[PLAYER_ANIMATION_WALKING] = Animation_Create("walk_left", 0, 5, 10);
		player->animations[PLAYER_ANIMATION_IDLE]    = Animation_Create("idle", 6, 11, 10);
	}
	else
	{
		player->entity->width = 35;
		player->entity->height = 65;		
		player->animations[PLAYER_ANIMATION_WALKING] = Animation_Create("walk_left", 4, 9, 10);
		player->animations[PLAYER_ANIMATION_IDLE]    = Animation_Create("idle", 0, 3, 10);
	}


	player->currentAnimationIndex = PLAYER_ANIMATION_IDLE;	
	
	player->weapon = Weapon_Create(player->entity);
	
	player->weapon->offsetX = player->entity->width;
	player->weapon->offsetY = (player->entity->height / 2) - 10;
	
	return player;	
}

void _Player_processInput(Player* player)
{
	snes_button_state_t state;
	if (player->ID == 1)
	{
		state = GetControllerState1();	
	}
	else
	{
		state = GetControllerState2();
	}
	
	
	if(state.buttons.Up)
	{
		player->entity->vY = -1;
	}
	
	if(state.buttons.Down)
	{
		player->entity->vY = 1;	
	}
	
	if(state.buttons.Left)
	{
		player->entity->vX = -1;	
	}
	
	if(state.buttons.Right)
	{
		player->entity->vX = 1;
	}			
	
	if(state.buttons.L) {
	    Weapon_Rotate(player->weapon, -0.1);
	}
	
	if(state.buttons.R) {
	    Weapon_Rotate(player->weapon, 0.1);
	}
	
	if(state.buttons.A) {
	    Player_Shoot(player);
	}
	
	if(state.buttons.X) {
	    if (player->entity->health < player->entity->maxHealth) {
    	    player->entity->health += 1;
	    }
	}
	
	if(state.buttons.Y) {
	    if (player->entity->health > 0) {
    	    player->entity->health -= 1;
	    }
	}
}

void Player_Update(void* player)
{	
	Player* p = player;
	
	snes_button_state_t state;
	if (p->ID == 1)
	{
		state = GetControllerState1();	
	}
	else
	{
		state = GetControllerState2();
	}
	
	if(state.buttons.Start)
	{
		p->entity->health = 100;
	}
	
	if(p->entity->health >= 0)
	{
		p->entity->vX = p->entity->vY = 0;
		
		
		_Player_processInput(p);
		
		if (p->weapon != NULL) {
			Entity_Update(p->weapon->entity);
		}
		
		if(p->entity->vX == 0 && p->entity->vY == 0)
		{
			p->currentAnimationIndex = PLAYER_ANIMATION_IDLE;
		}
		else
		{
			p->currentAnimationIndex = PLAYER_ANIMATION_WALKING;
		}		
	}
	else
	{
		p->entity->vX = p->entity->vY = 0;
	}
}

void Player_Shoot(Player* player) {
    if (player->weapon) {
        Weapon_Shoot(player->weapon);
    }
}

bool Player_Collision(void* context, Entity* other) {
    Player* this = context;
	
	if(this->entity->health >= 0)
	{
		switch (other->collisionType) {
			case COLLISION_TYPE_BULLET_ENEMY: {
				Bullet* b = other->context;
				this->entity->health -= b->damage;
				Bullet_Explode(b);
						
				break;
			}
			case COLLISION_TYPE_HEALTHPACK_ROBOT: {
				Entity_ModifyHealth(this->entity, ((Healthpack*)other->context)->healthBonus);
				other->destroyed = true;
				break;
			}
		}		
	}	
		    
    return false;
}

Animation* _Player_getCurrentAnimation(Player* player)
{
	return player->animations[player->currentAnimationIndex];
}

void Player_Draw(void* player, Bitmap* surface)
{
	Player* p = player;
	
	if(p->entity->health >= 0)
	{
		Animation* anim = _Player_getCurrentAnimation(p);
		Animation_Play(anim);
		if (p->ID == 1)
		{
			DrawRLEBitmap(surface, Sprite_Robo[anim->currentFrameIndex], p->entity->posX - camera->posX, p->entity->posY);
		}
		else
		{
			DrawRLEBitmap(surface, Sprite_Prof[anim->currentFrameIndex], p->entity->posX - camera->posX, p->entity->posY);
		}		
	}	
}

void Player_Destroy(void* player)
{
    Player* p = player;
	Animation_Destroy(p->animations[0]);
	Animation_Destroy(p->animations[1]);
    if (p->weapon) {
    	Entity_Destroy(p->weapon->entity);
	}
	
	free(p);
}
