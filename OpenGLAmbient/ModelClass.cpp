#include "ModelClass.hpp"


void ModelClass::loadModel(string ModelName)
{
	if (ModelName == PreloadCube) loadPreloadedCube();
	else
	{
		//cout << "Preloaded Model Not Found" << endl;
		loadObj(ModelName);
	}
}

void ModelClass::loadModel(string ModelName, string objPath , string texture)
{
	if (ModelName == PreloadCube) loadPreloadedCube();
	else
	{
		//cout << "Preloaded Model Not Found" << endl;
		loadObj(ModelName, objPath, texture);
	}
}

void ModelClass::updateModel(string ModelName, int size, glm::vec3 translate, glm::vec3 scale)
{
	if (ModelName == PreloadCube) updatePreloadedCube();
	else
	{
		//cout << "Preloaded Model Not Found" << endl;
		UpdateObj(ModelName, size, translate, scale);
	}
}

void ModelClass::renderModel(string ModelName)
{
	if (ModelName == PreloadCube) RenderPreloaded();
	else
	{
		//cout << "Preloaded Model Not Found" << endl;
		RenderObj(ModelName);
	}
}


void ModelClass::loadObj(string ModelName)
{
	Model* tempM = new Model;

	glGenVertexArrays(1, &tempM->VertexArrayID);

	// Create and compile our GLSL program from the shaders
	tempM->programID = LoadShaders(VertexShaderDir"StandardShading.vertexshader", FragmentShaderDir"StandardShading.fragmentshader");

	// Get a handle for our "MVP" uniform
	tempM->MatrixID = glGetUniformLocation(tempM->programID, "MVP");
	tempM->ViewMatrixID = glGetUniformLocation(tempM->programID, "V");
	tempM->ModelMatrixID = glGetUniformLocation(tempM->programID, "M");

	// Load the texture
	tempM->Texture = loadDDS("uvmap.DDS");

	//Texture = loadAnyFile("concreto.png");
	// Get a handle for our "myTextureSampler" uniform
	tempM->TextureID = glGetUniformLocation(tempM->programID, "myTextureSampler");

	// Read our .obj file
	//vector<glm::vec3> vertices;
	//bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);
	//bool res = loadOBJ("cube.obj", vertices, uvs, normals);
	//bool res = loadOBJ("12140_Skull_v3_L2.obj", vertices, uvs, normals);
	bool res = loadOBJ("legoobj.obj", tempM->vertices, tempM->uvs, tempM->normals);
	// Load it into a VBO

	glGenBuffers(1, &tempM->vertexbuffer);


	glGenBuffers(1, &tempM->uvbuffer);

	
	glGenBuffers(1, &tempM->normalbuffer);
	

	// Get a handle for our "LightPosition" uniform
	glUseProgram(tempM->programID);
	tempM->LightID = glGetUniformLocation(tempM->programID, "LightPosition_worldspace");

	Models.insert(pair<string, Model*>(ModelName, tempM));
}

void ModelClass::loadObj(string ModelName, string objPath,string texturePath)
{
	Model* tempM = new Model;

	glGenVertexArrays(1, &tempM->VertexArrayID);

	// Create and compile our GLSL program from the shaders
	tempM->programID = LoadShaders(VertexShaderDir"StandardShading.vertexshader", FragmentShaderDir"StandardShading.fragmentshader");

	// Get a handle for our "MVP" uniform
	tempM->MatrixID = glGetUniformLocation(tempM->programID, "MVP");
	tempM->ViewMatrixID = glGetUniformLocation(tempM->programID, "V");
	tempM->ModelMatrixID = glGetUniformLocation(tempM->programID, "M");

	// Load the texture
	//tempM->Texture = loadDDS("uvmap.DDS");
	tempM->Texture = loadAnyFile(texturePath.c_str());
	//Texture = loadAnyFile("concreto.png");
	// Get a handle for our "myTextureSampler" uniform
	tempM->TextureID = glGetUniformLocation(tempM->programID, "myTextureSampler");

	// Read our .obj file
	//vector<glm::vec3> vertices;
	//bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);
	//bool res = loadOBJ("cube.obj", vertices, uvs, normals);
	//bool res = loadOBJ("12140_Skull_v3_L2.obj", vertices, uvs, normals);
	bool res = loadOBJ(objPath.c_str(), tempM->vertices, tempM->uvs, tempM->normals);
	//bool res = loadObj2(objPath.c_str(), false, false, tempM->vertices, tempM->uvs, tempM->normals);
	// Load it into a VBO

	glGenBuffers(1, &tempM->vertexbuffer);


	glGenBuffers(1, &tempM->uvbuffer);


	glGenBuffers(1, &tempM->normalbuffer);


	// Get a handle for our "LightPosition" uniform
	glUseProgram(tempM->programID);
	tempM->LightID = glGetUniformLocation(tempM->programID, "LightPosition_worldspace");

	Models.insert(pair<string, Model*>(ModelName, tempM));
}

