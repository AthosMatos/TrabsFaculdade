#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <thread>
#include <functional>
#include <algorithm>
#include "structs.h"

using namespace std;

class Mochila
{
public:
	Mochila();
	void GerarItems(string filename);
	void GerarPopInicial();
	void Evoluir();
	void setMargemErro(float margem);
	void setMutacao(int porcentagem);
	void setNumeroMaxPopulacao(int num);
	void setMaxIteracoes(int iteracoes);

private:
	individuo getIndividuoProbabilities(vector<individuo>& tempIndividuos, vector <pair<int, float>> tempProbabilidades);
	pair<individuo, individuo> Reproduce(pair<individuo, individuo> par,int updatedsize);
	void gerarCromossomo(individuo& filhoRef, pair<individuo, individuo> par, int pontoCorte,bool turn);

	void CheckMutation(vector<individuo>& generations);
	void mutate(individuo& i);
	bool Evolve();
	void OrderUpdatedIndividuos();
	void PexteBulbonica();
	bool CriterioParada(individuo indiv);
	int CalcValorTotal(vector<individuo>individuos);

	vector<pair<individuo, individuo>> FazerPares();

private:

	void LogFileData();

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
	vector <thread> threads;

	vector<individuo> individuos;
	vector<item> items;
	individuo individuoWinner;
	individuo OptimalIndividuo;
};


