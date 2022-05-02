#include "cfgLoader.hpp"

using namespace std;

void LoadDataFromCFG(string filename, int* width, int* heigth, string* windowName)
{
	wifstream fileIn(filename.c_str());

	auto checkChar = fileIn.get();
	bool save = false;
	string data;
	string prop;

	if (fileIn)
	{
		cout << "CFG FOUND" << endl;
		cout << "loading CFG" << endl;
		while (fileIn)
		{
			if (checkChar == ':')
			{
				save = true;
			}	
			else if (checkChar == '\n') 
			{
				save = false; 
				
				if (prop == "width")
				{
					*width = stoi(data);
				}
				else if (prop == "height")
				{
					*heigth = stoi(data);
				}
				else if (prop == "windowName")
				{
					*windowName = data;
				}
				data.clear(); 
				prop.clear();
			}
			else if (save)
			{
				if (checkChar != ':' && checkChar != ' ')data.push_back(checkChar);
			}
			else
			{
				if (checkChar != ':' && checkChar != ' ')prop.push_back(checkChar);
			}
		
			checkChar = fileIn.get();
		}

		fileIn.close();
	}
	else
	{
		cout << "CFG NOT FOUND" << endl;
		cout << "Creating CFG" << endl;

		ofstream fileOut("config\\VideoConfig.cfg");
		fileOut <<
			"width: 1280\n"
			"height: 720\n"
			"windowName: OpenGL app\n";

		fileOut.close();

		*width = 1280;
		*heigth = 720;
		*windowName = "OpenGL app";
	}

	cout << "CFG data loaded" << endl;
}
