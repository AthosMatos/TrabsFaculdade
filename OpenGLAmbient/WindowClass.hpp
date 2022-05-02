#pragma once
#include <string>
#include <glew.h>
#include <glfw3.h>
#include "cfgLoader.hpp"

#define CFGPath "config\\VideoConfig.cfg"

class WindowClass
{
public:
	int CreateWindow();

public:
	int getWidth();
	int getHeight();
	GLFWwindow* GetGLFWWindow();

private:
	int width;
	int height;
	std::string windowName;
	GLFWwindow* win;

};

