#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <thread>
#include <functional>
#include "structs.h"

using namespace std;

class Mochila
{
public:
	Mochila();

private:
	individuo getIndividuoProbabilities(vector<individuo>& tempIndividuos, vector <pair<int, float>> tempProbabilidades);
	pair<individuo, individuo> Reproduce(pair<individuo, individuo> par);
	vector <pair<int, bool>> gerarCromossomo(pair<individuo, individuo> par, int pontoCorte,bool turn);
	void CheckMutation(vector<individuo>& generations);
	void mutate(individuo& i);
	bool Evolve(int iterations);
	void OrderUpdatedIndividuos();
	void PexteBulbonica();
	bool CriterioParada(individuo indiv);

private:
	void GerarIndivididuo(int type, vector<individuo>& individuosRef, int& valorTotalSomaRef);

private:
	int TotalItems; 

	int valorMax;

	int valorIdeal;
	int valorTotalSoma = 0;

	int PesoMax;
	int pesoTotalSoma = 0;

	int mutationPorcentage;
	int maxPopulataion;
	float margemErr; //porcento
	int iteracoes;

	int geracoes = 0;

private:
	
	vector<individuo> individuos;
	vector<item> items;

	vector <thread> threads;

	individuo individuoWinner;
};

