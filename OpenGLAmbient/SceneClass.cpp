#include "SceneClass.hpp"

int SceneClass::Load()
{
	m = new ModelClass;
	m->loadModel("");
	
	//loadPreloaded(PreloadCube);
	return 1;
}

void SceneClass::Update()
{
	m->updateModel("");
	//UpdatePreloaded(PreloadCube);
}

void SceneClass::Render()
{
	m->renderModel("");
	//RenderPreloaded(PreloadCube);
}

void SceneClass::Release()
{
	m->CleanModels();
}
