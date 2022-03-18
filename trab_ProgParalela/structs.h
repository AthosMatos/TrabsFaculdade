#pragma once
#include <vector>
#include <string>

using namespace std;

struct item
{
	int id;
	int valor;
	int peso;
};
struct individuo
{
	int pesoTotal = 0;
	int ValorTotal = 0;
	int id;
	vector <pair<int, bool>> items_Id_isActive;

};