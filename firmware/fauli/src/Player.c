#include <Player.h>

#include <stdbool.h>

#include <game/Game.h>
#include <Constants.h>
#include <Animation.h>
#include <bilder.h>
#include "Bullet.h"

Player* Player_Create()
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
	
	player->currentAnimationIndex = 0;
	
	player->animations[0] = Animation_Create("walk_left", 0, 5, 10);
	player->animations[1] = Animation_Create("idle", 6, 11, 10);
	
	player->health = 100;
	
	player->weapon = Weapon_Create(player->entity);
	
	return player;	
}

void _Player_processInput(Player* player)
{
	//TODO: Decide by PlayerType wether to poll State1 or 2
	snes_button_state_t state = GetControllerState1();
	
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
	p->entity->vX = p->entity->vY = 0;
	
	_Player_processInput(p);
	
	if (p->weapon != NULL) {
	    Entity_Update(p->weapon->entity);
	}
	
	if((p->entity->vX != 0) || (p->entity->vY != 0))
	{
		p->currentAnimationIndex = 0;
	}
	else
	{
		p->currentAnimationIndex = 1;
	}
}

void Player_Shoot(Player* player) {
    if (player->weapon) {
        Weapon_Shoot(player->weapon);
    }
}

bool Player_Collision(void* context, void* otherEntity) {
    Player* this = context;
    Entity* other = otherEntity;
    
    if (other->collisionType == COLLISION_TYPE_BULLET_ENEMY) {
        this->entity->health -= ((Bullet*)other->context)->damage;
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
	Animation* anim = _Player_getCurrentAnimation(p);
	Animation_Play(anim);
	
	DrawRLEBitmap(surface, Sprite_Robo[anim->currentFrameIndex], p->entity->posX - camera->posX, p->entity->posY);	
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
