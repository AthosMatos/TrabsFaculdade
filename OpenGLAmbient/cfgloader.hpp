#ifndef CFGLOADER_HPP
#define CFGLOADER_HPP

#include <string>
#include <iostream>
#include <fstream>

void LoadDataFromCFG(std::string filename, int* width, int* heigth, std::string* windowName);

#endif