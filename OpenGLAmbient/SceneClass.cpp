#include "SceneClass.hpp"

int SceneClass::Load()
{
	loadPreloaded(PreloadCube);
	return 1;
}

void SceneClass::Update()
{
	UpdatePreloaded(PreloadCube);
}

void SceneClass::Render()
{

	RenderPreloaded(PreloadCube);
}

void SceneClass::Release()
{
	CleanModels();
}
