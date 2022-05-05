#include "Graphics.hpp"

int Graphics::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Dark blue background
	glEnable(GL_DEPTH_TEST);	// Enable depth test
	glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one
	//glEnable(GL_CULL_FACE);	// Cull triangles which normal is not towards the camera

	scenes = new SceneClass;

	scenes->Load();

	return 1;
}

void Graphics::Update()
{
	scenes->Update();
}

void Graphics::Render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scenes->Render();
}

void Graphics::Release()
{
	scenes->Release();
}

/*

/// <summary>
		///     Reshapes the drawing are to maintain aspect ratio when the window is resized,
		///     using a target pixel ratio to maintain, and applying "pillars" or "letterbox"
		///     effect as needed, allowing the drawing context to shrink/grow uniformly.
		/// </summary>
		/// <param name="width">The new width of the window/drawing area to fit to.</param>
		/// <param name="height">The new height of the window/drawing area to fit to.</param>
		public void WindowReshape(int width, int height)
		{
			// Make the projection matrix active
			Gl.MatrixMode(MatrixMode.Projection);
			Gl.LoadIdentity();
			// The "Graphics" width and height contain the desired pixel resolution to keep.
			Gl.Ortho(0.0, Graphics.Width, Graphics.Height, 0.0, 1.0, -1.0);
			// Calculate the proper aspect ratio to use based on window ratio
			var ratioX = width / (float) Graphics.Width;
			var ratioY = height / (float) Graphics.Height;
			var ratio = ratioX < ratioY ? ratioX : ratioY;
			// Calculate the width and height that the will be rendered to
			var viewWidth = Convert.ToInt32(Graphics.Width * ratio);
			var viewHeight = Convert.ToInt32(Graphics.Height * ratio);
			// Calculate the position, which will apply proper "pillar" or "letterbox"
			var viewX = Convert.ToInt32((width - Graphics.Width * ratio) / 2);
			var viewY = Convert.ToInt32((height - Graphics.Height * ratio) / 2);
			// Apply the viewport and switch back to the GL_MODELVIEW matrix mode
			Gl.Viewport(viewX, viewY, viewWidth, viewHeight);
			Gl.MatrixMode(MatrixMode.Modelview);
			Gl.LoadIdentity();
		}

*/