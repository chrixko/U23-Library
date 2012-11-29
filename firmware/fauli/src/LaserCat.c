#include "LaserCat.h"
#include "ExplosionEntity.h"

LaserCat* LaserCat_Create(Entity* target) {
    LaserCat* this = malloc(sizeof(LaserCat));
    this->entity = Entity_Create(this);
    
	this->entity->width = 46;
	this->entity->height = 34;	
	
	this->entity->update = LaserCat_Update;
	this->entity->draw = LaserCat_Draw;
	this->entity->destroy = LaserCat_Destroy;
	this->entity->collision = LaserCat_Collision;
	
    this->entity->collisionType = COLLISION_TYPE_ENEMY;
	this->entity->sceneCollision = true;
	
    this->animations[LASERCAT_ANIMATION_WALKING] = Animation_Create("walk_left", 0, 5, 10);
    this->animations[LASERCAT_ANIMATION_IDLE]    = Animation_Create("idle", 0, 0, 10);
    this->animations[LASERCAT_ANIMATION_DYING]	 = Animation_Create("dying", 6, 8, 10);
    
    this->currentAnimationIndex = LASERCAT_ANIMATION_IDLE;        
    this->target = target;
    this->targetPosX = this->targetPosY = 0;
    
    _LaserCat_CalculateTargetPosition(this);
    
    this->entity->health = 30;
    
    this->weapon = Weapon_Create(this->entity);
    this->weapon->bulletSpeedX = -2;
    this->weapon->cooldownTime = 100;
    
    this->dead = false;
    
    return this;
}

void _LaserCat_CalculateTargetPosition(LaserCat* this) {
	//NOT IN USE ATM
	//this->targetPosX = this->entity->posX + (randomInRange(0, 10) - 20);	
	this->targetPosX = this->entity->posX;
	this->targetPosY = this->target->posY + ((this->target->height / 2) - 10);
}

void LaserCat_Update(void* laserCat) {
    LaserCat* this = laserCat;
    
    if(this->dead) {
		return;
	}
    
    if (this->target) {
        if (this->target->destroyed) {
            this->target = NULL;
        }
        
       if (this->target->posY+(this->target->height/2) < this->entity->posY) {
            this->entity->vY = -1;
        } else if (this->target->posY+(this->target->height/2) > this->entity->posY) {
            this->entity->vY = 1;
        } else {
            this->entity->vY = 0;
        }	
		
        LaserCat_Shoot(this);
    } else {
        // search new target
        Vector* entities = Scene_GetEntities(currentScene);
        for (unsigned int i=0; i < entities->usedElements; ++i) {
	        Entity* it = Vector_Get(entities, i);
	        if (it != NULL && it != this->entity && it->collisionType == COLLISION_TYPE_PLAYER) {
	            this->target = it;
	            _LaserCat_CalculateTargetPosition(this);
	            break;
	        }
        }
	}
	
	if (this->entity->vY == 0 && this->entity->vX == 0) {
        this->currentAnimationIndex = LASERCAT_ANIMATION_IDLE;
	} else {
	    this->currentAnimationIndex = LASERCAT_ANIMATION_WALKING;
	}
	
	if (this->weapon) {
    	Entity_Update(this->weapon->entity);
	}
}

void LaserCat_Draw(void* laserCat, Bitmap* surface) {
    LaserCat* this = laserCat;    
    
    Animation* anim = this->animations[this->currentAnimationIndex];      
    if(this->currentAnimationIndex == LASERCAT_ANIMATION_DYING && anim->currentFrameIndex >= anim->endIndex)
    {
		this->entity->destroyed = true;
	}
    Animation_Play(anim);
                
    DrawRLEBitmap(surface, Sprite_LaserCat[anim->currentFrameIndex], this->entity->posX - camera->posX, this->entity->posY);
}

void LaserCat_Destroy(void* laserCat) {
    LaserCat* this = laserCat;
    Animation_Destroy(this->animations[0]);
    Animation_Destroy(this->animations[1]);
    Animation_Destroy(this->animations[2]);
    
    if (this->weapon) {
        Entity_Destroy(this->weapon->entity);
    }
    free(this);
}

void LaserCat_Shoot(LaserCat* this) {
    if (this->weapon) {
        Weapon_Shoot(this->weapon);
    }
}

void LaserCat_Die(LaserCat* this) {
	this->entity->vX = 0; 
	this->entity->vY = 0;
	this->dead = true;
	this->currentAnimationIndex = LASERCAT_ANIMATION_DYING;
}

bool LaserCat_Collision(void* laserCat, Entity* otherEntity) {
    LaserCat* this = laserCat;
    if (otherEntity->collisionType == COLLISION_TYPE_BULLET_PLAYER) {
		Bullet* b = otherEntity->context;
		
        this->entity->health -= b->damage;
        Bullet_Explode(b);
	        
        if(this->entity->health <= 0)
        {
			LaserCat_Die(this);
		}
                
        return true;
    }
    return false;
}
