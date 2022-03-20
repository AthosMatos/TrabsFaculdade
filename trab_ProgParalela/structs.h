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
	int geracao = 1;
	int pesoTotal = 0;
	int ValorTotal = 0;
	int id;
	vector <pair<int, bool>> Cromossomo;

};