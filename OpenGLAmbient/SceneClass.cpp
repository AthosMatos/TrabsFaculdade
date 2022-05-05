#include "SceneClass.hpp"

int SceneClass::Load()
{
	m = new ModelClass;
	m->loadModel("1", "table.obj","textures\\rocktexture.png");
	m->loadModel("2", "cube.obj", "textures\\tiles.jpg");
	m->loadModel("3", "legoobj.obj", "textures\\texture.png");
	m->loadModel("4", "cube.obj", "textures\\rocktexture.png");
	//m->loadModel(PreloadCube);
	return 1;
}

void SceneClass::Update()
{
	auto size = 0.04f;
	auto size2 = 5.0f;
	auto size3 = 0.7f;
	m->updateModel("1", size, glm::vec3(0.0f, -100.0f, 0.0f), glm::vec3(1.0f * size, 1.0f * size, 1.0f * size));

	m->updateModel("2", size2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f * size2, 1.0f * size2, 1.0f * size2));
	m->updateModel("3", size, glm::vec3(-20.0f, -65.0f, 0.0f), glm::vec3(1.0f * size, 1.0f * size, 1.0f * size));
	m->updateModel("4", size3, glm::vec3(0.0f, -2.5f, -3.0f), glm::vec3(1.0f * size3, 1.0f * size3, 1.0f * size3));
	//m->updateModel(PreloadCube, 0, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
}

void SceneClass::Render()
{
	m->renderModel("1");
	m->renderModel("2");
	m->renderModel("3");
	m->renderModel("4");
	//m->renderModel(PreloadCube);
}

void SceneClass::Release()
{
	m->CleanModels();
}
