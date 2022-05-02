#pragma once
#include "ModelClass.hpp"

class SceneClass : protected ModelClass
{
public:
	int Load();
	void Update();
	void Render();
	void Release();

private:

};

