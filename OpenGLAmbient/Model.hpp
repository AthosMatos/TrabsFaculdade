#pragma once
#include <glew.h>
#include <glfw3.h>

class Model
{
public:
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint vertexbuffer;
	GLuint indexbuffer;
	GLuint uvbuffer;
	GLuint VertexArrayID;
	static GLfloat g_uv_buffer_data[]; //texture mapping data
	static GLfloat g_vertex_buffer_data[]; //vertex mapping data

public:
	void Release();
};

