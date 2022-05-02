#include "ModelClass.hpp"


void ModelClass::loadPreloaded(string ModelName)
{
	if (ModelName == PreloadCube) loadPreloadedCube();
	else
	{
		cout << "Preloaded Model Not Found" << endl;
	}
}

void ModelClass::UpdatePreloaded(string ModelName)
{
	if (ModelName == PreloadCube) updatePreloadedCube();
	else
	{
		cout << "Preloaded Model Not Found" << endl;
	}
}

void ModelClass::loadShader()
{

}

void ModelClass::loadPreloadedCube()
{
	Model* tempM = new Model;

	glGenVertexArrays(1, &tempM->VertexArrayID);
	glBindVertexArray(tempM->VertexArrayID);

	// Create and compile our GLSL program from the shaders
	tempM->programID = LoadShaders(VertexShaderDir"TransformVertexShader.vertexshader", FragmentShaderDir"TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	tempM->MatrixID = glGetUniformLocation(tempM->programID, "MVP");

	// Load the texture
	//GLuint Texture = loadDDS("textures\\uvtemplate.DDS");
	tempM->Texture = loadAnyFile("textures\\rocktexture.png");
	// Get a handle for our "myTextureSampler" uniform
	tempM->TextureID = glGetUniformLocation(tempM->programID, "myTextureSampler");

	GLfloat g_vertex_buffer_data[] = 
	{
		// Front Face
		-1.0f, -1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		// Back Face
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 
		1.0f,  1.0f, 1.0f, 
		-1.0f,  1.0f, 1.0f, 

		// Top Face
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f,  1.0f, 
		1.0f, 1.0f,  1.0f, 
		1.0f, 1.0f, -1.0f,

		// Bottom Face
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 
		1.0f, -1.0f,  1.0f, 
		-1.0f, -1.0f,  1.0f, 

		// Left Face
		-1.0f, -1.0f,  1.0f, 
		-1.0f,  1.0f,  1.0f, 
		-1.0f,  1.0f, -1.0f, 
		-1.0f, -1.0f, -1.0f, 

		// Right Face
		1.0f, -1.0f, -1.0f, 
		1.0f,  1.0f, -1.0f, 
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f, 

	};

	GLint indices[] =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	GLfloat g_uv_buffer_data[] = 
	{
		// Front Face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f, 
		1.0f, 1.0f, 

		// Back Face
		1.0f, 1.0f,
		0.0f, 1.0f, 
		0.0f, 0.0f, 
		1.0f, 0.0f,

		// Top Face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f, 
		1.0f, 1.0f,

		// Bottom Face
		1.0f, 1.0f,
		0.0f, 1.0f, 
		0.0f, 0.0f,
		1.0f, 0.0f,

		// Left Face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		// Right Face
		0.0f, 1.0f, 
		0.0f, 0.0f, 
		1.0f, 0.0f, 
		1.0f, 1.0f, 
	};

	glGenBuffers(1, &tempM->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tempM->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &tempM->indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempM->indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &tempM->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tempM->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	Models.insert(pair<string, Model*>(PreloadCube, tempM));
}

void ModelClass::updatePreloadedCube()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(Models[PreloadCube]->programID);

	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(Models[PreloadCube]->MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Models[PreloadCube]->Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Models[PreloadCube]->TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Models[PreloadCube]->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Models[PreloadCube]->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_TRUE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
}

void ModelClass::RenderPreloaded(string ModelName)
{
	// Draw the triangles!
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void ModelClass::CleanModels()
{
	for (auto& v : Models)
	{
		v.second->Release();
	}
}


