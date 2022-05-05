#pragma once
#include "ModelClass.hpp"

class SceneClass
{
public:
	int Load();
	void Update();
	void Render();
	void Release();

private:
	ModelClass* m;
};

