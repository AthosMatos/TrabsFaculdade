#include "SceneClass.hpp"

int SceneClass::Load()
{
	loadObjTest();

	//loadPreloaded(PreloadCube);
	return 1;
}

void SceneClass::Update()
{
	UpdateObjTest();
	//UpdatePreloaded(PreloadCube);
}

void SceneClass::Render()
{
	RenderObjTest();
	//RenderPreloaded(PreloadCube);
}

void SceneClass::Release()
{
	CleanModels();
}
