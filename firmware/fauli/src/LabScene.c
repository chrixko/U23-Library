#include <LabScene.h>

LabScene* LabScene_Create()
{
	LabScene* ls = (LabScene*)malloc(sizeof(LabScene));
	ls->scene = Scene_Create();
	ls->scene->update = LabScene_Update;
	ls->scene->draw = LabScene_Draw;
}

void LabScene_Update()
{
	//Additional update code
}
