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
	
	camera = Camera_Create(0,0);
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
