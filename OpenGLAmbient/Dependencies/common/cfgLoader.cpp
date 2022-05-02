#include "cfgLoader.hpp"
#include <string>
#include <iostream>
#include <fstream>

void LoadDataFromCFG(std::string filename)
{
	std::wifstream fileIn(filename.c_str());

	if (fileIn)
	{
		while (fileIn)
		{

		}
		auto checkChar = fileIn.get();

		if (checkChar == 't')    //vt - vert tex coords
		{

		}
		fileIn.close();
	}
	else
	{

	}
}