void ModelClass::UpdateObj(string ModelName, int size, glm::vec3 translate, glm::vec3 scale)
{
	Models[ModelName]->size = size;

	Models[ModelName]->scale = scale;
	Models[ModelName]->translate = translate;

	Models[ModelName]->ProjectionMatrix = getProjectionMatrix();
	Models[ModelName]->ViewMatrix = getViewMatrix();
	Models[ModelName]->ModelMatrix = glm::mat4();
	Models[ModelName]->ModelMatrix = glm::scale(Models[ModelName]->ModelMatrix, Models[ModelName]->scale);
	Models[ModelName]->ModelMatrix = glm::translate(Models[ModelName]->ModelMatrix, Models[ModelName]->translate);
	Models[ModelName]->MVP = Models[ModelName]->ProjectionMatrix * Models[ModelName]->ViewMatrix * Models[ModelName]->ModelMatrix;
}

void ModelClass::UpdatePreloaded(string ModelName)
{
	if (ModelName == PreloadCube) updatePreloadedCube();
	else
	{
		cout << "Preloaded Model Not Found" << endl;
	}
}

void ModelClass::RenderObj(string ModelName)
{
	glBindVertexArray(Models[ModelName]->VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, Models[ModelName]->vertices.size() * sizeof(glm::vec3), &Models[ModelName]->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, Models[ModelName]->uvs.size() * sizeof(glm::vec2), &Models[ModelName]->uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, Models[ModelName]->normals.size() * sizeof(glm::vec3), &Models[ModelName]->normals[0], GL_STATIC_DRAW);

	// Use our shader
	glUseProgram(Models[ModelName]->programID);


	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(Models[ModelName]->MatrixID, 1, GL_FALSE, &Models[ModelName]->MVP[0][0]);
	glUniformMatrix4fv(Models[ModelName]->ModelMatrixID, 1, GL_FALSE, &Models[ModelName]->ModelMatrix[0][0]);
	glUniformMatrix4fv(Models[ModelName]->ViewMatrixID, 1, GL_FALSE, &Models[ModelName]->ViewMatrix[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 2, 0);
	glUniform3f(Models[ModelName]->LightID, lightPos.x, lightPos.y, lightPos.z);


	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Models[ModelName]->Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Models[ModelName]->TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, Models[ModelName]->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, Models[ModelName]->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void ModelClass::loadShader()
{

}

void ModelClass::loadPreloadedCube()
{
	Model* tempM = new Model;

	glGenVertexArrays(1, &tempM->VertexArrayID);
	
	// Create and compile our GLSL program from the shaders
	tempM->programID = LoadShaders(VertexShaderDir"TransformVertexShader.vertexshader", FragmentShaderDir"TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	tempM->MatrixID = glGetUniformLocation(tempM->programID, "MVP");

	// Load the texture
	//GLuint Texture = loadDDS("textures\\uvtemplate.DDS");
	tempM->Texture = loadAnyFile("textures\\tiles.jpg");
	// Get a handle for our "myTextureSampler" uniform
	tempM->TextureID = glGetUniformLocation(tempM->programID, "myTextureSampler");
	glGenBuffers(1, &tempM->vertexbuffer);
	glGenBuffers(1, &tempM->indexbuffer);
	glGenBuffers(1, &tempM->uvbuffer);
	Models.insert(pair<string, Model*>(PreloadCube, tempM));
}

void ModelClass::updatePreloadedCube()
{
	
}

void ModelClass::RenderPreloaded()
{

	glBindVertexArray(Models[PreloadCube]->VertexArrayID);

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


	glBindBuffer(GL_ARRAY_BUFFER, Models[PreloadCube]->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Models[PreloadCube]->indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, Models[PreloadCube]->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// Use our shader
	glUseProgram(Models[PreloadCube]->programID);

	float size = 4.0f;

	glm::vec3 scale = glm::vec3(1.0f * size, 1.0f * size, 1.0f * size);
	glm::vec3 translate = glm::vec3(0.0f, 0.0f , 0.5f );

	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::scale(ModelMatrix, scale);
	ModelMatrix = glm::translate(ModelMatrix, translate);
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


