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

#define VertexShaderDir "shaders\\vertex\\"
#define FragmentShaderDir "shaders\\fragment\\"
#define PreloadCube "PreloadCube"

using namespace std;

class ModelClass
{
public:
	void loadPreloaded(string ModelName);
	void UpdatePreloaded(string ModelName);
	void RenderPreloaded(string ModelName);

	void loadShader();
	void CleanModels();

private:
	void loadPreloadedCube();
	void updatePreloadedCube();

protected:
	map<string, Model*> Models;
};

