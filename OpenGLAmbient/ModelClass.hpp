#pragma once
#include <string>
#include <map>
#include "Model.hpp"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <vector>
#include <objloader.hpp>

#define VertexShaderDir "shaders\\vertex\\"
#define FragmentShaderDir "shaders\\fragment\\"
#define PreloadCube "PreloadCube"

using namespace std;

class ModelClass
{
public:
	void loadModel(string ModelName);
	void loadModel(string ModelName, string objPath, string texture);
	//void loadFromObj(string ModelName);
	//void loadObjTest();
	void updateModel(string ModelName, int size, glm::vec3 translate, glm::vec3 scale);
	//void UpdatePreloaded(string ModelName);
	void renderModel(string ModelName);
	//void RenderPreloaded(string ModelName);

	void loadShader();
	void CleanModels();

private:
	void loadObj(string ModelName);
	void loadObj(string ModelName, string objPath, string texture);
	void UpdateObj(string ModelName, int size, glm::vec3 translate, glm::vec3 scale);
	void RenderObj(string ModelName);
	void loadPreloadedCube();
	void updatePreloadedCube();
	void UpdatePreloaded(string ModelName);
	void RenderPreloaded();

protected:
	map<string, Model*> Models;
};

