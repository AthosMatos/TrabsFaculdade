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
	Mochila(int numero_de_items, int PesoMax, int valorMax); //gera items iniciais
	Mochila();

private:
	individuo getIndividuoProbabilities(vector<individuo>& tempIndividuos);
	pair<individuo, individuo> Reproduce(pair<individuo, individuo> par);
	vector <pair<int, bool>> gerarCromossomo(pair<individuo, individuo> par, int pontoCorte,bool turn);
	void CheckMutation();
	void mutate(individuo& i);
	void Evolve(int iterations);
	void PexteBulbonica();
	bool CriterioParada(individuo i1, individuo i2);

private:
	int TotalItems; 

	int valorMax;
	int valorIdeal;
	int valorTotalSoma = 0;

	int PesoMax;
	int pesoTotalSoma = 0;

	int mutationPorcentage;
	int maxPopulataion;

private:
	vector<vector<individuo>>geracoes;
	vector<individuo>individuos;
	vector <pair<int, float>> Probabilidades;
	vector<pair<individuo, individuo>> paresIndividuos;
	vector<item> items;
};

