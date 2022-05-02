#include "App.hpp"

WindowClass* App::window;
Graphics* App::graphics;

int App::Init()
{
	window = new WindowClass;
	graphics = new Graphics;

	auto result = window->CreateWindow();
	if (result == -1 )return -1;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window->GetGLFWWindow(), GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window->GetGLFWWindow(), window->getWidth() / 2, window->getHeight() / 2);

	graphics->Init();

	return 1;
}

void App::Run()
{
	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window->GetGLFWWindow()) == 0)
	{
		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs(window->GetGLFWWindow());

		graphics->Update();
		graphics->Render();

		// Swap buffers
		glfwSwapBuffers(window->GetGLFWWindow());
		glfwPollEvents();
	}

	graphics->Release();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


