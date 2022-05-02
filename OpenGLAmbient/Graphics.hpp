#pragma once
#include <glew.h>
#include <glfw3.h>
#include "SceneClass.hpp"

class Graphics 
{
public:

	int Init();
	void Update();
	void Render();
	void Release();

private:
	SceneClass* scenes;
};

