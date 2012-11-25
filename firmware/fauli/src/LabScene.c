#include <LabScene.h>
#include <Player.h>
#include <Background_Lab.h>
#include <Healthpack.h>
#include <LaserCat.h>
#include <Constants.h>

LabScene* LabScene_Create()
{
	LabScene* ls = (LabScene*)malloc(sizeof(LabScene));
	ls->scene = Scene_Create(ls);
	ls->scene->init = LabScene_Init;
	ls->scene->update = LabScene_Update;
	ls->scene->draw = LabScene_Draw;
	
	ls->firstPlayer = Player_Create();
	
	return ls; //ARE YOU FUCKING KIDDING ME?
}

void LabScene_Init(void* labScene)
{
	LabScene* s = labScene;
	
	camera->posX = 0;
	camera->posY = 0;
	
	s->firstPlayer = Player_Create();
	s->ui = Ui_Create(s->firstPlayer->entity, NULL);
	Scene_AddEntity(s->scene, s->firstPlayer->entity);
	s->ui->storyboard = Storyboard_Create("Lorem ipsum dolor\n"
                                       "sit amet, consetetur\n"
                                       "sadipscing elitr,\n"
                                       "ed diam nonumy,\n"
                                       "\n"
                                       "press the A Button to continue...\n");
    s->ui->storyboard->next = Storyboard_Create("this is a second storyboard\n\n"
                                            "press the A Button to continue...\n");
	
	Healthpack* h = Healthpack_Create(COLLISION_TYPE_HEALTHPACK_ROBOT);
	h->entity->posX = 100;
	h->entity->posY = 80;
	Scene_AddEntity(s->scene, h->entity);

	LaserCat* lc = LaserCat_Create();
	lc->entity->posX = 200;
	lc->entity->posY = 120;
	Scene_AddEntity(s->scene, lc->entity);
	
	
	// Create Triggers 
	TriggerArea* t = TriggerArea_Create(LabScene_OnSpawnLaserCatsTrigger, NULL);
	t->entity->posX = SCREEN_WIDTH*0.5;
	Scene_AddEntity(s->scene, t->entity);
	
	t = TriggerArea_Create(LabScene_OnSpawnLaserCatsTrigger, NULL);
	t->entity->posX = SCREEN_WIDTH*1;
	Scene_AddEntity(s->scene, t->entity);
	
	t = TriggerArea_Create(LabScene_OnSpawnLaserCatsTrigger, NULL);
	t->entity->posX = SCREEN_WIDTH*2;
	Scene_AddEntity(s->scene, t->entity);
	
	t = TriggerArea_Create(LabScene_OnSpawnLaserCatsTrigger, NULL);
	t->entity->posX = SCREEN_WIDTH*3.5;
	Scene_AddEntity(s->scene, t->entity);
	
	t = TriggerArea_Create(LabScene_OnFinishTrigger, NULL);
	t->entity->posX = SCREEN_WIDTH*5;
	Scene_AddEntity(s->scene, t->entity);
}

void LabScene_Update(void* scene)
{
	LabScene* s = scene;
	
	if(!s->ui->storyboard)
	{
		s->scene->updateEntities = true;
	}
	else
	{
		s->scene->updateEntities = false;
	}
	
	Camera_FocusOnEntity(camera, s->firstPlayer->entity);
	Ui_Update(s->ui);
}

void LabScene_Draw(void* scene, Bitmap* surface)
{
	LabScene* s = scene;
	Ui_Draw(s->ui, surface);
}

void LabScene_Destroy(void* labScene) {
	LabScene* s = labScene;
	Ui_Destroy(s->ui);
}

void LabScene_OnSpawnLaserCatsTrigger(TriggerArea* trigger, Player* triggeringPlayer) {
    if (trigger->entity->destroyed) {
        return;
    }
    
    trigger->entity->destroyed = true;
    int minX = trigger->entity->posX + (SCREEN_WIDTH*0.25);
    int maxX = trigger->entity->posX + (SCREEN_WIDTH*0.75);
 
    int minY = FLOOR_HEIGHT;
    int maxY = SCREEN_HEIGHT - 5;
 
    unsigned int numberOfEnemies = randomInRange(1, 5);
    for (unsigned int i=0; i < numberOfEnemies; ++i) {
        LaserCat* cat = LaserCat_Create();
        cat->entity->posX = randomInRange(minX, maxX);
        cat->entity->posY = randomInRange(minY, maxY - cat->entity->height);
        Scene_AddEntity(currentScene, cat->entity);
    }
}

void LabScene_OnFinishTrigger(TriggerArea* trigger, Player* triggeringPlayer) {
    Storyboard* sb = Storyboard_Create("You Win!\nWe ran out of cats!\n\nPress A to play again...");
    sb->onClose = LabScene_OnFinishStorboardClosed;
    Ui_SetStoryboard(((LabScene*)currentScene->context)->ui, sb);
}

void LabScene_OnFinishStorboardClosed() {
    nextScene = LabScene_Create()->scene; // start a new game
}
