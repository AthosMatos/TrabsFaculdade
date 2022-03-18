#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "structs.h"

using namespace std;

class Mochila
{
public:
	Mochila(int capacidadeMAX, int valorMax, int numero_de_items); //gera items iniciais
	
private:
	int capacidadeMax;
	int capacidadePreenchida;

	int valorMax;
	int valorAdicionados;
	
private:
	vector <item> items;
};

