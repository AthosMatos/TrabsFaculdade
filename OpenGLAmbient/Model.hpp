#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <glm.hpp>

using namespace std;

class Model
{
public:
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint vertexbuffer;
	GLuint indexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;
	GLuint LightID;
	GLuint VertexArrayID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	vector<glm::vec2> uvs; //texture mapping data
	vector<glm::vec3> vertices; //vertex mapping data
	vector<glm::vec3> normals; //normal mapping data

public:
	void Release();
};

