#include "WindowClass.hpp"

using namespace std;

int WindowClass::CreateWindow()
{
	LoadDataFromCFG(CFGPath, &width, &height, &windowName);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	win = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
	if (win == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
}

int WindowClass::getWidth()
{
	return width;
}

int WindowClass::getHeight()
{
	return height;
}

GLFWwindow* WindowClass::GetGLFWWindow()
{
	return win;
}
