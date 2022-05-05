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

class ModelClass : public Model
{
public:
	void loadModel(string ModelName);
	//void loadFromObj(string ModelName);
	//void loadObjTest();
	void updateModel(string ModelName);
	//void UpdatePreloaded(string ModelName);
	void renderModel(string ModelName);
	//void RenderPreloaded(string ModelName);

	void loadShader();
	void CleanModels();

private:
	void loadObj();
	void UpdateObj();
	void RenderObj();
	void loadPreloadedCube();
	void updatePreloadedCube();
	void UpdatePreloaded(string ModelName);
	void RenderPreloaded(string ModelName);

protected:
	map<string, Model*> Models;
};

