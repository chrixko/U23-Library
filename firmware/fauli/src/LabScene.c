#include <LabScene.h>
#include <Player.h>

LabScene* LabScene_Create()
{
	LabScene* ls = (LabScene*)malloc(sizeof(LabScene));
	ls->scene = Scene_Create();
	ls->scene->update = LabScene_Update;
	ls->scene->draw = LabScene_Draw;
	
	ls->firstPlayer = Player_Create();
}

void LabScene_Update()
{
	//Additional update code
}
