#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include "WindowClass.hpp"
#include "Graphics.hpp"

using namespace glm;

class App
{
public:
	int Init();
	void Run();

protected:
	static WindowClass* window;
	static Graphics* graphics;

};

