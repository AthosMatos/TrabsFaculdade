#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "Item.hpp"

using namespace std;

class Itens
{
public:
	void SetItens(string filename);
	vector<Item*> GetVector();
	void release();

public:
	static vector<Item*> itens;

	static int pesoMax; //peso max suportado

	static int valorOtimo; //valor otimo desejado
	static int PesoOtimo; //peso otimo desejado

	friend class GodController;

};

